#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522390
        int TribesState::getUnitIDForIndexInTribe(int tribeID, int unitSelectionIndex)
        {
            int iVar2;
            short* psVar3;
            int _counter;
            _counter = 0;
            int iVar1 = 0;
            if ((this->tribes[tribeID].tribeState == 2) && (unitSelectionIndex < this->tribes[tribeID].size)) {
                psVar3 = this->tribes[tribeID].unitSelectionBitMasked;
                do {
                    if (*psVar3 != 0) {
                        for (iVar2 = 0; iVar2 < 16; iVar2++) {
                            if ((int)*psVar3 & 1 << ((byte)iVar2 & 0x1f)) {
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
