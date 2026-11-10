#include "OpenSHC/Map/Version.func.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_SkirmishDefinedData.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0053B610
    void Version::UpgradeMapUnitsLordHealthTo_169()
    {
        if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
            return;
        }
        for (int unitID = 1; unitID < 2500; ++unitID) {
            if (DAT_UnitsState::instance.units[unitID].unitType == Units::UT_LORD) {
                int owner = DAT_UnitsState::instance.units[unitID].owner;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[owner] == -1
                    && DAT_GameSynchronyState::instance.currentAIArray[owner] != 0) {
                    // The health of AI lords depends on the AI character
                    DAT_UnitsState::instance.units[unitID].maxHealthRatingLord
                        = DAT_SkirmishDefinedData::instance
                              .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[owner].aiType - 1]
                              .aiTypeA;
                    if (DAT_UnitsState::instance.units[unitID].health
                        == DAT_UnitsState::instance.units[unitID].maxHealth) {
                        DAT_UnitsState::instance.units[unitID].health = DAT_UnitsState::instance.units[unitID].health
                            * DAT_SkirmishDefinedData::instance
                                  .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[owner].aiType - 1]
                                  .maxHealthMultiplier
                            / 100;
                        DAT_UnitsState::instance.units[unitID].maxHealth
                            = DAT_UnitsState::instance.units[unitID].maxHealth
                            * DAT_SkirmishDefinedData::instance
                                  .MaxLordHealthMapping[DAT_GameState::instance.playerDataArray[owner].aiType - 1]
                                  .maxHealthMultiplier
                            / 100;
                    }
                }
            }
        }
    }

}
}
