/* eslint-disable prettier/prettier */
const path = require('path'),
  fs = require('fs'),
  _ = require('lodash'),
  yaml = require('yaml');

const StyleDictionary = require('style-dictionary');

// Log available pre-defined formats, transforms and transform groups
//console.log(StyleDictionary);

function isColor(prop) {
  return prop.attributes.category === 'color';
}

function LightenDarkenColor(col, amt) {
  var usePound = false;
  if (col[0] == '#') {
    col = col.slice(1);
    usePound = true;
  }
  var num = parseInt(col, 16);
  var r = (num >> 16) + amt;
  if (r > 255) r = 255;
  else if (r < 0) r = 0;
  var b = ((num >> 8) & 0x00ff) + amt;
  if (b > 255) b = 255;
  else if (b < 0) b = 0;
  var g = (num & 0x0000ff) + amt;
  if (g > 255) g = 255;
  else if (g < 0) g = 0;

  return (usePound ? '#' : '') + (g | (b << 8) | (r << 16)).toString(16);
}

/**
 * registerFormat
 */
StyleDictionary.registerFormat({
  name: 'json/raw',
  formatter: function (dictionary) {
    return JSON.stringify(dictionary.allProperties);
  },
});

StyleDictionary.registerFormat({
  name: 'sass/cellular',
  formatter: _.template(
    fs.readFileSync(__dirname + '/templates/sass.template'),
  ),
  /*function (dictionary, config) {
   Set up an empty object to hold the final shape to pass
   to the custom template.

   After the allProperties.map(), props will look like this: {
   'component-button': {
   padding: '16px',
   'font-size': '16px',
   'text-align': 'center',
   primary: {
   'background-color': '#e63c19',
   color: '#ffffff'
   },
   secondary: {
   'background-color': '#fad8d1',
   color: '#0000ff'
   }
   }
   }
   // allProperties is an array containing all the matched
   // tokens based on the filter.
   const {
   allProperties
   } = dictionary

   const props = {}

   // go through properties and structure final props object
   allProperties.map(prop => {

   //  Extract the attributes object created by the 'attribute/cti'
   //  transform and the transformed token value.
   const {
   attributes,
   value
   } = prop

   // extract attributes to build custom class and style rules
   const {
   category,
   type,
   item,
   subitem
   } = attributes

   // build main classname for .scss file
   const classname = `${category}-${type}`
   //  Add to the props object if it doesn't already exist.
   //  We run the check to see if the classname exists already as an
   //  object property because in our case, `classname` will be the
   //  same for each token object in allProperties because each token
   //  is under the same category and type.
   if (!props.hasOwnProperty(classname)) {
   props[classname] = {}
   }

   //  If the token object has a subitem, use the item as the subclass.
   //  Run the same check to see if this particular subclass (item) has
   //  been added yet.
   if (subitem) {
   if (!props[classname].hasOwnProperty(item)) {
   props[classname][item] = {}
   }

   // add the subitem and value as final CSS rule
   props[classname][item][subitem] = value
   } else {
   // add the item as a CSS rule, not a subclass
   props[classname][item] = value
   }
   })

   //  Pass the final `props` object to our custom template to render
   //  the contents for the final button.scss file.
   return template({
   props
   })

   }
   */
});

StyleDictionary.registerFormat({
  name: 'yaml',
  formatter: _.template(
    fs.readFileSync(__dirname + '/templates/yaml.template'),
  ),
});

StyleDictionary.registerFormat({
  name: 'yaml/info',
  formatter: _.template(
    fs.readFileSync(__dirname + '/templates/info.template'),
  ),
});

StyleDictionary.registerFormat({
  name: 'yaml/breakpoints',
  formatter: _.template(
    fs.readFileSync(__dirname + '/templates/breakpoints.template'),
  ),
});

/**
 * registerTransform
 */
StyleDictionary.registerTransform({
  name: 'adjust/scale',
  type: 'value',
  matcher: function (prop) {
    return prop.scale == true || prop.attributes.category === 'dynamic';
  },
  transformer: function (prop) {
    //console.log(prop);
    /*
     var num = parseInt(prop.original.value) * prop.attributes.scale;
     var unit = prop.original.value.replace(/[0-9]/g, '');
     return num.toString() + unit;
     */
  },
});

/**
 * registerTransform
 */
StyleDictionary.registerTransform({
  name: 'replace/empty',
  type: 'value',
  matcher: function (prop) {
    return prop.value === 'undefined' || !prop.value.length;
  },
  transformer: function (prop) {
    console.log('Undefined Value:' + prop.name + '\n');
    // prop.value = typeof(prop.value === Array) ? ["-"] : "-";

    /*
     var num = parseInt(prop.original.value) * prop.attributes.scale;
     var unit = prop.original.value.replace(/[0-9]/g, '');
     return num.toString() + unit;
     */
  },
});

StyleDictionary.registerTransform({
  name: 'quote/strings',
  type: 'value',
  matcher: function (prop) {
    return typeof prop.value === String;
  },
  transformer: function (prop) {
    console.log(prop.value);
    /*
     var num = parseInt(prop.original.value) * prop.attributes.scale;
     var unit = prop.original.value.replace(/[0-9]/g, '');
     return num.toString() + unit;
     */
  },
});

StyleDictionary.registerTransform({
  name: 'adjust/color/lightness',
  type: 'value',
  matcher: isColor,
  transformer: function (prop) {
    var color = Color(prop.value);
    var o = color.toHsl();
    var vals = `${Math.round(o.h)} ${Math.round(o.s * 100)}% ${Math.round(
      o.l * 100,
    )}%`;
    if (color.getAlpha() === 1) {
      return `hsl(${vals})`;
    } else {
      return `hsl(${vals} / ${o.a})`;
    }
  },
});

/**
 * Register transformGroup
 */
StyleDictionary.registerTransformGroup({
  name: 'sass/cellular',
  transforms: StyleDictionary.transformGroup['scss'].concat([
    'replace/empty',
    //'quote/strings',
    //'adjust/scale'
  ]),
});

StyleDictionary.registerTransformGroup({
  name: 'yaml',
  transforms: ['name/cti/snake', 'attribute/cti'],
});

StyleDictionary.registerTransformGroup({
  name: 'adjustments',
  transforms: ['adjust/color/lightness', 'adjust/scale'],
});

// Build
StyleDictionary.extend(
  path.join(__dirname, '..', 'drupal', 'config.json'),
).buildAllPlatforms();

StyleDictionary.extend(
  path.join(__dirname, '..', 'tokens', 'config.json'),
).buildAllPlatforms();
