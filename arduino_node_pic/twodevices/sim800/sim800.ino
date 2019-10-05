#include <SoftwareSerial.h>
SoftwareSerial Serial_sim(8,9);

const int led10 = 10;
const int led6 = 6;
String megaDato;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial_sim.begin(115200);
  Serial.print("COMUNICACION ARD-PC, ARD-SIM INICIALIZADAS");
  pinMode(led10, OUTPUT);
  pinMode(led6, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial_sim.available()){
      Serial.print("Reciviendo datos por el puerto serial ");
      String data = (String)Serial_sim.readStringUntil('\n');
      megaDato = data;
      //Serial.print(data);
      Serial.print(megaDato);
    }
  if(megaDato == "333333"){
      digitalWrite(led10, HIGH);
      digitalWrite(led6, LOW);
    }
  if(megaDato == "222222"){
      digitalWrite(led10, LOW);
      digitalWrite(led6, HIGH);
    }
}
