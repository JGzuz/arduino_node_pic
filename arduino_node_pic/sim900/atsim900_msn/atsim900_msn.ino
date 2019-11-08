#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8); //Rx: 7, Tx: 8
char caracter;
String datosSim="";
String datosPc="";
const int led2 = 2;
const int led3 = 3; 
const int led4 = 4;

void setup() {
  Serial.begin(19200);
  sim900.begin(19200);

  sim900.print("A");
  delay(500);
  sim900.print("AT\r");
  delay(200);
  sim900.print("AT\r");
  delay(200);
  sim900.println("AT+CMGF=1\r");
  delay(100);
  sim900.println("AT+CNMI=1,2,0,0,0\r");
  delay(100);

  pinMode(led2, OUTPUT);//indicador pata verificar que los datos se reciban correctamente del puerto serial-pc
  pinMode(led3, OUTPUT);//RECARGA FALLIDA FORMATO INCORRECTO 
  pinMode(led4, OUTPUT);//MENSAJE EXCEDE TAMAÑO PERMITIDO PARA RESPONDER AL MSN
}

void loop() {
  if (sim900.available()){
      datosSim = sim900.readString();
      Serial.print(datosSim);
      
    }
  if (Serial.available()){
      datosPc = Serial.readStringUntil('\n');
      //sim900.print("AT\r");
      /*
      sim900.print(datosPc);
      sim900.print("\r");*/
    }

//simula recarga realizada correctamente
  if(datosPc == "RECARGA_OK"){
      digitalWrite(led2, HIGH);
      delay(1000);
      sim900.print("AT+GSN\r");
      sim900.print("\r");
      digitalWrite(led2, LOW);
      datosPc = "";
    }
//simula recarga fallida por formato incorrecto
  if(datosPc == "sf_send_msn"){
      digitalWrite(led3,HIGH);
      delay(1000);
      sim900.print("AT+ATI\r");
      digitalWrite(led3, LOW);
      datosPc = "";
    }

   //para cuando el tamaño del texto es muy grande y no debe responder al msn
   if(datosPc == "sf_sin_msn"){
      digitalWrite(led4,HIGH);
      delay(1000);
      sim900.print("AT+GMI\r");
      digitalWrite(led4,LOW);
      datosPc = "";
    }
   
  
  //verificar datos del puerto serie por hardware, pc a arduino
  
}
