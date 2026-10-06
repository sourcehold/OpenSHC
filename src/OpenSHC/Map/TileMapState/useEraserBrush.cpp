
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x005017C0
    void TileMapState::useEraserBrush(uint x, uint y, int brush)
    {
        uint baseY = y;
        uint baseX = x;
        brush = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        int baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        /* the original reuses the x parameter as the tile the brush is walking */
        x = baseTile;
        MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::destroyEntitiesOnTile, DAT_EntityState::ptr)(
            baseTile);

        if (brush > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, baseY);
                int organism = (short)this->OrganismLayer[x];
                if (organism != 0) {
                    /* tree ids come first, rock ids are biased by 2000 */
                    if (organism >= 2000) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock,
                            DAT_LandscapeState::ptr)(organism - 2000);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(8, baseX, y);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree,
                            DAT_LandscapeState::ptr)(organism);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer,
                            DAT_PathFindingState::ptr)(3, baseX, y);
                    }
                    DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                }
                index++;
            } while (index < brush);
        }

        y = baseY;
        if (brush > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, baseY);
                this->field151_0x554998 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::validateBuildingPlacementAtTile, this)(0, baseX, y);
                if (this->buildingPlacementFail == FALSE) {
                    if (this->field151_0x554998 != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::spawnEraserTileEffect, this)(
                            0, DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + baseX);
                    } else if (this->field131_0x554954 != 0xffffffff) {
                        /* razing a keep takes the stockpile with it, and the other way round */
                        short owner = DAT_BuildingsState::instance.buildings[this->field131_0x554954].owner;
                        if (this->field131_0x554954 == DAT_GameState::instance.playerDataArray[owner].keep.id
                            && DAT_GameState::instance.playerDataArray[owner].stockpile.id != 0) {
                            this->showNoRubbleWhenDestroyingBuilding = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                                DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[owner].stockpile.id);
                        }
                        if (DAT_BuildingsState::instance.buildings[this->field131_0x554954].buildingType == OpenSHC::Map::Buildings::BT_STOCKPILE
                            && DAT_GameState::instance.playerDataArray[owner].keep.id != 0) {
                            this->showNoRubbleWhenDestroyingBuilding = 1;
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates,
                                DAT_BuildingsState::ptr)(DAT_GameState::instance.playerDataArray[owner].keep.id);
                        }
                        this->showNoRubbleWhenDestroyingBuilding = 1;
                        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::destroyBuildingAndLinkedDuplicates, DAT_BuildingsState::ptr)(
                            this->field131_0x554954);
                    }
                }
                index++;
            } while (index < brush);
        }

        y = baseY;
        if (brush > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, baseY);
                for (int unit = (short)DAT_TileMapState::instance.UnitLayer[x]; unit != 0;
                     unit = DAT_UnitsState::instance.units[unit].nextUnitOnTheSameTile) {
                    DAT_UnitsState::instance.units[unit].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
                index++;
            } while (index < brush);
        }
    }

}
}
