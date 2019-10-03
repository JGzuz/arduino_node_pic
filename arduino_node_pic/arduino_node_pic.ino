#include <SoftwareSerial.h>//libreria para implementar mas de un puerto serial
SoftwareSerial serieSim800(8,9);//configuracion puerto serie virtual (RX, TX)

int push12 = 12;
int led11 = 11;
int led6 = 6;//led para comprobar el caracter de comando
int pb_verificar = 7;//MANDA EL DATO POR EL PUERTO SERIE-PC PA VER QUE RECIBIO ANTERIORMENTE
char nodeDice = "Undefined";

//masconfiguraciones//
char comandoAt = 'X';

//////////////////////

//funcion que hace un cierto numero de parpadeos segun el caso

int blink_n (int veces){
    digitalWrite(led6, LOW);
    boolean estado = true;
    
    for(int i=0; i<=veces; i++){
        if(estado){digitalWrite(led6,HIGH); estado=false;}
        delay(200);
        if(!estado){digitalWrite(led6,LOW); estado=true;}
        delay(200);
      }
     return 0;
  }

void setup() {
  
  //arduino-pc, espera hasta que la comunicacion se haya establecido
  Serial.begin(115200);while(!Serial){;}//configuracion velocidad de transmision

  //serieSim800.println("Puerto virtual inicializado");
  serieSim800.begin(115200);//velocidad de transmison puerto virtual serie
  
  delay(800);
  pinMode(push12, INPUT);//enviar 13 cadenas por el puerto serie al pc
  pinMode(led11, OUTPUT);//indicador para verificar el caso  y que comando se mandara al sim800l
  pinMode(led6, OUTPUT);
  pinMode(pb_verificar, OUTPUT);//boton para verificar que le manda node a arduino
  digitalWrite(led11, HIGH);
  digitalWrite(led6, HIGH);
  Serial.println("Comunicacion serial inicializada");
}

void loop() {

  //escucha datos en puerto serial virtual
  if(serieSim800.available()>0){
      Serial.print((char)serieSim800.read());
    }

  if(comandoAt == 'C'){
      digitalWrite(led6, HIGH);
      Serial.print("Caracter: ");delay(300);
      serieSim800.write(comandoAt);delay(300);
      serieSim800.print('C');
    }

  if(comandoAt == 'D'){
      digitalWrite(led6, LOW);
      Serial.write("Caracter: ");delay(300);
      serieSim800.print(comandoAt);delay(300);
      serieSim800.print('D');
    }

    
    //funcion para seleccionar el comando:
    
    switch (comandoAt){
      case 'E': 
      blink_n(2);
      break;
      case 'F': 
      blink_n(3);
      break;
      case 'G': 
      blink_n(4);
      break;
      
      default: break;
    }
    
  

  //escucha puerto serial
  if(Serial.available()){
    char dato = (char)Serial.read();//leemos un caracter a la vez del puerto serie-pc
    comandoAt = dato;
    //Serial.println(dato);
    Serial.print(comandoAt);
    
    if(dato == 65){
    digitalWrite(led11, HIGH);
    }

    if(dato == 66){
    digitalWrite(led11, LOW);
    }

    /*if(dato == 67){
    digitalWrite(led6, HIGH);
    }

    if(dato == 68){
    digitalWrite(led6, LOW);
    }*/
    
    
    //serieSim800.print(comandoAt);
    }

  //imprime lo que envio node
  if((digitalRead(pb_verificar)) == 1){
      delay(200);
      /*
      Serial.println(comandoAt);//impreme en consola el valor por defelto de comandoAt
      serieSim800.print("7895");
      serieSim800.print(81,DEC);
      serieSim800.write('Q');
      //serieSim800.println("X");
      //serieSim800.println('X');
      //serieSim800.println(comandoAt);*/
      
    }
    
  if(digitalRead(push12) == 1){
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
    
}
