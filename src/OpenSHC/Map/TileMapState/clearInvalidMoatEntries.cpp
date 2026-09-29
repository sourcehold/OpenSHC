
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005006C0
    void TileMapState::clearInvalidMoatEntries()
    {
        for (int moatID = 1; moatID < this->currentMoatCount; moatID++) {
            if (this->moats[moatID].owner == 0) {
                continue;
            }
            int tile = this->moats[moatID].tile;
            if ((DAT_TileMapState::instance.LogicLayer[tile] & (L_MOAT_DUG_OR_PLANNED | L_MOAT)) != 0) {
                continue;
            }
            if (this->BuildingLayer[tile] != 0) {
                continue;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatData, this)(moatID);
        }
    }

}
}
