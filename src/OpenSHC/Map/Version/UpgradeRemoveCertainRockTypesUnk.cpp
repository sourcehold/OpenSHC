#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F3840
    void Version::UpgradeRemoveCertainRockTypesUnk()
    {
        for (int rockID = 1; rockID < 4000; ++rockID) {
            if (DAT_LandscapeState::instance.rocks[rockID].one != 0) {
                uint tile = DAT_LandscapeState::instance.rocks[rockID].tile;
                if (DAT_TileMapState::instance.OrganismLayer[tile] != rockID + 2000
                    || (DAT_TileMapState::instance.LogicLayer[tile] & 0x80) == 0) {
                    MACRO_CALL_MEMBER(LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(rockID);
                }
            }
        }
    }

}
}
