String box = "HOLA";
String acumula = "";
int box2 = "R";
int cambia = "A";
int led = 10;
int led1 = 7;
int push12 = 12;

//////////////////////

char cadena[30];
byte posicion=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(push12, OUTPUT);
  digitalWrite(led, LOW);

  /////////////////////
  
}



void loop() {
  // put your main code here, to run repeatedly:

        if(acumula == "o"){
            digitalWrite(led, LOW);
            Serial.print("activado: = ");
            Serial.println(acumula);
            delay(1000);
            
          }

        if((digitalRead(push12)) == 1){
            while(digitalRead(push12) == 1){;}
            Serial.print(acumula);
          }
        
        if(box == "HOLA"){
          digitalWrite(led, HIGH);
          box = "n_n";
          delay(1000);
          Serial.println(box);
        }

        if(box == "A"){
            Serial.print("box es solo: ");
            Serial.println(box);
          }

        
  
  if(Serial.available()>0){
      /*ENVIAR UN CARACTER A LA VEZ 
      char dato=(char)Serial.read();//almacenamos el dato del buffer seria, un byte por vez
      Serial.print(dato);
      box = dato;
      acumula = acumula + dato;
      if(dato == 65){
          digitalWrite(led, HIGH);
        }
      if(dato == 66){
          digitalWrite(led, LOW);
      }*/

      //ALMACENAR UNA CADENA EN UN CHAR

      memset(cadena, 0, sizeof(cadena));//borra la cadena desde 0 hasta tamaño de cadena

      while(Serial.available()>0){
          delay(5);
          cadena[posicion] = (char)Serial.read();
          posicion++;
        }
      Serial.println(cadena);
      Serial.print(cadena[0]);
      Serial.print(cadena[1]);
      Serial.print(cadena[2]);
      Serial.print(cadena[3]);
      Serial.print(cadena[4]);
      Serial.print(cadena[5]);
      Serial.println();
      if(cadena[2] == "d"){
         digitalWrite(led, LOW);
         Serial.print(cadena[2]);
        }
      Serial.println("rewrite");
      acumula=cadena;
      Serial.print(acumula);
      posicion=0;
      
    }//fin de leectura de datos del puerto serie
}
