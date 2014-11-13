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

package ami.simulations;

import org.mixim.base.connectionManager.ConnectionManager;
import org.mixim.base.modules.BaseWorldUtility;
import org.mixim.modules.connectionManager.UnitDisk;
import ami.nodePLC1.PLCNode1;
import ned.DatarateChannel;

network PLCNetwork1
{
    
    	parameters:
        double playgroundSizeX @unit(m); // x size of the area the nodes are in (in meters)
        double playgroundSizeY @unit(m); // y size of the area the nodes are in (in meters)
        double playgroundSizeZ @unit(m); // z size of the area the nodes are in (in meters)
        int numNodes; // total number of hosts in the network

		  
        @display("bgb=$playgroundSizeX,$playgroundSizeY,white;bgp=0,0");

        //**Signals to collect statistics**//
        //Registers location of each the node during simulation (static)
        @signal[coordX](type="double");
        @statistic[xCoordinates](title="X coordinates"; source="coordX"; record=vector);
        @signal[coordY](type="double");
        @statistic[yCoordinates](title="Y coordinates"; source="coordY"; record=vector);

        //Registers total packets sent during the simulation
        @signal[pktsSent](type="long");
        @statistic[sentPackets](title="numOfPacketsSent"; source="pktsSent"; record=sum);

        //Registers total packets received during the simulation
        @signal[pktsReceived](type="long");
        @statistic[receivedPackets](title="numOfPacketsReceived"; source="pktsReceived"; record=sum);

        //Registers total broadcast received during channel test
        @signal[broadcastRecvd](type="long");
        @statistic[numOfBroadcastRecvd](title="Total Broadcast Recvd"; source="broadcastRecvd"; record=sum);

        //Registers time at which each node learns a path to the gateway (convergence)
        @signal[convergenceTime](type="double");
        @statistic[convergence](title="Convergence"; source="convergenceTime"; record=vector,stats);

        //Registers time at which each node is able to start sending packets (two-way confirmation to collector)
        @signal[timeSending](type="double");
        @statistic[sending](title="timeSending"; source="timeSending"; record=vector,stats);
        //Registers the total control overhead (amount and bytes) sent by all nodes in the network
        @signal[controlOverhead](type="double");
        @statistic[overhead](title="Control overhead"; source="controlOverhead"; record=count,sum);

        //Registers the total data packets (amount and bytes) sent by all nodes in the network
        @signal[dataTraffic](type="double");
        @statistic[traffic](title="Data Traffic"; source="dataTraffic"; record=count,sum);

        //Registers the average end-to-end delay for all packets received during the simulation
        @signal[endToEndDelay](type="double");
        @statistic[avgDelay](title="averageDelay"; source="endToEndDelay"; record=mean,stats);
 
  types:
        channel C extends DatarateChannel
        {
            delay = uniform(0.1ms, 10ms);
            datarate = 250kbps;
            per = 0.01;
        }
        
    submodules:
        connectionManager: ConnectionManager {
        //connectionManager: UnitDisk {
            parameters:
                //radioRange = 50m;
                drawMaxIntfDist = true;
                @display("p=223,29;b=42,42,rect,green;i=abstract/multicast");
        }
        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = playgroundSizeX;
                playgroundSizeY = playgroundSizeY;
                playgroundSizeZ = playgroundSizeZ;
                @display("p=43,151;i=misc/globe");
        }
   
        node[numNodes]: PLCNode1 {
            parameters:
                
                 @display("i=misc/node_vs,gold;is=vs");
          
        }
        
        
    connections allowunconnected:

}

