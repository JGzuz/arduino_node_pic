#include <SoftwareSerial.h>
SoftwareSerial sim800L(8,9);
String valor="undefined";
String datosPc;
String imei="undefined";
int config_Start = 0;

int x = 0;

const int led12 = 12;
const int bjt4 = 4;//transistor 2n2222 conectado al pin 4
const int push3 = 3;
const int push2 = 2;
const int push5 = 5;
const int push6 = 6;

void getImei (){
    sim800L.print("AT+GSN\r");
    delay(10);
    Serial.print("Intentando obtener imei...");
    imei=sim800L.readString();
    Serial.print(imei);
    Serial.print(valor);
  }

void setup() {
  // put your setup code here, to run once:
  pinMode(led12, OUTPUT);
  pinMode(bjt4, OUTPUT);
  pinMode(push3, INPUT);
  pinMode(push2, INPUT);
  pinMode(push5, INPUT);
  pinMode(push6, INPUT);
  
  Serial.begin(115200);
  sim800L.begin(115200);

  sim800L.print("AT\r");
  delay(200);

  sim800L.println("AT+CMGF=1\r");
  delay(100);
  
  sim800L.println("AT+CNMI=1,2,0,0,0\r");
  delay(100);

  //UWU EL COMANDO: AT+CMGR=1 SE USA PARA LEER UN MSN ANTIGUO
  /*
  sim800L.println("ATI");
  delay(2000);

  sim800L.println("AT+IPR?");
  delay(2000);

  sim800L.println("AT+ICF=?");
  delay(2000);

  sim800L.println("AT+GSN");
  delay(2000);*/
  sim800L.print("AT\r");
  delay(200);
  
}

void loop() {

  
  
  if(sim800L.available() != 0){

      valor = sim800L.readString();
      delay(100);
      Serial.print(valor);
      delay(100);//descomnetar para ver en monitor serie arduino
    }

  if(Serial.available()){
    datosPc = Serial.readString();
    delay(100);
    /*
    Serial.print(datosPc);
    delay(100);*///descomentar para ver en arduino
    sim800L.print(datosPc);
    }
  
  if(digitalRead(push3)==1){
      while(digitalRead(push3)==1){;}
      digitalWrite(bjt4, HIGH);
    }

  if(digitalRead(push2)==1){
      while(digitalRead(push2)==1){;}
      digitalWrite(bjt4, LOW);
      Serial.print("+CMT: -4761016976-,--,-19/10/25,01:43:24-20-  4451882040");      
    }
  if(digitalRead(push5)==1){
      while(digitalRead(push5)==1){;}
      valor = sim800L.readString();
      delay(100);
      Serial.println(valor);
      delay(100);
    }

  if(digitalRead(push6)==1){
      while(digitalRead(push6)==1){;}
      Serial.println(valor);
      delay(100);
    }
}
