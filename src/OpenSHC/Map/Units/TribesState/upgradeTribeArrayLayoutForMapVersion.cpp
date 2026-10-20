#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "string.h"

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
              The source cursor starts at `this + 0xbd114`, which is tribes[944] + 0x1ac:
              `unitSelectionBitMasked` sits at 0x38, so the index is (0x1ac - 0x38) / 2 =
              0xba. The import's 0x7a put it 128 bytes short, and every tribe this loop
              moved came from the wrong place.
             */
            _Src = this->tribes[944].unitSelectionBitMasked + 0xba;
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
                for (iVar1 = 50; iVar1 != 0; iVar1 = iVar1 + -1) {
                    psVar3[0] = 0;
                    psVar3[1] = 0;
                    psVar3 = psVar3 + 2;
                }
            } while (-1 < iVar2);
            return;
        }

    }
}
}
