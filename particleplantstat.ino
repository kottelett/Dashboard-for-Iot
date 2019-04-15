// This #include statement was automatically added by the Particle IDE.
#include "RTWparticle.h"


RTWparticle rtwParticle;

String auth = "token=aToken_e3b9aabf40c5277023d164f6b718dbc772f27ad2b33333b1614829d6696cda1e";
String host = "academy7.rtw.no";
String pumpStatus = "off";
String waterlevel = "3000";
String stamp = "10:12:00";
String location = "Loc2";

int pumpRelay = D0;

unsigned long previousMillis = 0;   
const long interval = 2000;           


void setup() {
    Serial.begin(9600);
    rtwParticle.initGet(host, "PLANTSTAT", "1", auth);
    pinMode(pumpRelay, OUTPUT);
}

void loop() {
    String query = "ON=" + pumpStatus + "&waterlevel=" + waterlevel + "&timestamp=" + stamp + "&location=" + location;
    unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    rtwParticle.sendRTW("PLANTSTAT", "2", auth, query, host);
   
}
    Serial.println(query);
    workWithData(rtwParticle.getNewMessages());
    Serial.println(pumpStatus);
}



void workWithData(String rtwmsg){
    if(rtwmsg == ""){
        return;
    }
    Serial.println("!!" + rtwmsg + "!!");
    if( rtwParticle.parseRTW(rtwmsg, "LOCATION") != location){
        return;
    }
   
    String pumpStatusT = rtwParticle.parseRTW(rtwmsg, "UPDATESTATUS");
    Serial.println("before loop: " + pumpStatusT);
    
    if(pumpStatusT.length() > 1) {
        Serial.println("after loop: " + pumpStatusT);
        pumpStatus = pumpStatusT;
    }
  
    Serial.println("Pump is: " + pumpStatus);

}
