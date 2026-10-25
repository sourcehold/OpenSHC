#include "../../../Map.func.hpp"
#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521240
        void TribesState::swapTribeOwnership(int param_1, int param_2)
        {
            /*
              The original walks the global instance, not `this`: both the start and the
              end of the loop are absolute addresses in the binary.
             */
            for (int _tribeID = 1; _tribeID < 1250; _tribeID = _tribeID + 1) {
                Tribe& _tribe = DAT_TribesState::instance.tribes[_tribeID];
                if (_tribe.tribeState == 2) {
                    if (_tribe.owner == param_1) {
                        _tribe.owner = param_2;
                    } else if (_tribe.owner == param_2) {
                        _tribe.owner = param_1;
                    }
                }
            }
        }

    }
}
}
