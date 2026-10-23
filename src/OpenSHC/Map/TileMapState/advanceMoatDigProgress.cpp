#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;

    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_MOAT_DUG_OR_PLANNED;
    using OpenSHC::Map::LogicHelpers::L_PLAIN2_AND_PITCH;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00500500
    undefined4 TileMapState::advanceMoatDigProgress(int moatID)
    {
        this->moats[moatID].fillProgress = this->moats[moatID].fillProgress + 1;
        if ((char)this->moats[moatID].fillProgress <= 3) {
            return 0;
        }

        int tile = this->moats[moatID].tile;
        this->moats[moatID].someCountDown = 0;
        this->moats[moatID].fillProgress = 4;
        this->moats[moatID].stage = 2;
        this->HeightLayer[tile] = 0;
        this->LogicLayer[this->moats[moatID].tile]
            = this->LogicLayer[this->moats[moatID].tile] & ~L_MOAT_DUG_OR_PLANNED;
        this->LogicLayer[this->moats[moatID].tile] = this->LogicLayer[this->moats[moatID].tile] & ~L_PLAIN2_AND_PITCH;
        this->LogicLayer[this->moats[moatID].tile] = this->LogicLayer[this->moats[moatID].tile] | L_MOAT;
        this->Logic2Layer[this->moats[moatID].tile] = 0;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(2, this->moats[moatID].x, this->moats[moatID].y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(this->moats[moatID].y, this->moats[moatID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        return 1;
    }

}
}
