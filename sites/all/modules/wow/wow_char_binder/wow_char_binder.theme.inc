<?php

function theme_wow_char_binder_user_chars_list($vars) {
  $html = '<div class="chars-list">';
  $chars = $vars['chars'];

  if (is_null($vars['chars'])) {
    return t('No bound characters yet.');
  }

  foreach ($chars AS $char) {
    $data = unserialize($char->data);

    $html .= '<div class="profile">';
    $html .=   theme('wow_portrait', array('data' => $data));
    $html .=   '<div class="level">' . $data['level'] . '</div>';
    $html .=   '<div class="name">' . $data['name'] . '</div>';
    $html .=   '<div class="guild">' . $data['guildName'] . '</div>';
    $html .= '</div>';
  }

  $html .= '</div>';

  return $html;
}
