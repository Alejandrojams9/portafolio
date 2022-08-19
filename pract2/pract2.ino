#include<Arduino.h>
#include<SimpleDHT.h>
#include<ThingSpeak.h>
#include<ESP8266WiFi.h>

const char* ssid="Alumnos";
const char* password="alumnouptx";
WiFiClient client;
unsigned long myChannelNumber =1591029;
const char* myWriteAPIKey="QYJN17KD2VNJKTPR";
int pinDHT11=16;
SimpleDHT11 dht11;
void setup(){
    Serial.begin(115200);
    //


    ThingSpeak.begin(client);

}
void loop(){

    byte t=0;
    byte h=0;
    if(dht11.read(pinDHT11, &t, &h, NULL)){
        Serial.print("ERROR EN LA LECTIRA");
        return;

    }
     int ldr= analogRead(A0);
     int valorluz;
     valorluz=map(ldr,0,1023,0,100);

    Serial.print("HUMEDAD RELATIVA: ");
    Serial.print((int)h);
    Serial.print("%\t");
    Serial.print("TEMPERATURA: ");
    Serial.print((int)t);
    Serial.print(" *C   ");
    Serial.print("LUMINOSIDAD: ");
    Serial.print(valorluz);
        Serial.println("%\t");



    ThingSpeak.setField(1,(int)t);
    ThingSpeak.setField(2,(int)h);
    ThingSpeak.setField(3, valorluz);
    ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    delay(6000);
    
}
