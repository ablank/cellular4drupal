module.exports = {
  plugins: {
    precss: {},
    autoprefixer: {
      Browserslist: ['last 5 versions']
    },
    cssnano: {
      preset: 'default'
    },
    sorting: {
      order: [
        'custom-properties',
        'dollar-variables',
        'declarations',
        'at-rules',
        'rules'
      ],
      'properties-order': 'alphabetical',
      'unspecified-properties-position': 'bottom'
    },
    stylelint: {
      extends: "./stylelintrc.json",},
    reporter: {
      clearReportedMessages: true
    }
  }
};
