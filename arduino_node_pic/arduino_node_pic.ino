#include <SoftwareSerial.h>//libreria para implementar mas de un puerto serial

SoftwareSerial serieVirtual(8,9);//pines de transmision puerto virtual (RX, TX)
int c = 0;
String datosPic;//variable para almacenar datos de pic

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//velocidad de transmision arduino-pc
  serieVirtual.begin(115200);//velocidad de transmision arduino-pic
  
}

void loop() {
  // envia tres numeros por el puerto serie:
  for(int i=0; i<=2; i++){
  Serial.println(c++, DEC);
  delay(1000);
  }

  //escucha si hay datos en el puerto serial virtual
  if(serieVirtual.available()){
      datosPic=serieVirtual.readString();//almacena datos provenientes del pic
    }
}
