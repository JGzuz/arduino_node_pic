#include <SoftwareSerial.h>//libreria para configurar un puerto virtual serie
SoftwareSerial serie_sim(8,9); //configuracion puerto virtual, (RX, TX)
int x = 0;
int pushBoton1 = 12;//variable aux para usar pin 12 como entrada

void setup() {
  serie_sim.begin(115200);
  pinMode(pushBoton1, INPUT); //configura pin 12 como entrada
}

void loop() {
  if((digitalRead(pushBoton1))==1){
      switch(x){
        case 0: serie_sim.println("012345678912445236521245215254125412542");break;
        case 1: serie_sim.println("1111111111");break;
        case 2: serie_sim.println("2222222222");break;
        case 3: serie_sim.println("3333333333");break;
        case 4: serie_sim.println("4444444444");break;
          
      }x++; delay(1000);if(x==5){x=0;}
    }

}
