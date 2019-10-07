#include <SoftwareSerial.h>//Libreria para implementar mas de un puerto
SoftwareSerial Serial_sim(8,9);//configuracion puerto serie virtual (rx, tx)

const int led11 = 11;//Indicador que llego determinada cadena por 
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

  //cuando reciba datos del puerto Serial hardware de la pc
    if(Serial.available()){
        String data = (String)Serial.readStringUntil('\n');
        megaDato = data;
        datoNumerico = String(megaDato).toInt();
        //Serial.print(data);
        Serial.print(megaDato);
      }
      
    //cuando reciba datos por el puerto serie virtual del sim800L (simulado con otro arduino)
    if(Serial_sim.available()){
        Serial.print((char)Serial_sim.read());
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

    if(megaDato == "MSN_ENVIADO"){
        Serial_sim.print("1002");
        megaDato = "";
      }

    
    if(digitalRead(push5)==1){
        while(digitalRead(push5)==1){;}
        Serial.print("string do not problem");
      }

    if(digitalRead(push12)==1){
        while(digitalRead(push12)==1){;}
        Serial.print(megaDato);
      }

  }
