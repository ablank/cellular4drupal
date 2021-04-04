# DO NOT EDIT DIRECTLY
# @see ./style-dictionary/drupal/layout.json
# Generated on <% print(new Date().toString()); %>
<%
var theme = '';
var cells = {};

/**
 * Iterate over each layout
 */
 function iterateLayout(key){
  if (cells[key]) {
    print(`\n${theme}_layout_${key}:`);
    print(`\n  label: ${key}`);
    print(`\n  category: ${theme}`);
    print(`\n  path: templates/layout/${key}`);
    print(`\n  template: layout--${theme}-${key}`);
    print(`\n  default_region: ${cells[key]['default_region']}`);
    print(`\n  icon_map:`);

    print(`\n  regions:`);
  } 
}

var allProperties = _.each(allProperties, (prop) => {
  if(prop.name === "info_name"){
    theme = prop.value.toLowerCase();
  }
});

_.each(Object.keys(cells), (key)=>{
  iterateLayout(key);
});
%>