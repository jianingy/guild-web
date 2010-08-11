<?php

function wow_char_binder_user_chars_page($account) {
  $build = array();

  $build['user_chars_list'] = array(
    '#theme' => 'wow_char_binder_user_chars_list',
    '#chars' => isset($account->wow_chars) ? $account->wow_chars : NULL,
  );

  // if it's current logged user, show form for binding
  global $user;
  if ($user->uid == $account->uid && user_access('bind wow chars', $user)) {
    $build['add_char_form'] = drupal_get_form('wow_char_binder_add_char_form', $account);
  }

  return $build;
}

function wow_char_binder_add_char_form($form, &$form_state, $user) {
  $form['wow_char_binder'] = array(
    '#title' => t('Bind your World of Warcraft character'),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );

  $form['wow_char_binder']['user'] = array(
    '#type' => 'value',
    '#value' => $user,
  );

  $form['wow_char_binder']['region'] = array(
    '#title' => t('Region'),
    '#type' => 'select',
    '#options' => iArmory::get_regions(),
    '#default_value' => variable_get('wowarmory_region', ''),
  );

  $form['wow_char_binder']['realm'] = array(
    '#title' => t('Realm'),
    '#type' => 'textfield',
    '#default_value' => '',
  );

  $form['wow_char_binder']['name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#default_value' => '',
  );

  // this element is for storing data loaded from armory in validation
  $form['wow_char_binder']['remote_data'] = array(
    '#type' => 'value',
    '#value' => FALSE,
  );

  $form['wow_char_binder']['submit'] = array(
    '#value' => t('Bind'),
    '#type' => 'submit'
  );
    
  return $form;
}

function wow_char_binder_add_char_form_validate($form, &$form_state) {
  $wow_char_values = $form_state['values']['wow_char_binder'];
  $user = $wow_char_values['user'];

  // 1. check if the character has been bound
  $result = db_select('wow_char_binder', 'wcc')
    ->fields('wcc')
    ->condition('region', $wow_char_values['region'])
    ->condition('realm', $wow_char_values['realm'])
    ->condition('name', $wow_char_values['name'])
    ->execute();
  if ($row = $result->fetch()) {
    form_set_error('', t('This character has been bound.'));
    return FALSE;
  }

  // 2. validate the char info by sending request to armory
  $armory = new iArmory('http://' . $wow_char_values['region'] . '.wowarmory.com');

  $data = $armory->get_character($wow_char_values['realm'], $wow_char_values['name']);

  if (!isset($data['page']['characterInfo']['character_attr'])) {
    form_set_error('', t('Cannot correctly load your character.'));
    return FALSE;
  }

  form_set_value($form['wow_char_binder']['remote_data'], $data['page']['characterInfo']['character_attr'], $form_state);
}

function wow_char_binder_add_char_form_submit($form, &$form_state) {
  $wow_char_values = $form_state['values']['wow_char_binder'];
  $user = $wow_char_values['user'];

  db_insert('wow_char_binder')
    ->fields(array(
      'uid' => $user->uid,
      'region' => $wow_char_values['region'],
      'realm' => $wow_char_values['realm'],
      'name' => $wow_char_values['name'],
      'data' => serialize($wow_char_values['remote_data']),
      'validated' => 0,
      'updated' => REQUEST_TIME,
    ))
    ->execute();
  
}
