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

#ifndef NETLAYERCOLLECTOR_H_
#define NETLAYERCOLLECTOR_H_

#include "IPv4Address.h"
#include "IInterfaceTable.h"
#include "InterfaceTableAccess.h"
#include "NotificationBoard.h"
#include "RoutingTablesConf.h"
#include "BaseModule.h"

class NetLayerCollector : public BaseModule {

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

//long contadorEnviadosRTP;
//long contadorRecibidosAMR;
//long contadorRecibidosWAM;
//


// signals
//simsignal_t endToEndDelaySignal;
simsignal_t senalPaquetesEnviadosRTP;
simsignal_t senalPaquetesRecibidosAMR;
simsignal_t senalPaquetesRecibidosWAM;
simsignal_t senalEndToEndDelayAMR;
simsignal_t senalEndToEndDelayWAM;
simsignal_t senalMedidorFuenteAMR;
simsignal_t senalMedidorFuenteWAM;
simsignal_t senalXPosCollector;
simsignal_t senalYPosCollector;



//simsignal_t hopCountSignal;
//simsignal_t sourceAddressSignal;
public:
NetLayerCollector();
virtual ~NetLayerCollector();

   //virtual void initialize();
   virtual void initialize(int stage);
   virtual void handleMessage(cMessage *msg);
   virtual int numInitStages() const {
       return 2;
   }
};


#endif /* NETLAYERCOLLECTOR_H_ */
