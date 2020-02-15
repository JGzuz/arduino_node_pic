#include <Adafruit_Fingerprint.h>
SoftwareSerial mySerial(9,10);
SoftwareSerial sim900(7,8);
//declaraciones y definiciones
#define buttonRegistrar 2
#define buttonAsistencia 3
#define ledCancelar 4
#define buttonCancelar 6
#define ledRegistrar 11
#define ledAsistencia 12
#define ledSendMsn 13

String datosSim = "";
String datosPc = "";
String numAux = "4661016976";
String escogerRespuesta = "";
String numeroChecador = "";//para guardar el numero del checador en cadena
String verify = "gsmOkQ";
String id_persona = "";

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int checarHuella=0;
uint8_t id;
byte flagAsistencia = 0;
byte flagRegistrar = 0;

void setup() 
{
  pinMode(buttonRegistrar, INPUT);                     
  pinMode(buttonAsistencia, INPUT);
  pinMode(buttonCancelar, INPUT);
  pinMode(ledRegistrar, OUTPUT);                       
  pinMode(ledAsistencia, OUTPUT);
  pinMode(ledCancelar,OUTPUT);
  pinMode(ledSendMsn, OUTPUT);

  digitalWrite(ledSendMsn, LOW);
  digitalWrite(ledRegistrar, LOW);                     
  digitalWrite(ledAsistencia, LOW);
  digitalWrite(ledCancelar, LOW);

  Serial.begin(57600);
  while (!Serial);  // For Yun/Leo/Micro/Zero/...

  startSim900();
  delay(100);
  
 
}

void loop() {
  //Rutina de chequeo de asistencia////////////////////////////////////////////////////////////
  if(digitalRead(buttonAsistencia)==0){flagAsistencia = 1;startSensorHuellas();Serial.println("Entro a rutina de chequeo");}
  if( (flagAsistencia == 1) ){
      digitalWrite(ledAsistencia,HIGH);
      if(digitalRead(buttonCancelar) == 0){
        startSim900();
        flagAsistencia = 0;
        Serial.println("salio de rutina de chequeo");digitalWrite(ledAsistencia,LOW);
        digitalWrite(ledCancelar,HIGH);delay(50);digitalWrite(ledCancelar,LOW);
        }
      checarHuella = getFingerprintIDez();
      Serial.println(checarHuella);
      if(checarHuella > 0){startSim900();delay(100);enviarId(verify, checarHuella);startSensorHuellas();}
      
      delay(50);
    }

  //Rutina de registro de usuario////////////////////////////////////////////////////
  if(digitalRead(buttonRegistrar)==0){
    flagRegistrar = 1;
    //Serial.println("Entro a rutina de registro");
    }
  if(flagRegistrar == 1){
      digitalWrite(ledRegistrar,HIGH);
      if(digitalRead(buttonCancelar) == 0){
        flagRegistrar = 0;
        Serial.println("salio de rutina de registro");digitalWrite(ledRegistrar,LOW);
        digitalWrite(ledCancelar,HIGH);delay(50);digitalWrite(ledCancelar,LOW);
        }
      Serial.println("Ready to enroll a fingerprint!");
      Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");
      id = readnumber();
      if (id == 0) {// ID #0 not allowed, try again!
      return;
      }
      Serial.print("Enrolling ID #");
      Serial.println(id);
  
      while (!  getFingerprintEnroll() );
    }//fin rutina registro 

  //puerto serie del sim900, si hay datos:
  if (sim900.available()){
      datosSim = sim900.readString();
      Serial.print(datosSim);
      enviarMsn(datosSim);
    }
  //puerto serie del pc, si hay datos:
  if (Serial.available()){
      datosPc = Serial.readStringUntil('\n');
      //sim900.print("AT\r");
      sim900.print(datosPc);
      sim900.print("\r");
      chooseOneMsn(datosPc);
    }
   
}//fin del ciclo principal


