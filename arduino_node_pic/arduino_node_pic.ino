#include <SoftwareSerial.h>//libreria para implementar mas de un puerto serial
SoftwareSerial serieNode(8,9);//configuracion puerto serie virtual (RX, TX)


void setup() {
  Serial.begin(115200);while(!Serial){;}//configuracion velocidad de transmision
  //arduino-pc, espera hasta que la comunicacion se haya establecido
  Serial.println("Comunicacion arduino-pc establecida");

  serieNode.begin(115200);//velocidad de transmison puerto virtual serie
  serieNode.println("Puerto virtual inicializado");
  
}

void loop() {
  if(serieNode.available()>0){
      Serial.print((char)serieNode.read());
    }
}
