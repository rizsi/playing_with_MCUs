/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */

#include <SPI.h>
#include <Ethernet.h>
#include <avr/pgmspace.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);
EthernetClient client;

typedef struct {
} marker_progmem_struct;

#define MPSTR(s) ((const marker_progmem_struct *) PSTR(s))

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

#define low(x)   ((x) & 0xFF)
#define high(x)   (((x)>>8) & 0xFF)

void myprint(const marker_progmem_struct * str)
{
	PGM_P * p=(PGM_P*) str;
	while(1)
	{
		uint16_t w=pgm_read_word(p);
		uint8_t c=low(w);
		if(c==0) return;
		client.write(c);
		c=high(w);
		if(c==0) return;
		client.write(c);
		p++;
	}
}


void loop() {
  // listen for incoming clients
  client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
//		myprint(MPSTR("HTTP/1.1 200 OK\n"));
          myprint(MPSTR("HTTP/1.1 200 OK\nContent-Type: text/html\nConnection: close\nRefresh: 5\n\n"));  // refresh the page automatically every 5 sec
          myprint(MPSTR("<!DOCTYPE HTML>"));
          myprint(MPSTR("<html>CICA!<br/>"));

          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            myprint(MPSTR("analog input "));
            client.print(analogChannel);
            myprint(MPSTR(" is "));
            client.print(sensorReading);
            myprint(MPSTR("<br />"));
          }
          myprint(MPSTR("</html>"));
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

