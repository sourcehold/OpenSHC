#include "OpenSHC/Game/ScenarioEvents/InGameEventUnionVersion.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // data+8 is cleared as one 16-bit word (allOrAnyCondition + magic). Condition bytes: data+0x17 =
    // conditions[2].enabled, +0x1B = [3], +0x3F = [12], +0x4B = [15].
    // FUNCTION: STRONGHOLDCRUSADER 0x004BDA80
    void MapPropertiesState::createChainedMissionOutcomeEvents(int outcomeMode)
    {
        if (outcomeMode == 2) {
            this->currentEventID = this->eventsCount;
            this->eventsCount = this->eventsCount + 1;
            this->editedEventType = 3;
            MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent,
                &this->scenarioEvents[this->currentEventID])();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (this->scenarioEvents[this->currentEventID].header.month >= 12) {
                this->scenarioEvents[this->currentEventID].header.month -= 12;
                this->scenarioEvents[this->currentEventID].header.year += 1;
            }
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 1;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[12].enabled = 1;

            this->currentEventID = this->eventsCount;
            this->eventsCount = this->eventsCount + 1;
            this->editedEventType = 3;
            MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent,
                &this->scenarioEvents[this->currentEventID])();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (this->scenarioEvents[this->currentEventID].header.month >= 12) {
                this->scenarioEvents[this->currentEventID].header.month -= 12;
                this->scenarioEvents[this->currentEventID].header.year += 1;
            }
            *(short*)&this->scenarioEvents[this->currentEventID].data.scenario.allOrAnyCondition = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[3].enabled = 1;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[15].enabled = 1;
        }
        else if (outcomeMode == 1) {
            this->currentEventID = this->eventsCount;
            this->eventsCount = this->eventsCount + 1;
            this->editedEventType = 3;
            MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent,
                &this->scenarioEvents[this->currentEventID])();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (this->scenarioEvents[this->currentEventID].header.month >= 12) {
                this->scenarioEvents[this->currentEventID].header.month -= 12;
                this->scenarioEvents[this->currentEventID].header.year += 1;
            }
            *(short*)&this->scenarioEvents[this->currentEventID].data.scenario.allOrAnyCondition = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 1;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[2].enabled = 1;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[12].enabled = 1;

            this->currentEventID = this->eventsCount;
            this->eventsCount = this->eventsCount + 1;
            this->editedEventType = 3;
            MACRO_CALL_MEMBER(OpenSHC::Game::ScenarioEvents::InGameEventUnionVersion_Func::initializeScenarioEvent,
                &this->scenarioEvents[this->currentEventID])();
            this->scenarioEvents[this->currentEventID].header.month = DAT_GameState::instance.mapAndTime.month + 1;
            this->scenarioEvents[this->currentEventID].header.year = DAT_GameState::instance.mapAndTime.year;
            if (this->scenarioEvents[this->currentEventID].header.month >= 12) {
                this->scenarioEvents[this->currentEventID].header.month -= 12;
                this->scenarioEvents[this->currentEventID].header.year += 1;
            }
            *(short*)&this->scenarioEvents[this->currentEventID].data.scenario.allOrAnyCondition = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.ScenarioEventType = 0;
            this->scenarioEvents[this->currentEventID].data.scenario.conditions[15].enabled = 1;
        }
        MACRO_CALL_MEMBER(MapPropertiesState_Func::sortEventsByDate, this)();
    }

}
}
