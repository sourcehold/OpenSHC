#include "OpenSHC/Map/Buildings.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004184D0
    void Buildings::UpdateParadeGround3()
    {
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0x1f;
    }

}
}
