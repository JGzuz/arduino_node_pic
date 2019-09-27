#include <SoftwareSerial.h>

int botton22 = 22;//input pin digital 22 para un push boton 
int led_bufferPc = 23;
String node;

void setup() {
  // put your setup code here, to run once:
  //inicializando puertos seriales
  Serial.begin(115200);while(!Serial){;}//Para comunicacion con pc
  Serial1.begin(115200);while(!Serial){;}//Segunda comunicacion serie para el Modulo SIM800L
  pinMode(botton22, INPUT);
  pinMode(led_bufferPc, OUTPUT);
}

void loop() {
  // escucha datos de Serial1, del SIM800 y los envia por el Serial conenctado a pc: 
  if(Serial1.available()>0){//si hay datos en el buffer del serial
      Serial.print((char)Serial1.read());//lee los datos del serial1 y los imprime por Serial
    }

  if(digitalRead(botton22) == 1){
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

   //datos de node a arduino mega:
   if(Serial.available()){//si hay datos en el buffer del serial
      node=(char)Serial.read();
      if(node == "F"){
        digitalWrite(led_bufferPc, HIGH);
        }
      Serial1.print(node);
      //Serial.print("otra");
      //Serial.print("Vaca");
      //Serial1.println(node);//lee lo proviniente del puero Serial y la manda por el puerto Serial1
    }

}
