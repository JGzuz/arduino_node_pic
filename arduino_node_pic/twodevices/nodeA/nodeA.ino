#include <SoftwareSerial.h>
SoftwareSerial Serial_sim(8,9);

const int led11 = 11;
const int led6 = 6;
String megaDato;
int long datoNumerico;

void setup() {
    Serial.begin(115200);
    Serial_sim.begin(115200);
    delay(50);
    Serial.print("COMUNICACION ARD-PC, ARD-SIM INICIALIZADAS");
    pinMode(led11, OUTPUT);
    pinMode(led6, OUTPUT);
    Serial_sim.print("1020120");
  } 

void loop() {
    if(Serial.available()){
        String data = (String)Serial.readStringUntil('\n');
        megaDato = data;
        datoNumerico = (int)megaDato;
        //Serial.print(data);
        Serial.print(megaDato);
      }

    if(megaDato == "A"){
      digitalWrite(led11, HIGH);
      digitalWrite(led6, LOW);
      Serial_sim.print("222222");
      //Serial_sim.print(megaDato);
      Serial_sim.print("");
      megaDato = "";
      }
      
    if(megaDato == "COCO"){
      digitalWrite(led6, HIGH);
      digitalWrite(led11, LOW);
      Serial_sim.print("333333");
      //Serial_sim.print(megaDato);
      Serial_sim.print("");
      megaDato = "";
      }
      
     switch (datoNumerico) {
      case 'COCO': break;
      }
      
  }
