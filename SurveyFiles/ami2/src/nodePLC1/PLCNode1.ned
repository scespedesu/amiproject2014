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

package ami.nodePLC1;

import ami.net.IApp;
import ami.net.RoutingPLC;
import ami.net.Dummy;
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
module PLCNode1
{
    parameters:

        @node;
        //int address;
        string addressNode = default("");
        
        string appType;
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
                @display("p=229,105;i=block/cogwheel");
        }
        notificationBoard: NotificationBoard {
            parameters:
                @display("p=229,40");
        }

        interfaceTable: InterfaceTable {
            @display("p=229,164");
        }
//        
//         mobility: StationaryMobility {
//
//            @display("p=229,251");
//        }


        app: <appType> like IApp {
            parameters:
                address = addressNode;
                @display("p=140,33");
        }

        dummy: Dummy {
            parameters:
                @display("p=140,94");

            gates:
                lowerIn[1];
                lowerOut[1];


        }

        routing: RoutingPLC {
            parameters:
                @display("p=140,170");
            
        }

        wlan: Nic802154_TI_CC2420 {
            @display("p=140,245");
         //   address = addrStr;


        }

       //Modulo de bateria. Solucionar problemas de update y publish

        battery: SimpleBattery {

            parameters:

                nominal = 99999mAh;
                capacity = default(battery.nominal);
                voltage = default(3.3 V);
                resolution = default(60s);
                publishDelta = default(1);
                publishTime = default(0);
                numDevices = default(1);
                

                @display("p=229,238");
        }

        routingTable: RoutingTable {

            @display("p=321,94");
        }


        autoConf: HostAutoConfigurator {

            @display("p=321,33");
        }



        batteryStats: BatteryStats {

            parameters:

                detail = default(false);
                timeSeries = default(false);
                @display("p=343,245;i=block/table,#FF8040");
        }


    connections:


        dummy.upperOut --> app.in;
        dummy.upperIn <-- app.out;
        routing.localOut --> dummy.lowerIn[0];
        routing.localIn <-- dummy.lowerOut[0];
        wlan.upperLayerOut --> routing.lowerGateIn;
        wlan.upperLayerIn <-- routing.lowerGateOut;
        dummy.lowerControlIn <-- routing.upperControlOut;
        dummy.lowerControlOut --> routing.upperControlIn;
        wlan.upperControlOut --> routing.lowerControlIn;
        wlan.upperControlIn <-- routing.lowerControlOut;
        radioIn --> wlan.radioIn;
}

