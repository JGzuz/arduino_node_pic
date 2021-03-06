#include <SoftwareSerial.h>
SoftwareSerial sim900(7, 8); //Rx: 7, Tx: 8
char caracter;
String escogerRespuesta = "";
String datosSim="";
String datosPc="";
String numaux="4661016976";
String numeroCliente="";
String numeroRechar="";
const int led2 = 2;
const int led3 = 3; 
const int led4 = 4;

//para envio del msn
const int led5 = 5;//led5 indicador de que se envia el msn
const int push6 = 6;//push boton para enviar msn
const int push9 = 9;//push boton segundo boton 

void setup() {
  Serial.begin(19200);
  sim900.begin(19200);

  sim900.print("A\r");
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
  pinMode(led5, OUTPUT);//led indicador de envio de msn
  pinMode(push6, INPUT);//PUSH PARA ENVIAR MSN 
  pinMode(push9, INPUT);//PSUH PARA ENVIAR OTRO MSN
}

///////////////////////////////////////////////////////////////////////////////formato Incorrecto
void formatoIncorrecto(String numCli) {
    //Serial.println("Enviando SMS...");
    /*
    sim900.print("AT+CMGF=1\r");
    delay(200);
    */
    numCli = "AT+CMGS=\"" + numCli + "\"";
    
    sim900.println(numCli);
    delay(500);
    sim900.println("Formato incorrecto, envie un numero de 10 digitos sin espacios ni otros tipo de caracteres");//texto del sms
    delay(100);
    sim900.println((char)26);//comando de finilizacion 
    delay(100);
    sim900.println();
    delay(2000);
    //Serial.println("SMS enviado");
    numCli = "";
    digitalWrite(led4,LOW);
    digitalWrite(led3,LOW);
  }
///////////////////////////////////////////////////////////////////////////////formato Incorrecto

//********************************************************************************Recarga Exitosa
void RecargaExitosa(String numCli, String numRechRk) {
    
    numCli = "AT+CMGS=\"" + numCli + "\"";
    
    sim900.println(numCli);
    delay(500);
    sim900.println("El numero " + numRechRk + " se ha recargado exitosamente");//texto del sms
    delay(100);
    sim900.println((char)26);//comando de finilizacion 
    delay(100);
    sim900.println();
    delay(2000);
    
    numCli = "";
    digitalWrite(led4,LOW);
    digitalWrite(led3,LOW);
  }
//********************************************************************************Recarga Exitosa

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Numero no esta en la base
void NumNoBase(String numCli, String numRechRb) {
    
    numCli = "AT+CMGS=\"" + numCli + "\"";
    
    sim900.println(numCli);
    delay(500);
    sim900.println("El numero " + numRechRb + " no se encuentra en la base de datos");//texto del sms
    delay(100);
    sim900.println((char)26);//comando de finilizacion 
    delay(100);
    sim900.println();
    delay(2000);
    
    numCli = "";
    digitalWrite(led4,LOW);
    digitalWrite(led3,LOW);
  }
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Numero no esta en la base

//elegir la respuesta'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
void chooseOneMsn(String numbers){
    if(numbers.indexOf('R') >= 0){
        escogerRespuesta = numbers.substring(0,2);
        Serial.println();
        Serial.println(escogerRespuesta);
        digitalWrite(led4,HIGH);
        numeroCliente = numbers.substring(2,12);
        Serial.print(numeroCliente);
        if(numeroCliente == "4661016976"){digitalWrite(led3,HIGH);}
            if(escogerRespuesta == "RS"){formatoIncorrecto(numeroCliente);}
            if(escogerRespuesta == "RK"){
              numeroRechar = numbers.substring(12,22);
              RecargaExitosa(numeroCliente, numeroRechar);
              }
            if(escogerRespuesta == "RB"){
              numeroRechar = numbers.substring(12,22);
              NumNoBase(numeroCliente, numeroRechar);
              }
            datosPc="";
      }
  }
//elegir la respuesta'''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''

void loop() {
  //////////////////////////////////////////////////////////Puerto serie
  if (sim900.available()){
      datosSim = sim900.readString();
      Serial.print(datosSim);
      
    }
  if (Serial.available()){
      datosPc = Serial.readStringUntil('\n');
      //sim900.print("AT\r");
      sim900.print(datosPc);
      sim900.print("\r");
      chooseOneMsn(datosPc);
    }//////////////////////////////////////////////////////Puerto serie

  //simula recarga realizada correctamente*************Recarga correcta
  if(datosPc == "RECARGA_OK"){
      digitalWrite(led2, HIGH);
      delay(1000);
      
      sim900.print("AT+GSN\r");
      sim900.print("\r");
      digitalWrite(led2, LOW);
      datosPc = "";
    }//************************************************Recarga correcta

    
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>sim recarga fallida
  if(datosPc == "sf_send_msn"){
      digitalWrite(led3,HIGH);
      delay(1000);
      
      sim900.print("ATI\r");
      digitalWrite(led3, LOW);
      datosPc = "";
    }//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>sim recarga fallida

   //*****************************************************texto to long
   //para cuando el tamaño del texto es muy grande y no debe responder al msn
   if(datosPc == "sf_sin_msn"){
      digitalWrite(led4,HIGH);
      delay(1000);
      
      sim900.print("AT+GMI\r");
      digitalWrite(led4,LOW);
      datosPc = "";
    }//**************************************************texto to long
   
  
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<prueba el envio de sms
  if(digitalRead(push6)==1){
      delay(20);
      String thisNumCli = "4661016976";
      formatoIncorrecto(thisNumCli);
    }
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><>>prueba el envio de sms

  //############RS:formato incorrecto, RK: recarga exitosa, RB: numero no en la base de datos################
  
  //=============================================================================formato incorrecto
  /*
  if(datosPc == "RS4661016976"){
      Serial.println();
      digitalWrite(led4,HIGH);
      numeroCliente = datosPc.substring(2,12);
      Serial.print(numeroCliente);
      if(numeroCliente == "4661016976"){digitalWrite(led3,HIGH);}
      formatoIncorrecto(numeroCliente);
      datosPc="";
    }*/
  //=============================================================================================

  //recarga ok----------------------------------------------------------------recarga ok
  /*
  if(datosPc == "RK4661016976"){
      Serial.println();
      digitalWrite(led4,HIGH);
      numeroCliente = datosPc.substring(2,12);
      Serial.print(numeroCliente);
      if(numeroCliente == "4661016976"){digitalWrite(led3,HIGH);}
      RecargaExitosa(numeroCliente);
      datosPc="";
    }
    */
  //recarga ok----------------------------------------------------------------recarga ok

  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>NunNoBase
  /*
  if(datosPc == "RB4661016976"){
      Serial.println();
      digitalWrite(led4,HIGH);
      numeroCliente = datosPc.substring(2,12);
      Serial.print(numeroCliente);
      if(numeroCliente == "4661016976"){digitalWrite(led3,HIGH);}
      NumNoBase(numeroCliente);
      datosPc="";
    }
    */
  //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>NunNoBase
   /*
   //****************************************************segundo msn de prueba
   if(digitalRead(push9)==1){
      delay(20);
      numeroCliente = formatoPrueba.substring(3,12);
      respondeMsn();
      
    }
   //****************************************************segundo msn de prueba
   */
  
}
