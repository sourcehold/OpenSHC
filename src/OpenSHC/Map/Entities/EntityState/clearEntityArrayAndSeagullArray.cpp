#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // Works on `this` (ebx = ecx at 0x4010E2). 3000 entity records of 0xE8 bytes, 100 seagull records of
        // 100 bytes, each cleared with fillMemory_ByteValue; then maxEntityCount = 3000 (0x401139) and
        // everyTenTicks = 0x19 (0x401140).
        // FUNCTION: STRONGHOLDCRUSADER 0x004010E0
        void EntityState::clearEntityArrayAndSeagullArray()
        {
            this->totalEntityCount = 0;
            Entity* entity = this->entityArray;
            int count = 3000;
            do {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Entity), 0, entity);
                entity = entity + 1;
                count = count - 1;
            } while (count != 0);
            ExtraEntityInfo* seagull = this->seagullArray;
            count = 100;
            do {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(ExtraEntityInfo), 0, seagull);
                seagull = seagull + 1;
                count = count - 1;
            } while (count != 0);
            this->maxEntityCount = 3000;
            this->everyTenTicks = 0x19;
        }

    }
}
}
