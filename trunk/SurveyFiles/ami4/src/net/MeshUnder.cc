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

#include "MeshUnder.h"
#include "String.h"
#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "ArpInterface.h"
#include "FindModule.h"
#include "ARP.h"
#include "NetworkToMacControlInfo.h"
#include "IPvXAddressResolver.h"
#include "IPv4InterfaceData.h"
#include "NetwToMacControlInfo.h"
#include <Ieee802Ctrl_m.h>

typedef Ieee802Ctrl tNetwToMacControlInfoBase;
//typedef NetwToMacControlInfo tNetwToMacControlInfoBase;


Define_Module(MeshUnder);


MeshUnder::MeshUnder() {
    // TODO Auto-generated constructor stub

    //    configRed = new RoutingTablesConf();

}

void MeshUnder::initialize (int stage ){

    BaseModule::initialize(stage);
    senalLlegada = registerSignal("llegada");
    senalReDireccion = registerSignal("redireccion");
    distancia = par("distance");

}

void MeshUnder::handleMessage(cMessage *msg){

    EV << "Mensaje llegó al handleMessage de Mesh Under \n";

    // const char *text = getParentModule()->par("addressNode");
    //  myAddress = IPv4Address(text);
    cModule* host = getParentModule();
    IInterfaceTable *ift = IPvXAddressResolver().interfaceTableOf(host);
    InterfaceEntry* ie = ift->getInterfaceByName("wlan");

    myAddress = ie->ipv4Data()->getIPAddress(); //Mi dirección IP
    myMacAddress = ie->getMacAddress(); //Mi dirección MAC

    // MACAddress myAddress = ie->getMACAddress();
    EV << "Dirección del nodo actual: "<< myAddress.str().c_str()<< "\n";

    char pkname[40]="packet";


    if(msg->arrivedOn("localIn")){
        EV << "Mensaje llegó de Capa Dummy \n";

        if (strcmp (msg->getName(), pkname)==0){

            Packet *packet = check_and_cast<Packet *>(msg);
            if(packet->getDestAddr()==IPv4Address::ALLONES_ADDRESS){

                static MACAddress broadcastAddr("FF:FF:FF:FF:FF:FF");
                tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
                                       infoDeControl->setDest(broadcastAddr);
                                       packet->setControlInfo (infoDeControl);
                                       send(packet, "lowerGateOut");

            }else{

           configRed = new RoutingTablesConf();
            MACAddress packetMacDestino = configRed->getMACAddressFromID(configRed->getIdNode(packet->getDestAddr()));

            if(packetMacDestino==myMacAddress){

                EV << "El destino del paquete es el nodo actual \n";

                //Subo el paquete al nivel Dummy

                send(packet, "localOut");
            }else{
                EV << "El destino del paquete NO es el nodo actual. Debe enviarse al siguiente salto \n";

//                if(packetMacDestino==BroadcastSystemMessage()){
//
//                    tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
//                                           infoDeControl->setDest(BroadcastSystemMessage());
//                                           packet->setControlInfo (infoDeControl);
//                                           send(packet, "lowerGateOut");
//                }else{


                std::vector<MACAddress> path;
                MACAddress proximoSalto;
                IPv4Address dirDest = packet->getDestAddr();

                EV<<"Dirección IP destino:" <<dirDest.str()<<"\n";
                EV<<"Dirección MAC destino:" <<packetMacDestino.str()<<"\n";
                //double distancia = 60;
              //  configRed->setRoot(myMacAddress);
               // if(configRed!=NULL){
                //    if(configRed->findRoute(distancia,packetMacDestino, path)){
                 //       proximoSalto = path[path.size()-1];
                  //      EV<<"El proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<<" es "<<proximoSalto.str()<< " \n";
                        tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
                        infoDeControl->setDest(packetMacDestino);
                        packet->setControlInfo (infoDeControl);
                        send(packet, "lowerGateOut");
                        EV << "Se envió  paquete con información del proximo salto al nivel mac \n";
           //         }else{
           //             EV<<"No se encontro el proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<< " \n";
           //         }
       //         }
            }
            }
            }


    }else{
             /*   *Mensaje llegó del nivel MAC, debe direccionarlo hacia la capa de adaptación, via localOut, en caso de que el nodo actual
        sea el destino.


         */
        EV << "Mensaje llegó del nivel MAC \n";


        if (strcmp (msg->getName(), pkname)==0){

            Packet *packet = check_and_cast<Packet *>(msg);

            if(packet->getDestAddr()==IPv4Address::ALLONES_ADDRESS){

                send(packet, "localOut");
            }else{

           // static MACAddress broadcastAddr("FF:FF:FF:FF:FF:FF");



//           configRed = new RoutingTablesConf();
//                     Packet *packet = check_and_cast<Packet *>(msg);
//                     MACAddress packetMacDestino = configRed->getMACAddressFromID(configRed->getIdNode(packet->getDestAddr()));
//                     if(packetMacDestino==myMacAddress){
//
//                         EV << "El destino del paquete es el nodo actual \n";
//                         //Subo el paquete al nivel de Adaptación
                         send(packet, "localOut");
//                     }else{
////
////                         if(packetMacDestino==BroadcastSystemMessage()){
////
////                                           tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
////                                                                  infoDeControl->setDest(BroadcastSystemMessage());
////                                                                  packet->setControlInfo (infoDeControl);
////                                                                  send(packet, "lowerGateOut");
////                                       }else{
//                         EV << "El destino del paquete NO es el nodo actual. Debe enviarse al siguiente salto \n";
//                         std::vector<MACAddress> path;
//                         MACAddress proximoSalto;
//                         IPv4Address dirDest = packet->getDestAddr();
//                         EV<<"Dirección IP destino:" <<dirDest.str()<<"\n";
//                         EV<<"Dirección MAC destino:" <<packetMacDestino.str()<<"\n";
//                       //  double distancia = 60;
//                       //  configRed->setRoot(myAddress);
//                         configRed->setRoot(myMacAddress);
//
//                         if(configRed!=NULL){
//                             if(configRed->findRoute(distancia,packetMacDestino, path)){
//                                 proximoSalto = path[path.size()-1];
//                                 //Envio al nivel de abajo el paquete con la información de control (proximo salto)
//
//                                 //   sendDown (packet, proximoSalto);
//
//                                 EV<<"El proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<<" es "<<proximoSalto.str()<< " \n";
//
//                              //   NetworkToMacControlInfo *ctrlInfo =  new NetworkToMacControlInfo(proximoSalto);
//                              // NetwToMacControlInfo *infoContrl =  new NetwToMacControlInfo(dirProxSalto);
//                              //  LAddress::L2Type dirDestino = NetwToMacControlInfo::getDestFromControlInfo(infoContrl);
//
//                                tNetwToMacControlInfoBase * const infoDeControl = new tNetwToMacControlInfoBase();
//                                packet->removeControlInfo();
//                                infoDeControl->setDest(proximoSalto);
//                                packet->setControlInfo (infoDeControl);
//                                // cObject *infoDeControl = infoContrl->setControlInfo(fragment, dirProxSalto);
//                                 //cObject* infoDeControl;
//                                // infoDeControl = NetwToMacControlInfo::setControlInfo(fragment, dirProxSalto);
//                              //  fragment->setControlInfo (infoContrl);
//                              send(packet, "lowerGateOut");
//                           //   delete(infoDeControl);
//                                 EV << "Se envió  paquete con información del proximo salto al nivel mac \n";
//                             }else{
//                                 EV<<"No se encontro el proximo salto desde" <<myAddress.str().c_str() <<"para llegar a "<<packet->getDestAddr().str().c_str()<< " \n";
//                             }
//                         }
//                     }
                     }
        }
        }
    }


MeshUnder::~MeshUnder() {
    // TODO Auto-generated destructor stub
}

