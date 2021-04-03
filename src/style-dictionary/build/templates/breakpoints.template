# DO NOT EDIT DIRECTLY
# @see ./style-dictionary/tokens/globals/breakpoint.json
# Generated on <% print(new Date().toString()) %>
<%
var mediaquery = {};
var theme;
var i = 0;
/**
 * Iterate over specified props
 */
 function iterate(key){
  if (mediaquery[key]) {
    print(`\n\n${theme}.screen.${key}:`);
    print(`\n  label: ${key}`);
    print(`\n  mediaQuery: ${mediaquery[key]}`);
    print(`\n  group: screen`);
    print(`\n  weight: ${i}`);
    print(`\n  multipliers:`);
    print(`\n    - 1x`);
    print(`\n    - 2x`);

    i += 1;
    /*
    _.each(mediaquery[key], function (feature) {
      print(`\n    - ${feature}`);
    });
    */
  } 
}

var allProperties = _.each(allProperties, function (prop) {
  
  if(prop.name === "info_name"){
    theme = prop.value.toLowerCase();
  }

  if (prop.attributes.category === 'mediaquery') {    
    var rename = prop.name.replace(/mediaquery_/, '');
    mediaquery[rename] = prop.value;

  }
});

_.each(Object.keys(mediaquery), (key)=>{
  iterate(key);
});
%>