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

#include "OSCCommon/Pattern.h"



Pattern::Pattern(){
    patternNum=0;
    defaultAdrFunc=NULL;

}
Pattern::~Pattern(){    
}

void Pattern::addOscAddress(char *_adr ,  AdrFunc _func){
    if(strlen(_adr)==0){
        // blank means default - exec'd when no other handler matches.
        defaultAdrFunc=_func;
        return;
    }
    adrFunc[patternNum] = _func;
    addr[patternNum] = _adr;
    patternNum++;
}

void Pattern::execFunc(uint8_t _index,OSCMessage *_mes){
    adrFunc[_index](_mes);
}

int Pattern::paternComp(OSCMessage *_mes){
    
    for (uint8_t i=0 ; i<patternNum ; i++) {
      //
        if ( strcmp( addr[i] , _mes->_oscAddress ) == 0 ){
            execFunc( i , _mes ); 
            return 1;
          }

    }

    if(defaultAdrFunc){
        defaultAdrFunc(_mes);
        return 1; // did something
    }

    return 0;// nothing matched
}