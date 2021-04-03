# Colors

## Color
Color variables assign the actual colors used in the theme (i.e. $color-primary, $color-secondary, $color-hilight, etc.).

Set the variables as you will (i.e. hex or named color value), but prefer setting values from swatches.

## Schemes
Schemes allow you to extend or override default colorsare derivative from color.json, implementing the same structure/names but wrapped in a schemename property.

```
{
 color:{
     yourschemename: {
         primary: {value: "{swatch.yourswatchname.value}"}
     }
 }
```
Sass will look for a `$color-scheme` string, which should match yourschemename, and if a match is found the values for `$color-property` will be replaced with those from yourscheme.

## Swatches

Named variables for hex, rgba, hsla, etc. colors.