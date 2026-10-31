#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Trees::TreeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F37B0
    void Version::UpdateFixTrees2()
    {
        for (int treeID = 1; treeID < 2000; ++treeID) {
            if (DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)1
                || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)2
                || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)3
                || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)4) {
                DAT_LandscapeState::instance.trees[treeID].gmOriginX
                    = DAT_TextureRenderCoreObject::instance
                          .gmFileHeaderColorpaletteArray[DAT_LandscapeState::instance.trees[treeID].treeTypeBasedValue1]
                          .originX;
                DAT_LandscapeState::instance.trees[treeID].gmOriginY
                    = DAT_TextureRenderCoreObject::instance
                          .gmFileHeaderColorpaletteArray[DAT_LandscapeState::instance.trees[treeID].treeTypeBasedValue1]
                          .originY;
                if (MACRO_CALL_MEMBER(Navigation::PathFindingState_Func::findNoTreeInRange, DAT_PathFindingState::ptr)(
                        2, DAT_LandscapeState::instance.trees[treeID].xPosition,
                        DAT_LandscapeState::instance.trees[treeID].yPosition)
                    == 0) {
                    MACRO_CALL_MEMBER(LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(treeID);
                }
            }
        }
    }

}
}
