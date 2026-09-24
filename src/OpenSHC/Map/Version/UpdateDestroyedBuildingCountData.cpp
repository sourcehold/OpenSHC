#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_DestroyedBuildingsCountHistory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0044AAA0
    void Version::UpdateDestroyedBuildingCountData(int param_1)
    {
        DAT_DestroyedBuildingsCountHistory::instance[0] = DAT_DestroyedBuildingsCountHistory::instance[0] + param_1;
    }

}
}
