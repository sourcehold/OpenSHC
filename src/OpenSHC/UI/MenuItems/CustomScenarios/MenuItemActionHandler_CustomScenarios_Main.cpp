#include "../CustomScenarios.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::MenuViewType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00440770
        void CustomScenarios::MenuItemActionHandler_CustomScenarios_Main(int param_1, ...)
        {
            switch (param_1) {
            case 1:
                DAT_MenuTextInputState::instance.dialogResult = 0;
                DAT_MenuTextInputState::instance.field42_0x9c = 1;
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::activateLoadOrSaveMapUI, DAT_MenuTextInputState::ptr)(9);
                return;
            case 2:
                MACRO_CALL(OpenSHC::UI::Helpers_Func::InitializeBasicMap)();
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_NEW_MAP_MAPTYPE, 0);
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
                MACRO_CALL(OpenSHC::UI::Helpers_Func::InitializeBasicMap)();
                DAT_GameCore::instance.U2_mapType_singleOrMulti = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_NEW_MAP_MAPSIZE, 0);
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
                DAT_GameCore::instance.missionNumber1to20 = 0;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_BUILDERUnk;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_MapMissionType::instance = 3;
                INT_00b95b64::instance = 1;
                DAT_GameCore::instance.standaloneFilename[0] = '\0';
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty_3;
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM;
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
            case 5:
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
            }
        }

    }
}
}
