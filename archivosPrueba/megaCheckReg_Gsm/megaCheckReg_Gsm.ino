//checar gsm con arduino mega uwu
#include <Adafruit_Fingerprint.h>
SoftwareSerial sim900(7,8);
SoftwareSerial mySerial(52, 53);

//declaracion de variables:
#define buttonRegistrar 22
#define buttonAsistencia 23
#define ledCancelar 24
#define buttonCancelar 25
#define ledRegistrar 26
#define ledAsistencia 27
#define ledSendMsn 28

String datosSim = "";
String datosPc = "";
String numAux = "4111225115";
String escogerRespuesta = "";
String numeroChecador = "";//para guardar el numero del checador en cadena
String verify = "gsmOkQ";
String id_persona = "";


Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int checarHuella=0;
uint8_t id;
byte flagAsistencia = 0;
byte flagRegistrar = 0;

void setup() {
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
  // put your main code here, to run repeatedly:

}
