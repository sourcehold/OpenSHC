#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522BC0
        void TribesState::clearTribe(int param_1)
        {
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
                820, 0, &this->tribes[param_1]);
        }

    }
}
}
