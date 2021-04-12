const config = require("./postcss.config");
const fs = require("fs");
const path = require("path");
const postcss = require("postcss");

const autoprefixer = require("autoprefixer")({
  /* your options */
});
const cssnano = require('cssnano')({
  preset: 'default',
});
const stylelint = require("stylelint")({

});
const sorting = require('postcss-sorting')({});
const reporter = require("postcss-reporter")({
  clearReportedMessages: true
});

// Code to be processed
const code = fs.readFileSync(
  path.join(__dirname, '..', '..', 'dist', 'css', 'style.css')
);

postcss([autoprefixer, sorting, stylelint, reporter, cssnano])
  .catch((err) => console.error(err.stack));
