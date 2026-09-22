#include "../GameCore.func.hpp"

#include "OpenSHC/IO/SettingsFileState.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_SettingsFileState.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471A00
    void GameCore::incrementMission()
    {
        ++this->missionNumber1to20;
        MACRO_CALL_MEMBER(GameCore_Func::removeLadyAndJester, this)();
        if (!this->unlockAllHistoricalCampaigns && this->missionNumber1to20 > (int)this->furthestMission) {
            this->furthestMission = this->missionNumber1to20;
        }
        MACRO_CALL_MEMBER(IO::SettingsFileState_Func::writeUserConfig, DAT_SettingsFileState::ptr)();

        if (!MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::isValueInRangeOneToTwenty, DAT_MapPropertiesState::ptr)(
                this->missionNumber1to20)) {
            DAT_GameCore::instance.field22_0x64 = 0;
            MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
        } else {
            DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
            if (this->missionNumber1to20 != 33 && !DAT_GameCore::instance.field26_0x74) {
                MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MISSION_FINISHED_TRANSITION, 0);
            } else {
                DAT_GameCore::instance.field22_0x64 = 0;
                MACRO_CALL_MEMBER(GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_SCENARIO_DESCRIPTION, 0);
            }
        }
        DAT_GameCore::instance.field26_0x74 = 0;
        DAT_GameCore::instance.unknownAlwaysZero = 0;
    }

}
}
