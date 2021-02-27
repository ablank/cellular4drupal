cellular.jAV = function (opts) {
  var o = jQuery.extend({
    cclass: "jAV",
    type: 'video', // audio || video || iframe
    source: [
      // Array of source files to use.
      // 1st source is preferred, fallback to other sources
      /*
       'https://youtu.be/Jy1O9PqvMD8', //https://www.youtube.com/watch?v=Jy1O9PqvMD8
       'assets/video/demo.mp4',
       'assets/video/demo.ogg'
       */
    ],
    opt: {
      showControls: true,
      autoHideControls: 200, // Time in ms; Set to false || null to unset.
      volume: 0.75
    },
    attributes: {
      width: '480',
      height: '270',
      poster: '../../assets/images/png/logo.png', // Image src
      preload: 'none',
      autoPlay: false
    },
    controls: {
      prev: {
        text: 'Previous',
        display: true
      },
      play: {
        text: 'Play',
        display: true
      },
      pause: {
        text: 'Pause',
        display: false
      },
      next: {
        text: 'Next',
        display: true
      },
      timeElapsed: {
        text: 'Time Elapsed',
        display: true
      },
      timeScrubber: {
        text: 'Seek',
        display: true
      },
      timeTotal: {
        text: 'Time Total',
        display: true
      },
      volume: {
        text: 'Volume',
        display: true,
        orient: 'horizontal' // || 'vertical'
      },
      fullscreen: {
        text: 'Fullscreen',
        display: true
      },
      loop: {
        text: 'Loop',
        display: true
      }
    },
    features: {
      ads: [],
      tracks: [],
      subtitles: [
        {
          lang: 'en',
          label: 'English',
          src: 'en.vtt'
        }
      ]
    },
    events: {
      keyboard: true,
      mouse: true,
      touch: true
    },
    playlist: ''
  }, opts),
          fn = {},
          iframe = false,
          uuid = new Date().getTime();

  /**
   * Play media.
   *
   * @param {} $obj
   * @param audio/video media
   * @param string provider
   */
  fn.play = function ($obj, media, provider) {
    switch (provider) {
      case 'local':
        media.play();
        break;

      case 'youtube':

        break;

      case 'vimeo':

        break;
    }
  };

  /**
   * Update player state.
   *
   * @param {} $obj
   */
  fn.update = function ($obj, state) {

  };


  /**
   * Update player state.
   *
   * @param {} $obj
   */
  fn.updateVolume = function ($obj, state) {
    // state.volume =
  };

  /**
   * Return controls for media object.
   *
   * @param {} $obj
   */
  fn.getControls = function ($obj) {
    var block = $obj.find('.' + o.cclass + '-controls'),
            controls = {
              overlay: $obj.find('.' + o.cclass + '-overlay'),
              seek: block.find('.seek-handle'),
              vol: $obj.find('.volume'),
              volHandle: block.find('.volume-handle'),
              mute: block.find('.mute'),
              play: block.find('.play'),
              next: block.find('.next'),
              prev: block.find('.prev'),
              fullscreen: block.find('.fullscreen'),
              loop: block.find('.loop')
            };

    return controls;
  };

  /**
   * Youtube API integration
   *
   * @param {} $obj
   */
  fn.youtube = function ($obj, link) {
    var youtube,
            controls = fn.getControls($obj),
            vid;
    // match(\/youtu.be\/(.*))

    $obj.attr('id', o.cclass + '-' + uuid++);
    // Load dependencies
    jQuery.getScript("https://www.youtube.com/iframe_api");

    // Get video id from given URL
    if (link.indexOf('https://www.youtube.com/embed/')) {
      // Embed link: https://www.youtube.com/embed/Jy1O9PqvMD8

    } else if (link.indexOf('https://youtu.be/')) {
      // Share link: https://youtu.be/Jy1O9PqvMD8

    } else if (link.indexOf('https://www.youtube.com/watch?v=')) {
      // Browser URL: https://www.youtube.com/watch?v=Jy1O9PqvMD8

    }
    // Generate iframe from given URL
    //mid =
    //
    //
    //

    function onYouTubeIframeAPIReady() {
      var vid = link.match(/\/watch\?v=(.*)/),
              uPlaylist = o.playlist,
              youtube = new YT.Player($obj.find(o.type).attr('id'), {
                height: o.attributes.height,
                width: o.attributes.width,
                videoId: vid,
                events: {
                  onReady: onPlayerReady,
                  onStateChange: onPlayerStateChange
                }
              });
    }
    //console.log();
    jQuery(controls.play, controls.overlay).on('click', function (e) {
      controls.play.toggleClass('pause');
      $t = jQuery(this);
      if (media.paused === true) {
        media.play();
        $t.attr({
          'aria-label': o.controls.pause,
          'title': o.controls.pause
        })
                .text(o.controls.pause);
      } else {
        media.pause();
        $t.attr({
          'aria-label': o.controls.play,
          'title': o.controls.play
        })
                .text(o.controls.pause);
      }
    });
  };

  /**
   * Vimeo API integration
   *
   * @param {} $obj
   */
  fn.vimeo = function ($obj, link) {
    // Load dependencies
    //jQuery.getScript("https://f.vimeocdn.com/js/froogaloop2.min.js");


    //link: https://vimeo.com/167414855

    // embed: <iframe src="https://player.vimeo.com/video/167414855" width="640" height="360" frameborder="0" webkitallowfullscreen mozallowfullscreen allowfullscreen></iframe>
    //<p><a href="https://vimeo.com/167414855">Chaud Lapin - Animated Short Movie</a> from <a href="https://vimeo.com/chaudlapin">Chaud lapin</a> on <a href="https://vimeo.com">Vimeo</a>.</p>
  };

  fn.addSource = function ($obj, arr) {
    arr.map(function (el) {
      $obj.append('<source src="' + el + '">');
    });
  };

  fn.style = function ($obj) {
    var media = jQuery('<' + o.type + '/>', {
      id: o.cclass + '-' + uuid++
    }),
            overlay = jQuery('<div class="' + o.cclass + '-overlay" />'),
            controls = '',
            source = $obj.attr('data-src') || o.source;

    // Generate list of media sources.
    if (typeof (source !== 'undefined')) {

      if (typeof (source) === 'string') {
        source = source.split(',');
      }

      source.map(function (el) {
        if (el.indexOf('https://www.youtube.com') !== -1 || el.indexOf('https://youtu.be') !== -1) {
          media = $obj;
          fn.youtube($obj, el);
        } else if (el.indexOf('https://vimeo.com') !== -1) {
          fn.vimeo($obj, el);
        } else {
          media.append('<source src="' + el + '">');
        }
      });
    }

    // Generate media controls.
    if (o.opt.showControls === true) {
      controls = jQuery('<div class="' + o.cclass + '-controls" />');

      for (var control in o.controls) {
        if (o.controls.hasOwnProperty(control)) {
          var btn = jQuery('<a>' + o.controls[control].text + '</a>')
                  .classify([control])
                  .attr({
                    "href": '#' + o.cclass + '-' + control,
                    "aria-label": o.controls[control].text
                  });

          controls.append(btn);
        }
      }

      if (typeof (o.controls.timeScrubber) !== 'undefined') {
        $obj.find('.timeScrubber').wrap('<div class="slider" />')
                .append('<div class="seek-handle" />');

        //console.log($obj.find('.' + o.cclass + '-timeScrubber'));
      }


      if (typeof (o.controls.volume) !== 'undefined') {
        $obj.find('.volume')
                .append('<div class="volume-handle" />');
      }

    }

    $obj.append(overlay, media, controls);
    //console.log($obj.attr('id'));
    for (var attribute in o.attributes) {
      if (o.attributes[attribute] !== false) {
        media.attr(attribute, o.attributes[attribute]);
      }
    }
  };

  /**
   *
   *
   * @param object $obj
   */
  fn.events = function ($obj, state) {
    var media = document.getElementById($obj.find(o.type).attr('id')),
            controls = fn.getControls($obj),
            $t;

    // console.log($obj.find(o.type));
    $obj.on('click', function () {
      jQuery(this).activate();
    });

    $obj.find('a').on('click', function (e) {
      // Apply action to all controls
      e.preventDefault();
    });

    jQuery(controls.play, controls.overlay).on('click', function (e) {
      controls.play.toggleClass('pause');
      $t = jQuery(this);
      if (media.paused === true) {
        media.play();
        $t.attr({
          'aria-label': o.controls.pause.text,
          'title': o.controls.pause.text
        })
                .text(o.controls.pause.text);
      } else {
        media.pause();
        $t.attr({
          'aria-label': o.controls.play.text,
          'title': o.controls.play.text
        })
                .text(o.controls.play.text);
      }
    });

    controls.prev.on('click', function (e) {

    });


    controls.next.on('click', function (e) {

    });

    controls.seek.on('click', function (e) {

    });

    controls.fullscreen.on('click', function (e) {

    });

    controls.loop.on('click', function (e) {

    });

    controls.mute.on('click', function (e) {

    });

    if (o.controls.volume.orient === 'vertical') {
      controls.vol.on('mouseenter', function () {
        jQuery(this).activate();
      });

      controls.vol.on('mouseleave', function () {
        jQuery(this).deactivate();
      });
    }

  };

  /**
   * Init jTabs
   */
  fn.init = function () {
    var $obj = jQuery(this),
            state = {
              active: false,
              fullscreen: false,
              buffering: false,
              playing: o.attributes.autoplay = true ? true : false,
              paused: o.attributes.autoplay = true ? false : true,
              muted: false,
              volume: o.opt.initVolume,
              timer: 0
            };

    $obj.once(o.cclass, fn.style($obj));
    // Set default content
    fn.events($obj, state);
  };

  return this.each(fn.init);
};
