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
            for (int entityID = 0; entityID < 3000; ++entityID) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Entity), 0, &this->entityArray[entityID]);
            }
            for (int seagullID = 0; seagullID < 100; ++seagullID) {
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(ExtraEntityInfo), 0, &this->seagullArray[seagullID]);
            }
            this->maxEntityCount = 3000;
            this->everyTenTicks = 25;
        }

    }
}
}
