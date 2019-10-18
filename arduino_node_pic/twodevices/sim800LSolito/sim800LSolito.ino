#include <SoftwareSerial.h>
SoftwareSerial sim800L(8,9);
String valor;
String datosPc;

const int led13 = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  sim800L.begin(115200);

  sim800L.println("AT+CMGF=1");
  delay(100);
  
  sim800L.println("AT+CNMI=1,2,0,0,0");
  delay(100);
  /*
  sim800L.println("ATI");
  delay(2000);

  sim800L.println("AT+IPR?");
  delay(2000);

  sim800L.println("AT+ICF=?");
  delay(2000);

  sim800L.println("AT+GSN");
  delay(2000);*/
}

void loop() {
  if(sim800L.available()){
    valor = sim800L.readString();
    delay(100);
    Serial.println(valor);
    delay(100);
    }

  if(Serial.available()){
    datosPc = Serial.readString();
    delay(100);
    Serial.print(datosPc);
    delay(100);
    sim800L.print(datosPc);
    }
  

}
