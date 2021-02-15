#Under development
***In its current state, this theme should only be used for referencing odd bits of code. I'll change this notice after a general theme skeleton is complete and split a dev branch for continued development, but until then Cellular 9.x is experimental.***

##Cellular base theme 
Install with 
composer `composer require`or 
npm `npm install` 
After the project is installed, `npm build` to regenerate the theme (***all changes will be overwritten in `/dist`***, always edit the `/src` files!*).


##npm build tasks
- Create style-dictionary formats & transforms
  - lodash templates to compile drupal theme (themeName.theme, info, breakpoints, etc.).
  - compile/optimize sass
  - compile/optimize js
- optimize & convert images

##Theme functions
  - Make it play nice with layout builder
  - Conditional ie stylesheet
  - Inject critical css in <head>
  - Pass theme settings as json to script.js

##Templates
  - Replace bootstrap classes w/ cellular
  - Update theme variables

##Sass
- Reconfigure to use without Compass (*doesn't play nice w/ dart-sass*)
  - Copy crucial mixins from compass

##JS
- script.js, plugins.js need to be configured to receive Drupal settings
- cellular-ui plugin development

