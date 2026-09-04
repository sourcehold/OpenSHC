#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F2FE0
    BOOLEnum LandscapeState::isTreeAdult(int treeID, int treeUID)
    {
        if (this->trees[treeID].uid != treeUID) {
            return FALSE;
        }
        return 0 < (short)this->trees[treeID].treeAdultHoodStageRelatedVisual3;
    }

}
}
