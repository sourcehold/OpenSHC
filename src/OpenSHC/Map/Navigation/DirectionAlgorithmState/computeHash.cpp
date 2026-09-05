#include "../DirectionAlgorithmState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        // FUNCTION: STRONGHOLDCRUSADER 0x0046CD30
        uint DirectionAlgorithmState::computeHash(int byteCount, int* address)
        {
            uint hash = 0;
            // The native routine hashes complete 32-bit words and ignores trailing bytes.
            // Keep the addition unsigned: wraparound is part of the synchronization hash.
            while (byteCount >= 4) {
                hash += static_cast<uint>(*address++);
                hash = (hash << 1) | (hash >> 31);
                byteCount -= 4;
            }
            return hash;
        }

    } // namespace Navigation
} // namespace Map
} // namespace OpenSHC
