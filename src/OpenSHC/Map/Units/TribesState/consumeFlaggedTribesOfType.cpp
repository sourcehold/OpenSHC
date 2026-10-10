#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523790
        void TribesState::consumeFlaggedTribesOfType(int param_1, int param_2)
        {
            short* psVar1;
            int iVar2;
            psVar1 = &this->tribes[1].unknownBool02;
            iVar2 = 1;
            do {
                if (param_2 < 1) {}
                if (psVar1[-0x139] != 0 && psVar1[-0x138] == param_1 && *psVar1 != 0) {
                    *psVar1 = 0;
                    psVar1[1] = 1;
                    param_2 = param_2 + -1;
                }
                iVar2 = iVar2 + 1;
                psVar1 = psVar1 + 0x19a;
            } while (iVar2 < 0x4e2);
        }

    }
}
}
