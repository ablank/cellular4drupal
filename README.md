# Cellular :: Base Theme for Drupal 7

The Cellular base theme for Drupal 7 simplifies Drupal front-end development
 using the theme layer to add functionality that doesn't require heavy
 database interaction.

## Features

* jQuery & jQuery-UI update (that doesn't break Views & simplifies UI theming)
* Mobile 1st, fluid/jello styling with SASS styling broken into logical partials
* Full menu tree display, dynamic conditional CSS, & lots of other nifty
settings
* Easy favicons & apple-touch-icons (.ai files included)
* Integration with several javascript libraries (D3.js, GreenSocks Animation,
 Modernizr, etc.)
* Integrated social media follow & share links with custom icons

## Usage

##### Advanced theme features require the cellular library:
http://github.com/ablank/cellular.library

Download and extract the contents to `$base_path/sites/all/libraries/cellular`
```
cd sites/all/libraries
git clone --branch master https://github.com/ablank/cellular.library.git cellular
```

1. Navigate to `/admin/appearance` and enable the Cellular theme
2. Enable & set `subcellular` as the default theme
3. Modify the theme Settings to suit your needs.
  * __Personalize__ : Set copyright & favicons
  * __Style__ : Add/Edit media query, remove Drupal CSS,
  configure breadcrumb & menu display settings, set content classes
  * __Javascript__ : Select the javascript libraries to include.
  * __Social Media__ : Select and configure the social media links to you
  would like to include.

Cellular uses theme functions rather than theme settings (.INFO files) to
add/update/delete stylesheets and javascript, providing a simple code-based
solution to add multiple elements to your theme with a high degree of control
 over the loading order.

## Styling

* Load additional css in the order you need with `cellular_add_css()` - Add
your stylesheets to the array `$add_css` in `/inc/css_alter.inc`

* Get rid of unnecessary stylesheets with `cellular_remove_css()` - Add the
module => stylesheet to the array `$exclude` in `/inc/css_alter.inc`

* SASS is preconfigured & ready to watch (`cd /path/to/theme`, `compass watch`)

## Scripting

* `/js/script.js` is ready for you to add your custom scripting.

* Load scripts in the order you need with `cellular_add_js()` - Add your
scripts to the array `$add_js` in `/inc/js_alter.inc`
  * ***nice*** Link to a CDN script by including the `['cdn']` key. If the
  `['object']` & `['file']` keys are also present, a local fallback link will
   be automatically generated after the cdn link.

### Included/Optional Javascript Libraries

* __jQuery Update__
Update jQuery to the version of your choice (1.11.1, 1.10.2, 1.9.1, 1.8.3,
1.7.2, 1.6.4, 1.5.2, 1.4.4) without breaking Views. Loads from the
Cloudflare, Google, or MS CDNs with a local fallback.
  * The jquery.migrate module is optionally loaded for versions >= 1.9.x
  for backward compatibility.

* __jQuery Core Plugins Update__
Update Drupal's core jQuery plugins to the latest stable version.
  * BBQ v1.3
  * Cookie v1.4.1
  * Form v3.48
  * Once v1.2.6

* __jQuery UI Update__
Update jQueryUI to the version of your choice (1.10.4, 1.9.2, 1.8.24).
  * Select the UI theme of your choice, or use the CUSTOM flat UI style
  (`/sass/jquery-ui`) for a lightweight theme that matches your site.

* __Cellular UI__
UI elements (accordions, tabs, mobile menu, etc.) built for easy integration
with Views.

* __Modernizr__
Test browser feature support and load resources based on capabilities.

* __D3js__
D3.js is a JavaScript library for manipulating documents based on data. D3
helps you bring data to life using HTML, SVG and CSS.

* __GSAP__ (GreenSock Animation Platform)
GSAP is a suite of tools for scripted, high-performance HTML5 animations that
 work in all major browsers.

* __THREEjs__
A JavaScript 3D Library which makes WebGL simpler.

* __Prism Syntax Hilighter__
Code syntax hilighter.

* __Backstretch__
Add a dynamically-resized, slideshow-capable background image to any page or element.

* __Flowtype__
Dynamically resize text: font-size based on element width.

* __Freetile__
Enables the organization of webpage content in an efficient, dynamic and responsive layout, similar to Masonry.

* __Parallax__
A dirt simple parallax scrolling effect.

* __Smoove__
Smoove makes it easy to implement awesome CSS3 transition effects,
making your content smoothly glide into the page as your scroll down the page.

* __SnapSVG__
The Snap.svg JavaScript library makes working with your SVG assets as easy as jQuery makes working with the DOM.
