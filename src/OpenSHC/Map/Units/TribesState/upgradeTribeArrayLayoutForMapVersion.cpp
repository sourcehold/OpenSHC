#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "string.h"
#include <intrin.h>

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523EF0
        void TribesState::upgradeTribeArrayLayoutForMapVersion(
            PackagedFileMagicNum receivedMapVersion, PackagedFileMagicNum packagerMapVersion)
        {
            int iVar1;
            Tribe* _Dst;
            int iVar2;
            short* _Src;
            short* psVar3;
            /*
              Two early-return guards rather than one wrapping `if`, which is where the
              original places its epilogue.
             */
            if (receivedMapVersion == packagerMapVersion) {
                return;
            }
            if (169 <= (int)receivedMapVersion) {
                return;
            }
            iVar2 = 1249;
            _Dst = this->tribes + 0x4e1;
            /*
              0x7a, which puts the cursor at `this + 0xbd114` - the `lea esi, [ecx +
              0xbd114]` the original starts its loop with. I changed this to 0xba earlier on
              arithmetic that used 944 * 0x334 = 0xbcf40; the product is 0xbcfc0, so the
              import's index was right all along and 0xba put the cursor 0x80 too high.
              0x28 + 944 * 0x334 + 0x38 + 0x7a * 2 == 0xbd114. diff_anchor.py names this
              error directly - use it rather than doing the arithmetic by hand.
             */
            _Src = this->tribes[944].unitSelectionBitMasked + 0x7a;
            do {
                if (_Dst != (Tribe*)_Src) {
                    memmove(_Dst, (void*)((int)(_Src)), (size_t)((int)(620)));
                }
                psVar3 = _Dst->unitSelectionBitMasked;
                memmove(&_Dst->field34_0x1c8, (void*)((int)(_Src + 0x80)), (size_t)((int)(364)));
                iVar2 = iVar2 + -1;
                _Src = _Src + -0x136;
                _Dst = _Dst + -1;
                psVar3 = psVar3 + 100;
                /*
                  The original clears these 200 bytes with `mov ecx, 0x32` and a single
                  `rep stosd` - fifty dwords. Three spellings, measured:

                    the decompiler's two-shorts-per-iteration loop   46.5%
                    memset(psVar3, 0, 200)                           49.4%
                    __stosd((unsigned long*)psVar3, 0, 50)           57.5%

                  The loop compiles to eight instructions. `memset` is better but this
                  build does not inline it - it emits `push 0xc8; push 0; push ebx; call
                  memset; add esp, 0x18`, so the original's `rep stosd` is an inlined
                  memset and /Oi is not on here. The intrinsic emits the instruction
                  directly, which is why it is used in preference to the more idiomatic
                  memset: it is the only one of the three that produces what the original
                  has.
                 */
                __stosd((unsigned long*)psVar3, 0, 50);
            } while (-1 < iVar2);
            return;
        }

    }
}
}
