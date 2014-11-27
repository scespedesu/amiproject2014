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

#include "PERModelPLC.h"
#include "MiXiMAirFrame.h"

//Define_Module(PERModelPLC);
PERModelPLC::PERModelPLC() {
    // TODO Auto-generated constructor stub
    packetErrorRate =0;
    inferior=0;
    superior=0;

    //    configRed = new RoutingTablesConf();

}


PERModelPLC::~PERModelPLC() {
    // TODO Auto-generated destructor stub
}

bool PERModelPLC::initFromMap(const ParameterMap& params) {



    paqDescartados =0;
    //senalPaquetesDescartados = cComponent::registerSignal("descartados");
    ParameterMap::const_iterator it;
    bool                         bInitSuccess = true;

    if ((it = params.find("seed")) != params.end()) {
        srand( ParameterMap::mapped_type(it->second).longValue() );
    }
    if ((it = params.find("packetErrorRate")) != params.end()) {
        packetErrorRate = ParameterMap::mapped_type(it->second).doubleValue();
    }
    else {
        bInitSuccess = false;
        opp_warning("No packetErrorRate defined in config.xml for PERModel!");
    }

    return AnalogueModel::initFromMap(params) && bInitSuccess;
}

void PERModelPLC::filterSignal(airframe_ptr_t frame, const Coord& /*sendersPos*/, const Coord& /*receiverPos*/) {
    Signal&   signal = frame->getSignal();
    //simtime_t start  = signal.getReceptionStart();
    //simtime_t end    = signal.getReceptionEnd();

    double attenuationFactor = 1;  // no attenuation

    packetErrorRate =  uniform(inferior, superior);
    if(packetErrorRate > 0 && uniform(0, 1) < packetErrorRate) {
        attenuationFactor = 0;  // absorb all energy so that the receveir cannot receive anything
        paqDescartados++;

    }

    TimeMapping<Linear>* attMapping = new TimeMapping<Linear> ();
    Argument arg;
    attMapping->setValue(arg, attenuationFactor);
    signal.addAttenuation(attMapping);
}

void PERModelPLC::finish(){

    numPaquetesDescartados.record(paqDescartados);
    numPkDescartados.collect(paqDescartados);
}



