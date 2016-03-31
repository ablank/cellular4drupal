/*
 * scsslint
 *
 *
 * Copyright (c) 2014 Fabrice Weinberg
 * Licensed under the MIT license.
 */

'use strict';


var readline  = require('readline');
var numCPUs = require('os').cpus().length;
var fs = require('fs');

var async = require('async');
var dargs = require('dargs');
var chalk = require('chalk');
var spawn = require('win-spawn');
var which = require('which');



var defaultReporter = {
  warn : function (message) {
    console.log(chalk.red(message));
  },
  log : {
    warn : function (message){
      console.log(chalk.red(message));
    },
    writeln : function (message){
      console.log(message + '\n');
    }
  }
};

var noopReporter = {
  warn : function(){},
  log : {
    warn : function(){},
    writeln : function(){}
  }
};

var defaultFormatter = function (src, report){
    var type = report.type === 'E' ? chalk.red(report.type) : chalk.yellow(report.type );
    return chalk.cyan(src) + ':' + chalk.magenta(''+report.line) + ' [' + type + '] ' + report.message;
};

var noopFormatter = function(){};


var reduceArray = function(options, key){
  if ( !!options[key] ) {
    if ( Array.isArray(options[key])){
      return options[key].join(',');
    } else  {
      return options[key];
    }
  }
};

var ScssLinter = function ( options ) {
  if ( options === false ) {
    this.reporter = noopReporter;
    this.formatter = noopFormatter;
  } else if ( options === undefined ) { 
    this.reporter = defaultReporter;
    this.formatter = defaultFormatter;
  } else {
    this.reporter = options.reporter || defaultReporter;
    this.formatter = options.formatter || defaultFormatter;
  }
};

ScssLinter.prototype = {

  lint : function ( files, options, doneCallback ){
    var self = this;

    try {
      which.sync('scss-lint');
    } catch (err) {
      return self.reporter.warn(
        '\nYou need to have Ruby and scss-lint installed and in your PATH for this task to work.\n' +
        'More info: https://github.com/FWeinb/scsslint\n'
      );
    }

    options.excludeLinter = reduceArray(options, 'excludeLinter');
    options.includeLinter = reduceArray(options, 'includeLinter');

    var passedArgs = dargs(options, ['format', 'version', 'showLinters', 'help', 'bundleExec']);


    var bundleExec = options.bundleExec;
    var allResults = {};

    async.eachLimit(files, numCPUs, function(src, next){
      if (!fs.existsSync(src)) {
        self.reporter.warn('Source file "' + src + '" not found.');
        return next();
      }

      if (!fs.lstatSync(src).isFile()) { 
        return next();
      }


      var args = [
        src
      ].concat(passedArgs);

      var bin = 'scss-lint';

      if (bundleExec) {
        bin = 'bundle';
        args.unshift('exec', bin);
      }

      var cp = spawn('scss-lint', args);
      var reports = [];

      readline.createInterface({
        input     : cp.stdout,
        terminal  : false
      }).on('line', function(line) {
        var split = line.split(':');
        if ( split.length === 2 ) {
          var report = {
            line : parseInt(split[1]),
            type : split[1].substr(split[1].indexOf('[')+1, 1),
            message : split[1].substr(split[1].indexOf(']')+2)
          };
          self.reporter.log.writeln(self.formatter(src, report));
          reports.push(report);
        }
      });

      cp.on('close', function(code){
        allResults[src] = reports;

        if ( code > 0 ) {
          next(true);
          return self.reporter.warn('Exited with error code ' + code);
        }

        self.reporter.log.writeln('File ' + chalk.cyan(src) + ' lint free');
        next();
      });

    }, function(){
      doneCallback(allResults);
    });
  }

};

module.exports = ScssLinter;