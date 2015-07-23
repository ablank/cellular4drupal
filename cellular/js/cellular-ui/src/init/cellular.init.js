var cellular = {};

function breakpoint(){
  var content = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content'),
    mq = {
      size: content.match(/\d/g).join(""),
      type: content.match(/\w*[^\"\'](?=-)/g).join("")
    };

  return mq;
};

$(window).on('resize', breakpoint);

cellular.opts = {
  cclass: "cellular",
  tclass: "title",
  bclass: "body",
  wrapper: "<div />",
  speed: 300,
  breakpoint: breakpoint().type
};
