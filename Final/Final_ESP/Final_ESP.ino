#define BLYNK_PRINT Serial 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "bb23daf3c125442a906576b3d5a47713";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Ruiz";
char pass[] = "_Cielo422494";
BLYNK_WRITE(V1){
  // variable declarations
  int x = param[0].asInt();    // x direction value
  int y = param[1].asInt();   // y direction value

  // turning data into percentages
  x /= 100;
  y /= 100;
  
  // left & right wheel percentage calculations
  x = -x;
  int v = (100-abs(x)) * y/100 + y;
  int w = (100-abs(y)) * x/100 + x;
  int r = (v+w) / 2;
  int l = (v-w) / 2;
  
  // sending joystick data onto Atmega328p
  Serial.write(l);
  Serial.write('l');
  Serial.write(r);
  Serial.write('r');
}

void setup(){
  Serial.begin(9600);       // setup UART
  Blynk.begin(auth, ssid, pass);  // setup Wi-Fi authentication
  Serial.write('<');        // send '<' for read ready
}

void loop(){
  Blynk.run();  // run Blynk
}
