<?php
/**
 * @file
 * drupalcampmel_core.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function drupalcampmel_core_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_contact-us:eform/submit/contact
  $menu_links['main-menu_contact-us:eform/submit/contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'eform/submit/contact',
    'router_path' => 'eform/submit/%',
    'link_title' => 'Contact us',
    'options' => array(
      'identifier' => 'main-menu_contact-us:eform/submit/contact',
    ),
    'module' => 'entityform',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: user-menu_create-session:node/add/session
  $menu_links['user-menu_create-session:node/add/session'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'node/add/session',
    'router_path' => 'node/add/session',
    'link_title' => 'Create session',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_create-session:node/add/session',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Contact us');
  t('Create session');

  return $menu_links;
}
