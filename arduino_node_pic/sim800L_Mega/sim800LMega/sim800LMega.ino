#include <SoftwareSerial.h>

int x = 0;//contador para enviar una cadena a la vez
int botton1 = 12;//boton para enviar un cadena a la vez
int botton2 = 11;//boton para enviar varias cadenas a la vez
int led_sms = 10;//led indicador para enviar mensaje
int led_buffer = 9;//led indicar que hay datos disponibles en buffer
String datos_arduino;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);while(!Serial){;}

  pinMode(botton1, INPUT);
  pinMode(botton2, INPUT);
  pinMode(led_sms, OUTPUT);
  pinMode(led_buffer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if((digitalRead(botton1))==1){
      delay(200);//para evitar rebote
      switch(x){
        case 0: Serial.println("1000000000");break;
        case 1: Serial.println("1000000001");break;
        case 2: Serial.println("1000000002");break;
        case 3: Serial.println("1000000003");break;
        case 4: Serial.println("1000000004");break;
        case 5: Serial.println("1000000005");break;
        case 6: Serial.println("1000000006");break;
        case 7: Serial.println("1000000007");break;
        case 8: Serial.println("1000000008");break;
        case 9: Serial.println("1000000009");break;
        case 10: Serial.println("1000000010");break;
        case 11: Serial.println("1000000011");break;
        case 12: Serial.println("1000000012");break;
        default: break;
      }x++; delay(1000);if(x==12){x=0;}
   }

  //envia una serie de nuemeros por el puerto Serial
  if(digitalRead(botton2) == 1){
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

   //si hay datos disponibles en el puerto serial
   if(Serial.available()){
      datos_arduino = (char)Serial.read();
      
      if(datos_arduino == "CARRO"){
          digitalWrite(led_sms, HIGH);
        }
      if(datos_arduino == "LED_OFF"){
          digitalWrite(led_sms, LOW);
        }
    }
   
}
