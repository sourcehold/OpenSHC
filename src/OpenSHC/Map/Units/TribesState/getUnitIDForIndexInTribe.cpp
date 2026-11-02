#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522390
        int TribesState::getUnitIDForIndexInTribe(int tribeID, int unitSelectionIndex)
        {
            int _counter = 0;
            int iVar1 = 0;
            if ((this->tribes[tribeID].tribeState == 2) && (unitSelectionIndex < this->tribes[tribeID].size)) {
                short* psVar3 = this->tribes[tribeID].unitSelectionBitMasked;
                do {
                    /*
                      The word is read once: `movzx edx, word ptr [esi]` for the zero test,
                      then `movsx edx, dx` for the bit tests, rather than a load per bit.
                     */
                    short const _bits = *psVar3;
                    if (_bits != 0) {
                        for (int iVar2 = 0; iVar2 < 16; iVar2++) {
                            if ((int)_bits & 1 << iVar2) {
                                if (_counter == unitSelectionIndex) {
                                    return iVar1 * 0x10 + iVar2;
                                }
                                _counter = _counter + 1;
                            }
                        }
                    }
                    iVar1 = iVar1 + 1;
                    psVar3 = psVar3 + 1;
                } while (iVar1 < 200);
            }
            return 0;
        }

    }
}
}
