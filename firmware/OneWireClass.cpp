#include <OneWire.h>
#include "OneWireClass.h"
#include "MethodDescriptor.h"
#include <stdlib.h>

onewire ds;
SlimArray <OneWire*> v(2);

PyOneWire::PyOneWire() {

};

void PyOneWire::elaborate( MethodDescriptor* m ) {

    if (strcmp(m->getClass(), "OneWire") == 0) {

        if (strcmp(m->getName(), "new") == 0) {      
            v.insert(new OneWire(m->getInt(0)));
            Serial.println(v.getLastIndex());
        }

        if (strcmp(m->getName(), "search") == 0) {              
            byte addr[8];
            int res = v[m->getObjectId()]->search(addr);

            if(!res) {
                v[m->getObjectId()]->reset_search();
                delay(250);
                Serial.println("1");
            }

            else {    
                String addr_hex = String(); 
                for( int cc = 0; cc < 7; cc++ )
                    addr_hex += String(addr[cc]) + " ";
                addr_hex += String(addr[7]);
                Serial.println(addr_hex);
            }
        }

        if (strcmp(m->getName(), "reset_search") == 0) {
            v[m->getObjectId()]->reset_search();
            Serial.println("0");
        }

        if (strcmp(m->getName(), "reset") == 0) {
            Serial.println(v[m->getObjectId()]->reset());
        }

        if (strcmp(m->getName(), "select") == 0) {
            byte* addr = (byte*)malloc(m->getNArgs() * sizeof(byte));
            
            for(int i = 0 ; i < m->getNArgs() ; i++) {
                addr[i] = (byte)m->getInt(i);
            }

            v[m->getObjectId()]->select(addr);

            delete(addr);
            Serial.println("0");
        }

        if (strcmp(m->getName(), "write") == 0) {
            if(m->getNArgs() == 1)
                v[m->getObjectId()]->write(m->getInt(0));
            else
                v[m->getObjectId()]->write(m->getInt(0), m->getInt(1));
            Serial.println("0");
        }

        if (strcmp(m->getName(), "read") == 0) {
            Serial.println(v[m->getObjectId()]->read());
        }

    }
};