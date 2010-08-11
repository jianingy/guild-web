<?php
/**
 * Override or insert variables into the maintenance page template.
 */
function wow_preprocess_maintenance_page(&$vars) {
  // While markup for normal pages is split into page.tpl.php and html.tpl.php,
  // the markup for the maintenance page is all in the single
  // maintenance-page.tpl.php template. So, to have what's done in
  // wow_preprocess_html() also happen on the maintenance page, it has to be
  // called here.
  wow_preprocess_html($vars);
}

/**
 * Override or insert variables into the html template.
 */
function wow_preprocess_html(&$vars) {
  // Add conditional CSS for IE6.
  drupal_add_css(path_to_theme() . '/css/fix-ie.css', array('weight' => CSS_THEME, 'browsers' => array('IE' => 'lt IE 7', '!IE' => FALSE)));
}

/**
 * Override or insert variables into the page template.
 */
function wow_preprocess_page(&$vars) {
  $vars['tabs2'] = menu_secondary_local_tasks();
  if (isset($vars['main_menu'])) {
    $vars['primary_nav'] = theme('links__system_main_menu', array(
      'links' => $vars['main_menu'],
      'attributes' => array(
        'class' => array('links', 'main-menu'),
      ),
      'heading' => array(
        'text' => t('Main menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['primary_nav'] = FALSE;
  }
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_nav'] = theme('links__system_secondary_menu', array(
      'links' => $vars['secondary_menu'],
      'attributes' => array(
        'class' => array('links', 'secondary-menu'),
      ),
      'heading' => array(
        'text' => t('Secondary menu'),
        'level' => 'h2',
        'class' => array('element-invisible'),
      )
    ));
  }
  else {
    $vars['secondary_nav'] = FALSE;
  }
}

/**
 * Override or insert variables into the block template.
 */
function wow_preprocess_block(&$vars) {
  $vars['title_attributes_array']['class'][] = 'title';
  $vars['classes_array'][] = 'clearfix';
}

/**
 * Override or insert variables into the region template.
 */
function wow_preprocess_region(&$vars) {
  if ($vars['region'] == 'header') {
    $vars['classes_array'][] = 'clearfix';
  }
}

/**
 * Returns the rendered local tasks. The default implementation renders
 * them as tabs. Overridden to split the secondary tasks.
 */
function wow_menu_local_tasks() {
  return menu_primary_local_tasks();
}
