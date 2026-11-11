#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523750
        void TribesState::flagTribesOfType(int tribeType)
        {
            for (int _tribeID = 1; _tribeID < 1250; ++_tribeID) {
                Tribe& _tribe = this->tribes[_tribeID];
                if (_tribe.tribeState && _tribe.tribeType == tribeType) {
                    _tribe.unknownBool02 = 1;
                }
            }
        }

    }
}
}
