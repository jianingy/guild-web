<?php

include_once('xml2array.inc');

class iArmory {
  private $armory = 'http://tw.wowarmory.com';
  private $lang = 'zh_TW';
  private $timeout = 30;
  private $user_agent = 'Mozilla/5.0 (Macintosh; U; Intel Mac OS X 10.6; en-US; rv:1.9.2.6) Gecko/20100625 Firefox/3.6.6';

  public function __construct($armory, $lang = NULL) {
    $this->armory = rtrim($armory, "/");
    !is_null($lang) && $this->lang = $lang;
  }

  public static function get_regions() {
    return array(
      'www' => 'Americas',
      'cn'  => 'China',
      'eu'  => 'Europe',
      'kr'  => 'Korea',
      'tw'  => 'Taiwan',
    );
  }

  public static function get_langs() {
    return array(
      'de_DE' => 'Dutch',
      'en_US' => 'English (US)',
      'en_GB' => 'English (EU)',
      'es_MX' => 'Spanish (AL)',
      'es_ES' => 'Spanish (EU)',
      'fr_FR' => 'French',
      'ru_RU' => 'Kazakh',
      'ko_KR' => 'Korean',
      'zh_CN' => 'Simplified Chinese',
      'zh_TW' => 'Traditional Chinese',
    );
  }

  /**
   * Setters and getters.
   */
  public function set_armory($armory) {
    $this->armory = rtrim($armory, "/");
  }

  public function set_lang($lang) {
    $this->lang = $lang;
  }

  /**
   * The only interface to send out a request
   * @param string $url the dest url
   */
  public function send_request($url) {
    $cookie = "cookieLangId=$this->lang;";

    $ch = curl_init($url);
    curl_setopt_array($ch, array(
      CURLOPT_RETURNTRANSFER => TRUE,
      CURLOPT_USERAGENT      => $this->user_agent,
      CURLOPT_COOKIE         => $cookie,
      CURLOPT_TIMEOUT        => $this->timeout,
    ));

    $response = curl_exec($ch);
    
    // Handler cURL errors.
    if (FALSE === $response) {
      throw new Exception('Failed loading data from WoW Armory. CURL error: ' . curl_error($ch) . '.');
      curl_close($ch);
    }

    curl_close($ch);
    return $response;
  }

  public function make_url($path, $query = array()) {
    $url = $this->armory . '/' . $path;

    if (count($query) > 0) {
      $params = array();

      foreach ($query AS $key => $value) {
        // For better readability of paths in query strings, we decode slashes.
        $params[] = $key . '=' . str_replace('%2F', '/', rawurlencode($value));
      }

      $url .= ('?' . implode('&', $params));
    }

    return $url;
  }
  
  /**
   * Get item info by id
   * @param integer $id the item id
   * @param string $format 'html' or 'xml'
   * @return string $return XML or HTML response
   */
  public function get_item_tooltip_by_id($id, $format = 'html') {
    $query = array('i' => $id);
    if ('html' == $format) {
      $query['rhtml'] = 'y';
    }
    $url = $this->make_url('item-tooltip.xml', $query);

    return $this->send_request($url);
  }

  /**
   * Get item id by name
   * @param string $name the item name
   * @return integer $item_id 
   */
  public function get_item_id_by_name($name) {
    $url = $this->make_url('search.xml', array(
      'searchQuery' => $name,
      'searchType' => 'items',
    ));
    $xmlstr = $this->send_request($url);

    // Parsing XML data.
    libxml_use_internal_errors(true);
    $xml = simplexml_load_string($xmlstr);

    if (!$xml) {
      $err_msgs = array();
      foreach (libxml_get_errors() AS $error) {
        $err_msgs[] = trim($error->message);
      }

      throw new Exception('Failed parsing XML data from WoW Armory. HTTP Response: ' . $xmlstr . '. Error messages: ' . implode('; ', $err_msgs) . '.');
    }

    // Check if we get any results.
    if (0 == $xml->armorySearch->tabs->attributes()->count) {
      return FALSE;
    }
    
    $items = $xml->armorySearch->searchResults->items->item;
    foreach ($items AS $item) {
      if ($name == $item->attributes()->name) {
        return (int)$item->attributes()->id;
      }
    }

    return FALSE;
  }

  /**
   * Get item info by name, this function firstly gets item id then it
   * calls get_item_by_id() internally.
   * @param string $name the item name
   * @param string $format 'html' or 'xml'
   * @return string $return XML or HTML response
   */
  public function get_item_tooltip_by_name($name, $format = 'html') {
    $item_id = $this->get_item_id_by_name($name);
    return $this->get_item_tooltip_by_id($item_id, $format);
  }

  public function get_character($realm, $name) {
    $url = $this->make_url('character-sheet.xml', array(
      'r' => $realm,
      'cn' => $name,
    ));
    $xmlstr = $this->send_request($url);

    return xml2array($xmlstr);
  }

}

