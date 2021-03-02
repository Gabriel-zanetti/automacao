#include <SocketIoClient.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h>

#define USE_SERIAL Serial 
String comando = "";
String sentido = "ligadoHorario";
 
ESP8266WiFiMulti WiFiMulti;
SocketIoClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
  comandos(payload);

 }


void setup() {
    
    
pinMode(16,OUTPUT);
pinMode(5,OUTPUT);
pinMode(4,OUTPUT); 
digitalWrite(16,HIGH);
digitalWrite(5,HIGH);
digitalWrite(4,HIGH);
    USE_SERIAL.begin(115200);

    USE_SERIAL.setDebugOutput(true);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

      for(uint8_t t = 4; t > 0; t--) {
          USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
          USE_SERIAL.flush();
          delay(1000);
      }

    WiFiMulti.addAP("DEUS CONOSCO", "04092018");

    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
    }

    webSocket.on("a@a", event);
    webSocket.begin("54.84.189.116", 80, "/socket.io/?transport=websocket");
       
    // use HTTP Basic Authorization this is optional remove if not needed
    //webSocket.setAuthorization("username", "password");
  
}

void loop() {
    webSocket.loop(); 
}


void comandos(const char * payload){
 String g = String(payload);
   if(g.indexOf("ligadoHorario")&&g.indexOf("desligar")&&g.indexOf("status")&&g.indexOf("ligadoReverso")&&g.indexOf("emergencia")&&g.indexOf("ligar")){
     webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"comandoInvalido\"}");
    
  }
   if(g.equals("ligadoHorario")){
     comando = "ligadoHorario";
     sentido = "ligadoHorario";
     digitalWrite(5,HIGH);
     delay(1000);
     digitalWrite(16,LOW);
     webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoHorario\"}");
   
  }
    if(g.equals("ligadoReverso")){
      comando = "ligadoReverso";
      sentido = "ligadoReverso";
      digitalWrite(16,HIGH);
      delay(1000);
      digitalWrite(5,LOW);
     webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoReverso\"}");
   
  }
   if(g.equals("desligar")){
     digitalWrite(5,HIGH);
     delay(1000);
     digitalWrite(16,HIGH);
     comando = "desligar";
     webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"desligar\"}");
    
  }
  if(g.equals("ligar")){
     digitalWrite(16, HIGH);
     comando = sentido;
   if(sentido.equals("ligadoReverso")){
      webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoReverso\"}");
      digitalWrite(16,HIGH);
      delay(1000);
      digitalWrite(5,LOW);
      
      }
      if(sentido.equals("ligadoHorario")){
      webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoHorario\"}");
     digitalWrite(5,HIGH);
     delay(1000);
     digitalWrite(16,LOW);
      }
     
     
    
  }
    if(g.equals("emergencia")){
      comando = "emergencia";
     digitalWrite(16,HIGH);
     digitalWrite(5,HIGH);
    
     webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"emergencia\"}");
     
     
  }
   if(g.equals("status")){
    if(comando.equals("ligadoReverso")){
       webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoReverso\"}");
    }
     if(comando.equals("ligadoHorario")){
       webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"ligadoHorario\"}");
    }
      if(comando.equals("emergencia")){
       webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"emergencia\"}");
    }
     if(comando.equals("desligar")){
       webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"desligar\"}");
    }
     if(comando.equals("")){
       webSocket.emit("EnviarCliente", "{\"user\":\"g@g\",\"comando\":\"desligar\"}");
    }
  }
 }
