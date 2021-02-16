const StyleDictionary = require('style-dictionary').extend('./style-dictionary/config.json'),
  fs = require('fs'),
  _ = require('lodash');
/*
var templates = [
  'breakpoints',
  'info',
  'layouts'
];

templates.map(function(template){
  Handlebars.compile(fs.readFileSync("build/templates/${template}"));
});
*/
// Log available pre-defined formats, transforms and transform groups
//console.log(StyleDictionary);

function isColor(prop) {
  return prop.attributes.category === 'color';
}

function LightenDarkenColor(col, amt) {
  var usePound = false;
  if (col[0] == "#") {
    col = col.slice(1);
    usePound = true;
  }
  var num = parseInt(col, 16);
  var r = (num >> 16) + amt;
  if (r > 255) r = 255;
  else if (r < 0) r = 0;
  var b = ((num >> 8) & 0x00FF) + amt;
  if (b > 255) b = 255;
  else if (b < 0) b = 0;
  var g = (num & 0x0000FF) + amt;
  if (g > 255) g = 255;
  else if (g < 0) g = 0;

  return (usePound ? "#" : "") + (g | (b << 8) | (r << 16)).toString(16);
};

/**
 * registerFormat
 */

StyleDictionary.registerFormat({
  name: 'json',
  formatter: function (dictionary) {
    return JSON.stringify(dictionary.allProperties, null, 2);
  }
});

/**
 * registerTransform
 */

StyleDictionary.registerTransform({
  name: 'adjust/scale',
  type: 'value',
  matcher: function (prop) {
    return prop.attributes.scale == true;
  },
  transformer: function (prop) {
    return (prop.attributes.scale * parseInt(prop.original.value)).toString();
  }
});

StyleDictionary.registerTransform({
  name: 'color/lighten',
  type: 'value',
  matcher: isColor,
  transformer: function (prop) {
    var color = Color(prop.value);
    var o = color.toHsl()
    var vals = `${Math.round(o.h)} ${Math.round(o.s * 100)}% ${Math.round(o.l * 100)}%`
    if (color.getAlpha() === 1) {
      return `hsl(${vals})`
    } else {
      return `hsl(${vals} / ${o.a})`
    }
  }
});

/**
 * Register transformGroup
 */

StyleDictionary.buildAllPlatforms();
