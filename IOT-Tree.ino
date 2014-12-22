/* 

This scripts sets the Arduino up as
a Rest-device which can trigger two relays, and two buttons on a remote control wired to them, to fire from urls:
 
http://[Arduino IP Address]/digital/7/0 and /6/0
 
My son Dylan and I made a local-network hosted webpage with a couple of large ON OFF buttons to control a string of Christmas Tree lights. Button press called a javascript which in turn fed a php file with the URL information for a Curl call to the arduino. 

Works only for devices on the same SSID. 

Written by Brian Fitzgerald and Dylan Fitzgerald. 

Based on a simple example of the aREST Library for Arduino (Uno/Mega/Due/Teensy)
using the CC3000 WiFi chip wich was written in 2014 by Marco Schwartz under a GPL license. 
*/

// Import required libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include <CC3000_MDNS.h>
#include <aREST.h>
#include <avr/wdt.h>

// These are the pins for the CC3000 chip if you are using a breakout board
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Create CC3000 instance
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2);
// Create aREST instance
aREST rest = aREST();

// Your WiFi SSID and password                                         
#define WLAN_SSID       "YOUR SSID NAME HERE"
#define WLAN_PASS       "YOUR SSID PASSWORD HERE"
#define WLAN_SECURITY   WLAN_SEC_WPA2
int OnSwitch = 7;
int OffSwitch = 6;


// The port to listen for incoming TCP connections 
#define LISTEN_PORT           80

// Server instance
Adafruit_CC3000_Server restServer(LISTEN_PORT);

// DNS responder instance
MDNSResponder mdns;



void setup(void)
{  
  // Start Serial
  Serial.begin(115200);
pinMode(OnSwitch, OUTPUT);
pinMode(OffSwitch, OUTPUT);

//The Songle Relay we use is off when the pin is set HIGH. These pins should
//remain high as default state to conserve battery on the remote control.

digitalWrite(OnSwitch, HIGH);
digitalWrite(OffSwitch, HIGH);
  // Give name and ID to device
  rest.set_id("008");
  rest.set_name("Meow_Meow");
  
  // Set up CC3000 and get connected to the wireless network.
  if (!cc3000.begin())
  {
    while(1);
  }
  if (!cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY)) {
    while(1);
  }
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }
  Serial.println();
  
  // Print CC3000 IP address. Enable if mDNS doesn't work
  while (! displayConnectionDetails()) {
   delay(1000);
  }
  
  // Start multicast DNS responder
  if (!mdns.begin("arduino", cc3000)) {
    while(1); 
  }
   
  // Start server
  restServer.begin();
  Serial.println(F("Listening for connections..."));

  // Enable watchdog
  wdt_enable(WDTO_4S);
}

void loop() {
  
  // Handle any multicast DNS requests
  mdns.update();
  
  // Handle REST calls
  Adafruit_CC3000_ClientRef client = restServer.available();
  rest.handle(client);
  wdt_reset();

  // Check connection, reset if connection is lost
  if(!cc3000.checkConnected()){while(1){}}
  wdt_reset();
 
}

// Print connection details of the CC3000 chip
bool displayConnectionDetails(void)
{
  uint32_t ipAddress, netmask, gateway, dhcpserv, dnsserv;
  
  if(!cc3000.getIPAddress(&ipAddress, &netmask, &gateway, &dhcpserv, &dnsserv))
  {
    Serial.println(F("Unable to retrieve the IP Address!\r\n"));
    return false;
  }
  else
  {
    Serial.print(F("\nIP Addr: ")); cc3000.printIPdotsRev(ipAddress);
    Serial.print(F("\nNetmask: ")); cc3000.printIPdotsRev(netmask);
    Serial.print(F("\nGateway: ")); cc3000.printIPdotsRev(gateway);
    Serial.print(F("\nDHCPsrv: ")); cc3000.printIPdotsRev(dhcpserv);
    Serial.print(F("\nDNSserv: ")); cc3000.printIPdotsRev(dnsserv);
    Serial.println();
    return true;
  }
}

