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

#include "NetLayer.h"
#include <vector>
#include <omnetpp.h>
#include "Packet_m.h"
#include "IPv4Address.h"
#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "IPv4InterfaceData.h"
#include "String.h"
#include "IPvXAddressResolver.h"

class IPv4InterfaceData;

Define_Module(NetLayer);

NetLayer::NetLayer() {
    // TODO Auto-generated constructor stub

}

NetLayer::~NetLayer() {
    // TODO Auto-generated destructor stub

//    emit(senalPaquetesEnviadosAMR, contadorEnviadosAMR);
//    emit (senalPaquetesEnviadosWAM, contadorEnviadosWAM);
//    emit (senalPaquetesRecibidosRTP, contadorRecibidosRTP);
}

void NetLayer::initialize (int stage){

    //   if (stage == 2){

    if(stage==0){

//        const char *text = par ("address");
//
//        myAddress = IPv4Address(text);
//        cModule* host = getParentModule();
//        IInterfaceTable *ift = IPvXAddressResolver().interfaceTableOf(host);
//        InterfaceEntry* ie = ift->getInterfaceByName("wlan");
//
//        myAddress = ie->ipv4Data()->getIPAddress();
//        EV << "Dirección del nodo actual: "<< myAddress.str().c_str()<< "\n";
//
  //      std::string miDir =  myAddress.str();
        packetLengthBytesAMR = &par("packetLengthAMR");
      //  packetLengthBytesRTP = &par("packetLengthRTP");
        packetLengthBytesWAM = &par("packetLengthWAM");
        sendIATimeAMR = &par("sendIaTimeAMR");  // volatile parameter
     //   sendIATimeRTP = &par("sendIaTimeRTP");
        sendIATimeWAM = &par("sendIaTimeWAM");
//        contadorEnviadosAMR =0;
//        contadorEnviadosWAM=0;
//        contadorRecibidosRTP=0;
        pkCounter = 0;
      //  numPackets = par ("numPackets");

        WATCH(pkCounter);
        WATCH(myAddress);

        const char *destAddressesPar = par("destAddresses");
        IPv4Address destAddress = IPv4Address(destAddressesPar);
        cStringTokenizer tokenizer(destAddressesPar);
        const char *token;
        while ((token = tokenizer.nextToken())!=NULL)
            destAddresses.push_back(atoi(token));

       // if (destAddresses.size() != 0  && myAddress!= destAddress){

       // if (destAddresses.size() != 0){
            //throw cRuntimeError("At least one address must be specified in the destAddresses parameter!");

            if(myAddress!=destAddress){
            generatePacketAMR = new cMessage("nextPacketAMR");
            generatePacketWAM = new cMessage("nextPacketWAM");
        //    generatePacketRTP = new cMessage("nextPacketRTP");

            //Diferentes momentos de envío de paquetes

            double envioAMR =  uniform(0.001, 0.05);
            double envioWAM =  uniform(0.001, 0.05);
       //     double envioRTP =  uniform(0.001, 0.05);

            scheduleAt(sendIATimeWAM->doubleValue() + envioAMR, generatePacketAMR);
            scheduleAt(sendIATimeWAM->doubleValue() + envioWAM, generatePacketWAM);
       //     scheduleAt(sendIATimeWAM->doubleValue() + envioRTP, generatePacketRTP);

        }
//
//            else{
//            generatePacketRTP = new cMessage("nextPacketRTP");
//            double envioRTP =  uniform(0.001, 0.05);
//            scheduleAt(simTime()+ envioRTP, generatePacketRTP);
//
//
//        }
     //   endToEndDelaySignal = registerSignal("endToEndDelay");
        senalPaquetesEnviadosAMR = registerSignal("enviadosAMR");
        senalPaquetesEnviadosWAM= registerSignal("enviadosWAM");
        senalPaquetesRecibidosRTP = registerSignal("recibidosRTP");
        senalEndToEndDelayRTP = registerSignal("endToEndDelayRTP");

        // hopCountSignal =  registerSignal("hopCount");
        // sourceAddressSignal = registerSignal("sourceAddress");

            }
}

