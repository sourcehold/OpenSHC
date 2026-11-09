#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00425720
        void HistoricCampaignSelect::MenuItemActionHandler_HistoricCampaignSelect_Main(int param_1, ...)
        {
            switch (param_1) {
            case 1:
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameCore::instance.missionNumber1to20 = 1;
                DAT_GameCore::instance.historicCampaignNumber = 1;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                for (int i = 0; i < 9; i++) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 2:
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameCore::instance.missionNumber1to20 = 6;
                DAT_GameCore::instance.historicCampaignNumber = 2;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                for (int i = 0; i < 9; i++) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 3:
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.missionNumber1to20 = 11;
                DAT_GameCore::instance.historicCampaignNumber = 3;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                for (int i = 0; i < 9; i++) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 4:
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.missionNumber1to20 = 16;
                DAT_GameCore::instance.historicCampaignNumber = 4;
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                for (int i = 0; i < 9; i++) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 5:
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
            }
        }

    }
}
}
