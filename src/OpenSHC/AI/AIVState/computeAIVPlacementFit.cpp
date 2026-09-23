#include "../AIVState.func.hpp"

#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    // returns the lowest AIV step (minus one) that can not be placed, 999999 is a perfect fit
    // FUNCTION: STRONGHOLDCRUSADER 0x004EF8C0
    int AIVState::computeAIVPlacementFit(int playerID)
    {
        int minSteps = 1000000;
        DAT_TileMapState::instance.buildingPlacementProperty_7 = 0;
        DAT_TileMapState::instance.buildingPlacementProperty_6 = 0;
        DAT_TileMapState::instance.buildingPlacementProperty_5 = 0;
        DAT_TileMapState::instance.buildingPlacementProperty_3 = 0;
        int index = 0;
        for (int y = 0; y < 100; ++y) {
            for (int x = 0; x < 100; ++x, ++index) {
                int const type = this->constructions[index];
                if (type == 0) {
                    continue;
                }
                if (type == 1) {
                    this->isHandled[index] = 1;
                    continue;
                }
                MappersEnum const mapper = MACRO_CALL_MEMBER(
                    AIVState_Func::convertAIVBuildingTypeToCommandBuildingType, this)((AIV::AIVBuildingType2)type);
                DAT_TileMapState::instance.buildingHeightLimit
                    = DAT_BuildingDefinedData::instance.BuildingPlacement_HeightLimit[MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                        DAT_BuildingsState::ptr)(mapper)];
                DAT_TileMapState::instance.buildingMaxHeightDifference
                    = DAT_BuildingDefinedData::instance.BuildingPlacement_MaxHeightDifference[MACRO_CALL_MEMBER(
                        Map::Buildings::BuildingsState_Func::convertCommandBuildingTypeToBuildingType,
                        DAT_BuildingsState::ptr)(mapper)];
                ++this->buildingCounter;
                uint const realY = this->aivs[playerID].keepYOffset + y;
                uint const realX = this->aivs[playerID].keepXOffset + x;
                if (realX > 399 || realY > 399
                    || !DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[realY * 400 + realX]) {
                    continue;
                }
                int const rowTile = DAT_ViewportRenderState::instance.translationMatrix[realY].addXgetTile;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::storeMinAndMaxHeightOfArea, DAT_TileMapState::ptr)(
                    realX, realY, 1);
                if (MACRO_CALL_MEMBER(Map::TileMapState_Func::isBuildingPlacementAllowedAtTile, DAT_TileMapState::ptr)(
                        rowTile + realX, 0, mapper, 0)) {
                    this->isHandled[index] = 1;
                    // steps is accessed as a flat 100 * 100 array
                    if (this->steps[0][index] < minSteps) {
                        minSteps = this->steps[0][index];
                    }
                    ++this->invalidTileCounter;
                }
            }
        }
        return minSteps - 1;
    }

}
}
