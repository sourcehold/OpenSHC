#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // healthDelta is added as 16 bit; the hit points are then tested signed (test cx,cx / jg 0x4F3047).
    // FUNCTION: STRONGHOLDCRUSADER 0x004F3010
    BOOLEnum LandscapeState::damageTreeAndTriggerDeathIfDepleted(int treeID, undefined4 healthDelta, int treeUID)
    {
        if (this->trees[treeID].uid == treeUID && this->trees[treeID].zeroUpTo2 == 0) {
            this->trees[treeID].stageRelated1 += (short)healthDelta;
            if ((short)this->trees[treeID].stageRelated1 <= 0) {
                this->trees[treeID].stageRelated1 = 0;
                this->trees[treeID].zeroUpTo2 = 1;
                this->trees[treeID].animationFrameIndex = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::applyTreeBrushToLogicalLayer, DAT_TileMapState::ptr)(
                    treeID, 1);
                return TRUE;
            }
        }
        return FALSE;
    }

}
}