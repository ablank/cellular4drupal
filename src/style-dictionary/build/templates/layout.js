# DO NOT EDIT DIRECTLY
# @see ./style-dictionary/drupal/layout.json
# Generated on <% print(new Date().toString()) %>
<%
var theme;
var cells = {};

/**
 * Iterate over specified props
 */
 function iterate(key){
  if (cells[key]) {
    print(`\n\n${theme}_layout_${key}:`);
    print(`\n  label: ${key}`);
    print(`\n  category: ${theme}`);
    print(`\n  path: templates/layout/${key}`);
    print(`\n  template: layout--${theme}-${key}`);
    print(`\n  default_region: ${cells[key]['default_region']}`);
    print(`\n  icon_map:`);

    print(`\n  regions:`);
    

    /*
    _.each(cells[key], function (feature) {
      print(`\n    - ${feature}`);
    });
    */
  } 
}

var allProperties = _.each(allProperties, function (prop) {
  
  if(prop.name === "info_name"){
    theme = prop.value.toLowerCase();
  }

  if (prop.attributes.category === 'layout') {    
    var rename = prop.name.replace(/layout_/, '');
    cells[rename] = prop.value;

  }
});

_.each(Object.keys(cells), (key)=>{
  iterate(key);
});
%>