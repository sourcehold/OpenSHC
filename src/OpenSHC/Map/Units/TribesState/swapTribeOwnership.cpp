#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521240
        void TribesState::swapTribeOwnership(int param_1, int param_2)
        {
            Tribe* piVar1;
            piVar1 = &this->tribes[1];
            do {
                if (piVar1->tribeState == 2) {
                    if (piVar1->owner == param_1) {
                        piVar1->owner = param_2;
                    } else if (piVar1->owner == param_2) {
                        piVar1->owner = param_1;
                    }
                }
                piVar1 = piVar1 + 0xcd;
            } while ((int)piVar1 < 0x176238c);
        }

    }
}
}
