#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Buildings::Building;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A620
    void Version::UpgradeClearBuildings1000AndHigher()
    {
        for (int buildingID = 1000; buildingID < 2000; ++buildingID) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(DAT_BuildingsState::instance.buildings[buildingID]), 0,
                &DAT_BuildingsState::instance.buildings[buildingID]);
        }
    }

}
}
