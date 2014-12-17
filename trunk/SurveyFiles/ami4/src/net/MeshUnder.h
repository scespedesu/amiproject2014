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

#ifndef MESHUNDER_H_
#define MESHUNDER_H_
#include "Packet_m.h"
#include "Fragment_m.h"
#include "RoutingTablesConf.h"
#include "NotificationBoard.h"
#include "IInterfaceTable.h"
#include "ArpInterface.h"
#include "BaseModule.h"
#include "ARP.h"

#include <csimplemodule.h>

class MeshUnder: public BaseModule {
public:
    MeshUnder();
    //void handleMessage(cMessage *msg);

        ARP* arp;
        IPv4Address myAddress;
        MACAddress myMacAddress;
       // MACAddress packetMacDestino;
        RoutingTablesConf *configRed;
        MACAddress proximoSalto;
        int contadorPaquetes;

    virtual ~MeshUnder();

private:
 //      simsignal_t senalLlegada;
   //    simsignal_t senalReDireccion;
    simsignal_t senalForwardedAMR;
    simsignal_t senalForwardedWAM;
    simsignal_t senalForwardedRTP;
//    simsignal_t senalNumeroSaltosWAM;
//    simsignal_t senalNumeroSaltosRTP;
            double distancia;


protected:

    virtual void initialize(int stage);
//    virtual int numInitStages() const {
//        return 4;
//    }
    virtual void handleMessage(cMessage *msg);
};

#endif /* MESHUNDER_H_ */
