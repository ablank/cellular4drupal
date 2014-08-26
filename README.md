# Cellular :: Base Theme for Drupal 7

The Cellular base theme for Drupal 7 simplifies front-end development of Drupal websites by using the theme layer to control functionality that doesn't require interaction with the database.

The goal of this project is simple- to simplify workflow as much as possible.

#### Get the Cellular library for Drupal

To get the most out of this theme, you will need to add the Cellular libraryto use the more advanced features like updating jQuery, icons, conditionally loading stylesheets, and all the other great things these plugins enable.



```
cd sites/all/libraries
mkdir cellular
git clone --branch master https://github.com/ablank/cellular.library.git cellular
```


## Features


* Mobile 1st, fluid/jello styling with SASS styling broken into logical partials
* Full menu tree display, dynamic conditional CSS, & lots of other nifty settings
* Easy favicons & apple-touch-icons (.ai files included)
* jQuery & jQuery-UI update (that doesn't break Views & simplifies UI theming)
* Integration with several javascript libraries (D3.js, GreenSocks Animation, Modernizr, etc.)
* Integrated social media follow & share links with custom icons

## Usage
1. Navigate to `/admin/appearance` and enable the Cellular theme
2. Enable & set `subcellular` as the default theme
3. Modify the theme Settings to suit your needs.
  * __Personalize__ : Set copyright & favicons
  * __Style__ : Add/Edit media query, remove Drupal CSS, configure breadcrumb & menu display settings, set content classes
  * __Javascript__ : Select the javascript libraries to include.
  * __Social Media__ : Select and configure the social media links to you would like to include.
  
  Rather than adding scripts and stylesheets using theme settings/.INFO files as most themes do, theme functions are provided to simplify the process of adding/updating/deleting stylesheets and javascript in the theme using a code-based solution that provides highly granular control. 
 such as by providing a better way to add multiple meta elements, css, and javascript files in your theme by adding it to a simple array.
 

## Styling
* Get rid of unnecessary stylesheets with `cellular_remove_css()` - Add the module => stylesheet to the array `$exclude` in `/inc/css_alter.inc` 

* Load additional css in the order you need with `cellular_add_css()` - Add your stylesheets to the array `$add_css` in `/inc/css_alter.inc`

* SASS is preconfigured & ready to watch (`cd /path/to/theme`, `compass watch`)

## Scripting
* `/js/script.js` is ready for you to add your custom scripting.

* Load scripts in the order you need with `cellular_add_js()` - Add your scripts to the array `$add_js` in `/inc/js_alter.inc`
  * ***nice*** if you include the `['cdn']` key, a fallback link is generated directly after the cdn link by querying `['object']` to conditionally load `['file']`

### Included/Optional Javascript Libraries
*Requires the javascript libraries at http://github.com/ablank/cellular.jslib

`git clone --branch master https://github.com/ablank/cellular.jslib.git`


* __jQuery Update__
Update jQuery to the version of your choice (1.8.2, 1.7.1, 1.5.1, 1.4.4) without breaking Views from the Google or MS CDN with a local fallback 

* __jQuery UI Update__
Update jQueryUI to the version of your choice (1.10.1, 1.9.2, 1.8.11, 1.8.7)

Select the UI theme of your choice, or use the CUSTOM flat UI style for a lightweight theme that matches your site.

* __Cellular UI__
UI elements (accordions, tabs, mobile menu, etc.) built for easy integration with Views.

* __Modernizr__
Test browser feature support and load resources based on capabilities.

* __D3js__
D3.js is a JavaScript library for manipulating documents based on data. D3 helps you bring data to life using HTML, SVG and CSS.

* __GSAP__ (GreenSock Animation Platform)
GSAP is a suite of tools for scripted, high-performance HTML5 animations that work in all major browsers.

* __THREEjs__
A JavaScript 3D Library which makes WebGL simpler.

* __Masonry__
Cascading grid layouts

* __Prism Syntax Hilighter__
Code syntax hilighter.

## Known Issues
* __(Warning)__ Drupal doesn't like it when you take control of the logo & favicon 
 
* __[Solution]__ tbd... 

* __(Warning)__ Drupal doesn't like `/node_modules/` used by grunt. 

* __[Solution]__ Don't push `/node_modules/` to production. 


## Planned Updates
* jQueryUI from CDN

* Admin theme

* Cellular Foundation- Cellular theme functions with ZURB Foundation frontend.

* Optimize icon build process- fork grunticon, output DirectoryColorfy to svg files (!base-encoded in stylesheet), compile PNG sprite (svg2png, spritesmith), build stylesheet from handlebar template w/ link to files.

* Requirejs?