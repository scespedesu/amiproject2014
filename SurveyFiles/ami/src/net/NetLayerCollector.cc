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

#include "NetLayerCollector.h"

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

Define_Module(NetLayerCollector);

NetLayerCollector::NetLayerCollector() {
    // TODO Auto-generated constructor stub

}

NetLayerCollector::~NetLayerCollector() {
    // TODO Auto-generated destructor stub
}

void NetLayerCollector::initialize (int stage){

    //   if (stage == 2){

    if(stage==0){


        packetLengthBytesRTP = &par("packetLengthRTP");
     //   packetLengthBytesWAM = &par("packetLengthWAM");
        sendIATimeRTP = &par("sendIaTimeRTP");
        sendIATimeWAM = &par("sendIaTimeWAM");
        pkCounter = 0;
      //  numPackets = par ("numPackets");

        WATCH(pkCounter);
        WATCH(myAddress);
//
//        const char *destAddressesPar = par("destAddresses");
//        IPv4Address destAddress = IPv4Address(destAddressesPar);
//        cStringTokenizer tokenizer(destAddressesPar);
//        const char *token;
//        while ((token = tokenizer.nextToken())!=NULL)
//            destAddresses.push_back(atoi(token));
//
//       // if (destAddresses.size() != 0  && myAddress!= destAddress){

   //   if (destAddresses.size() != 0){
            //throw cRuntimeError("At least one address must be specified in the destAddresses parameter!");

          generatePacketRTP = new cMessage("nextPacketRTP");

            //Diferentes momentos de env�o de paquetes

       //     double envioAMR =  uniform(0.001, 0.05);
      //     double envioWAM =  uniform(0.001, 0.05);
         double envioRTP =  uniform(0.001, 0.05);


          scheduleAt(sendIATimeWAM->doubleValue() + envioRTP, generatePacketRTP);

        }

        endToEndDelaySignal = registerSignal("endToEndDelay");
        // hopCountSignal =  registerSignal("hopCount");
        // sourceAddressSignal = registerSignal("sourceAddress");

            }
//}

void NetLayerCollector::handleMessage (cMessage *msg){


        if(msg==generatePacketRTP){

            //Envio paquete del tipo RTP
                char pkname[40];
                   sprintf(pkname,"packet");
                   pkCounter++;
                   EV << "generating packet " << pkname << endl;
                   Packet *pk = new Packet(pkname);
                   pk->setTimestamp(simTime());
                   pk->setByteLength(packetLengthBytesRTP->longValue());
                   pk->setSrcAddr(myAddress);
                   pk->setDestAddr(IPv4Address::ALLONES_ADDRESS);
                   pk->setSpecialField(false);
                   send(pk,"out");
                   scheduleAt(simTime() + sendIATimeRTP->doubleValue(), generatePacketRTP);
     //   }
        }

        //else{
//            if(msg==generatePacketWAM){
//                //Envio paquete del tipo WAM
//                               const char *text = par ("destAddresses");
//                               IPv4Address destAddress = IPv4Address(text);
//                            // IPvXAddress destAddress = check_and_cast<IPvXAddress> (IPvXAddressResolver().resolve(par ("destAddresses")));
//
//                               char pkname[40];
//                               // sprintf(pkname,"packet", myAddress, destAddress, pkCounter++);
//                               //sprintf(pkname,"packet", pkCounter++;)
//
//                               sprintf(pkname,"packet");
//                               pkCounter++;
//                               EV << "generating packet " << pkname << endl;
//                               Packet *pk = new Packet(pkname);
//                               pk->setTimestamp(simTime());
//                               pk->setByteLength(packetLengthBytesWAM->longValue());
//                               pk->setSrcAddr(myAddress);
//                               pk->setDestAddr(destAddress);
//                               pk->setSpecialField(false);
//                               send(pk,"out");
//                               scheduleAt(simTime() + sendIATimeWAM->doubleValue(), generatePacketWAM);
//

 else{

                // Handle incoming packet
                     Packet *pk = check_and_cast<Packet *>(msg);
                     EV << "El paquete de tama�o original: " << pk->getByteLength() << " bytes ha llegado a su destino!\n";

                     //   EV << "received packet " << pk->getName() << " sent at " << pk->getTimestamp() << endl;
                     emit(endToEndDelaySignal, simTime() - pk->getTimestamp());
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

          //}
      //}

  //  }


