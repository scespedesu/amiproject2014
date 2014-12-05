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

#ifndef NETLAYER_H_
#define NETLAYER_H_

#include "IPv4Address.h"
#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "NotificationBoard.h"
#include "RoutingTablesConf.h"
#include "BaseModule.h"

class NetLayer : public BaseModule {

    private:
    // configuration
   // int myAddress;

    IPv4Address myAddress;
    IInterfaceTable *ift;
    NotificationBoard *nb;
   // int numPackets;
    std::vector<int> destAddresses;
    cPar *sendIATimeAMR;
    cPar *sendIATimeRTP;
    cPar *sendIATimeWAM;
    cPar *packetLengthBytesAMR;
    cPar *packetLengthBytesRTP;
    cPar *packetLengthBytesWAM;
    RoutingTablesConf *configRed;

    // state
    cMessage *generatePacketAMR;
    cMessage *generatePacketRTP;
    cMessage *generatePacketWAM;

    long pkCounter;
//
//    long contadorEnviadosAMR;
//
//    long contadorEnviadosWAM;
//
//    long contadorRecibidosRTP;


    // signals
  //  simsignal_t endToEndDelaySignal;
    simsignal_t senalPaquetesEnviadosAMR;
    simsignal_t senalPaquetesEnviadosWAM;
    simsignal_t senalPaquetesRecibidosRTP;
    simsignal_t senalEndToEndDelayRTP;
//    simsignal_t senalXPos;
//    simsignal_t senalYPos;

 //   simsignal_t hopCountSignal;
   // simsignal_t sourceAddressSignal;
public:
    NetLayer();
    virtual ~NetLayer();

       //virtual void initialize();
       virtual void initialize(int stage);
       virtual void handleMessage(cMessage *msg);
       virtual int numInitStages() const {
           return 2;
       }
};

#endif /* NETLAYER_H_ */
