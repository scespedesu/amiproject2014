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

//
// TODO generated message class
//


cplusplus
{{
#include "IPv4Address.h"
}};

class noncobject IPv4Address;

packet Fragment {
   
  //  int idPacket;
  
    IPv4Address srcAddr;
    IPv4Address destAddr;
//    int srcAddress;
//    int destAddress;
   // int fragmentSize; 
    int originalPacketSize;
    int moreFragments;
    int gateIndex;
    int fragmentId;

}
