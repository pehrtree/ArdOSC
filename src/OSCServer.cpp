/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- licence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */

#include <stdlib.h>
#include <string.h>
#include "OSCCommon/OSCServer.h"
#include "OSCCommon/OSCcommon.h"
#include "OSCCommon/OSCMessage.h"


OSCServer::OSCServer(void){

}

OSCServer::~OSCServer(void){
    udp.stop();
     
}

int16_t OSCServer::begin(uint16_t _receivePort){
    int result = udp.begin(_receivePort);

    if(!result){
    return result;
    }//no socket avail

    _port=_receivePort;
        
	rcvFlush();
	
    return 1;
    
}


void OSCServer::stop(void){
    udp.stop();
}

int16_t OSCServer::availableCheck(void){
    int num=udp.parsePacket();

    if(num <=0){return 0;}

    udp.read(_rcvData, kMaxreceiveData);

    OSCMessage rcvMes;

    _decoder.decode( &rcvMes ,_rcvData );

    // set IP and port after decoding.
    IPAddress ip = udp.remoteIP();
    // manually copy the IPAddress bytes
    for(int i=0; i <4; i++){
        rcvMes._ip[i]=ip[i];
    }
    rcvMes._port = udp.remotePort();

    if(!_adrMatch.paternComp(&rcvMes)){
        // nothing matched, not even the default handler.
    } // call the callbacks
    
	return 1;
}



void OSCServer::rcvFlush(void){
    udp.flush();
}


void OSCServer::addCallback(char *_adr , Pattern::AdrFunc _func ){
    _adrMatch.addOscAddress( _adr , _func );
}
void OSCServer::addDefaultCallback(Pattern::AdrFunc _func ){
    char * _adr = ""; // convention - blank means default
    _adrMatch.addOscAddress( _adr , _func );
}

