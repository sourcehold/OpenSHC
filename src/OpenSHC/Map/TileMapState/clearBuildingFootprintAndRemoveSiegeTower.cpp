#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_CRENEL;
    using OpenSHC::Map::LogicHelpers::L_CRENEL_VARIATIONUnk;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_STAIRS;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FAC70
    void TileMapState::clearBuildingFootprintAndRemoveSiegeTower(int x, int y, int size)
    {
        int tileIndex = 0;

        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(tileIndex, size);
            int tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + y].addXgetTile
                + this->buildingX + x;
            this->LogicLayer[tile] &= ~(L_WALL_OR_GATEHOUSE | L_CRENEL | L_BUILDING | L_STAIRS | L_CRENEL_VARIATIONUnk
                | L_KEEP_NON_MANOR_HOUSE);
            this->BuildingLayer[tile] = 0;
            this->HeightLayer[tile] = this->DefaultHeightLayer[tile];
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
                DAT_PathFindingState::ptr)(
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile], tile);
            int unitID = this->UnitLayer[tile];
            if (unitID != 0 && DAT_UnitsState::instance.units[unitID].unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                DAT_UnitsState::instance.units[unitID].state.generic = OpenSHC::Map::Units::States::US_DISAPPEAR;
            }
            tileIndex++;
            if (tileIndex >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
