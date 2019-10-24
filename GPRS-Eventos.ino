#include <SoftwareSerial.h>
#include "inetGSM.h"

#define sensibilidade2 A5

InetGSM inet;

int sensorSensibilidade2;
int flagRain=0;

boolean started = false;
char smsbuffer[160];
char n[20];

byte valor;

void setup()
{
  Serial.begin(9600);
   powerUpOrDown();
  Serial.println(F("Testando GSM Shield SIM800l"));
  if (gsm.begin(2400))
  {
    Serial.println(F("\nstatus=READY"));
    started = true;
  }
  else Serial.println(F("\nstatus=IDLE"));
}

void loop()
{
  if (started) {
      chuva();
      delay(5000);
    }
    delay(1000);
  Serial.println(sensorSensibilidade2);
}

void powerUpOrDown()
{
  //Start SIM800L
  Serial.print(F("Start GSM..."));
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  delay(1000);
  digitalWrite(6, HIGH);
  delay(1000);
  Serial.println(F("OK!"));
  digitalWrite(6, LOW);
  delay(500);
}

void envia_GSM(){


Serial.println("AT+CGATT?");
gsm.SimpleWriteln("AT+CGATT?");
delay(1000);
int i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\""); 
gsm.SimpleWriteln("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=3,1,\"APN\",\"tim.br\"");
gsm.SimpleWriteln("AT+SAPBR=3,1,\"APN\",\"tim.br\"");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=3,1,\"USER\",\"tim\"");
gsm.SimpleWriteln("AT+SAPBR=3,1,\"USER\",\"tim\"");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=3,1,\"PWD\",\"tim\"");
gsm.SimpleWriteln("AT+SAPBR=3,1,\"PWD\",\"tim\"");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=1,1");
gsm.SimpleWriteln("AT+SAPBR=1,1");
delay(3000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+SAPBR=2,1");
gsm.SimpleWriteln("AT+SAPBR=2,1");
delay(3000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+HTTPINIT");
gsm.SimpleWriteln("AT+HTTPINIT");
delay(2000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+HTTPPARA=\"CID\",1");
gsm.SimpleWriteln("AT+HTTPPARA=\"CID\",1");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 
Serial.println("AT+HTTPPARA=\"REDIR\",1");
gsm.SimpleWriteln("AT+HTTPPARA=\"REDIR\",1");
delay(1000);
i=0;
while(i<20) {
gsm.SimpleRead();
i++;
} 

char message_url[200]; 

if (flagRain==0)
           
           {
      
sprintf(message_url,"AT+HTTPPARA=\"URL\",\"xxxxxxxx.000webhostapp.com/add.php?MSG_Texto1=%s\"","Inicio Chuva");
          }
          if (flagRain==1)
          {
 sprintf(message_url,"AT+HTTPPARA=\"URL\",\"xxxxxxxx.000webhostapp.com/add.php?MSG_Texto1=%s\"","Sensor Seco");          
          }

Serial.println(message_url);
gsm.SimpleWriteln(message_url);
delay(3000);
i=0;
while(i<50) {
gsm.SimpleRead();
i++;
}
Serial.println("AT+HTTPACTION=0");
gsm.SimpleWriteln("AT+HTTPACTION=0");
delay(3000);
i=0;
while(i<100) {
gsm.SimpleRead();
i++;
}

Serial.println("AT+HTTPTERM");
gsm.SimpleWriteln("AT+HTTPTERM");
delay(3000);
i=0;
while(i<100) {
gsm.SimpleRead();
i++;
}
}

void chuva()

{

  sensorSensibilidade2 = analogRead(sensibilidade2);
  
        if (flagRain==0)
           {
                    if(sensorSensibilidade2<960)
           {
            envia_GSM();
         flagRain=1;
          }                     
          }
           
           if (flagRain==1)           
           {
                    if(sensorSensibilidade2>1010) 
           {
            envia_GSM();
            flagRain=0;
          }
          }
}  

 

