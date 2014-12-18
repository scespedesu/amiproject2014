//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "Adaptation.h"
#include <cassert>
#include <string.h>
#include <Ieee802Ctrl_m.h>
#include "NetwToMacControlInfo.h"
typedef Ieee802Ctrl tNetwToMacControlInfoBase;

Define_Module(Adaptation);

static vector<Fragment> buffer; //Buffer de fragmentos
Adaptation::Adaptation() {
    // TODO Auto-generated constructor stub

}

void Adaptation::initialize(){

}

void Adaptation::handleMessage(cMessage *msg){

    EV << "Paquete llego a la capa de Adaptation  \n";

     //Primero se verifica si el paquete llegó de arriba.
    if(msg->arrivedOn("upperIn")){

        //EV << "Paquete llego de la capa de APP  \n";
        EV << "Paquete llego de la capa de APP  \n";

        Packet *pack = check_and_cast<Packet *>(msg); //Cast del mensaje a objeto tipo Packet
        EV << "Tamaño de paquete original: " << pack->getByteLength() << " bytes \n";

            send (pack, "lowerOut", 0);
            EV<<"El paquete se envió al nivel de enrutamiento";


        }
    else{
        EV << "Mensaje llega de capa de enrutamiento \n";

        Packet *paquete = check_and_cast<Packet *>(msg);
        send(paquete, "upperOut");
        }
    }

Adaptation::~Adaptation() {
//    cOwnedObject *Del=NULL;
//      int OwnedSize=this->defaultListSize();
//      for(int i=0;i<OwnedSize;i++){
//              Del=this->defaultListGet(0);
//              this->drop(Del);
//              delete Del;
//      }
}

