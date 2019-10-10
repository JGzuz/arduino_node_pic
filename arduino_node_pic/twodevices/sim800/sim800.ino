#include <SoftwareSerial.h>
SoftwareSerial Serial_sim(8,9);
int x = 0, count = 0;
const int led10 = 10;//indicador verifica que se envie de manera correcta una cadena
const int led6 = 6;//indicador que verifica que se envie de manera correcta una cadena
const int push12 = 12;//para enviar un numero de 10 digitos a la vez
const int push11 = 11;//para enviar una serie de numeros de 10 digitos
const int push7 = 7;//para verificar que es lo que se esta recibiendo por el puerto virtual
String megaDato;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial_sim.begin(115200);
  Serial.println("COMUNICACION ARD-PC, ARD-SIM INICIALIZADAS");
  pinMode(led10, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(push12, INPUT);
  pinMode(push11, INPUT);
  pinMode(push7, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial_sim.available()){
      Serial.print("Reciviendo datos por el puerto serial ");
      String data = (String)Serial_sim.readStringUntil('\n');
      megaDato = data;
      //Serial.print(data);
      Serial.println(megaDato);
    }
  if(megaDato == "1000"){
      digitalWrite(led10, HIGH);
      digitalWrite(led6, LOW);
      megaDato = "";
    }
  if(megaDato == "1001"){
      digitalWrite(led10, LOW);
      digitalWrite(led6, HIGH);
      megaDato = "";
    }

  if(megaDato == "1002"){count++;
      Serial.println("MSN_ENVIADO");
      Serial.println(count);
      digitalWrite(led10, HIGH);
      digitalWrite(led6, HIGH);
      delay(100);
      digitalWrite(led10, LOW);
      digitalWrite(led6, LOW);
      megaDato = "";
    }

  //enviar un dato a la vez
  if(digitalRead(push12)==1){
      while(digitalRead(push12)==1){;}
        switch(x){
          case 0: Serial_sim.println("1111111111");delay(100);/*Serial.println("1000000000");*/break;
          case 1: Serial_sim.println("1000000020");delay(100);/*Serial.println("1000000001");*/break;
          case 2: Serial_sim.println("1000000030");delay(100);/*Serial.println("1000000002");*/break;
          case 3: Serial_sim.println("1000000040");delay(100);/*Serial.println("1000000003");*/break;
          case 4: Serial_sim.println("1000000050");delay(100);/*Serial.println("1000000004");*/break;
          case 5: Serial_sim.println("1000000060");delay(100);/*Serial.println("1000000005");*/break;
          case 6: Serial_sim.println("1000000070");delay(100);/*Serial.println("1000000006");*/break;
          case 7: Serial_sim.println("1000000080");delay(100);/*Serial.println("1000000007");*/break;
          case 8: Serial_sim.println("1000000090");delay(100);/*Serial.println("1000000008");*/break;
          case 9: Serial_sim.println("1000000091");delay(100);/*Serial.println("1000000009");*/break;
          case 10: Serial_sim.println("1000000092");delay(100);/*Serial.println("1000000010");*/break;
          case 11: Serial_sim.println("1000000093");delay(100);/*Serial.println("1000000011");*/break;
          case 12: Serial_sim.println("1000000094");delay(100);/*Serial.println("1000000012");*/break;
        }x++; delay(200);if(x==12){x=0;}
        
    }

  //enviar 13 numeros de 10 digitos cada uno
  if(digitalRead(push11)==1){
      while(digitalRead(push11)==1){;}
      Serial_sim.println("1000000000");delay(100);/*Serial.println("1000000000");*/
      Serial_sim.println("1000000001");delay(100);/*Serial.println("1000000001");*/
      Serial_sim.println("1000000002");delay(100);/*Serial.println("1000000002");*/
      Serial_sim.println("1000000003");delay(100);/*Serial.println("1000000003");*/
      Serial_sim.println("1000000004");delay(100);/*Serial.println("1000000004");*/
      Serial_sim.println("1000000005");delay(100);/*Serial.println("1000000005");*/
      Serial_sim.println("1000000006");delay(100);/*Serial.println("1000000006");*/
      Serial_sim.println("1000000007");delay(100);/*Serial.println("1000000007");*/
      Serial_sim.println("1000000008");delay(100);/*Serial.println("1000000008");*/
      Serial_sim.println("1000000009");delay(100);/*Serial.println("1000000009");*/
      Serial_sim.println("1000000010");delay(100);/*Serial.println("1000000010");*/
      Serial_sim.println("1000000011");delay(100);/*Serial.println("1000000011");*/
      Serial_sim.println("1000000012");delay(100);/*Serial.println("1000000012");*/
    }

  //enviar un dato a la vez
  if(digitalRead(push7)==1){
      while(digitalRead(push7)==1){;}
      Serial.print(megaDato);
    }
  
}
