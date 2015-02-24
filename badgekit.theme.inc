<?php

/**
 * Generates a Badgekit badge.
 *
 * @param array $vars
 *
 * @return array
 */
function theme_badge($vars) {
  $badge = $vars['badge'];

  $output = '<div class="badgekit-badge">';
  $output .= '<img src="' . $badge->imageUrl . '" width="250px" height="250px" alt="Badge" />';
  $output .= '<h2>' . $badge->name . '</h2>';
  $output .= '<h3>' . $badge->strapline . '</h3>';
  $output .= '</div>';

  return $output;
}