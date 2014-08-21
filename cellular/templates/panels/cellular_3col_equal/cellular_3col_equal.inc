<?php

$plugin = array(
    'category' => t('Cellular'),
    'title' => t('3 Equal Columns @ 33%'),
    'icon' => 'cellular_3col_equal.png',
    'theme' => 'cellular_3col_equal',
    'theme arguments' => array('id', 'content'),
    'admin css' => 'admin.css',
    'regions' => array(
        'top' => t('Top'),
        'left' => t('Left Column'),
        'middle' => t('Middle Column'),
        'right' => t('Right Column'),
        'bottom' => t('Bottom')
    )
);
