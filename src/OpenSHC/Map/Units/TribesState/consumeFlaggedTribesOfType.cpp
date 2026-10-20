#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523790
        void TribesState::consumeFlaggedTribesOfType(int param_1, int param_2)
        {
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                if (param_2 <= 0) {
                    return;
                }
                Tribe& _tribe = this->tribes[_tribeID];
                if (_tribe.tribeState != 0 && _tribe.tribeType == param_1 && _tribe.unknownBool02 != 0) {
                    _tribe.unknownBool02 = 0;
                    _tribe.unknownBool01 = 1;
                    param_2 = param_2 + -1;
                }
            }
        }

    }
}
}
