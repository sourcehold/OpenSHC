
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

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

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508DD0
    void TileMapState::applyTreeBrushToLogicalLayer(int treeID, int noVariation)
    {
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[MACRO_CALL_MEMBER(
            OpenSHC::Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, DAT_LandscapeState::ptr)(
            DAT_LandscapeState::instance.trees[treeID].treeType, DAT_LandscapeState::instance.trees[treeID].stage)];
        uint baseY = DAT_LandscapeState::instance.trees[treeID].yPosition;
        int baseTile = DAT_LandscapeState::instance.trees[treeID].xPosition
            + DAT_ViewportRenderState::instance.translationMatrix[baseY].addXgetTile;

        int tile = baseTile;
        uint y = baseY;
        for (int tileIndex = 0; tileIndex < brushSize; tileIndex++) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                1, tileIndex, &tile, (int*)&y, baseTile, baseY);
            if ((this->LogicLayer[tile] & L_BORDER) != 0) {
                break;
            }
            if ((this->LogicLayer[tile] & (L_SEA | L_MARSH | L_MOAT)) == 0) {
                if (noVariation == 0) {
                    this->LogicLayer[tile] = this->LogicLayer[tile] | L_TREE_VARIATION;
                } else {
                    this->LogicLayer[tile] = this->LogicLayer[tile] & ~L_TREE_VARIATION;
                }
            }
        }
        MACRO_CALL_MEMBER(
            OpenSHC::Map::Navigation::PathFindingState_Func::updateWalkAndPathLayer, DAT_PathFindingState::ptr)(7,
            DAT_LandscapeState::instance.trees[treeID].xPosition, DAT_LandscapeState::instance.trees[treeID].yPosition);
    }

}
}
