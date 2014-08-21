<?php

$plugin = array(
    'category' => t('Cellular'),
    'title' => t('2 Columns @ 30/70'),
    'icon' => 'cellular_2col_30_70.png',
    'theme' => 'cellular_2col_30_70',
    'theme arguments' => array('id', 'content'),
    'admin css' => 'admin.css',
    'regions' => array(
        'top' => t('Top'),
        'left' => t('Left'),
        'right' => t('Right'),
        'bottom' => t('Bottom'),
    ),
);