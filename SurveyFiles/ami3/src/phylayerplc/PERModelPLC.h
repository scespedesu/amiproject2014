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

#ifndef PERMODELPLC_H_
#define PERMODELPLC_H_

//#include "BaseModule.h"
#include "MiXiMDefs.h"
#include "AnalogueModel.h"


class PERModelPLC : public AnalogueModel {

protected:
    double packetErrorRate;
    double inferior;
    double superior;

public:
    PERModelPLC();
    virtual ~PERModelPLC();
    /** @brief Initialize the analog model from XML map data.
     *
     * This method should be defined for generic analog model initialization.
     *
     * @param params The parameter map which was filled by XML reader.
     *
     * @return true if the initialization was successfully.
     */
    virtual bool initFromMap(const ParameterMap&);

    virtual void filterSignal(airframe_ptr_t, const Coord&, const Coord&);
};

#endif /* PERMODELPLC_H_ */
