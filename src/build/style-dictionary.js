/* eslint-disable prettier/prettier */
const path = require('path');
const fs = require('fs');
const _ = require('lodash');
const yaml = require('yaml');

const StyleDictionary = require('style-dictionary');

// Log available pre-defined formats, transforms and transform groups
// console.log(StyleDictionary);

/**
 * registerFormat
 */
StyleDictionary.registerFormat({
  name: 'json/raw',
  formatter: function (dictionary) {
    return JSON.stringify(dictionary.allProperties);
  }
});

StyleDictionary.registerFormat({
  name: 'sass/cellular',
  formatter: _.template(
    fs.readFileSync(path.join(__dirname, '../build/templates', 'sass.js')),
  )
});

StyleDictionary.registerFormat({
  name: 'yaml',
  formatter: _.template(
    fs.readFileSync(path.join(__dirname, '../build/templates', 'yaml.js')),
  ),
});

StyleDictionary.registerFormat({
  name: 'yaml/info',
  formatter: _.template(
    fs.readFileSync(path.join(__dirname, '../build/templates', 'info.js')),
  ),
});

StyleDictionary.registerFormat({
  name: 'yaml/breakpoint',
  formatter: _.template(
    fs.readFileSync(path.join(__dirname, '../build/templates', 'breakpoint.js')),
  ),
});

StyleDictionary.registerFormat({
  name: 'yaml/layout',
  formatter: _.template(
    fs.readFileSync(path.join(__dirname, '../build/templates', 'layout.js')),
  ),
});

/**
 * registerFilter
 */
StyleDictionary.registerFilter({
  name: 'info',
  matcher: (prop) => prop.attributes.category === 'info'
});


/**
 * registerTransformGroup
 */
StyleDictionary.registerTransformGroup({
  name: 'yaml',
  transforms: ['name/cti/snake', 'attribute/cti'],
});

StyleDictionary.registerTransformGroup({
  name: 'sass/cellular',
  transforms: StyleDictionary.transformGroup['scss'].concat([]),
});

/**
 * Build
 */
console.log("path: " + path.join(__dirname, '..', 'style-dictionary/drupal', 'config.json'));

StyleDictionary.extend(
  path.join(__dirname, '..', 'style-dictionary/drupal', 'config.json'),
).buildAllPlatforms();

StyleDictionary.extend(
  path.join(__dirname, '..', 'style-dictionary/tokens', 'config.json'),
).buildAllPlatforms();
