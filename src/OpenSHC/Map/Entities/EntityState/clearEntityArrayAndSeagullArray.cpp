#include "../EntityState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        // FUNCTION: STRONGHOLDCRUSADER 0x004010E0
        void EntityState::clearEntityArrayAndSeagullArray()
        {
            this->totalEntityCount = 0;
            for (int entityID = 0; entityID < countof(this->entityArray); ++entityID) {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(this->entityArray[entityID]), 0, &this->entityArray[entityID]);
            }
            for (int seagullID = 0; seagullID < countof(this->seagullArray); ++seagullID) {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(this->seagullArray[seagullID]), 0, &this->seagullArray[seagullID]);
            }
            this->maxEntityCount = 3000;
            this->everyTenTicks = 25;
        }

    }
}
}
