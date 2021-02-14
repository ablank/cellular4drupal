"adjust" = {
  "color": function ($color = "{color.primary.value}", $percent = "{color.adjust.value}") {
    return color;
  },
  "size": function ($base = "{size.default.value}", $percent = "{size.adjust.value}") {
    return $base * $percent;
  },
  "opacity": function ($base = "{size.default.value}", $percent = "{size.adjust.value}") {
    return $base * $percent;
  }
}


function throwSizeError(name, value, unitType) {
  throw `Invalid Number: '${name}: ${value}' is not a valid number, cannot transform to '${unitType}' \n`;
}
/**
 * @namespace Transforms
 */
module.exports = {
  /**
   * Lightens or darkens color based on options value
   *
   * @memberof Transforms
   */
  'color/darkenlighten': {
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
  }
};