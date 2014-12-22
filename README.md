An Arduino REST API project to fire two relays via GET HTTP calls. Project originated by my 10 year old son wanting to turn the Christmas Tree lights off with his phone. Connected relays to the buttons on a remote controlled infrared mains socket, created a web page/Javascript/Curl combination to set Arduino digtial pins 6 and 7 high and low with GET calls to http://[IP ADDRESS OF ARDUINO]/digital/7/1 /7/0  and /6/1 and /6/0

Based on the Arduino REST API by Mark Schwartz. https://learn.adafruit.com/a-rest-api-for-arduino-and-the-cc3000-wifi-chip/overview
