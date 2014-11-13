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

#ifndef NETWORKTOMACCONTROLINFO_H_
#define NETWORKTOMACCONTROLINFO_H_


#include <omnetpp.h>

#include "MiXiMDefs.h"
#include "SimpleAddress.h"
#include "MACAddress.h"

class NetworkToMacControlInfo : public cObject {

      protected:
    /** @brief MAC address del proximo salto*/
    MACAddress macProximoSalto;
public:
   // NetworkToMacControlInfo();
    NetworkToMacControlInfo (MACAddress macDelProximoSalto);
    virtual ~NetworkToMacControlInfo();
    virtual MACAddress getNextHopMac();

    virtual MACAddress getDest();

     /** @brief Setter method */
     virtual void setNextHopMac( MACAddress addr);
     virtual void setDest (MACAddress addr);

    static cObject* setControlInfo(cMessage *const pMsg, MACAddress pDestAddr);
       /**
        * @brief Extracts the MAC address from the "control info" structure (object).
        *
        * Extract the destination MAC address from the "control info" which was prev. set by NetwToMacControlInfo::setControlInfo().
        *
        * @param pCtrlInfo The "control info" structure (object) prev. set by NetwToMacControlInfo::setControlInfo().
        * @return The MAC address of message receiver.
        */
    // static MACAddress getDestFromControlInfo(const cObject *const pCtrlInfo);

};

#endif /* NETWORKTOMACCONTROLINFO_H_ */
