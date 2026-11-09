#include "../TribesState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentTribeID.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x005211B0
        void TribesState::clearAllTribes()
        {
            this->clans = 0;
            this->field_0x8 = 1;
            this->field_0x24 = 0;
            for (DAT_CurrentTribeID::instance = 1; (int)DAT_CurrentTribeID::instance < (int)_countof(this->tribes);
                ++DAT_CurrentTribeID::instance) {
                MACRO_CALL_MEMBER(IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                    sizeof(Tribe), '\0', &this->tribes[DAT_CurrentTribeID::instance]);
            }
        }

    }
}
}
