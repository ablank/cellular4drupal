# scsslint [![Build Status](https://travis-ci.org/FWeinb/scsslint.svg?branch=master)](https://travis-ci.org/FWeinb/scsslint)

> nodejs bindings for [scss-lint](https://github.com/causes/scss-lint)

## Overview

This is the core library used in [grunt-scsslint](https://github.com/FWeinb/grunt-scsslint). This can be used programmaticly in Node.js.

## Getting Started

These are bindings for [scss-lint](https://github.com/causes/scss-lint) and requires you to have [Ruby](http://www.ruby-lang.org/en/downloads/) and [scss-lint](https://github.com/causes/scss-lint) installed. If you're on OS X or Linux you probably already have Ruby installed; test with `ruby -v` in your terminal. When you've confirmed you have Ruby installed, run `gem install scss-lint` to install [scss-lint](https://github.com/causes/scss-lint).

### Install

```shell
npm install scsslint --save
```

## Usage

```js
var ScssLinter = require('scsslint');
var linter = new ScssLinter();


linter.lint( fileArray, options, doneCallback );

```

## Contributing
In lieu of a formal styleguide, take care to maintain the existing coding style. Add unit tests for any new or changed functionality. Lint and test your code using [Grunt](http://gruntjs.com/).

## Release History

  * 0.0.3 Fixed file detection. And error detecting
  * 0.0.2 Fixed error during instantiation
  * 0.0.1 First Release

## License
Copyright (c) 2014 Fabrice Weinberg. Licensed under the MIT license.
