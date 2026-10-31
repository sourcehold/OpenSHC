#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Trees/TreeType.hpp"

#include "OpenSHC/Globals/DAT_CurrentTreeID.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_OrganismDefinedData.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Trees::TreeType;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F38A0
    void Version::UpdateTreesOfCertainTypes()
    {
        for (int treeID = 1; treeID < 2000; ++treeID) {
            if (DAT_LandscapeState::instance.trees[treeID].state == 2
                && (DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)16
                    || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)17
                    || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)18
                    || DAT_LandscapeState::instance.trees[treeID].treeType == (TreeType)19)) {
                NoArgCallback* update
                    = DAT_OrganismDefinedData::instance.UpdateTree[DAT_LandscapeState::instance.trees[treeID].treeType];
                DAT_LandscapeState::instance.trees[treeID].state = 4;
                DAT_CurrentTreeID::instance = treeID;
                update();
            }
        }
    }

}
}
