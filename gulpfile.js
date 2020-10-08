// Load gulp and required tools
var path = require('path'),
  gulp = require('gulp'),
  using = require('gulp-using'),
  grep = require('gulp-grep'),
  babel = require('gulp-babel'),
  del = require('del'),
  sass = require('gulp-sass'),
  sassLint = require('gulp-sass-lint'),
  sourcemaps = require('gulp-sourcemaps'),
  eslint = require('gulp-eslint'),
  debug = require('gulp-debug'), // Debug Vinyl file streams to see what files are run through your Gulp pipeline
  globbing = require('gulp-css-globbing'), // Expands CSS @import statements containing globs with the full paths. Useful with pre-processors like Sass.
  concat = require('gulp-concat'),
  uglify = require('gulp-uglify'),
  cleancss = require('gulp-clean-css'),
  rename = require('gulp-rename'),
  changed = require('gulp-changed'), // By default it's only able to detect whether files in the stream changed.
  minify = require('gulp-minify'),
  merge = require('merge-stream'),
  autoprefixer = require('gulp-autoprefixer'),
  csscomb = require('gulp-csscomb'),
  imagemin = require('gulp-imagemin');


var paths = {
  dirs: {
    build: 'dist',
    source: 'src'
  },
  images: 'src/**/*.{JPG,jpg,png,gif,svg}',
  sass: 'src/sass/styles.scss',
  js: 'src/js/script.js',
  vendor: {
    components: {
      all: 'src/**/vendors/**/*.*',
      js: 'src/**/vendors/**/*.js',
      nonJs: [
        'src/**/vendors/**/*',
        '!src/**/vendors/**/*.js',
        '!src/**/vendors/**/*.scss'
      ]
    },
    libs: {
      js: [
        'node_modules/bootstrap/dist/js/bootstrap.bundle.js',
        'node_modules/bootstrap/dist/js/bootstrap.bundle.js.map'
      ],
      css: [
        'node_modules/@fortawesome/fontawesome-free-webfonts/css/fontawesome.css'
      ],
      fonts: [
        'node_modules/@fortawesome/fontawesome-free-webfonts/webfonts/*'
      ]
    }
  },
  eslint: {
    files: [
      'src/**/*.js',
      '!src/**/*.min.js',
      '!src/**/vendors/**/*.js',
      '!node_modules/**'
    ]
  }
};

// Cleaning build directories
gulp.task('clean', function (cb) {
  return del(paths.dirs.build, cb);
});

// Lint JavaScript.
gulp.task('lint:js', function () {
  return gulp.src(paths.eslint.files)
    .pipe(eslint())
    .pipe(eslint.format());
});

// Lint JavaScript and throw an error for a CI to catch.
gulp.task('lint:js-with-fail', function () {
  return gulp.src(paths.eslint.files)
    .pipe(eslint())
    .pipe(eslint.format())
    .pipe(eslint.failOnError());
});

// Lint Sass.
gulp.task('lint:sass', function () {
  return gulp.src(paths.dirs.source + '/**/*.s+(a|c)ss')
    .pipe(sassLint())
    .pipe(sassLint.format());
});

// Lint Sass and throw an error for a CI to catch.
gulp.task('lint:sass-with-fail', function () {
  return gulp.src(paths.dirs.source + '/**/*.s+(a|c)ss')
    .pipe(sassLint())
    .pipe(sassLint.format())
    .pipe(sassLint.failOnError());
});

gulp.task('lint', gulp.parallel('lint:js', 'lint:sass'));


// building sass files
gulp.task('sass', function () {
  return gulp.src(paths.sass)
    .pipe(using({prefix: 'After changed:'}))
    .pipe(sourcemaps.init())
    .pipe(globbing({
      // Configure it to use SCSS files
      extensions: ['.scss']
    }))
    .pipe(sass({
      outputStyle: 'expanded'
    }))
    .pipe(autoprefixer({
      browsers: ['last 2 versions'],
      cascade: false
    }))
    .pipe(changed(paths.dirs.build))
    .pipe(csscomb())
    .pipe(sourcemaps.write('.', {sourceRoot: '/'}))
    .pipe(gulp.dest(paths.dirs.build + '/css'));
});

