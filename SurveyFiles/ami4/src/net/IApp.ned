//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 1992-2008 Andras Varga
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package ami.net;



//
// Interface for network traffic generator modules that
// can be used in Node.
//
moduleinterface IApp
{

    parameters:
    string  address;  // local node address
    
  //    IPv4Address address;
    gates:
        input in;
        output out;
}


