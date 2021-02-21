const path = require('path'),
  fs = require('fs'),
  _ = require('lodash'),
  yaml = require('yaml');

const StyleDictionary = require('style-dictionary').extend(path.join(__dirname,'..', 'config.json'));
/*s,
  Handlebars = require('handlebars'),
  source = fs.readFileSync(`${cwd}/${file}`).toString(),
  template = Handlebars.compile(source),
  contents = template({ PROJECT_NAME: `${name}`, PROJECT_VERSION: `${version}`, DOCKER_IMAGE: `${image}` })
  */

// Log available pre-defined formats, transforms and transform groups
//console.log(StyleDictionary);

function isColor(prop) {
  return prop.attributes.category === 'color';
};

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
  name: 'json/raw',
  formatter: function (dictionary) {
    return JSON.stringify(dictionary.allProperties);
  }
});

StyleDictionary.registerFormat({
  name: 'yaml',
  formatter: function (dictionary) {
    return yaml.stringify(dictionary.allProperties);
  }
});

StyleDictionary.registerFormat({
  name: 'yaml/info',
  formatter: _.template(fs.readFileSync(__dirname + '/templates/info.template'))
});

StyleDictionary.registerFormat({
  name: 'yaml/breakpoints',
  formatter: _.template(fs.readFileSync(__dirname + '/templates/breakpoints.template'))
});
/**
 * registerTransform
 */

StyleDictionary.registerTransform({
  name: 'adjust/scale',
  type: 'value',
  matcher: function (prop) {
    return prop.scale;
  },
  transformer: function (prop) {
    console.log(prop.name);
    var num = parseInt(prop.original.value) * prop.attributes.scale;
    var unit = prop.original.value.replace(/[0-9]/g, '');
    return num.toString() + unit;
  }
});

StyleDictionary.registerTransform({
  name: 'adjust/color/lightness',
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

StyleDictionary.registerTransformGroup({
  name: 'yaml',
  transforms: ['name/cti/kebab', 'attribute/cti']
});

StyleDictionary.registerTransformGroup({
  name: 'adjustments',
  transforms: ['adjust/color/lightness', 'adjust/scale']
});

// Build
StyleDictionary.buildAllPlatforms();
