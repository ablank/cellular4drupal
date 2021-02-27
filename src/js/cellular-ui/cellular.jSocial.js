cellular.jSocial = function (opts) {
  var doctitle = document.title,
          page = $("link[rel='canonical']") ? $("link[rel='canonical']").attr('href') : window.location;
  var o = jQuery.extend({
    sharetitle: "", // "Share this page",
    followtitle: "", // "Follow Us",
    buttonclass: "social",
    share: [
      // 'facebook',
      // 'digg',
      // 'google',
      // 'twitter',
      // 'linkedin',
      // 'pinterest',
      // 'reddit',
      // 'stumbleupon',
      //'tumblr'
    ],
    follow: {
      /*
       facebook: {
       title: "Facebook",
       url: "https://facebook.com"
       }
       */
    }
  }, opts),
          fn = {};
  /**
   * Generate markup for buttons.
   *
   * @param object $obj
   */
  fn.style = function ($obj) {
    $obj.once('jSocial', function () {

      if (o.share) {
        var sWrap = $('<div class="jSocial-share" />'),
                sharetitle,
                sharelinks = {
                  facebook: {
                    title: "Facebook",
                    url: "http://facebook.com/sharer/sharer.php?u=" + page
                  },
                  digg: {
                    title: "Digg",
                    url: "http://digg.com/submit?url=" + page + "&title=" + doctitle
                  },
                  google: {
                    title: "Google",
                    url: "https://plus.google.com/share?url=" + page
                  },
                  twitter: {
                    title: "Twitter",
                    url: "https://twitter.com/intent/tweet?url=" + page + "&text=" + doctitle
                  },
                  linkedin: {
                    title: "LinkedIn",
                    url: "http://linkedin.com/shareArticle?url=" + page + "&title=" + doctitle
                  },
                  pinterest: {
                    title: "Pinterest",
                    url: "http://pinterest.com/pin/create/bookmarklet/?url=" + page + "&description=" + doctitle
                  },
                  reddit: {
                    title: "Reddit",
                    url: "http://reddit.com/submit?url=" + page + "&title=" + doctitle
                  },
                  stumbleupon: {
                    title: "StumbleUpon",
                    url: "http://www.stumbleupon.com/submit?url=" + page + "&title=" + doctitle
                  },
                  tumblr: {
                    title: "Tumblr",
                    url: "https://www.tumblr.com/widgets/share/tool?canonicalUrl=" + page + "&title=" + doctitle
                  }
                };


        if (o.sharetitle) {
          sWrap.append('<span class="title">' + o.sharetitle + '</span>');
          sharetitle = o.sharetitle + ' on ';
        }

        o.share.map(function (i) {
          sWrap.buttonize(sharelinks[i].url, sharetitle + sharelinks[i].title, [
            sharelinks[i].title.toLowerCase(),
            o.buttonclass,
            'icon'
          ]);
        });

        $obj.append(sWrap);
      }

      if (Object.keys(o.follow) !== 'undefined') {
        var fWrap = $('<div class="jSocial-follow" />'),
                followtitle = ''
                /*
                 facebook: {
                 title: "Facebook",
                 url: "https://facebook.com"
                 },
                 google: {
                 title: "Google",
                 url: "https://plus.google.com"
                 },
                 twitter: {
                 title: "Twitter",
                 url: "https://twitter.com"
                 },
                 linkedin: {
                 title: "LinkedIn",
                 url: "https://linkedin.com"
                 },
                 pinterest: {
                 title: "Pinterest",
                 url: "https://pinterest.com"
                 },
                 yelp: {
                 title: "Yelp",
                 url: "https://yelp.com"
                 }*/;

        if (o.followtitle) {
          fWrap.append('<span class="title">' + o.followtitle + '</span>');
          followtitle = o.followtitle + ' on ';
        }

        $.each(o.follow, function () {
          fWrap.buttonize(this.url, followtitle + this.title, [
            this.title.replace(/ /g, '').toLowerCase(),
            o.buttonclass,
            'icon'
          ]);
        });

        $obj.append(fWrap);
      }

    });
  };

  /**
   * Init jSocial
   */
  fn.init = function () {
    // Generate markup for links.
    fn.style(jQuery(this));
  };

  return this.each(fn.init);
};
