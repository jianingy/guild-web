<?php

function wow_tooltip_item_ajax_load($item) {
  $status = 1;

  if (FALSE === $item) {
    $status = 0;
  }

  drupal_json_output(array(
    'status' => $status,
    'html' => '<div class="tooltip">' . $item->tooltip . '</div>',
  ));

  exit;
}
