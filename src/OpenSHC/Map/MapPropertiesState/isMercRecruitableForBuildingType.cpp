#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Game::GameMode2;

    // FUNCTION: STRONGHOLDCRUSADER 0x004BB0B0
    int MapPropertiesState::isMercRecruitableForBuildingType(int buildingType)
    {
        if (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_EDITOR) {
            return 1;
        }
        return this->buildingAvailabilityArray2[buildingType];
    }

}
}
