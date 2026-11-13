#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BEB20
    void MapPropertiesState::updateEventYearsAndCommitBuildingAvailability()
    {
        if (DAT_MapPropertiesState::instance.SEC_StartingYear < 1000) {
            DAT_MapPropertiesState::instance.SEC_StartingYear = 1181;
        }
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(10);
        char yearText[12];
        // "%d"
        MACRO_CALL(OS_Func::_sprintf)(yearText, s__d_005aa7f0, this->SEC_StartingYear);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(yearText);
        DAT_MapPropertiesState::instance.eventListSelection = -1;
        DAT_MapPropertiesState::instance.eventListScrollOffset = 0;
        this->year_copy = this->SEC_StartingYear;
        for (int i = 0; i < this->eventsCount; ++i) {
            if (DAT_GameState::instance.mapAndTime.year < this->scenarioEvents[i].header.year) {
                continue;
            }
            if (DAT_GameState::instance.mapAndTime.year == this->scenarioEvents[i].header.year
                && DAT_GameState::instance.mapAndTime.month >= this->scenarioEvents[i].header.month) {
                continue;
            }
            if (this->scenarioEvents[i].header.tl_type == 1
                && this->scenarioEvents[i].data.invasion.repeatMonths != 0) {
                if (this->scenarioEvents[i].data.invasion.messageYear != 0) {
                    this->scenarioEvents[i].header.year = this->scenarioEvents[i].data.invasion.messageYear;
                } else {
                    this->scenarioEvents[i].data.invasion.messageYear = this->scenarioEvents[i].header.year;
                }
            }
        }
        MACRO_CALL_MEMBER(MapPropertiesState_Func::commitBuildingAvailability, this)();
    }

}
}
