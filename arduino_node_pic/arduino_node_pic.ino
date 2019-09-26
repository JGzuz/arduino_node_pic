#include <SoftwareSerial.h>//libreria para implementar mas de un puerto serial
SoftwareSerial serieNode(8,9);//configuracion puerto serie virtual (RX, TX)

int push12 = 12;
int led11 = 11;
String node;
void setup() {
  Serial.begin(115200);while(!Serial){;}//configuracion velocidad de transmision
  //arduino-pc, espera hasta que la comunicacion se haya establecido
  //Serial.println("Comunicacion arduino-pc establecida");

  serieNode.begin(115200);//velocidad de transmison puerto virtual serie
  //serieNode.println("Puerto virtual inicializado");
  delay(800);
  pinMode(push12, INPUT);
  pinMode(led11, OUTPUT);

  serieNode.println("4661016969");
  
}

void loop() {

  //escucha datos en puerto serial virtual
  if(serieNode.available()>0){
      Serial.print((char)serieNode.read());
      
    }

  //escucha puerto serial
  if(Serial.available()>0){
      //delay(2000);
      serieNode.print("4014");
      node=((String)Serial.read());
      serieNode.print(node);
      if(node == "LED_ON"){digitalWrite(led11, HIGH);}
      if(node == "LED_OFF"){digitalWrite(led11, HIGH);}  
    }
    
  if(digitalRead(push12) == 1){
      delay(200);
      Serial.println("1000000000");delay(100);
      Serial.println("1000000001");delay(100);
      Serial.println("1000000003");delay(100);
      Serial.println("1000000004");delay(100);
      Serial.println("1000000005");delay(100);
      Serial.println("1000000006");delay(100);
      Serial.println("1000000007");delay(100);
      Serial.println("1000000008");delay(100);
      Serial.println("1000000009");delay(100);
      Serial.println("1000000010");delay(100);
      Serial.println("1000000011");delay(100);
      Serial.println("1000000012");delay(100);
      Serial.println("1000000013");delay(100);
    }
    
}
