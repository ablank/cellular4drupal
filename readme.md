# Under development
***In its current state, this theme should only be used for referencing odd bits of code. I'll change this notice after a general theme skeleton is complete and split a dev branch for continued development, but until then Cellular 9.x is experimental and won't compile.***

## Cellular base theme 
Install with 
composer `composer require`or 
npm `npm install` 
After the project is installed, `npm build` to regenerate the theme (***all changes will be overwritten to theme.info.yml, theme.breakpoints.yml, and `//dist`***, always edit the `/src` files!*).


## npm build tasks
- Create style-dictionary formats & transforms
  - Integrate style-dictionary with Figma
  - lodash templates to compile drupal theme (themeName.theme, info, breakpoints, etc.).
  - compile/optimize sass
  - compile/optimize js
- optimize & convert images
- Yeoman generator

## Theme functions
  - Play nice with layout builder
  - Inject critical css in <head> (frontpage & others)
  - Conditional ie stylesheet
  - Pass theme settings as json to plugins.js & script.js

## Templates
  - Templates for most common elements (*block, article, node, etc.*) are provided in the `/templates` directory.

## Sass
- Style-dictionary is the ultimate source of truth for variables.
- Modularity is crucial for managing large code bases... 
  -  Let the styles flow: They're easier to manage that way.
  -  Collecting styles as ordered partials allows styles to cascade properly... Each subset of styles is collected in `__index.sass`


## JS
- script.js, plugins.js need to be configured to receive Drupal settings
- cellular-ui plugin development

# Recommended Modules

- [Admin Toolbar]('https://www.drupal.org/project/admin_toolbar')
- [Content Lock]('https://www.drupal.org/project/')
- [Diff]('https://www.drupal.org/project/diff')
- [Field Group]('https://www.drupal.org/project/field_group')
- [Image Effects](https://www.drupal.org/project/image_effects)
- [Mail System]('https://www.drupal.org/project/mailsystem')
- [Swift Mailer]('https://www.drupal.org/project/swiftmailer')
- [Metatag]('https://www.drupal.org/project/metatag')
- [Pathauto]('https://www.drupal.org/project/pathauto')
- [Search API]('https://www.drupal.org/project/search_api')
- [Simple XML Sitemap]('https://www.drupal.org/project/simple_sitemap')
- [Security Kit]('https://www.drupal.org/project/seckit')
- [Token]('https://www.drupal.org/project/token')
- [Webform]('https://www.drupal.org/project/webform')
- [Search404]('https://www.drupal.org/project/search404')