#include "../TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;

    // FUNCTION: STRONGHOLDCRUSADER 0x004FB8E0
    void TileMapState::clearTreeFootprintFlags(int treeID)
    {
        int const treeX = DAT_LandscapeState::instance.trees[treeID].xPosition;
        int const treeY = DAT_LandscapeState::instance.trees[treeID].yPosition;
        this->OrganismLayer[DAT_LandscapeState::instance.trees[treeID].tile] = 0;
        this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile] &= ~L_TREE;
        int index = 0;
        while (true) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, this)(
                index, DAT_LandscapeState::instance.trees[treeID].size);
            int const tile = DAT_ViewportRenderState::instance.translationMatrix[this->buildingY + treeY].addXgetTile
                + treeX + this->buildingX;
            index++;
            this->LogicLayer[tile] &= ~L_TREE_VARIATION;
            if (index >= this->constructionTileCount) {
                break;
            }
        }
    }

}
}
