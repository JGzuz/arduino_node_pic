#include <SoftwareSerial.h>//Libreria para implementar mas de un puerto
SoftwareSerial Serial_sim(8,9);//configuracion puerto serie virtual (rx, tx)

const int led11 = 11;//Indicador que llego determinada cadena por 
const int led6 = 6;
const int push12 = 12;
const int push5 = 5;
const int high4 = 4;//alto continuo en el pin

int enviarDato = 0;

String megaDato;
String giga = "";
unsigned long datoNumerico = 0;

void setup() {
    Serial.begin(115200);
    Serial_sim.begin(115200);
    delay(2000);


    //comandos para trabajar con el sim800L
    /* Serial_sim.println("AT+CMGF=1");//Vamos a utilizatr los SMS
    delay(200);
    Serial_sim.println("AT+CNMI=1,2,0,0,0"); /*configurar modulo sim800L para enviar msn por
    puerto serie*/
    
    
    /*descomnetar solo cuando se use la terminal del puerto serial arduino
    Serial.println("COMUNICACION ARD-PC, ARD-SIM INICIALIZADAS");*/
    
    pinMode(led11, OUTPUT);
    pinMode(led6, OUTPUT);
    pinMode(push12, INPUT);
    pinMode(push5, INPUT);
    pinMode(high4, OUTPUT);

    digitalWrite(high4, HIGH);

    //descomentar cuando se va emular el sim800L con otro arduino
    //Serial_sim.print("12345");//datos para comprobar que le llegan datos al modulo sim800L
  } 

void loop() {

  //cuando reciba datos del puerto Serial hardware de la pc
    if(Serial.available()){
        String data = (String)Serial.readStringUntil('\n');
        megaDato = data;
        datoNumerico = String(megaDato).toInt();
        //Serial.print(data);
        //Serial.print(megaDato);
      }

    
    //cuando reciba datos por el puerto serie virtual del sim800L (simulado con otro arduino)
    if(Serial_sim.available()){
      /*
        String data1 = (String)Serial.readStringUntil('\n');
        Serial.print(data1);*/
        //Serial.print((char)Serial_sim.read());
        
        while(Serial_sim.available()){
          giga = giga + (char)Serial_sim.read();
          }
        //enviamos los datos almacenados a procesar a node
        Serial.print("+CMV: +4661016976+,++,+19/10/17,13:53:02-20+ 1234567890 ");
        delay(500);
      }

    if(megaDato == "ATC_ON"){
      digitalWrite(led11, HIGH);
      digitalWrite(led6, LOW);
      Serial_sim.print("1000");
      //Serial_sim.print(megaDato);
      //Serial_sim.print("");
      megaDato = "";
      }

    if(megaDato == "ATC_OFF"){
      digitalWrite(led6, HIGH);
      digitalWrite(led11, LOW);
      Serial_sim.print("1001");
      //Serial_sim.print(megaDato);
      //Serial_sim.print("");
      megaDato = "";
      }

    if(megaDato == "MSN_ENVIADO"){
        Serial_sim.print("1002");
        megaDato = "";
      }

    
    if(digitalRead(push5)==1){
        
        
        while(digitalRead(push5)==1){;}
        
        Serial.print(giga);
        //Serial.print("string do not problem");
      }

    if(digitalRead(push12)==1){
        while(digitalRead(push12)==1){;}
        giga = "";//borramos lo que tiene giga
        //Serial.print(megaDato);
      }

  }
