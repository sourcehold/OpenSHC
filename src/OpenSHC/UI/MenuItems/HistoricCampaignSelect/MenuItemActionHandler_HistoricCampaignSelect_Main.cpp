#include "../HistoricCampaignSelect.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425720
        void HistoricCampaignSelect::MenuItemActionHandler_HistoricCampaignSelect_Main(int param_1, ...)
        {
            switch (param_1) {
            case 1:
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameCore::instance.missionNumber1to20 = 1;
                DAT_GameCore::instance.historicCampaignNumber = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                return;
            case 2:
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameCore::instance.missionNumber1to20 = 6;
                DAT_GameCore::instance.historicCampaignNumber = 2;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                return;
            case 3:
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.missionNumber1to20 = 11;
                DAT_GameCore::instance.historicCampaignNumber = 3;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                return;
            case 4:
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                DAT_GameCore::instance.missionNumber1to20 = 16;
                DAT_GameCore::instance.historicCampaignNumber = 4;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_MISSION_SELECT, 0);
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[0]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[0];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[1]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[1];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[2]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[2];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[3]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[3];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[4]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[4];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[5]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[5];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[6]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[6];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[7]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[7];
                DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[8]
                    = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[8];
                return;
            case 5:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
            }
        }

    }
}
}
