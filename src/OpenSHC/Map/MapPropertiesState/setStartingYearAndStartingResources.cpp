#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004BE590
    void MapPropertiesState::setStartingYearAndStartingResources()
    {
        DAT_MapPropertiesState::instance.SEC_StartingYear = 1181;
        DAT_GameState::instance.mapAndTime.year = 1181;
        for (int i = 0; i < 25; ++i) {
            DAT_MapPropertiesState::instance.SEC_StartingResources[i] = 0;
        }
        for (int i = 0; i < 25; ++i) {
            DAT_MapPropertiesState::instance.SEC_Section1065.tradeabilityArray[i] = 1;
        }
        DAT_MapPropertiesState::instance.SEC_StartingMonth = 0;
        DAT_GameState::instance.mapAndTime.month = 0;
        DAT_MapPropertiesState::instance.eventsCount = 0;
        // the siege information is a block of 20 unit counts
        for (int i = 0; i < 20; ++i) {
            DAT_MapPropertiesState::instance.SEC_SiegeInformation[i] = 0;
        }
        for (int i = 0; i < 6; ++i) {
            DAT_MapPropertiesState::instance.SEC_Section1067.siegeEngineCounts[i] = 0;
        }
        DAT_MapPropertiesState::instance.SEC_StartingPopularity = 100;
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(10);
        char yearText[12];
        // "%d"
        MACRO_CALL(OS_Func::_sprintf)(yearText, s__d_005aa7f0, DAT_MapPropertiesState::instance.SEC_StartingYear);
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::copyIntoTextArray, DAT_UserTextHandlerState::ptr)(yearText);
        DAT_MapPropertiesState::instance.eventListSelection = -1;
        DAT_MapPropertiesState::instance.eventListScrollOffset = 0;
        for (int i = 0; i < 100; ++i) {
            this->buildingAvailability[i] = 1;
        }
        MACRO_CALL_MEMBER(MapPropertiesState_Func::commitBuildingAvailability, this)();
        MACRO_CALL_MEMBER(Text::UserTextHandler_Func::resetToTextIndex, DAT_UserTextHandlerState::ptr)(9);
    }

}
}
