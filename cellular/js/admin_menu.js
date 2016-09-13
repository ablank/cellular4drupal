(function (a) {
  Drupal.admin = Drupal.admin || {};
  Drupal.admin.behaviors = Drupal.admin.behaviors || {};
  Drupal.admin.hashes = Drupal.admin.hashes || {};/**
   * Core behavior for Administration menu.
   *
   * Test whether there is an administration menu is in the output and execute all
   * registered behaviors.
   */
  Drupal.behaviors.adminMenu = {attach: function (b, c) {
// Initialize settings.
      c.admin_menu = a.extend({suppress: false, margin_top: false, position_fixed: false, tweak_modules: false, tweak_permissions: false, tweak_tabs: false, destination: "", basePath: c.basePath, hash: 0, replacements: {}}, c.admin_menu || {});
// Check whether administration menu should be suppressed.
      if (c.admin_menu.suppress) {
        return
      }
      var d = a("#admin-menu:not(.admin-menu-processed)", b);
// Client-side caching; if administration menu is not in the output, it is
// fetched from the server and cached in the browser.
      if (!d.length && c.admin_menu.hash) {
        Drupal.admin.getCache(c.admin_menu.hash, function (d) {
          if (typeof d == "string" && d.length > 0) {
            a("body", b).append(d)
          }
          var e = a("#admin-menu:not(.admin-menu-processed)", b);
// Apply our behaviors.
          Drupal.admin.attachBehaviors(b, c, e);
// Allow resize event handlers to recalculate sizes/positions.
          a(window).triggerHandler("resize")
        })
      } else {
// Apply our behaviors.
        Drupal.admin.attachBehaviors(b, c, d)
      }
    }};/**
     * Collapse fieldsets on Modules page.
     */
  Drupal.behaviors.adminMenuCollapseModules = {attach: function (b, c) {
      if (c.admin_menu.tweak_modules) {
        a("#system-modules fieldset:not(.collapsed)", b).addClass("collapsed")
      }
    }};/**
     * Collapse modules on Permissions page.
     */
  Drupal.behaviors.adminMenuCollapsePermissions = {attach: function (b, c) {
      if (c.admin_menu.tweak_permissions) {
// Freeze width of first column to prevent jumping.
        a("#permissions th:first", b).css({width: a("#permissions th:first", b).width()});
// Attach click handler.
        $modules = a("#permissions tr:has(td.module)", b).once("admin-menu-tweak-permissions", function () {
          var b = a(this);
          b.bind("click.admin-menu", function () {
// @todo Replace with .nextUntil() in jQuery 1.4.
            b.nextAll().each(function () {
              var b = a(this);
              if (b.is(":has(td.module)")) {
                return false
              }
              b.toggleClass("element-hidden")
            })
          })
        });
// Collapse all but the targeted permission rows set.
        if (window.location.hash.length) {
          $modules = $modules.not(":has(" + window.location.hash + ")")
        }
        $modules.trigger("click.admin-menu")
      }
    }};/**
     * Apply margin to page.
     *
     * Note that directly applying marginTop does not work in IE. To prevent
     * flickering/jumping page content with client-side caching, this is a regular
     * Drupal behavior.
     */
  Drupal.behaviors.adminMenuMarginTop = {attach: function (b, c) {
      if (!c.admin_menu.suppress && c.admin_menu.margin_top) {
        a("body:not(.admin-menu)", b).addClass("admin-menu")
      }
    }};/**
     * Retrieve content from client-side cache.
     *
     * @param hash
     *   The md5 hash of the content to retrieve.
     * @param onSuccess
     *   A callback function invoked when the cache request was successful.
     */
  Drupal.admin.getCache = function (b, c) {
    if (Drupal.admin.hashes.hash !== undefined) {
      return Drupal.admin.hashes.hash
    }
    a.ajax({cache: true, type: "GET", dataType: "text", // Prevent auto-evaluation of response.
      global: false, // Do not trigger global AJAX events.
      url: Drupal.settings.admin_menu.basePath.replace(/admin_menu/, "js/admin_menu/cache/" + b), success: c, complete: function (a, b) {
        Drupal.admin.hashes.hash = b
      }})
  };/**
   * TableHeader callback to determine top viewport offset.
   *
   * @see toolbar.js
   */
  Drupal.admin.height = function () {
    var b = a("#admin-menu");
    var c = b.outerHeight();
// In IE, Shadow filter adds some extra height, so we need to remove it from
// the returned height.
    if (b.css("filter") && b.css("filter").match(/DXImageTransform\.Microsoft\.Shadow/)) {
      c -= b.get(0).filters.item("DXImageTransform.Microsoft.Shadow").strength
    }
    return c
  };/**
   * @defgroup admin_behaviors Administration behaviors.
   * @{
   */
  /**
   * Attach administrative behaviors.
   */
  Drupal.admin.attachBehaviors = function (b, c, d) {
    if (d.length) {
      d.addClass("admin-menu-processed");
      a.each(Drupal.admin.behaviors, function () {
        this(b, c, d)
      })
    }
  };/**
   * Apply 'position: fixed'.
   */
  Drupal.admin.behaviors.positionFixed = function (a, b, c) {
    if (b.admin_menu.position_fixed) {
      c.addClass("admin-menu-position-fixed");
      c.css("position", "fixed")
    }
  };/**
   * Move page tabs into administration menu.
   */
  Drupal.admin.behaviors.pageTabs = function (b, c, d) {
    if (c.admin_menu.tweak_tabs) {
      var e = a(b).find("ul.tabs.primary");
      d.find("#admin-menu-wrapper > ul").eq(1).append(e.find("li").addClass("admin-menu-tab"));
      a(b).find("ul.tabs.secondary").appendTo("#admin-menu-wrapper > ul > li.admin-menu-tab.active").removeClass("secondary");
      e.remove()
    }
  };/**
   * Perform dynamic replacements in cached menu.
   */
  Drupal.admin.behaviors.replacements = function (b, c, d) {
    for (var e in c.admin_menu.replacements) {
      a(e, d).html(c.admin_menu.replacements[e])
    }
  };/**
   * Inject destination query strings for current page.
   */
  Drupal.admin.behaviors.destination = function (b, c, d) {
    if (c.admin_menu.destination) {
      a("a.admin-menu-destination", d).each(function () {
        this.search += (!this.search.length ? "?" : "&") + Drupal.settings.admin_menu.destination
      })
    }
  };/**
   * Apply JavaScript-based hovering behaviors.
   *
   * @todo This has to run last.  If another script registers additional behaviors
   *   it will not run last.
   */
  Drupal.admin.behaviors.hover = function (b, c, d) {
// Delayed mouseout.
    a("li.expandable", d).hover(function () {
// Stop the timer.
      clearTimeout(this.sfTimer);
// Display child lists.
      a("> ul", this).addClass("active")
    }, function () {
// Start the timer.
      var b = a("> ul", this);
      this.sfTimer = setTimeout(function () {
        b.removeClass("active")
      }, 400)
    })
  };/**
   * Apply the search bar functionality.
   */
  Drupal.admin.behaviors.search = function (b, c, d) {
// @todo Add a HTML ID.
    var e = a("input.admin-menu-search", d);
// Initialize the current search needle.
    var f = e.val();
// Cache of all links that can be matched in the menu.
    var g;
// Minimum search needle length.
    var h = 2;
// Append the results container.
    var i = a("<div />").insertAfter(e);/**
     * Executes the search upon user input.
     */
    function j() {
      var b, c, e = a(this).val();
// Only proceed if the search needle has changed.
      if (e !== f) {
        f = e;
// Initialize the cache of menu links upon first search.
        if (!g && f.length >= h) {
// @todo Limit to links in dropdown menus; i.e., skip menu additions.
          g = k(d.find("li:not(.admin-menu-action, .admin-menu-action li) > a"))
        }
// Empty results container when deleting search text.
        if (f.length < h) {
          i.empty()
        }
// Only search if the needle is long enough.
        if (f.length >= h && g) {
          b = l(f, g);
// Build the list in a detached DOM node.
          c = m(b);
// Display results.
          i.empty().append(c)
        }
      }
    }/**
     * Builds the search index.
     */
    function k(a) {
      return a.map(function () {
        var a = this.textContent || this.innerText;
// Skip menu entries that do not contain any text (e.g., the icon).
        if (typeof a === "undefined") {
          return
        }
        return{text: a, textMatch: a.toLowerCase(), element: this}
      })
    }/**
     * Searches the index for a given needle and returns matching entries.
     */
    function l(b, c) {
      var d = b.toLowerCase();
// Select matching links from the cache.
      return a.grep(c, function (a) {
        return a.textMatch.indexOf(d) !== -1
      })
    }/**
     * Builds the search result list in a detached DOM node.
     */
    function m(b) {
      var c = a('<ul class="dropdown admin-menu-search-results" />');
      a.each(b, function () {
        var b = this.text;
        var d = a(this.element);
// Check whether there is a top-level category that can be prepended.
        var e = d.closest("#admin-menu-wrapper > ul > li");
        var f = e.find("> a").text();
        if (e.length && f) {
          b = f + ": " + b
        }
        var g = a('<li><a href="' + d.attr("href") + '">' + b + "</a></li>");
        g.data("original-link", a(this.element).parent());
        c.append(g)
      });
      return c
    }/**
     * Highlights selected result.
     */
    function n(b) {
      var c = a(this);
      var d = b.type === "mouseenter" || b.type === "focusin";
      c.trigger(d ? "showPath" : "hidePath", [this])
    }/**
     * Closes the search results and clears the search input.
     */
    function o(b, c) {
      var d = a(this).data("original-link");
      d.trigger("mouseleave");
      e.val("").trigger("keyup")
    }/**
     * Shows the link in the menu that corresponds to a search result.
     */
    function p(b, c) {
      if (c) {
        var d = a(c).data("original-link");
        var e = b.type === "showPath";
// Toggle an additional CSS class to visually highlight the matching link.
// @todo Consider using same visual appearance as regular hover.
        d.toggleClass("highlight", e);
        d.trigger(e ? "mouseenter" : "mouseleave")
      }
    }
// Attach showPath/hidePath handler to search result entries.
    i.delegate("li", "mouseenter mouseleave focus blur", n);
// Hide the result list after a link has been clicked, useful for overlay.
    i.delegate("li", "click", o);
// Attach hover/active highlight behavior to search result entries.
    d.delegate(".admin-menu-search-results li", "showPath hidePath", p);
// Attach the search input event handler.
    e.bind("keyup search", j)
  }
})(jQuery);