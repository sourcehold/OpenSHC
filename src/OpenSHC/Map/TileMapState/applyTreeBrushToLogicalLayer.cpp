#include "../TileMapState.func.hpp"

#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_BORDER;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;

    // FUNCTION: STRONGHOLDCRUSADER 0x00508DD0
    void TileMapState::applyTreeBrushToLogicalLayer(int treeID, int noVariation)
    {
        int const brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[MACRO_CALL_MEMBER(
            OpenSHC::Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, DAT_LandscapeState::ptr)(
            DAT_LandscapeState::instance.trees[treeID].treeType, DAT_LandscapeState::instance.trees[treeID].stage)];
        int tile = DAT_LandscapeState::instance.trees[treeID].xPosition
            + DAT_ViewportRenderState::instance.translationMatrix[DAT_LandscapeState::instance.trees[treeID].yPosition]
                  .addXgetTile;
        int brushY = DAT_LandscapeState::instance.trees[treeID].yPosition;
        int const baseTile = tile;
        int const baseY = brushY;
        for (int tileIndex = 0; tileIndex < brushSize; tileIndex++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, tileIndex, &tile, &brushY, baseTile, baseY);
            if ((this->LogicLayer[tile] & L_BORDER) != 0) {
                break;
            }
            if ((this->LogicLayer[tile] & (L_SEA | L_MARSH | L_MOAT)) != 0) {
                continue;
            }
            if (noVariation != 0) {
                this->LogicLayer[tile] &= ~L_TREE_VARIATION;
            } else {
                this->LogicLayer[tile] |= L_TREE_VARIATION;
            }
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(7,
            DAT_LandscapeState::instance.trees[treeID].xPosition, DAT_LandscapeState::instance.trees[treeID].yPosition);
    }

}
}
