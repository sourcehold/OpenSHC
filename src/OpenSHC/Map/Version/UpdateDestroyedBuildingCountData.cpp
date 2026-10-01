#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_DestroyedBuildingsCountHistory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044AAA0
    void Version::UpdateDestroyedBuildingCountData(int destroyedCount)
    {
        DAT_DestroyedBuildingsCountHistory::instance[0] += destroyedCount;
    }

}
}
