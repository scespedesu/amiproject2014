//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//


//
// Represents a packet in the network.
//

cplusplus
{{
#include "IPv4Address.h"
}};

class noncobject IPv4Address;

packet Packet
{
    int sourceID;
    IPv4Address srcAddr;
    IPv4Address destAddr;
    int hopCount;
    int packetSize;
    bool specialField;
    int outGateIndex;
}