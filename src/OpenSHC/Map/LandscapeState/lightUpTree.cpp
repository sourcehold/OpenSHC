#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // OrganismLayer is read signed (movsx); ids >= 2000 (rocks, signed jl 0x4F2291) and burning trees fail.
    // Types 1-4 need burningTreeCount < 20 (signed jge 0x4F22D4) and stage >= 3. Their stageTracker is read
    // from TreeStageLevels with a row stride of 0x20 bytes (shl ecx, 5 at 0x4F22E3), i.e. flat index type * 8,
    // not TreeStageLevels[type][0] (row stride 0x1C).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F2280
    BOOLEnum LandscapeState::lightUpTree(int tileUnk, int playerID)
    {
        int const treeID = DAT_TileMapState::instance.OrganismLayer[tileUnk];
        if (treeID >= 2000) {
            return FALSE;
        }
        if (this->trees[treeID].field92_0x98 != 0) {
            return FALSE;
        }
        int const treeType = this->trees[treeID].treeType;
        switch (treeType) {
        case OpenSHC::Map::Trees::TT_CHESTNUT:
        case OpenSHC::Map::Trees::TT_OAK:
        case OpenSHC::Map::Trees::TT_PINE:
        case OpenSHC::Map::Trees::TT_BIRCH:
            if (DAT_GameState::instance.mapAndTime.burningTreeCount >= 20) {
                return FALSE;
            }
            if (this->trees[treeID].stage < 3) {
                return FALSE;
            }
            this->trees[treeID].stage = 6;
            this->trees[treeID].stageTracker = DAT_OrganismDefinedData::instance.TreeStageLevels[0][treeType * 8];
            this->trees[treeID].field92_0x98 = 20;
            this->trees[treeID].igniterPlayer = (short)playerID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::igniteFireAtTilesDistanceAway,
                DAT_PathFindingState::ptr)(tileUnk, 2, playerID);
            return TRUE;
        case OpenSHC::Map::Trees::TT_SHRUB1A:
        case OpenSHC::Map::Trees::TT_SHRUB1B:
        case OpenSHC::Map::Trees::TT_SHRUB1C:
        case OpenSHC::Map::Trees::TT_SHRUB1D:
        case OpenSHC::Map::Trees::TT_SHRUB1E:
        case OpenSHC::Map::Trees::TT_SHRUB2A:
        case OpenSHC::Map::Trees::TT_SHRUB2B:
        case OpenSHC::Map::Trees::TT_SHRUB2C:
        case OpenSHC::Map::Trees::TT_SHRUB2D:
        case OpenSHC::Map::Trees::TT_SHRUB2E:
        case OpenSHC::Map::Trees::TT_SHRUB3A:
        case OpenSHC::Map::Trees::TT_SHRUB3B:
        case OpenSHC::Map::Trees::TT_SHRUB3C:
        case OpenSHC::Map::Trees::TT_SHRUB3D:
            this->trees[treeID].state = 3;
            return TRUE;
        case OpenSHC::Map::Trees::TT_APPLEUnk:
            this->trees[treeID].stageTracker = 0;
            this->trees[treeID].stage = 6;
            this->trees[treeID].field92_0x98 = 20;
            this->trees[treeID].igniterPlayer = (short)playerID;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::igniteFireAtTilesDistanceAway,
                DAT_PathFindingState::ptr)(tileUnk, 1, playerID);
            return TRUE;
        }
        return FALSE;
    }

}
}