//funcion para envio de msn que se hizo correcto
void RegistroCorrecto(String thisDatosSim){
  digitalWrite(ledSendMsn, HIGH);
  if(thisDatosSim.indexOf("gsmOkQ") >=0 ){
      thisDatosSim = "AT+CMGS=\"" + numeroChecador + "\"";
      sim900.println(thisDatosSim);
      delay(500);
      sim900.println("coneccion gsm ok");//texto del sms
      delay(100);
      sim900.println((char)26);//comando de finilizacion 
      delay(100);
      sim900.println();
      delay(2000);
    }
  thisDatosSim = "";
  datosSim = "";
  digitalWrite(ledSendMsn, LOW);
}


//funcion para escoger respuesta
void chooseOneMsn(String selectNumChecador){
    //seleccionar respuesta para checador
    if(selectNumChecador.indexOf('R') >= 0){
        escogerRespuesta = selectNumChecador.substring(0,2);
        Serial.println();
        Serial.println(escogerRespuesta);
        //poner un led
        numeroChecador = selectNumChecador.substring(2,12);//toda de la cadena de mensaje el numero del checador
        Serial.print(numeroChecador);
        if(escogerRespuesta == "RX"){
            RegistroCorrecto(numeroChecador);
          }
      }
  }

//funcion para verificar conecciongsm////
  void enviarMsn(String thisDatosSim){
  digitalWrite(ledSendMsn, HIGH);
  if(thisDatosSim.indexOf("gsmOkQ") >=0 ){
      thisDatosSim = "AT+CMGS=\"" + numAux + "\"";
      sim900.println(thisDatosSim);
      delay(500);
      sim900.println("coneccion gsm ok");//texto del sms
      delay(100);
      sim900.println((char)26);//comando de finilizacion 
      delay(100);
      sim900.println();
      delay(2000);
    }
  thisDatosSim = "";
  datosSim = "";
  digitalWrite(ledSendMsn, LOW);
}
/////////////////////////////////////////

//funcion para verificar conecciongsm////
  void enviarId(String thisDatosSim, int thisId){
  
  digitalWrite(ledSendMsn, HIGH);
  if(thisDatosSim.indexOf("gsmOkQ") >=0 ){
      id_persona = (String) thisId;
      thisDatosSim = "AT+CMGS=\"" + numAux + "\"";
      sim900.println(thisDatosSim);
      delay(500);
      sim900.println("persona " + id_persona + " ya llego");//texto del sms
      delay(100);
      sim900.println((char)26);//comando de finilizacion 
      delay(100);
      sim900.println();
      delay(2000);
    }
  thisDatosSim = "";
  datosSim = "";
  digitalWrite(ledSendMsn, LOW);
}
/////////////////////////////////////////





//inicializacion de puertos serie

//funcion para inicializar modulo gsm
void startSim900(){
  sim900.begin(57600);//velocidad de transmision arduino-sim900
  //inicializando modulo sim900/////////////////
  sim900.print("A\r");                        //
  delay(500);                                 //
  sim900.print("AT\r");                       //
  delay(200);                                 //
  sim900.print("AT\r");                       //
  delay(200);                                 //
  sim900.println("AT+CMGF=1\r");              //
  delay(100);                                 //
  sim900.println("AT+CNMI=1,2,0,0,0\r");      //
  delay(100);                                 //
  //////////////////////////////////////////////
  }

//inicializacion de sensor de huellas
void startSensorHuellas(){
   Serial.println("\n\nAdafruit finger detect test");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  //Serial.println("Waiting for valid finger...");
  }

//funciones::ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
//funcion para registrar huella_11111111111111111111111111111111111111111111111111111111111111111111
uint8_t readnumber(void) {
  uint8_t num = 0;
  
  while ((num == 0) && (digitalRead(buttonCancelar)==1)) {
    while (! Serial.available());
    num = Serial.parseInt();
    
  }
  return num;
}

uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);
  
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
}
//fin funcion registrar huella_111111111111111111111111111111111111111111111111111111111111111111111

//funcion checar huella_2222222222222222222222222222222222222222222222222222222222222222222222222222
uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 

  return finger.fingerID;
}

// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID; 
}
//fin funcion checar huella_222222222222222222222222222222222222222222222222222222222222222222222222
