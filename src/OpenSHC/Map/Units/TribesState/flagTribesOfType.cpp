#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00523750
        void TribesState::flagTribesOfType(int param_1)
        {
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                Tribe& _tribe = this->tribes[_tribeID];
                if (_tribe.tribeState && (short)_tribe.tribeType == param_1) {
                    _tribe.unknownBool02 = 1;
                }
            }
        }

    }
}
}
