#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8); //Rx: 7, Tx: 8

String datosSim900 = "undefined";
String datosPc = "undefined";

void setup() {
  sim900.begin(115200);
  Serial.begin(115200);

  sim900.print("AT\r");
  delay(200);
  sim900.println("AT+CMGF=1\r");
  delay(100);
  sim900.println("AT+CNMI=1,2,0,0,0\r");
  delay(100);
  sim900.println("AT+GMI\r");
  delay(100);
}

void loop() {
  if (sim900.available() != 0){
      datosSim900 = sim900.readString();
      delay(100);
      Serial.print(datosSim900);
      
    }
  if (Serial.available() > 0){
      datosPc = Serial.readString();
      delay(100);
      sim900.print(datosPc);
    }
}
