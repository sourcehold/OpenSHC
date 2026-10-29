#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1C60
    void LandscapeState::clearRocksAndTrees()
    {
        this->DAT_TotalOrganisms = 0;
        this->field3_0xc = 0;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2 = 0;
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        for (int i = 0; i < 2000; i++) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x9c, 0, &this->trees[i]);
        }
        for (int i = 0; i < 4000; i++) {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                0x20, 0, &this->rocks[i]);
        }
        this->maxTreeCount = 2000;
    }

}
}
