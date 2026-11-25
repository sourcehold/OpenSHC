#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x004A9680
        void PathFindingState::updateClimbData()
        {
            this->numberOfClimbTeleports = 0;
            this->debugGreatestClimbLoading = 0;
            this->maxClimbDataCount = 0;
            for (DAT_CurrentClimbDataID::instance = 1; DAT_CurrentClimbDataID::instance < countof(this->climbData);
                DAT_CurrentClimbDataID::instance += 1) {
                if (this->climbData[DAT_CurrentClimbDataID::instance].canBeUsed) {
                    this->maxClimbDataCount = DAT_CurrentClimbDataID::instance + 1;
                    (*DAT_ClimbLogicDefinedData::instance
                            .updateFunctions[this->climbData[DAT_CurrentClimbDataID::instance].type])();
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::recountUnitsUsingClimbData,
                        this)(DAT_CurrentClimbDataID::instance);
                    if (!this->climbData[DAT_CurrentClimbDataID::instance].canBeUsed) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                            DAT_CurrentClimbDataID::instance);
                    } else {
                        this->numberOfClimbTeleports += 1;
                        int numberOfUnitsUsing = this->climbData[DAT_CurrentClimbDataID::instance].numberOfUnitsUsing;
                        if (numberOfUnitsUsing > this->debugGreatestClimbLoading) {
                            this->debugGreatestClimbLoading = numberOfUnitsUsing;
                        }
                    }
                }
            }
        }

    }
}
}
