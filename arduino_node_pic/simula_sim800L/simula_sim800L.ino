#include <SoftwareSerial.h>//libreria para utilizar un segundo puerto serial virtual
SoftwareSerial serieNodeDice(8,9);//(RX,TX)

int x = 0;
int pushBoton1 = 12;//variable aux para usar pin 12 como entrada
int pushBoton2 = 11;//push boton en pin 11
String datos_arduino; 
int led_sms = 10;//led indicador de envio de mensaje

void setup() {
  Serial.begin(115200);while(!Serial){;}
  serieNodeDice.begin(115200);//

  pinMode(pushBoton1, INPUT); //configura pin 12 como entrada
  pinMode(pushBoton2, INPUT); //configura pin 11 como entrada
  pinMode(led_sms, OUTPUT);//salida para led indicador de envio de mensaje
}

void loop() {
  //para enviar un dato a la vez
  if((digitalRead(pushBoton1))==1){
      delay(200);//para evitar rebote
      switch(x){
        case 0: serieNodeDice.println("1000000000");break;
        case 1: serieNodeDice.println("1000000001");break;
        case 2: serieNodeDice.println("1000000002");break;
        case 3: serieNodeDice.println("1000000003");break;
        case 4: serieNodeDice.println("1000000004");break;
        case 5: serieNodeDice.println("1000000005");break;
        case 6: serieNodeDice.println("1000000006");break;
        case 7: serieNodeDice.println("1000000007");break;
        case 8: serieNodeDice.println("1000000008");break;
        case 9: serieNodeDice.println("1000000009");break;
        case 10: serieNodeDice.println("1000000010");break;
        case 11: serieNodeDice.println("1000000011");break;
        case 12: serieNodeDice.println("1000000012");break;
        default: break;
      }x++; delay(1000);if(x==12){x=0;}
   }

   //para enviar una serie de datos consecutivos
   if(digitalRead(pushBoton2) == 1){
    delay(200);
      serieNodeDice.println("1000000000");delay(100);
      serieNodeDice.println("1000000001");delay(100);
      serieNodeDice.println("1000000003");delay(100);
      serieNodeDice.println("1000000004");delay(100);
      serieNodeDice.println("1000000005");delay(100);
      serieNodeDice.println("1000000006");delay(100);
      serieNodeDice.println("1000000007");delay(100);
      serieNodeDice.println("1000000008");delay(100);
      serieNodeDice.println("1000000009");delay(100);
      serieNodeDice.println("1000000010");delay(100);
      serieNodeDice.println("1000000011");delay(100);
      serieNodeDice.println("1000000012");delay(100);
      serieNodeDice.println("1000000013");delay(100);
    }

    //datos de retor de arduino de node
    
    if(serieNodeDice.available()){
        datos_arduino = (char)Serial.read();//leyendo datos de arduino_node
        //Serial.print(datos_arduino);//para reenviar a arduino_node y visualizar que le llego
        if(datos_arduino == "ON"){
            digitalWrite(led_sms, HIGH);
          }
        if(datos_arduino == "OFF"){
            digitalWrite(led_sms, LOW);
          }
      }
      

}
