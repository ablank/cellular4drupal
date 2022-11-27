(function($) {
    Drupal.admin = Drupal.admin || {};
    Drupal.admin.behaviors = Drupal.admin.behaviors || {};
    Drupal.admin.hashes = Drupal.admin.hashes || {};
    Drupal.behaviors.adminMenu = {
        attach: function(context, settings) {
            settings.admin_menu = $.extend({
                suppress: false,
                margin_top: false,
                position_fixed: false,
                tweak_modules: false,
                tweak_permissions: false,
                tweak_tabs: false,
                destination: "",
                basePath: settings.basePath,
                hash: 0,
                replacements: {}
            }, settings.admin_menu || {});
            if (settings.admin_menu.suppress) {
                return;
            }
            var $adminMenu = $("#admin-menu:not(.admin-menu-processed)", context);
            if (!$adminMenu.length && settings.admin_menu.hash) {
                Drupal.admin.getCache(settings.admin_menu.hash, function(response) {
                    if (typeof response == "string" && response.length > 0) {
                        $("body", context).append(response);
                    }
                    var $adminMenu = $("#admin-menu:not(.admin-menu-processed)", context);
                    Drupal.admin.attachBehaviors(context, settings, $adminMenu);
                    $(window).triggerHandler("resize");
                });
            } else {
                Drupal.admin.attachBehaviors(context, settings, $adminMenu);
            }
        }
    };
    Drupal.behaviors.adminMenuCollapseModules = {
        attach: function(context, settings) {
            if (settings.admin_menu.tweak_modules) {
                $("#system-modules fieldset:not(.collapsed)", context).addClass("collapsed");
            }
        }
    };
    Drupal.behaviors.adminMenuCollapsePermissions = {
        attach: function(context, settings) {
            if (settings.admin_menu.tweak_permissions) {
                $("#permissions th:first", context).css({
                    width: $("#permissions th:first", context).width()
                });
                $modules = $("#permissions tr:has(td.module)", context).once("admin-menu-tweak-permissions", function() {
                    var $module = $(this);
                    $module.bind("click.admin-menu", function() {
                        $module.nextAll().each(function() {
                            var $row = $(this);
                            if ($row.is(":has(td.module)")) {
                                return false;
                            }
                            $row.toggleClass("element-hidden");
                        });
                    });
                });
                if (window.location.hash.length) {
                    $modules = $modules.not(":has(" + window.location.hash + ")");
                }
                $modules.trigger("click.admin-menu");
            }
        }
    };
    Drupal.behaviors.adminMenuMarginTop = {
        attach: function(context, settings) {
            if (!settings.admin_menu.suppress && settings.admin_menu.margin_top) {
                $("body:not(.admin-menu)", context).addClass("admin-menu");
            }
        }
    };
    Drupal.admin.getCache = function(hash, onSuccess) {
        if (Drupal.admin.hashes.hash !== undefined) {
            return Drupal.admin.hashes.hash;
        }
        $.ajax({
            cache: true,
            type: "GET",
            dataType: "text",
            global: false,
            url: Drupal.settings.admin_menu.basePath.replace(/admin_menu/, "js/admin_menu/cache/" + hash),
            success: onSuccess,
            complete: function(XMLHttpRequest, status) {
                Drupal.admin.hashes.hash = status;
            }
        });
    };
    Drupal.admin.height = function() {
        var $adminMenu = $("#admin-menu");
        var height = $adminMenu.outerHeight();
        if ($adminMenu.css("filter") && $adminMenu.css("filter").match(/DXImageTransform\.Microsoft\.Shadow/)) {
            height -= $adminMenu.get(0).filters.item("DXImageTransform.Microsoft.Shadow").strength;
        }
        return height;
    };
    Drupal.admin.attachBehaviors = function(context, settings, $adminMenu) {
        if ($adminMenu.length) {
            $adminMenu.addClass("admin-menu-processed");
            $.each(Drupal.admin.behaviors, function() {
                this(context, settings, $adminMenu);
            });
        }
    };
    Drupal.admin.behaviors.positionFixed = function(context, settings, $adminMenu) {
        if (settings.admin_menu.position_fixed) {
            $adminMenu.addClass("admin-menu-position-fixed");
            $adminMenu.css("position", "fixed");
        }
    };
    Drupal.admin.behaviors.pageTabs = function(context, settings, $adminMenu) {
        if (settings.admin_menu.tweak_tabs) {
            var $tabs = $(context).find("ul.tabs.primary");
            $adminMenu.find("#admin-menu-wrapper > ul").eq(1).append($tabs.find("li").addClass("admin-menu-tab"));
            $(context).find("ul.tabs.secondary").appendTo("#admin-menu-wrapper > ul > li.admin-menu-tab.active").removeClass("secondary");
            $tabs.remove();
        }
    };
    Drupal.admin.behaviors.replacements = function(context, settings, $adminMenu) {
        for (var item in settings.admin_menu.replacements) {
            $(item, $adminMenu).html(settings.admin_menu.replacements[item]);
        }
    };
    Drupal.admin.behaviors.destination = function(context, settings, $adminMenu) {
        if (settings.admin_menu.destination) {
            $("a.admin-menu-destination", $adminMenu).each(function() {
                this.search += (!this.search.length ? "?" : "&") + Drupal.settings.admin_menu.destination;
            });
        }
    };
    Drupal.admin.behaviors.hover = function(context, settings, $adminMenu) {
        $("li.expandable", $adminMenu).hover(function() {
            clearTimeout(this.sfTimer);
            $("> ul", this).addClass("active");
        }, function() {
            var uls = $("> ul", this);
            this.sfTimer = setTimeout(function() {
                uls.removeClass("active");
            }, 400);
        });
    };
    Drupal.admin.behaviors.search = function(context, settings, $adminMenu) {
        var $input = $("input.admin-menu-search", $adminMenu);
        var needle = $input.val();
        var links;
        var needleMinLength = 2;
        var $results = $("<div />").insertAfter($input);
        function keyupHandler() {
            var matches, $html, value = $(this).val();
            if (value !== needle) {
                needle = value;
                if (!links && needle.length >= needleMinLength) {
                    links = buildSearchIndex($adminMenu.find("li:not(.admin-menu-action, .admin-menu-action li) > a"));
                }
                if (needle.length < needleMinLength) {
                    $results.empty();
                }
                if (needle.length >= needleMinLength && links) {
                    matches = findMatches(needle, links);
                    $html = buildResultsList(matches);
                    $results.empty().append($html);
                }
            }
        }
        function buildSearchIndex($links) {
            return $links.map(function() {
                var text = this.textContent || this.innerText;
                if (typeof text === "undefined") {
                    return;
                }
                return {
                    text: text,
                    textMatch: text.toLowerCase(),
                    element: this
                };
            });
        }
        function findMatches(needle, links) {
            var needleMatch = needle.toLowerCase();
            return $.grep(links, function(link) {
                return link.textMatch.indexOf(needleMatch) !== -1;
            });
        }
        function buildResultsList(matches) {
            var $html = $('<ul class="dropdown admin-menu-search-results" />');
            $.each(matches, function() {
                var result = this.text;
                var $element = $(this.element);
                var $category = $element.closest("#admin-menu-wrapper > ul > li");
                var categoryText = $category.find("> a").text();
                if ($category.length && categoryText) {
                    result = categoryText + ": " + result;
                }
                var $result = $('<li><a href="' + $element.attr("href") + '">' + result + "</a></li>");
                $result.data("original-link", $(this.element).parent());
                $html.append($result);
            });
            return $html;
        }
        function resultsHandler(e) {
            var $this = $(this);
            var show = e.type === "mouseenter" || e.type === "focusin";
            $this.trigger(show ? "showPath" : "hidePath", [ this ]);
        }
        function resultsClickHandler(e, link) {
            var $original = $(this).data("original-link");
            $original.trigger("mouseleave");
            $input.val("").trigger("keyup");
        }
        function highlightPathHandler(e, link) {
            if (link) {
                var $original = $(link).data("original-link");
                var show = e.type === "showPath";
                $original.toggleClass("highlight", show);
                $original.trigger(show ? "mouseenter" : "mouseleave");
            }
        }
        $results.delegate("li", "mouseenter mouseleave focus blur", resultsHandler);
        $results.delegate("li", "click", resultsClickHandler);
        $adminMenu.delegate(".admin-menu-search-results li", "showPath hidePath", highlightPathHandler);
        $input.bind("keyup search", keyupHandler);
    };
})(jQuery);