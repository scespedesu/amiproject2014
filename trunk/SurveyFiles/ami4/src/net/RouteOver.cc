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

#include "RouteOver.h"
#include "String.h"
#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "NetworkToMacControlInfo.h"
#include "IPvXAddressResolver.h"
#include "IPv4InterfaceData.h"
#include "NetwToMacControlInfo.h"
#include <Ieee802Ctrl_m.h>
typedef Ieee802Ctrl tNetwToMacControlInfoBase;

Define_Module(RouteOver);

RouteOver::RouteOver() {
    // TODO Auto-generated constructor stub

}

void RouteOver::initialize (int stage ){

    BaseModule::initialize(stage);
  //  senalLlegada = registerSignal("llegada");
    //senalReDireccion = registerSignal("redireccion");
    distancia = par("distance");

}

void RouteOver::handleMessage(cMessage *msg){


    //Siempre se recibe un paquete (desde NetLayer o desde Adaptation)


    Packet *packet = check_and_cast<Packet *>(msg);

    cModule* host = getParentModule();
    IInterfaceTable *ift = IPvXAddressResolver().interfaceTableOf(host);
    InterfaceEntry* ie = ift->getInterfaceByName("wlan");

    myAddress = ie->ipv4Data()->getIPAddress(); //Mi dirección IP
    //  myMacAddress = ie->getMacAddress(); //Mi dirección MAC

    // MACAddress myAddress = ie->getMACAddress();
    EV << "Dirección del nodo actual: "<< myAddress.str().c_str()<< "\n";

    if(msg->arrivedOn("localIn")){

        //Paquete llegó de NetLayer. Enviar a nivel de adaptación con info control

        if(packet->getDestAddr() == myAddress){

            //Nodo actual es el destino. Enviar a NetLayer
            send(packet, "localOut");

        }else{

            //El nodo actual no es el destino. Redireccionar paquete
            //Buscar próximo salto y enviar paquete con esta info control al nivel de adaptación
            configRed = new RoutingTablesConf();

            std::vector<IPv4Address> path;
            IPv4Address proximoSalto;
            IPv4Address dirDest = packet->getDestAddr();


            EV<<"Dirección IP destino:" <<dirDest.str()<<"\n";
            //double distancia = 100;
            //  configRed->setRoot(myAddress);
            configRed->setRoot(myAddress);

            if(configRed!=NULL){
                if(configRed->findRoute(distancia,dirDest, path)){

                    proximoSalto = path[path.size()-1];

                    EV<<"El proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<<" es "<<proximoSalto.str()<< " \n";

                    tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
                    infoDeControl->setDest(configRed->getMACAddressFromID(configRed->getIdNode(proximoSalto)));
                    packet->setControlInfo (infoDeControl);
                    packet->setSpecialField(true);

                    send(packet, "out");

                    //  delete(infoDeControl);

                    EV << "Se envió  paquete con información del proximo salto al nivel de adaptación \n";

                }else{
                    EV<<"No se encontro el proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<< " \n";
                }
            }
        }
    }else{

        //paquete llegó de nivel de adaptación
        //Revisar si soy o no el destino

        if(packet->getDestAddr() == myAddress){

            //El nodo actual es el destino. Subirlo a nivel NetLayer

            send(packet, "localOut");
        }else{

            //El nodo actual no es el destino. Redireccionar paquete
            //Buscar próximo salto y enviar paquete con esta info control al nivel de adaptación
            packet->removeControlInfo();
            configRed = new RoutingTablesConf();

            std::vector<IPv4Address> path;
            IPv4Address proximoSalto;
            IPv4Address dirDest = packet->getDestAddr();


            EV<<"Dirección IP destino:" <<dirDest.str()<<"\n";
            //double distancia = 60;
            //  configRed->setRoot(myAddress);
            configRed->setRoot(myAddress);

            if(configRed!=NULL){
                if(configRed->findRoute(distancia,dirDest, path)){

                    proximoSalto = path[path.size()-1];

                    EV<<"El proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<<" es "<<proximoSalto.str()<< " \n";

                    tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();

                    infoDeControl->setDest(configRed->getMACAddressFromID(configRed->getIdNode(proximoSalto)));

                    packet->setControlInfo (infoDeControl);

                    send(packet, "out");

                    //  delete(infoDeControl);

                    EV << "Se envió  paquete con información del proximo salto al nivel de adaptación \n";

                }else{
                    EV<<"No se encontro el proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<< " \n";
                }
            }

        }

    }

}



RouteOver::~RouteOver() {
    // TODO Auto-generated destructor stub
}

