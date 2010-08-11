<?php

function wow_core_admin_region_and_lang_settings() {
  $form['wow_core_region'] = array(
    '#title' => t('Select a Region'),
    '#type' => 'select',
    '#options' => iArmory::get_regions(),
    '#default_value' => variable_get('wow_core_region', 'www'),
    '#required' => TRUE,
  );

  $form['wow_core_lang'] = array(
    '#title' => t('Select a Language'),
    '#type' => 'select',
    '#options' => iArmory::get_langs(),
    '#default_value' => variable_get('wow_core_lang', 'en_us'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
