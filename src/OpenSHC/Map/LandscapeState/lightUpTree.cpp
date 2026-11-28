#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2280
    BOOLEnum LandscapeState::lightUpTree(int tileUnk, int playerID)
    {
        int const treeID = DAT_TileMapState::instance.OrganismLayer[tileUnk];
        if (treeID >= countof(this->trees)) {
            return FALSE;
        }
        if (this->trees[treeID].field_0x98 != 0) {
            return FALSE;
        }
        int const treeType = this->trees[treeID].treeType;
        switch (treeType) {
        case OpenSHC::Map::Trees::TT_TREE_OLIVE:
        case OpenSHC::Map::Trees::TT_TREE_DATE:
        case OpenSHC::Map::Trees::TT_TREE_COCONUT:
        case OpenSHC::Map::Trees::TT_TREE_CHERRY:
            if (DAT_GameState::instance.mapAndTime.burningTreeCount >= 20) {
                return FALSE;
            }
            if (this->trees[treeID].stage < 3) {
                return FALSE;
            }
            this->trees[treeID].stage = 6;
            this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[0][treeType * 8];
            this->trees[treeID].field_0x98 = 20;
            this->trees[treeID].igniterPlayer = playerID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::igniteFireAtTilesDistanceAway,
                DAT_PathFindingState::ptr)(tileUnk, 2, playerID);
            return TRUE;
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_A:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_B:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_C:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_D:
        case OpenSHC::Map::Trees::TT_SHRUB_NEEDLE_PALM_E:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_A:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_B:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_C:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_D:
        case OpenSHC::Map::Trees::TT_SHRUB_PYGMY_E:
        case OpenSHC::Map::Trees::TT_SHRUB_PIPE_CACTUS:
        case OpenSHC::Map::Trees::TT_SHRUB_SUCCULENT:
        case OpenSHC::Map::Trees::TT_SHRUB_CYCAD:
        case OpenSHC::Map::Trees::TT_SHRUB_PRICKLYPEAR:
            this->trees[treeID].state = 3;
            return TRUE;
        case OpenSHC::Map::Trees::TT_TREE_APPLE:
            this->trees[treeID].stageTracker = 0;
            this->trees[treeID].stage = 6;
            this->trees[treeID].field_0x98 = 20;
            this->trees[treeID].igniterPlayer = playerID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::igniteFireAtTilesDistanceAway,
                DAT_PathFindingState::ptr)(tileUnk, 1, playerID);
            return TRUE;
        }
        return FALSE;
    }

}
}
