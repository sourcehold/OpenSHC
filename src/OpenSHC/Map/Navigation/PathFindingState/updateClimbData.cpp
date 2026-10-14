#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_ClimbLogicDefinedData.hpp"
#include "OpenSHC/Globals/DAT_CurrentClimbDataID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A9680
        void PathFindingState::updateClimbData()
        {
            int iVar1;
            this->numberOfClimbTeleports = 0;
            this->debugGreatestClimbLoading = 0;
            this->maxClimbDataCount = 0;
            DAT_CurrentClimbDataID::instance = 1;
            do {
                if (this->climbData[DAT_CurrentClimbDataID::instance].canBeUsed != 0) {
                    this->maxClimbDataCount = DAT_CurrentClimbDataID::instance + 1;
                    (*DAT_ClimbLogicDefinedData::instance
                            .updateFunctions[this->climbData[DAT_CurrentClimbDataID::instance].type])();
                    MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::recountUnitsUsingClimbData,
                        this)(DAT_CurrentClimbDataID::instance);
                    if (this->climbData[DAT_CurrentClimbDataID::instance].canBeUsed == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::clearClimbData, this)(
                            DAT_CurrentClimbDataID::instance);
                        iVar1 = this->debugGreatestClimbLoading;
                    } else {
                        this->numberOfClimbTeleports = this->numberOfClimbTeleports + 1;
                        iVar1 = this->climbData[DAT_CurrentClimbDataID::instance].numberOfUnitsUsing;
                        if (iVar1 <= this->debugGreatestClimbLoading)
                            goto LAB_004a9740;
                    }
                    this->debugGreatestClimbLoading = iVar1;
                }
            LAB_004a9740:
                DAT_CurrentClimbDataID::instance = DAT_CurrentClimbDataID::instance + 1;
                if (199 < DAT_CurrentClimbDataID::instance) {
                    return;
                }
            } while (true);
        }

    }
}
}
