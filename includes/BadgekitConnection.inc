<?php

/**
 * @file
 * BadgekitConnection class.
 */

/**
 * Badgekit Connection class.
 */
class BadgekitConnection {

  public $method;

  public $path;

  public $key;

  public $token;

  public $url;

  public $response;

  /**
   * @param string $key
   */
  public function __construct($key = 'master') {
    $this->key = $key;
    $this->method = '';
    $this->path = '';
    $this->url = '';
  }


  /**
   * Connect to the BridgeKit API and attempt to return data
   */
  public function connect() {
    $this->setToken();

    // Retrieve data from the API
    $options = array(
      'http' => array(
        'header' => 'Authorization: JWT token="' . $this->token . '"'
      )
    );

    $this->response = json_decode(file_get_contents($this->url, false , stream_context_create($options)));
  }


  /**
   * Set method of API connection
   *
   * @param string $method
   */
  public function setMethod($method) {
    $this->method = $method;
  }


  /**
   * Set path of API connection
   *
   * @param string $path
   */
  public function setPath($path) {
    $this->path = $path;
    $this->url = 'https://still-dawn-1736.herokuapp.com' . $path;
  }


  /**
   * Set path of API connection
   */
  public function setToken() {
    $token_data = array(
      "key"    => $this->key,
      "exp"    => strtotime('+1 minute', time()),
      "method" => $this->method,
      "path"   => $this->path,
    );
    $secret = variable_get('badgekit_api_key', '');
    $this->token = JWT::encode($token_data, $secret);
  }


  /**
   * Gets all published badges
   *
   * @param string $system
   *  The system identifier
   *
   * @return array An array of badge objects
   */
  public function getBadges($system) {
    // Set up the JSON Web Token
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/badges');
    $this->connect();
    return $this->response->badges;
  }


  /**
   * Gets a specific system
   *
   * @param string $system
   *  The system identifier
   *
   * @return object A system object
   */
  public function getSystem($system) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system);
    $this->connect();
    return $this->response->system;
  }


  /**
   * Gets all systems
   *
   * @return array An array of system objects
   */
  public function getSystems() {
    // Set up the JSON Web Token
    $this->setMethod('GET');
    $this->setPath('/systems');
    $this->connect();
    return $this->response->systems;
  }


  /**
   * Gets all issuers for a specified system
   *
   * @param string $system
   *  The system identifier
   *
   * @param string $issuer
   *  The issuer identifier
   *
   * @return An issuer object
   */
  public function getIssuer($system, $issuer) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/issuers/' . $issuer);
    $this->connect();
    return $this->response->issuer;
  }


  /**
   * Gets all instances (awarded awards) for a specified system and badge
   *
   * @param string $system
   *  The system identifier
   *
   * @param string $badge
   *  The badge
   *
   * @return array An array of instance objects
   */
  public function getInstancesByBadge($system, $badge) {
    $this->setMethod('GET');

    $this->setPath('/systems/' . $system . '/badges/' . $badge . '/instances');
    $this->connect();
    return $this->response->instances;
  }


  /**
   * Gets all instances (awarded awards) for a specified system and email address
   *
   * @param string $system
   *  The system identifier
   *
   * @param string $email
   *  The user's email address
   *
   * @return array An array of instance objects
   */
  public function getInstancesByUser($system, $email) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/instances/' . $email);
    $this->connect();
    return $this->response->instances;
  }


  /**
   * Gets all issuers for a specified system
   *
   * @param string $system
   *  The system identifier
   *
   * @return array An array of issuer objects
   */
  public function getIssuers($system) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/issuers');
    $this->connect();
    return $this->response->issuers;
  }


  /**
   * Gets all milestones for a specified system
   *
   * @param string $system
   *  The system identifier
   *
   * @return array An array of milestone objects
   */
  public function getMilestones($system) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/milestones');
    $this->connect();
    return $this->response->milestones;
  }


  /**
   * Gets all programs for a specified system and issuer
   *
   * @param string $system
   *  The system identifier
   *
   * @param string $issuer
   *  The issuer identifier
   *
   * @return array An array of program objects
   */
  public function getPrograms($system, $issuer) {
    $this->setMethod('GET');
    $this->setPath('/systems/' . $system . '/issuers/' . $issuer . '/programs');
    $this->connect();
    return $this->response->programs;
  }

}