
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
    using OpenSHC::Map::LogicHelpers::L_BORDER_EDGE;
    using OpenSHC::Map::LogicHelpers::L_BOULDERS;
    using OpenSHC::Map::LogicHelpers::L_BUILDING;
    using OpenSHC::Map::LogicHelpers::L_FORD;
    using OpenSHC::Map::LogicHelpers::L_IRON;
    using OpenSHC::Map::LogicHelpers::L_KEEP_NON_MANOR_HOUSE;
    using OpenSHC::Map::LogicHelpers::L_MARSH;
    using OpenSHC::Map::LogicHelpers::L_MOAT;
    using OpenSHC::Map::LogicHelpers::L_PEBBLES;
    using OpenSHC::Map::LogicHelpers::L_PLAIN1_AND_FARM;
    using OpenSHC::Map::LogicHelpers::L_RIVER;
    using OpenSHC::Map::LogicHelpers::L_ROCKY;
    using OpenSHC::Map::LogicHelpers::L_SEA;
    using OpenSHC::Map::LogicHelpers::L_TREE;
    using OpenSHC::Map::LogicHelpers::L_TREE_VARIATION;
    using OpenSHC::Map::LogicHelpers::L_WALL_OR_GATEHOUSE;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00515DA0
    void TileMapState::placeTree(uint x, uint y, undefined4 treeType)
    {
        if (x > 399 || y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }

        int stage = MACRO_CALL_MEMBER(
            OpenSHC::Map::LandscapeState_Func::getValueFrom0UpTo3ForTreeTypeAndTreeStage, DAT_LandscapeState::ptr)(
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::mapUITreeTypeToLogicalTreeType,
                DAT_LandscapeState::ptr)((short)treeType),
            3);
        uint baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[stage];
        if ((this->LogicLayer[baseTile]
                & (L_SEA | L_PLAIN1_AND_FARM | L_BORDER | L_BORDER_EDGE | L_ROCKY | L_WALL_OR_GATEHOUSE | L_BUILDING
                    | L_TREE_VARIATION | L_BOULDERS | L_PEBBLES | L_IRON | L_RIVER | L_FORD | L_KEEP_NON_MANOR_HOUSE
                    | L_MARSH | L_MOAT))
            != 0) {
            return;
        }

        uint tile = baseTile;
        uint brushY = y;
        int index = 0;
        if (brushSize > 0) {
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(
                    1, index, (int*)&tile, (int*)&brushY, baseTile, y);
                if ((this->LogicLayer[tile] & L_BORDER) != 0) {
                    break;
                }
                if ((this->LogicLayer[tile] & (L_WALL_OR_GATEHOUSE | L_BUILDING | L_RIVER | L_KEEP_NON_MANOR_HOUSE))
                    != 0) {
                    return;
                }
                if ((this->LogicLayer[tile] & L_ROCKY) != 0) {
                    return;
                }
                if (this->OrganismLayer[tile] != 0) {
                    return;
                }
                index++;
            } while (index < brushSize);
        }

        int treeID = MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::createTree, DAT_LandscapeState::ptr)(x, y,
            (TreeType)(short)MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::mapUITreeTypeToLogicalTreeType,
                DAT_LandscapeState::ptr)((short)treeType),
            stage, 0, 0, 3);
        this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile]
            = this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile] & ~L_ROCKY;
        this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile]
            = this->LogicLayer[DAT_LandscapeState::instance.trees[treeID].tile] | L_TREE;
        this->OrganismLayer[DAT_LandscapeState::instance.trees[treeID].tile] = (short)treeID;
        MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, this)(treeID, 0);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkagesInAllEightDirections,
            DAT_PathFindingState::ptr)(
            DAT_LandscapeState::instance.trees[treeID].yPosition, DAT_LandscapeState::instance.trees[treeID].tile);
        DAT_PathFindingState::instance.toggleUpdateSeparateAreaTileMap = 1;
    }

}
}
