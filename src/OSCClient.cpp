/*
 
 ArdOSC 2.1 - OSC Library for Arduino.
 
 -------- licence -----------------------------------------------------------
 
 ArdOSC
 
 The MIT License
 
 Copyright (c) 2009 - 2011 recotana( http://recotana.com )　All right reserved
 
 */



#include <stdlib.h>

#include "OSCCommon/OSCClient.h"

#include <Ethernet2.h>



OSCClient::OSCClient(void){
}

OSCClient::~OSCClient(void){
    flushSendData();
}




int16_t OSCClient::send(OSCMessage *_message){
	
    uint16_t result=0;
    
    flushSendData();
    
	_sendData = ( uint8_t*)calloc( _message->getMessageSize()  ,1 );
    
    
	if( encoder.encode( _message , _sendData ) < 0 ){
		flushSendData();
		return -1;
	}
    
  // Grab a fresh socket
    _udp.begin(kDummyPortNumber+random(100));

    _udp.beginPacket(_message->getIpAddress(), _message->getPortNumber());
    _udp.write(_sendData, _message->getMessageSize());
    _udp.endPacket();
    _udp.stop(); // close the socket
    flushSendData();
	return 0;
    
}


void OSCClient::flushSendData(void){
    
	free(_sendData);
	_sendData=0;
    
}



