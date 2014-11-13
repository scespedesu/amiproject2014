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
simple MeshUnder
{
    parameters:
        @display("i=block/switch");
       // double coverageArea @unit(m) = default(-1m);
      //  @signal[llegada](type="int");
   //    @signal[redireccion](type="string");
 		  @signal[llegada](type="int");
  		  @signal[redireccion](type="int");
      //  @signal[drop](type="long");
      //  @signal[outputIf](type="int");
        @statistic[llegadaPaquete](title="Paquete entregado en destino";source = "llegada"; record=vector, count;interpolationmode=none);
        @statistic[redireccionPaquete](title="Paquete reenviado";source = "redireccion"; record=vector, count;interpolationmode=none);
    	double distance  @unit(m) = default(150m);
      //  @statistic[drop](title="dropped packet byte length";unit=bytes;record=vector?,count,sum;interpolationmode=none);
     //   @statistic[outputIf](title="output interface for each routed packet";record=histogram;interpolationmode=none);
    gates:
        input in[];
        output out[];
        input localIn;
        output localOut;
        input lowerGateIn;
        output lowerGateOut;
        input lowerControlIn;
        output lowerControlOut;
        input upperControlIn;
        output upperControlOut;
}


