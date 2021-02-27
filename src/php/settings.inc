<?

/**
* Theme settings for Cellular theme.
* Implements hook_form_FORM_ID_alter()
*/
function cellular_form_system_theme_settings_alter(&$form, FormStateInterface $form_state) {

// Footer copyrights settings.
$form['cellular_settings'] = [
'#type' => 'fieldset',
'#title' => t('Cellular Theme Settings'),
'#collapsible' => FALSE,
'#collapsed' => FALSE,
];

$form['cellular_settings']['tabs'] = [
'#type' => 'vertical_tabs',
'#default_tab' => 'general_tab',
];

$form['cellular_settings']['general_tab']['general_options'] = [
'#type' => 'details',
'#title' => t('General Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['general_tab']['general_options']['display_sample_blocks'] = [
'#type' => 'checkbox',
'#title' => t('Show Sample Blocks'),
'#default_value' => theme_get_setting('display_sample_blocks', 'cellular'),
'#description' => t('Just shows sample blocks for your idea. On production disable this'),
];

$form['cellular_settings']['general_tab']['general_options']['user_page_intro'] = [
'#type' => 'textarea',
'#title' => t('User Page Intro'),
'#default_value' => theme_get_setting('user_page_intro', 'cellular'),
'#description' => t('Text will be shown on left side of login, registration, forgot password pages.'),
];

$form['cellular_settings']['header_tab']['header_options'] = [
'#type' => 'details',
'#title' => t('Top Header Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['header_tab']['header_options']['header_position'] = [
'#type' => 'select',
'#title' => t('Header Position'),
'#default_value' => theme_get_setting('header_position', 'cellular'),
'#description' => t('Choose header position'),
'#options' => [
'header-top' => t('Top'),
'header-left' => t('Left'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_color'] = [
'#type' => 'color',
'#title' => t('Header Background Color'),
'#default_value' => theme_get_setting('header_color', 'cellular'),
'#description' => t('Choose color that applies to header as background color. If choose header type Overlay, then background color will apply only when sticky header'),
];

$form['cellular_settings']['header_tab']['header_options']['header_link_style'] = [
'#type' => 'select',
'#title' => t('Header link Style'),
'#default_value' => theme_get_setting('header_link_style', 'cellular'),
'#description' => t('Choose header link style'),
'#options' => [
'navbar-dark' => t('Light'),
'navbar-light' => t('Dark'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_type'] = [
'#type' => 'select',
'#title' => t('Header Type'),
'#description'   => t('Choose header type. If you choose overlay, then header will be overlaid over the below section/content.'),
'#default_value' => theme_get_setting('header_type', 'cellular'),
'#options' => [
'standard' => t('Standard'),
'overlay' => t('Overlay'),
],
];

$form['cellular_settings']['header_tab']['header_options']['header_type_sticky'] = [
'#type' => 'checkbox',
'#title' => t('Sticky Header'),
'#default_value' => theme_get_setting('header_type_sticky', 'cellular'),
'#description' => t('Enable the sticky header when scrolling down the page'),
];

$form['cellular_settings']['header_tab']['header_options']['header_type_sticky_resize'] = [
'#type' => 'checkbox',
'#title' => t('Sticky header resizing'),
'#default_value' => theme_get_setting('header_type_sticky_resize', 'cellular'),
'#description' => t('Enable the sticky header to resize when scrolling down the page'),
];

$form['cellular_settings']['page_tab']['page_options'] = [
'#type' => 'details',
'#title' => t('Page Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['page_tab']['page_options']['page_header_style'] = [
'#type' => 'select',
'#title' => t('Page Header Style'),
'#default_value' => theme_get_setting('page_header_style', 'cellular'),
'#description' => t('Choose page header style. Ex. default, Full size, Box size. If node has field_image field then image shown as background for full and box sizes.'),
'#options' => [
'default' => t('Default'),
'full-size' => t('Full Size'),
'box-size' => t('Box Size'),
],
];

$form['cellular_settings']['social_tab']['social_profiles'] = [
'#type' => 'details',
'#title' => t('Social Profiles'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['social_tab']['social_profiles']['display_social_round_icons'] = [
'#type' => 'checkbox',
'#title' => t('Show round icons'),
'#default_value' => theme_get_setting('display_social_round_icons', 'cellular'),
'#description' => t('Enable to show round icons for below updated social profiles'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_facebook'] = [
'#type' => 'textfield',
'#title' => t('Facebook'),
'#default_value' => theme_get_setting('social_facebook', 'cellular'),
'#description' => t('Your facebook page/profile url'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_googleplus'] = [
'#type' => 'textfield',
'#title' => t('Google+'),
'#default_value' => theme_get_setting('social_googleplus', 'cellular'),
'#description' => t('Your Google+ page/profile URL'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_linkedin'] = [
'#type' => 'textfield',
'#title' => t('LinkedIn'),
'#default_value' => theme_get_setting('social_linkedin', 'cellular'),
'#description' => t('Your LinkedIn page/profile url'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_twitter'] = [
'#type' => 'textfield',
'#title' => t('Twitter'),
'#default_value' => theme_get_setting('social_twitter', 'cellular'),
'#description' => t('Your Twitter username (no @).'),
];

$form['cellular_settings']['social_tab']['social_profiles']['social_youtube'] = [
'#type' => 'textfield',
'#title' => t('Youtube'),
'#default_value' => theme_get_setting('social_youtube', 'cellular'),
'#description' => t('Your YouTube URL'),
];

$form['cellular_settings']['footer_tab']['footer_options'] = [
'#type' => 'details',
'#title' => t('Footer Options'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
'#group' => 'tabs',
];

$form['cellular_settings']['footer_tab']['footer_options']['copyright_text'] = [
'#type' => 'textfield',
'#title' => t('Enter copyright text'),
'#default_value' => theme_get_setting('copyright_text', 'cellular'),
'#description' => t('The copyright text that appears in the footer. Use @year placeholder for define current year.'),
];

$form['cellular_settings']['footer_tab']['footer_options']['backlink_container'] = [
'#type' => 'fieldset',
'#title' => t('Show Backlink'),
'#collapsible' => TRUE,
'#collapsed' => TRUE,
];

$form['cellular_settings']['footer_tab']['footer_options']['backlink_container']['display_theme_credits'] = [
'#type' => 'checkbox',
'#title' => t('Display theme credits'),
'#default_value' => theme_get_setting('display_theme_credits', 'cellular'),
'#description' => t('If checked, a backlink to our site will be shown in the footer. This is not compulsory, but always appreciated!'),
];
}
