#include <SoftwareSerial.h>
SoftwareSerial sim800L(8,9);
String valor;
String datosPc;

int x = 0;

const int led13 = 13;
const int bjt4 = 4;//transistor 2n2222 conectado al pin 4
const int push3 = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, INPUT);
  Serial.begin(115200);
  sim800L.begin(115200);

  sim800L.print("AT\r");
  delay(100);

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
  
  if(digitalRead(push3)==1){
      while(digitalRead(push3)==1){;}
      if(x==0){digitalWrite(bjt4, HIGH); x=1;}
      if(x==1){digitalWrite(bjt4,LOW); x=0;}
    }

}
