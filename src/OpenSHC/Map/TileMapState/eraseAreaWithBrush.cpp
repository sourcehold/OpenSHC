
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508EC0
    void TileMapState::eraseAreaWithBrush(uint x, uint y, uint brush)
    {
        uint baseX = x;
        if (x > 399) {
            return;
        }
        if (y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }

        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[brush];
        uint baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        /* the original reuses the brush parameter as the saved y and x as the walking tile */
        brush = y;
        x = baseTile;

        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, brush);
                if ((this->LogicLayer[x] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
                int organism = (short)this->OrganismLayer[x];
                if (organism != 0) {
                    /* tree ids come first, rock ids are biased by 2000 */
                    if (organism >= 2000) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeRock, DAT_LandscapeState::ptr)(organism - 2000);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(8, baseX, y);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(organism);
                        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(3, baseX, y);
                    }
                    DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
                    this->field204_0x554a30 = 1;
                }
                index++;
            } while (index < brushSize);
        }

        y = brush;
        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, brush);
                if ((this->LogicLayer[x] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    break;
                }
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
            } while (index < brushSize);
        }

        y = brush;
        if (brushSize > 0) {
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, (int*)&x, (int*)&y, baseTile, brush);
                if ((this->LogicLayer[x] & (L_BORDER | L_BORDER_EDGE)) != 0) {
                    return;
                }
                for (int unit = (short)this->UnitLayer[x]; unit != 0;
                     unit = DAT_UnitsState::instance.units[unit].nextUnitOnTheSameTile) {
                    DAT_UnitsState::instance.units[unit].logicalState = OpenSHC::Map::Units::ULS_REMOVE;
                }
                index++;
            } while (index < brushSize);
        }
    }

}
}
