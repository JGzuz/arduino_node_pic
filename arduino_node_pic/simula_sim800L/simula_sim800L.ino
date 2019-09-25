#include <SoftwareSerial.h>//libreria para configurar un puerto virtual serie
SoftwareSerial serie_sim(8,9); //configuracion puerto virtual, (RX, TX)
int x = 0;
int pushBoton1 = 12;//variable aux para usar pin 12 como entrada
int pushBoton2 = 11;//push boton en pin 11

void setup() {
  serie_sim.begin(115200);
  pinMode(pushBoton1, INPUT); //configura pin 12 como entrada
  pinMode(pushBoton2, INPUT); //configura pin 11 como entrada
}

void loop() {
  //para enviar un dato a la vez
  if((digitalRead(pushBoton1))==1){
      delay(200);//para evitar rebote
      switch(x){
        case 0: serie_sim.println("1000000000");break;
        case 1: serie_sim.println("1000000001");break;
        case 2: serie_sim.println("1000000002");break;
        case 3: serie_sim.println("1000000003");break;
        case 4: serie_sim.println("1000000004");break;
          
      }x++; delay(1000);if(x==5){x=0;}
   }

   //para enviar una serie de datos consecutivos
   if(digitalRead(pushBoton2) == 1){
    delay(200);
      serie_sim.println("1000000000");delay(100);
      serie_sim.println("1000000001");delay(100);
      serie_sim.println("1000000003");delay(100);
      serie_sim.println("1000000004");delay(100);
      serie_sim.println("1000000005");delay(100);
      serie_sim.println("1000000006");delay(100);
      serie_sim.println("1000000007");delay(100);
      serie_sim.println("1000000008");delay(100);
      serie_sim.println("1000000009");delay(100);
      serie_sim.println("1000000010");delay(100);
      serie_sim.println("1000000011");delay(100);
      serie_sim.println("1000000012");delay(100);
      serie_sim.println("1000000013");delay(100);
    }

}
