#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00523E30
    void Version::UpgradeMapTribesStateVersionTo_Unknown1()
    {
        for (int tribeID = 1; tribeID < 1250; ++tribeID) {
            if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0) {
                if (DAT_TribesState::instance.tribes[tribeID].size > 30) {
                    MACRO_CALL_MEMBER(Units::TribesState_Func::trimTribeToSize, DAT_TribesState::ptr)(tribeID, 30);
                    DAT_TribesState::instance.tribes[tribeID].herdMinSize = 15;
                    DAT_TribesState::instance.tribes[tribeID].herdMaxSize = 60;
                } else {
                    DAT_TribesState::instance.tribes[tribeID].herdMinSize
                        = DAT_TribesState::instance.tribes[tribeID].size / 2;
                    DAT_TribesState::instance.tribes[tribeID].herdMaxSize
                        = DAT_TribesState::instance.tribes[tribeID].size * 2;
                }
                DAT_TribesState::instance.tribes[tribeID].field138_0x284 = 0;
            }
        }
    }

}
}