// Building scripts
gulp.task('scripts:build', function () {
  return gulp.src(paths.js)
    .pipe(babel())
    .pipe(gulp.dest(paths.dirs.build + '/js'));
});

// Moving source libraries to build
gulp.task('scripts:move', function () {
  return gulp.src(paths.vendor.components.js)
    .pipe(uglify())
    .pipe(gulp.dest(paths.dirs.build + '/vendors'));
});

gulp.task('scripts', gulp.parallel('scripts:build', 'scripts:move'));

// Optimize images
gulp.task('images', function () {
  return gulp.src(paths.images)
    .pipe(debug({title: 'optimized images:'}))
    .pipe(imagemin())
    .pipe(gulp.dest(paths.dirs.build + '/img'));
});


gulp.task('app', gulp.series('lint', 'images', 'sass', 'scripts'));

gulp.task('vendor:components:js', function () {
  return gulp.src(paths.vendor.components.js)
    .pipe(gulp.dest(paths.dirs.build + '/vendors'));
});

gulp.task('vendor:components:other', function () {
  return gulp.src(paths.vendor.components.nonJs)
    .pipe(gulp.dest(paths.dirs.build + '/vendors'));
});

gulp.task('vendor:components', gulp.parallel(
  'vendor:components:js', 'vendor:components:other'
));

gulp.task('vendor:js', function () {
  return gulp.src(paths.vendor.libs.js)
    .pipe(gulp.dest(paths.dirs.build + '/vendors/js'));
});

gulp.task('vendor:css', function () {
  return gulp.src(paths.vendor.libs.css)
    .pipe(csscomb())
    .pipe(gulp.dest(paths.dirs.build + '/vendors/css'));
});

gulp.task('vendor:fonts', function () {
  return gulp.src(paths.vendor.libs.fonts)
    .pipe(gulp.dest(paths.dirs.build + '/vendors/fonts'));
});

gulp.task('vendor', gulp.parallel(
  'vendor:components', 'vendor:js', 'vendor:css', 'vendor:fonts'
));

// Production building start here

// building image for production with compression
gulp.task('images:prod', function () {
  return gulp.src(paths.images)
    .pipe(imagemin())
    .pipe(gulp.dest(paths.dirs.build + '/img'));
});

// building styles for production
gulp.task('styles:prod', function () {
  var cssStream = gulp.src(paths.vendor.libs.css);

  var sassStream = gulp.src(paths.sass)
    .pipe(globbing({
      // Configure it to use SCSS files
      extensions: ['.scss']
    }))
    .pipe(sass())
    .pipe(autoprefixer({
      browsers: ['last 2 versions'],
      cascade: false
    }))
    .pipe(changed(paths.dirs.build))
    .pipe(csscomb())
    .pipe(gulp.dest(paths.dirs.build + '/css'));

  return merge(cssStream, sassStream)
    .pipe(concat('all.min.css'))
    .pipe(cleancss())
    .pipe(gulp.dest(paths.dirs.build + '/css'));
});

// watching sass files
gulp.task('watch:styles', function () {
  gulp.watch(paths.dirs.source + '/**/*.scss', gulp.series('sass'));
});
// watching scripts and other files
gulp.task('watch:code', function () {
  gulp.watch([
    paths.images,
    paths.vendor.components.all,
    paths.js
  ], gulp.series('build'));
});

gulp.task('watch', gulp.parallel('watch:code', 'watch:styles'));

// build for local development
gulp.task('all', gulp.parallel('app', 'vendor'));
gulp.task('build', gulp.series('clean', 'all'));

// Building for production
gulp.task('all:prod', gulp.parallel('images:prod', 'vendor', 'styles:prod', 'scripts'));
gulp.task('build:prod', gulp.series('clean', 'all:prod'));

// The default task.
gulp.task('default', gulp.series('build', 'watch'));
