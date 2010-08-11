<?php

function theme_wow_tooltip_box($variables) {
  $content = $variables['content'];

  $html  = '<table class="wow-tooltip-box">';
  $html .=   '<tr>';
  $html .=     '<td class="cell top left"></td>';
  $html .=     '<td class="cell top center"></td>';
  $html .=     '<td class="cell top right"></td>';
  $html .=   '</tr>';
  $html .=   '<tr>';
  $html .=     '<td class="cell middle left"></td>';
  $html .=     '<td class="cell middle center content">' . $content . '</td>';
  $html .=     '<td class="cell middle right"></td>';
  $html .=   '</tr>';
  $html .=   '<tr>';
  $html .=     '<td class="cell bottom left"></td>';
  $html .=     '<td class="cell bottom center"></td>';
  $html .=     '<td class="cell bottom right"></td>';
  $html .=   '</tr>';
  $html .= '</table>';

  return $html;
}
