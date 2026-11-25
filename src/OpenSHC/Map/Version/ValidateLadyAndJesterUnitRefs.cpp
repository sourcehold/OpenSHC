#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045ACC0
    void Version::ValidateLadyAndJesterUnitRefs()
    {
        for (int playerID = 1; playerID < 9; ++playerID) {
            int ladyID = DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk;
            if (ladyID != 0
                && DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef
                    != DAT_UnitsState::instance.units[ladyID].uid) {
                DAT_GameState::instance.playerDataArray[playerID].ladyIDUnk = 0;
                DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef = 0;
            }
            int jesterID = DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk;
            if (jesterID != 0
                && DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2
                    != DAT_UnitsState::instance.units[jesterID].uid) {
                DAT_GameState::instance.playerDataArray[playerID].jesterIDUnk = 0;
                DAT_GameState::instance.playerDataArray[playerID].someUnitIDSelfRef_2 = 0;
            }
        }
    }

}
}
