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

package ami.nodeRouteOver;

import ami.net.IApp;
import ami.net.RouteOver;
import ami.net.Adaptation;
import org.mixim.modules.nic.Nic802154_TI_CC2420;
import org.mixim.modules.power.battery.SimpleBattery;
import inet.mobility.models.StationaryMobility;
import org.mixim.modules.power.battery.BatteryStats;
import inet.networklayer.common.InterfaceTable;
import inet.base.NotificationBoard;
import inet.networklayer.autorouting.ipv4.HostAutoConfigurator;
import inet.networklayer.ipv4.RoutingTable;

//
// A "Node" consists of a Routing plus an App module which represents the
// aggregate traffic of the subnets connected to that router.
//
module WirelessNodeRO
{
    parameters:

        @node;
        //int address;
        string addressNode;
        string netType;
        //string addrStr;
        string mobilityType = default("StationaryMobility"); //type of the mobility module
       //  string mobilityType = default(numRadios > 0 ? "StationaryMobility" : "");

   //    string mobilityType;

    gates:

        input radioIn; // gate for sendDirect

    types:
    submodules:

        mobility: <mobilityType> like inet.mobility.IMobility {
            parameters:
                @display("p=227,153;i=block/cogwheel");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=227,33");
        }

        interfaceTable: InterfaceTable {
            @display("p=227,270");
        }
//        
//         mobility: StationaryMobility {
//
//            @display("p=229,251");
//        }


        net: <netType> like IApp {
            parameters:
                address = addressNode;
                @display("p=140,33");
        }

        adaptation: Adaptation {
            parameters:
                @display("p=140,164");

            gates:
                lowerIn[1];
                lowerOut[1];

        }

        routing: RouteOver {
            parameters:
                @display("p=140,92");
        }

        wlan: Nic802154_TI_CC2420 {
            @display("p=140,231");
         //   address = addrStr;


        }

       //Modulo de bateria. Solucionar problemas de update y publish

        battery: SimpleBattery {

            parameters:

                nominal = 99999mAh;
                capacity = default(battery.nominal);
                voltage = default(3.3 V);
                resolution = default(60s);
                publishDelta = default(0.1);
                publishTime = default(0);
                numDevices = default(1);

                @display("p=305,33");
        }

        routingTable: RoutingTable {

            @display("p=227,209");
        }


        autoConf: HostAutoConfigurator {

            @display("p=227,92");
        }



        batteryStats: BatteryStats {

            parameters:

                detail = default(false);
                timeSeries = default(false);
                @display("p=305,221;i=block/table,#FF8040");
        }


    connections:


        routing.localOut --> net.in;
        routing.localIn <-- net.out;
        routing.out --> adaptation.upperIn;
        routing.in <-- adaptation.upperOut;
        adaptation.lowerOut[0] --> wlan.upperLayerIn;
        adaptation.lowerIn[0] <-- wlan.upperLayerOut;
        adaptation.lowerControlOut --> wlan.upperControlIn;
        adaptation.lowerControlIn <-- wlan.upperControlOut;
        radioIn --> wlan.radioIn;


//        adaptation.upperOut --> net.in;
//        adaptation.upperIn <-- net.out;
//        routing.localOut --> adaptation.lowerIn[0];
//        routing.localIn <-- adaptation.lowerOut[0];
//        wlan.upperLayerOut --> routing.lowerGateIn;
//        wlan.upperLayerIn <-- routing.lowerGateOut;
//        wlan.upperControlOut --> routing.lowerControlIn;
//        wlan.upperControlIn <-- routing.lowerControlOut;
      //  radioIn --> wlan.radioIn;
}

