#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A0A0
    void Version::UpgradeFirst9Buildings()
    {
        for (int buildingID = 1; buildingID < 9; buildingID++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupBarracksCampgroundPositions,
                DAT_BuildingsState::ptr)(buildingID);
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::setupMercenaryPostCampgroundPositions,
                DAT_BuildingsState::ptr)(buildingID);
        }
    }

}
}
