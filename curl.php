<?php

  $pin = $_GET['pin'];
  $state = $_GET['state'];
  // Create cURL call
//  $service_url = 'http://arduino.local/digital/' . $pin . '/' . $state;
// The MDNS service kept failing for unknown reasons for me -- I substituted 
//arduino.local for the IP of the Arduino and all was well. 
//Substitute the IP address below in TWO places with the IP addressType
//of your Arduino device 
$service_url = 'http://192.168.0.15/digital/' . $pin . '/' . $state;

  $curl = curl_init($service_url);
  
    
  // Send cURL to Yun board

  curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 ); 
  $curl_response = curl_exec($curl);
  curl_close($curl);

  //Print answer
  echo $curl_response;
  //Now wait 1 second and turn that pin OFF: you only need a short burst
  //to fire the infrared signal, and you don't want to leave the 
  //remote in a perpetual ON state: you'll kill your battery.
  sleep(1); 
  $service_url = 'http://192.168.0.15/digital/' . $pin . '/1';
  $curl = curl_init($service_url);
    // Send cURL to Yun board

  curl_setopt($curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4 ); 
  $curl_response = curl_exec($curl);
  curl_close($curl);

  //Print answer. Dance Like nobody's looking.
  echo $curl_response;

?>