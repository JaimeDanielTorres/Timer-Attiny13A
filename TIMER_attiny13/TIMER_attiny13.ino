//Jaime Daniel Torres  ---  timer attiny13  -- 02/12/20 
//Version 1.0 - 

//hora automatica?
#define automat 1    //1 si - 0 no
//hora default:
#define horadefst 18 //inicio num de 0-24
#define mindefst 3   //inicio num de 0-5
#define horadeffn 0  //final num de 0-24
#define mindeffn 0   //final num de 0-5
//hora actual
#define horaahora 11
#define minutoaho 1

//calibracion de timer 10 min= 530seg

//pines 3 y 4 reservados para osc ext 16mhz
#define rele 0     //rele y led verde----------0
#define sele 1     //boton select y led azul---1
#define ente 2     //boton enter y led amarillo

long previousMillis = 0;  // almacenará la última vez que el estado del tiempo se actualizó (general)
long interval = 1000;
int horaactual=horaahora, minutoactual=minutoaho, horastr=0, horafin=0, minstr=0, minfin=0;
int contador=0, contenter=0;
int estadosele=0, estadoente=0, wile=1, activ32=0, botonactivos=0, botonactivoe=0;

void setup() {

  
  
  if(automat==1){
    horastr=horadefst;
    horafin=horadeffn;
    minstr=mindefst;
    minfin=mindeffn;
  }
  
  pinMode(rele, OUTPUT);
  pinMode(sele, OUTPUT);
  pinMode(ente, OUTPUT);

  digitalWrite(sele, HIGH);
  digitalWrite(ente, HIGH);
  delay(100);
  digitalWrite(sele, LOW);
  digitalWrite(ente, LOW);
  delay(50);
  digitalWrite(sele, HIGH);
  digitalWrite(ente, HIGH);
  delay(500);

  pinMode(sele, INPUT);
  pinMode(ente, INPUT);

  delay(1000);
  estadoente = digitalRead(ente); //leer el estado del boton
  if(estadoente==true){
    digitalWrite(rele, HIGH);
  }

  
  while(wile==0){
    ingresohora();
  }
  
}

void loop() {

  unsigned long currentMillis = millis();    // Se toma el tiempo actual
  if (currentMillis - previousMillis > interval){ //Si pasa el tiempo del intervalo
    previousMillis = currentMillis;
    
    contador++;

    if(contador>=590){ //conteo de segundos
      contador=0;
      minutoactual++;
    }
    if(minutoactual>=6){
      minutoactual=0;
      horaactual++;
    }
    if(horaactual>=24){
      horaactual=0;
    }
  }
  
  if(horaactual==horastr){
    if(minutoactual==minstr){
      digitalWrite(rele, HIGH);
    }
  }
  else if(horaactual==horafin){
    if(minutoactual==minfin){
      digitalWrite(rele, LOW);
    }
  }

}

void ingresohora(){
    if(botonactivoe==false){
      estadosele = digitalRead(sele); //leer el estado del boton
    }
    if(botonactivos==false){
      estadoente = digitalRead(ente); //leer el estado del boton
    }
   
    if(estadosele == HIGH && botonactivos==false){  /////////////boton select
      botonactivos = true;
      
      if(contenter==0){  //horas
        if(horaactual>=24){
          horaactual=0;
        }
        else{
          horaactual++;
        }  
      }
      else if(contenter==1){ //minutos
        if(minutoactual>=6){
          minutoactual=0;
        }
        else{
          minutoactual++;
        }
      }
      
    }
    
    if(botonactivos==true && estadosele == LOW){
      botonactivos = false;
    }

    if(estadoente == HIGH && botonactivoe==false){///////////////boton enter
      botonactivoe = true;
    }

    if(botonactivoe==true && estadoente == LOW){
      botonactivoe = false;
      contenter++;

      if(contenter==1){
        pinMode(ente, OUTPUT);
        digitalWrite(ente, LOW);
        delay(1000);
        for(int i=1; i<=horaactual; i++){
          digitalWrite(ente, HIGH);
          delay(300);
          digitalWrite(ente, LOW);
          delay(300);
        }
        pinMode(ente, INPUT);

      }
      if(contenter==2){
        pinMode(ente, OUTPUT);
        digitalWrite(ente, LOW);
        delay(1000);
        for(int i=1; i<=minutoactual; i++){
          digitalWrite(ente, HIGH);
          delay(200);
          digitalWrite(ente, LOW);
          delay(300);
        }
        pinMode(ente, INPUT);

      }
      else if(contenter>=3){ //3 enter
        wile=1;
        contenter=0;
      }
    }
}
