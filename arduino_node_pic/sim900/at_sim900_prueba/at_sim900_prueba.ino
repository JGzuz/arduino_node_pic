#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8); //Rx: 7, Tx: 8
char caracter;

void setup() {
  Serial.begin(19200);
  sim900.begin(19200);

  sim900.print("AT\r");
  delay(200);
  sim900.print("AT+CMFG=1\r");
  delay(200);
  
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
