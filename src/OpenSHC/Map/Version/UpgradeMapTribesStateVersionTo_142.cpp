#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"

#include "OpenSHC/Globals/DAT_TribesState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Map::Units::SomeTribeBehaviorType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00523E00
    void Version::UpgradeMapTribesStateVersionTo_142()
    {
        for (int _tribeID = 1; _tribeID < 1250; _tribeID++) {
            if (DAT_TribesState::instance.tribes[_tribeID].tribeState != 0
                && DAT_TribesState::instance.tribes[_tribeID].attackWave <= 0) {
                DAT_TribesState::instance.tribes[_tribeID].tribeBehaviorType = 0;
            }
        }
    }

}
}
