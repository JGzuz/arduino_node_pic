#include <SoftwareSerial.h>
SoftwareSerial Serial_sim(8,9);

const int led11 = 11;
const int led6 = 6;
const int push12 = 12;
const int push5 = 5;
String megaDato;
unsigned long datoNumerico = 0;

void setup() {
    Serial.begin(115200);
    Serial_sim.begin(115200);
    delay(50);
    Serial.println("COMUNICACION ARD-PC, ARD-SIM INICIALIZADAS");
    pinMode(led11, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(push12, INPUT);
    pinMode(push5, INPUT);
    Serial_sim.print("123");Serial_sim.print(456);Serial_sim.write("ABC");
  } 

void loop() {
    if(Serial.available()){
        String data = (String)Serial.readStringUntil('\n');
        megaDato = data;
        datoNumerico = String(megaDato).toInt();
        //Serial.print(data);
        Serial.print(megaDato);
      }

    if(megaDato == "ATC_SEND"){
      digitalWrite(led11, HIGH);
      digitalWrite(led6, LOW);
      Serial_sim.print("1000");
      //Serial_sim.print(megaDato);
      Serial_sim.print("");
      megaDato = "";
      }

    if(megaDato == "ATC_WRITE"){
      digitalWrite(led6, HIGH);
      digitalWrite(led11, LOW);
      Serial_sim.print("1001");
      //Serial_sim.print(megaDato);
      Serial_sim.print("");
      megaDato = "";
      }

    if(digitalRead(push5)==1){
        while(digitalRead(push5)==1){;}
        //Serial.print(megaDato);
        Serial_sim.print('A');
        //Serial_sim.print('ABC');
        //Serial_sim.print("dfg");
      }

    if(digitalRead(push12)==1){
        while(digitalRead(push12)==1){;}
        Serial.print(datoNumerico);
      }

    //CONVERTIR CADENA A CHAR PARA ENVIAR
      
     /*switch (datoNumerico) {
      case 1001: Serial_sim.print("CAYO"); break;
      case 1002: break;
      case 1003: break;
      case 1004: break;
      case 1005: break;
      case 1006: break;
      case 1007: break;
      default: break; 
      }*/
      
  }
