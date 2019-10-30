#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8); //Rx: 7, Tx: 8
char caracter;

void setup() {
  Serial.begin(19200);
  sim900.begin(19200);

  sim900.print("A");
  delay(500);
  sim900.print("AT\r");
  delay(200);
  sim900.print("AT\r");
  delay(200);
  sim900.println("AT+CMGF=1\r");
  delay(100);
  sim900.println("AT+CNMI=1,2,0,0,0\r");
  delay(100);
  
}

void loop() {
  if (sim900.available()){
      caracter = sim900.read();
      Serial.print(caracter);
    }
  if (Serial.available()){
      caracter = Serial.read();
      sim900.print(caracter);
    }
}