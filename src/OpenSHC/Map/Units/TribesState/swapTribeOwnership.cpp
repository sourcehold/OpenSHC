#include "../TribesState.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x00521240
        void TribesState::swapTribeOwnership(int playerA, int playerB)
        {
            for (int _tribeID = 1; _tribeID < (int)_countof(DAT_TribesState::instance.tribes); ++_tribeID) {
                Tribe& _tribe = DAT_TribesState::instance.tribes[_tribeID];
                if (_tribe.tribeState == 2) {
                    if (_tribe.owner == playerA) {
                        _tribe.owner = playerB;
                    } else if (_tribe.owner == playerB) {
                        _tribe.owner = playerA;
                    }
                }
            }
        }

    }
}
}
