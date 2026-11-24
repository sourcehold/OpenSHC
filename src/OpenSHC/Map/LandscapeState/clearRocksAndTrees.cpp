#include "../../Map.func.hpp"
#include "../LandscapeState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F1C60
    void LandscapeState::clearRocksAndTrees()
    {
        Tree* destination;
        Rock* destination_00;
        int iVar1;
        this->DAT_TotalOrganisms = 0;
        this->field_0xc = 0;
        DAT_GameState::instance.mapAndTime.newOrganismsValue2 = 0;
        DAT_GameState::instance.mapAndTime.newOrganisms = 0;
        destination = this->trees;
        iVar1 = 2000;
        do {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                156, '\0', (void*)((int)(destination)));
            destination = destination + 1;
            iVar1 = iVar1 + -1;
        } while (iVar1);
        destination_00 = this->rocks;
        iVar1 = 4000;
        do {
            MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                32, '\0', (void*)((int)(destination_00)));
            destination_00 = destination_00 + 1;
            iVar1 = iVar1 + -1;
        } while (iVar1);
        this->maxTreeCount = 2000;
    }

}
}
