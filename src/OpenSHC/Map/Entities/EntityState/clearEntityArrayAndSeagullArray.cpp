#include "../../../Map.func.hpp"
#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004010E0
        void EntityState::clearEntityArrayAndSeagullArray()
        {
            Entity* destination;
            ExtraEntityInfo* destination_00;
            int iVar1;
            this->totalEntityCount = 0;
            destination = this->entityArray;
            iVar1 = 3000;
            do {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    232, '\0', (void*)((int)(destination)));
                destination = destination + 1;
                iVar1 = iVar1 + -1;
            } while (iVar1);
            destination_00 = this->seagullArray;
            iVar1 = 100;
            do {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    100, '\0', (void*)((int)(destination_00)));
                destination_00 = destination_00 + 1;
                iVar1 = iVar1 + -1;
            } while (iVar1);
            this->maxEntityCount = 3000;
            this->everyTenTicks = 0x19;
        }

    }
}
}
