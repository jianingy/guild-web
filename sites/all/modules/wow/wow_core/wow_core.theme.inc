<?php

function theme_wow_portrait($vars) {
  $module_path = drupal_get_path('module', 'wow_core');

  $data = $vars['data'];
  $set = $data['level'] >= 80 ? '80' : ($data['level'] >= 70 ? '70' : 'default');

  $html = theme('image', array(
    'path' => $module_path . "/images/portraits/wow-$set/{$data['genderId']}-{$data['raceId']}-{$data['classId']}.gif",
    'title' => "{$data['race']} {$data['class']} {$data['name']}",
    'attributes' => array(
      'class' => 'portrait',
    ),
  ));
  
  return $html;
}
