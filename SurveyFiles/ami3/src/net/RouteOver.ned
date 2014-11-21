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
// Models a router.
//
simple RouteOver
{
    parameters:
        @display("i=block/switch");
        @signal[drop](type="long");
        @signal[outputIf](type="int");
        @statistic[drop](title="dropped packet byte length";unit=bytes;record=vector?,count,sum;interpolationmode=none);
        @statistic[outputIf](title="output interface for each routed packet";record=histogram;interpolationmode=none);
        double distance @unit(m) = default(100m);
    gates:
        input in;
        output out; //hacia adaptation
        input localIn; //desde el nivel de app
        output localOut;  //hacia el nivel de app
}


