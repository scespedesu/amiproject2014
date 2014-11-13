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

package ami.net;

simple NetLayerCollector like IApp
{
    parameters:
        
        //int address;  // local node address
        
        string address;
        //double coverageArea @unit(m) = default(-1m);
        double coverageArea @unit(m) = default(100m);
     //   string destAddresses;  // destination addresses
   //     volatile double sendIaTimeAMR @unit(s) = default(exponential(1s)); // time between generating packets
        volatile double sendIaTimeRTP @unit(s) = default(exponential(1s));
        volatile double sendIaTimeWAM @unit(s) = default(exponential(1s));
  //      volatile int packetLengthAMR @unit(byte);  // length of one message (fixed! no "volatile" modifier)
        volatile int packetLengthRTP@unit(byte);
   //     volatile int packetLengthWAM @unit(byte);
       // int numPackets;
        @display("i=block/browser");
        @signal[endToEndDelay](type="simtime_t");
       // @signal[hopCount](type="int");
       // @signal[sourceAddress](type="int");
        @statistic[endToEndDelay](title="end-to-end delay of arrived packets";source="endToEndDelay";unit=s;record=vector,mean,max;interpolationmode=none);
        //@statistic[hopCount](title="hop count of arrived packets";interpolationmode=none;record=vector?,mean,max);
        //@statistic[sourceAddress](title="source address of arrived packets";interpolationmode=none;record=vector?);
    gates:
        input in;
        output out;
}


