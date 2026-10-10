#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523750
        void TribesState::flagTribesOfType(int param_1)
        {
            Tribe* psVar1;
            int iVar1;
            psVar1 = &this->tribes[1];
            iVar1 = 0x4e1;
            do {
                if (psVar1->tribeState && (short)psVar1->tribeType == param_1) {
                    psVar1->unknownBool02 = 1;
                }
                psVar1 = psVar1 + 0x19a;
                iVar1 = iVar1 + -1;
            } while (iVar1);
        }

    }
}
}
