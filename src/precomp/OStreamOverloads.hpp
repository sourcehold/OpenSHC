#pragma once

#include <iosfwd>

namespace OpenSHC {
namespace Audio {
    namespace MSS {
        struct UnkSoundFlagsAndLoopCount;
        std::ostream& operator<<(std::ostream&, UnkSoundFlagsAndLoopCount const&);
    }
}
}
