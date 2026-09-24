#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2FB0
    BOOLEnum LandscapeState::isTreeAliveAndMatchingUID(int treeID, int treeUID)
    {
        if (this->trees[treeID].uid != treeUID) {
            return FALSE;
        }
        return this->trees[treeID].zeroUpTo2 == 0;
    }

}
}
