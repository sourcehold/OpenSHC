#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523790
        void TribesState::consumeFlaggedTribesOfType(int tribeType, int maxTribesToConsume)
        {
            for (int _tribeID = 1; _tribeID < 1250; ++_tribeID) {
                if (maxTribesToConsume <= 0) {
                    return;
                }
                Tribe& _tribe = this->tribes[_tribeID];
                if (_tribe.tribeState != 0 && _tribe.tribeType == tribeType && _tribe.unknownBool02 != 0) {
                    _tribe.unknownBool02 = 0;
                    _tribe.unknownBool01 = 1;
                    --maxTribesToConsume;
                }
            }
        }

    }
}
}
