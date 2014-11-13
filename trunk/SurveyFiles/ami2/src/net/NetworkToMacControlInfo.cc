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

#include "NetworkToMacControlInfo.h"


cObject* NetworkToMacControlInfo::setControlInfo(cMessage * const pMsg, MACAddress destAddr)
{
    NetworkToMacControlInfo *cCtrlInfo = new NetworkToMacControlInfo (destAddr);
    pMsg->setControlInfo(cCtrlInfo);

    return cCtrlInfo;
}

NetworkToMacControlInfo :: NetworkToMacControlInfo (MACAddress macDelProximoSalto){

    macProximoSalto = macDelProximoSalto;
}

NetworkToMacControlInfo::~NetworkToMacControlInfo() {
    // TODO Auto-generated destructor stub
}

MACAddress NetworkToMacControlInfo::getNextHopMac (){

                  return macProximoSalto;
}

MACAddress NetworkToMacControlInfo::getDest (){

                  return macProximoSalto;
}

void NetworkToMacControlInfo :: setNextHopMac(MACAddress addr){

            macProximoSalto = addr;
}

void NetworkToMacControlInfo :: setDest(MACAddress addr){

            macProximoSalto = addr;
}




//static MACAddress NetworkToMacControlInfo::getDestFromControlInfo(const cObject * const pCtrlInfo)
//{
////    const tNetwToMacControlInfoBase * const cCtrlInfo = dynamic_cast<const tNetwToMacControlInfoBase *>(pCtrlInfo);
////
////    assert(cCtrlInfo);
//    return cCtrlInfo->getDest();
//}
