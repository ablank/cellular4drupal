<?php

/**
 * Implements hook_default_page_manager_handlers().
 */
function cellular_default_page_manager_handlers() {
  if (module_exists('panels_everywhere')) {
    $handler = new stdClass();
    $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
    $handler->api_version = 1;
    $handler->name = 'site_template_panel_context_basic';
    $handler->task = 'site_template';
    $handler->subtask = '';
    $handler->handler = 'panel_context';
    $handler->weight = 0;
    $handler->conf = array(
      'title' => 'Cellular Panels Everywhere Site Template',
      'no_blocks' => 1,
      'css_id' => '',
      'css' => '',
      'contexts' => array(),
      'relationships' => array(),
      'access' => array(
        'plugins' => array(),
        'logic' => 'and',
      ),
      'pipeline' => 'standard',
    );

    $display = new panels_display();
    $display->layout = 'page_standard';
    $display->layout_settings = array();
    $display->panel_settings = array(
      'style_settings' => array(
        'default' => NULL,
        'content' => NULL,
        'header' => NULL,
        'body' => NULL,
        'footer' => NULL,
      ),
    );
    $display->cache = array();
    $display->title = '';
    $display->content = array();
    $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'body';
    $pane->type = 'page_content'; //'block';
    $pane->subtype = 'page_content'; //'system-navigation';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array(); //'';
    $display->content['new-1'] = $pane;
    $display->panels['body'][0] = 'new-1';

    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'body';
    $pane->type = 'pane_messages';
    $pane->subtype = 'pane_messages';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $display->content['new-2'] = $pane;
    $display->panels['body'][1] = 'new-2';

    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'body';
    $pane->type = 'page_content';
    $pane->subtype = 'page_content';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'context' => 'argument_page_content_1',
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = '';
    $display->content['new-3'] = $pane;
    $display->panels['body'][2] = 'new-3';

    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'footer';
    $pane->type = 'block';
    $pane->subtype = 'user-login';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $display->content['new-4'] = $pane;
    $display->panels['footer'][0] = 'new-4';

    $pane = new stdClass();
    $pane->pid = 'new-5';
    $pane->panel = 'header';
    $pane->type = 'pane_header';
    $pane->subtype = 'pane_header';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = '';
    $display->content['new-5'] = $pane;
    $display->panels['header'][0] = 'new-5';

    $pane = new stdClass();
    $pane->pid = 'new-6';
    $pane->panel = 'header';
    $pane->type = 'pane_navigation';
    $pane->subtype = 'pane_navigation';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = '';
    $display->content['new-6'] = $pane;
    $display->panels['header'][1] = 'new-6';
    $display->hide_title = PANELS_TITLE_PANE;
    $display->title_pane = 'new-6';
    $handler->conf['display'] = $display;

    $handlers[$handler->name] = $handler;

    return $handlers;
  }
}
