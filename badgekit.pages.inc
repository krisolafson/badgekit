<?php

/**
 * Page callback; Returns all published badges
 */
function badgekit_page() {
  $connection = new BadgekitConnection();

  $badges = $connection->getBadges('badgekit');

  foreach($badges as $badge) {
    $output['badges'][] = array(
      '#theme' => 'badge',
      '#badge' => $badge,
    );
  }

  return $output;
}