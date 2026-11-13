#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_MOAT;

    // FUNCTION: STRONGHOLDCRUSADER 0x005113F0
    BOOLEnum TileMapState::removeMoat(uint moatID, int unused)
    {
        this->moats[moatID].fillProgress -= 1;
        if (this->moats[moatID].fillProgress <= 0) {
            this->HeightLayer[this->moats[moatID].tile] = 8;
            this->LogicLayer[this->moats[moatID].tile] &= ~L_MOAT;
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
        return FALSE;
    }

}
}
