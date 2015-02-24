<?php

/**
 * Page callback; Returns all published badges
 *
 * @return array
 */
function badgekit_page() {
  $output = array();

  $connection = new BadgekitConnection();

  $badges = $connection->getBadges('badgekit');

  if (!empty($badges)) {
    foreach($badges as $badge) {
      $output['badges'][] = array(
        '#theme' => 'badge',
        '#badge' => $badge,
      );
    }
  }

  return $output;
}

/**
 * Form callback; Module configuration form
 */
function badgekit_admin() {
  $form = array();

  $form['badgekit_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Badgekit API secret'),
    '#default_value' => variable_get('badgekit_api_key', ''),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t("Badgekit API shared secret. Required to connect."),
    '#required' => TRUE,
  );

  $form['badgekit_api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Badgekit API URL'),
    '#default_value' => variable_get('badgekit_api_url', ''),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t("Badgekit API URL. Required to connect."),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}