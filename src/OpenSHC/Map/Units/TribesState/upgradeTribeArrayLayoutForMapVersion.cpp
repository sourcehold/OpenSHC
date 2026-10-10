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
            if (receivedMapVersion != packagerMapVersion && (int)receivedMapVersion < 169) {
                iVar2 = 1249;
                _Dst = this->tribes + 0x4e1;
                _Src = this->tribes[944].unitSelectionBitMasked + 0x7a;
                do {
                    if (_Dst != (Tribe*)_Src) {
                        memmove(_Dst, (void*)((int)(_Src)), (size_t)((int)(620)));
                    }
                    psVar3 = _Dst->unitSelectionBitMasked;
                    memmove(&_Dst->field35_0x1c8, (void*)((int)(_Src + 0x80)), (size_t)((int)(364)));
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
            }
            return;
        }

    }
}
}
