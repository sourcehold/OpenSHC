#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentRockID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2140
    int LandscapeState::createRock(undefined4 x, undefined4 y, int rockType, undefined4 size, undefined4 orientation)
    {
        // find a free rock slot
        int _rockID;
        for (_rockID = 1; _rockID < 4000; _rockID++) {
            if (this->rocks[_rockID].one == 0) {
                break;
            }
            if (_rockID >= 3999) {
                return 0;
            }
        }
        this->rocks[_rockID].uid = DAT_GameCore::instance.uniqueGameObjectTracker;
        DAT_GameCore::instance.uniqueGameObjectTracker = DAT_GameCore::instance.uniqueGameObjectTracker + 1;
        this->rocks[_rockID].size = (short)size;
        this->rocks[_rockID].y = (ushort)y;
        this->rocks[_rockID].x = (ushort)x;
        this->rocks[_rockID].one = 1;
        this->rocks[_rockID].type = (short)rockType;
        this->rocks[_rockID].tile
            = (int)(short)(ushort)x + DAT_ViewportRenderState::instance.translationMatrix[(short)(ushort)y].addXgetTile;
        this->rocks[_rockID].orientation = (short)orientation;
        this->rocks[_rockID].unknownGMID = (short)DAT_OrganismDefinedData::instance.Rock_field0xe[rockType];
        DAT_CurrentRockID::instance = _rockID;
        (*DAT_OrganismDefinedData::instance.RockTypeFunctions[this->rocks[_rockID].type])();
        return _rockID;
    }

}
}
