#include <SoftwareSerial.h>//libreria para utilizar un segundo puerto serial virtual
SoftwareSerial serieNodeDice(8,9);//(RX,TX)

int x = 0;
int pushBoton1 = 12;//variable aux para usar pin 12 como entrada
int pushBoton2 = 11;//push boton en pin 11
int pb_verificar = 7;//push boton
char datos_arduino = "undefine"; 
char aux;
int led_sms = 10;//led indicador de envio de mensaje

void setup() {
  Serial.begin(115200);while(!Serial){;}
  serieNodeDice.begin(115200);//velocidad de trasnision puerto virtual

  pinMode(pushBoton1, INPUT); //configura pin 12 como entrada
  pinMode(pushBoton2, INPUT); //configura pin 11 como entrada
  pinMode(led_sms, OUTPUT);//salida para led indicador de envio de mensaje
  pinMode(pb_verificar, INPUT);//pin coomo entra, cuando es igual a 1 => envia 1 cadena a arduinoNode

  Serial.println("modulo sim800L LISTO!!");
}

void loop() {
  //para enviar un dato a la vez
  if((digitalRead(pushBoton1))==1){
      delay(200);//para evitar rebote
      switch(x){
        case 0: serieNodeDice.println("1000000000");delay(100);Serial.println("1000000000");break;
        case 1: serieNodeDice.println("1000000001");Serial.println("1000000001");break;
        case 2: serieNodeDice.println("1000000002");Serial.println("1000000002");break;
        case 3: serieNodeDice.println("1000000003");Serial.println("1000000003");break;
        case 4: serieNodeDice.println("1000000004");Serial.println("1000000004");break;
        case 5: serieNodeDice.println("1000000005");Serial.println("1000000005");break;
        case 6: serieNodeDice.println("1000000006");Serial.println("1000000006");break;
        case 7: serieNodeDice.println("1000000007");Serial.println("1000000007");break;
        case 8: serieNodeDice.println("1000000008");Serial.println("1000000008");break;
        case 9: serieNodeDice.println("1000000009");Serial.println("1000000009");break;
        case 10: serieNodeDice.println("1000000010");Serial.println("1000000010");break;
        case 11: serieNodeDice.println("1000000011");Serial.println("1000000011");break;
        case 12: serieNodeDice.println("1000000012");Serial.println("1000000012");break;
        default: break;
      }x++; delay(1000);if(x==12){x=0;}
   }

   //para enviar una serie de datos consecutivos
   if(digitalRead(pushBoton2) == 1){
    delay(200);
      serieNodeDice.println("1000000000");Serial.println("1000000000");delay(100);
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

    //reenvia los datos del arduino conectado a node para verificar que es lo que le esta llegando a este pic
    if((digitalRead(pb_verificar)) == 1){
        
      }

    //leer datos del arduino conectado a node
    if(serieNodeDice.available()){
        
        char dato = (char)serieNodeDice.read();delay(5);
        
        //char dato2 = (char)serieNodeDice.read();
        Serial.print(dato);
        //Serial.println(dato2);
        
      }
      

}
