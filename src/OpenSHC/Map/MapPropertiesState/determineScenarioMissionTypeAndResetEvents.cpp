#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004B7980
    void MapPropertiesState::determineScenarioMissionTypeAndResetEvents()
    {
        BOOLEnum hasAttackers = FALSE;
        BOOLEnum hasScenarioGoal = FALSE;
        for (int i = 0; i < this->eventsCount; ++i) {
            switch (this->scenarioEvents[i].header.tl_type) {
            case 1:
                hasAttackers = TRUE;
                break;
            case 3: {
                int const scenarioEventType = this->scenarioEvents[i].data.scenario.ScenarioEventType;
                if (scenarioEventType >= 0 && (scenarioEventType <= 1 || scenarioEventType == 26)) {
                    hasScenarioGoal = TRUE;
                }
                break;
            }
            }
        }
        for (int i = 1; i < 2500; ++i) {
            if (DAT_UnitsState::instance.units[i].logicalState != 0 && DAT_UnitsState::instance.units[i].owner > 1) {
                hasAttackers = TRUE;
                break;
            }
        }
        if (this->SEC_U3_MapType2_1 == 0) {
            for (int i = 0; i < 20; ++i) {
                if (this->SEC_SiegeInformation[i] != 0) {
                    hasAttackers = TRUE;
                    break;
                }
            }
            for (int i = 0; i < 6; ++i) {
                if (this->SEC_Section1067.siegeEngineCounts[i] != 0) {
                    hasAttackers = TRUE;
                    break;
                }
            }
        }
        if (hasAttackers) {
            this->scenarionMissionType = (this->SEC_U3_MapType2_1 != 0) + 2;
        } else {
            this->scenarionMissionType = hasScenarioGoal != FALSE;
        }
        DAT_GameState::instance.mapAndTime.month = this->SEC_StartingMonth;
        DAT_GameState::instance.mapAndTime.year = this->SEC_StartingYear;
        for (int i = 0; i < this->eventsCount; ++i) {
            this->scenarioEvents[i].header.done = 0;
            this->scenarioEvents[i].header.pre_done = 0;
        }
    }

}
}
