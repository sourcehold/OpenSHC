#include "../Unused.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00425C20
        void Unused::MenuItemActionHandler_UnusedEconomicGametypeSelect_Main(int param_1, ...)
        {
            switch (param_1) {
            case 1:
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty2;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_UNUSED_ECONOMIC_MISSION_SELECTUnk, 0);
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
                DAT_GameCore::instance.missionNumber1to20 = 0;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_BUILDERUnk;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty_1;
                DAT_MapMissionType::instance = 1;
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.standaloneFilename[0] = '\0';
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
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
                DAT_GameCore::instance.missionNumber1to20 = 0;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_BUILDERUnk;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_MapMissionType::instance = 0;
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.standaloneFilename[0] = '\0';
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty_0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
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
                goto switchD_00425c32_caseD_4;
            case 5:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
            switchD_00425c32_caseD_4:
                return;
            default:
                break;
            }
        }

    }
}
}
