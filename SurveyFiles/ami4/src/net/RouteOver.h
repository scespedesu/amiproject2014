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

#ifndef ROUTEOVER_H_
#define ROUTEOVER_H_
#include "Packet_m.h"
#include "Fragment_m.h"
#include "RoutingTablesConf.h"
#include "NotificationBoard.h"
#include "IInterfaceTable.h"
#include "BaseModule.h"


#include <csimplemodule.h>

class RouteOver : public BaseModule  {
public:
    RouteOver();

    IPv4Address myAddress;
    RoutingTablesConf *configRed;
    virtual ~RouteOver();

private:
       simsignal_t senalLlegada;
       simsignal_t senalReDireccion;
       double distancia;

protected:

    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *msg);
};

#endif /* ROUTEOVER_H_ */
