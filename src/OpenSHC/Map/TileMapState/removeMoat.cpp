
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005113F0
    BOOLEnum TileMapState::removeMoat(uint moatID, int param_2)
    {
        this->moats[moatID].fillProgress = this->moats[moatID].fillProgress - 1;
        if ((char)this->moats[moatID].fillProgress >= 1) {
            return FALSE;
        }

        this->HeightLayer[this->moats[moatID].tile] = 8;
        this->LogicLayer[this->moats[moatID].tile] = this->LogicLayer[this->moats[moatID].tile] & ~L_MOAT;
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
            DAT_PathFindingState::ptr)(2, this->moats[moatID].x, this->moats[moatID].y);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(this->moats[moatID].y, this->moats[moatID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
        int tile = this->moats[moatID].tile;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::clearMoatData, this)(moatID);
        if (this->BuildingLayer[tile] != 0) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, this)(
                this->BuildingLayer[tile]);
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::triggerMinimapRedraw, DAT_MinimapViewState::ptr)(1);
        return TRUE;
    }

}
}
