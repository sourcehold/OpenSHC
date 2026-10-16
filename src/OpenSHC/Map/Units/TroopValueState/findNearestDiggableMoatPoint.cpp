#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A8A0
        int TroopValueState::findNearestDiggableMoatPoint(int param_1)
        {
            BOOLEnum tile;
            int iVar1;
            tile = MACRO_CALL_MEMBER(Map::TileMapState_Func::findNearestFriendlyMoatTileForDigging,
                DAT_TileMapState::ptr)((int)DAT_UnitsState::instance.units[param_1].owner, param_1, 2);
            if (tile < 0x80000000) {
                iVar1 = MACRO_CALL_MEMBER(Map::TileMapState_Func::setXYBasedOnMoatID, DAT_TileMapState::ptr)(
                    tile, 2, (uint)((int)((int)DAT_UnitsState::instance.units[param_1].x)),
                    (uint)((int)((int)DAT_UnitsState::instance.units[param_1].y)));
                if (0 < iVar1) {
                    this->x = DAT_TileMapState::instance.ALG_MoatXResult;
                    this->y = DAT_TileMapState::instance.ALG_MoatYResult;
                    this->tile = DAT_TileMapState::instance.someMoatTile;
                    return iVar1;
                }
            }
            return 0;
        }

    }
}
}
