<?php

/**
 * @file
 * Vars & regions for single column panel layout.
 */
$plugin = array(
    'category' => t('Cellular'),
    'title' => t('1 Column'),
    'icon' => 'cellular_1col.png',
    'theme' => 'cellular_1col',
    'theme arguments' => array('id', 'content'),
    'admin css' => 'admin.css',
    'regions' => array(
        'middle' => t('Middle Column'),
    ),
);
