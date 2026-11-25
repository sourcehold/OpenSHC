#include "../LandscapeState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1C60
    void LandscapeState::clearRocksAndTrees()
    {
        this->DAT_TotalOrganisms = 0;
        this->field_0xc = 0;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2 = 0;
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        for (int treeID = 0; treeID < countof(this->trees); ++treeID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->trees[treeID]), 0, &this->trees[treeID]);
        }
        for (int rockID = 0; rockID < countof(this->rocks); ++rockID) {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                sizeof(this->rocks[rockID]), 0, &this->rocks[rockID]);
        }
        this->maxTreeCount = 2000;
    }

}
}