void NetLayer::handleMessage (cMessage *msg){

    if (msg == generatePacketAMR)
    {

        //Envio paquete del tipo AMR
        const char *text = par ("destAddresses");
        IPv4Address destAddress = IPv4Address(text);

       // IPvXAddress destAddress = check_and_cast<IPvXAddress> (IPvXAddressResolver().resolve(par ("destAddresses")));

        char pkname[40];
        // sprintf(pkname,"packet", myAddress, destAddress, pkCounter++);
        //sprintf(pkname,"packet", pkCounter++;)
        sprintf(pkname,"packet");
        pkCounter++;
        EV << "generating packet " << pkname << endl;
        Packet *pk = new Packet(pkname);
        pk->setTimestamp(simTime());
        pk->setByteLength(packetLengthBytesAMR->longValue());
        pk->setSrcAddr(myAddress);
        pk->setDestAddr(destAddress);
        pk->setSpecialField(false);
        send(pk,"out");
        emit (senalPaquetesEnviadosAMR, 1);
       // contadorEnviadosAMR++;
        scheduleAt(simTime() + sendIATimeAMR->doubleValue(), generatePacketAMR);


    }else{

//        if(msg==generatePacketRTP){
//
//            //Envio paquete del tipo RTP
//
//            const char *text = par ("destAddresses");
//                IPv4Address destAddress = IPv4Address(text);
//                char pkname[40];
//                   sprintf(pkname,"packet");
//                   pkCounter++;
//                   EV << "generating packet " << pkname << endl;
//                   Packet *pk = new Packet(pkname);
//                   pk->setTimestamp(simTime());
//                   pk->setByteLength(packetLengthBytesRTP->longValue());
//                   pk->setSrcAddr(myAddress);
//                   pk->setDestAddr(IPv4Address::ALLONES_ADDRESS);
//                   pk->setSpecialField(false);
//                   send(pk,"out");
//                   scheduleAt(simTime() + sendIATimeRTP->doubleValue(), generatePacketRTP);
//     //   }
//        }else{
            if(msg==generatePacketWAM){
                //Envio paquete del tipo WAM
                               const char *text = par ("destAddresses");
                               IPv4Address destAddress = IPv4Address(text);
                            // IPvXAddress destAddress = check_and_cast<IPvXAddress> (IPvXAddressResolver().resolve(par ("destAddresses")));

                               char pkname[40];
                               // sprintf(pkname,"packet", myAddress, destAddress, pkCounter++);
                               //sprintf(pkname,"packet", pkCounter++;)

                               sprintf(pkname,"packet");
                               pkCounter++;
                               EV << "generating packet " << pkname << endl;
                               Packet *pk = new Packet(pkname);
                               pk->setTimestamp(simTime());
                               pk->setByteLength(packetLengthBytesWAM->longValue());
                               pk->setSrcAddr(myAddress);
                               pk->setDestAddr(destAddress);
                               pk->setSpecialField(false);
                               send(pk,"out");
                               emit (senalPaquetesEnviadosWAM, 1);
                              // contadorEnviadosWAM++;
                               scheduleAt(simTime() + sendIATimeWAM->doubleValue(), generatePacketWAM);

            }else{

                // Handle incoming packet
                     Packet *pk = check_and_cast<Packet *>(msg);
                     EV << "El paquete de tamaño original: " << pk->getByteLength() << " bytes ha llegado a su destino!\n";

                     //   EV << "received packet " << pk->getName() << " sent at " << pk->getTimestamp() << endl;

                    emit (senalPaquetesRecibidosRTP, 1);
                  //   contadorRecibidosRTP++;
                     emit (senalEndToEndDelayRTP, simTime() - pk->getTimestamp());
                 //    emit(endToEndDelaySignal, simTime() - pk->getTimestamp());
                     //   emit(hopCountSignal, pk->getHopCount());
                     //    emit(sourceAddressSignal, pk->getSrcAddr());
                     delete pk;

                //     endSimulation();

             //        if(pkCounter==numPackets){
             //
             //        cSimpleModule::endSimulation   ( );
             //
             //        }

                     if (ev.isGUI())
                     {
                         getParentModule()->getDisplayString().setTagArg("i",1,"green");
                         getParentModule()->bubble("Arrived!");


                     }
                 }

            }
        }

 //   }



