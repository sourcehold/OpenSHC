#include "OpenSHC/Audio/mss/UnkSoundFlagsAndLoopCount.hpp"

#include "core/OStreamOverloads/OStreamOverloadsSupport.hpp"

namespace OpenSHC {
namespace Audio {
    namespace MSS {

        std::ostream& operator<<(std::ostream& os, UnkSoundFlagsAndLoopCount const& value)
        {
            return os << "{loopCount=" << value.loopCount << ", flagsUnk=0x" << std::hex << std::setw(2)
                      << std::setfill('0') << static_cast<int>(value.flagsUnk) << std::dec << "}";
        }

    }
}
}
