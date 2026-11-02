#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // Old record layout: 0x26C bytes per tribe (100-word member bitmask), tail of 0x16C bytes at old offset 0x100.
        // The original calls the CRT memmove at 0x583760 twice (the first one guarded by dst != src, 0x523F16); there
        // is no resolver for it, so the DLL's own CRT memmove is called (same semantics). The new second half of the
        // bitmask is zeroed with rep stosd (0x32 dwords, 0x523F62): MSVC 2005 emits that for this loop but a call for
        // memset(p, 0, 200) (tested). receivedMapVersion is compared signed (jge at 0x523EFF). Tribes 0x4E1 down to 0.
        // FUNCTION: STRONGHOLDCRUSADER 0x00523EF0
        void TribesState::upgradeTribeArrayLayoutForMapVersion(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            if (receivedMapVersion != packagerMapVersion && (int)receivedMapVersion < 0xa9) {
                int tribeIndex = 1249;
                char* src = (char*)this->tribes + 1249 * 0x26c;
                Tribe* dst = &this->tribes[1249];
                do {
                    if ((void*)dst != (void*)src) {
                        memmove(dst, src, 0x26c);
                    }
                    short* maskTail = &dst->unitSelectionBitMasked[100];
                    memmove(&dst->field34_0x1c8, src + 0x100, 0x16c);
                    --tribeIndex;
                    src -= 0x26c;
                    --dst;
                    for (int k = 0; k < 100; ++k) {
                        maskTail[k] = 0;
                    }
                } while (tribeIndex >= 0);
            }
        }

    }
}
}
