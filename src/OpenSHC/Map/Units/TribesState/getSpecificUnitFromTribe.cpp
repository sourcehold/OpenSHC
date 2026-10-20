#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_00ee0fb4.hpp"
#include "OpenSHC/Globals/DAT_Tribe_HighestID.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00522410
        int TribesState::getSpecificUnitFromTribe(int tribeID, int param_2)
        {
            short* psVar3;
            if (param_2 == 0) {
                DAT_Tribe_HighestID::instance = (int)this->tribes[tribeID].highestID;
                DAT_00ee0fb4::instance = 0;
            }
            /*
              Both globals are read before the bound test, which is the order the original
              loads them in.
             */
            int iVar1 = DAT_Tribe_HighestID::instance;
            int iVar2 = DAT_00ee0fb4::instance;
            if (iVar1 < 200) {
                psVar3 = this->tribes[tribeID].unitSelectionBitMasked + iVar1;
                do {
                    if ((*psVar3 != 0) && (iVar2 < 0x10)) {
                        do {
                            if ((int)*psVar3 & 1 << iVar2) {
                                DAT_00ee0fb4::instance = iVar2 + 1;
                                if (iVar2 + 1 != 0x10) {
                                    DAT_Tribe_HighestID::instance = iVar1;
                                    return iVar1 * 0x10 + iVar2;
                                }
                                DAT_Tribe_HighestID::instance = iVar1 + 1;
                                DAT_00ee0fb4::instance = 0;
                                return iVar1 * 0x10 + iVar2;
                            }
                            iVar2 = iVar2 + 1;
                        } while (iVar2 < 0x10);
                    }
                    iVar2 = 0;
                    iVar1 = iVar1 + 1;
                    psVar3 = psVar3 + 1;
                    DAT_00ee0fb4::instance = 0;
                } while (iVar1 < 200);
            }
            return 0;
        }

    }
}
}
