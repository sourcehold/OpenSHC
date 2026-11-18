#include "../LandscapeState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1.hpp"

#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2E00
    BOOLEnum LandscapeState::setupBabyTreeLocation(uint treeID, int treeType, uint x, uint y)
    {
        int direction = (byte)SEC_RNG::instance.currentNumber2 & 7;
        int climbValueUnk = 3;
        if (treeID & 1) {
            climbValueUnk = 4;
        }
        DAT_PathFindingState::instance.ALG_ResultTile = 0;
        DAT_PathFindingState::instance.ALG_ResultY = 0;
        DAT_PathFindingState::instance.ALG_ResultX = 0;
        bool const onMap
            = x <= 399 && y <= 399 && DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] != 0;
        if (!onMap) {
            return FALSE;
        }
        int const height = DAT_TileMapState::instance
                               .HeightLayer[DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x];
        for (int i = 0; i < 8; ++i) {
            uint const babyX = DAT_OrganismDefinedData::instance.TreeSpreadOffsets[direction].x + x;
            uint const babyY = DAT_OrganismDefinedData::instance.TreeSpreadOffsets[direction].y + y;
            direction += 1;
            if (direction >= 8) {
                direction = 0;
            }
            if (babyX > 399 || babyY > 399
                || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[babyY * 400 + babyX] == 0) {
                continue;
            }
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[babyY].addXgetTile + babyX;
            int const logic2 = DAT_TileMapState::instance.Logic2Layer[tile];
            if (DAT_TileMapState::instance.OrganismLayer[tile] != 0) {
                continue;
            }
            if (DAT_TileMapState::instance.LogicLayer[tile]
                & (LogicHelpers::L_SEA | LogicHelpers::L_PLAIN1_AND_FARM | LogicHelpers::L_BORDER
                    | LogicHelpers::L_BORDER_EDGE | LogicHelpers::L_ROCKY | LogicHelpers::L_WALL_OR_GATEHOUSE
                    | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE_VARIATION | LogicHelpers::L_BOULDERS
                    | LogicHelpers::L_PEBBLES | LogicHelpers::L_IRON | LogicHelpers::L_RIVER | LogicHelpers::L_FORD
                    | LogicHelpers::L_KEEP_NON_MANOR_HOUSE | LogicHelpers::L_MARSH | LogicHelpers::L_MOAT)) {
                continue;
            }
            if (DAT_TileMapState::instance.UnitLayer[tile] != 0) {
                continue;
            }
            if (DAT_TileMapState::instance.BuildingLayer[tile] != 0) {
                continue;
            }
            if (treeType == 1) {
                if (logic2 & 0x90) {
                    continue;
                }
            } else if (!(logic2 & 0x90)) {
                continue;
            }
            int const babyHeight = DAT_TileMapState::instance.HeightLayer[tile];
            if (babyHeight > height + 64 || babyHeight < height - 64) {
                continue;
            }
            if (MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::setupBabyTreeLocationInfo,
                    DAT_PathFindingState::ptr)(climbValueUnk, treeType, babyX, babyY)) {
                DAT_PathFindingState::instance.ALG_ResultTile = tile;
                DAT_PathFindingState::instance.ALG_ResultX = babyX;
                DAT_PathFindingState::instance.ALG_ResultY = babyY;
                return TRUE;
            }
        }
        return FALSE;
    }

}
}
