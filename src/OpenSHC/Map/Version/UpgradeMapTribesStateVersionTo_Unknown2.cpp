#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Version.func.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00523EB0
    void Version::UpgradeMapTribesStateVersionTo_Unknown2()
    {
        for (int tribeID = 1; tribeID < 1250; tribeID++) {
            if (DAT_TribesState::instance.tribes[tribeID].tribeState != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::setWhetherTribeContainsAnyUnits,
                    DAT_TribesState::ptr)(tribeID);
            }
        }
    }

}
}
