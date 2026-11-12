#include "../MainMenu.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/UserTextHandler.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/MenuTextInputState.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Rendering/Enums/DirectDrawStatus.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95954.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004251A0
        void MainMenu::MenuItemActionHandler_MainMenu_Main(int button, ...)
        {
            switch (button) {
            case 1:
                // historical campaigns
                DAT_GameCore::instance.gameSuspended = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 2:
                // crusader
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SELECT_CRUSADE, 0);
                return;
            case 3:
                // castle builder; the tail in each case (one copy after the switch: quick_diff 0.9500 -> 0.7756)
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
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = OpenSHC::UI::Enums::BASMTT_NONE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 4:
                // multiplayer
                if (DAT_GameCore::instance.directDrawStatus < OpenSHC::Rendering::Enums::DD7_LOADED) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(5);
                MACRO_CALL_MEMBER(OpenSHC::Text::UserTextHandler_Func::clearEntry, DAT_UserTextHandlerState::ptr)(6);
                DAT_GameSynchronyState::instance.nextModalDialog
                    = OpenSHC::UI::Enums::MMT_CHOOSE_NETWORK_SERVICE_PROVIDER;
                DAT_GameSynchronyState::instance.kickedAtTime = 0;
                DAT_GameSynchronyState::instance.ipArrayIndex = 0;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_SKIRMISH_AND_MULTIPLAYER;
                DAT_GameCore::instance.xbowProducible_logic = 1;
                DAT_GameCore::instance.pikeProducible_logic = 1;
                DAT_GameCore::instance.swordProducible_logic = 1;
                DAT_GameCore::instance.bowProducible_logic = 1;
                DAT_GameCore::instance.spearProducible_logic = 1;
                DAT_GameCore::instance.maceProducible_logic = 1;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MP_CONNECTION, 0);
                for (int i = 0; i < countof(DAT_BlendingDefinedData::instance.PlayerSlotUnitColor); ++i) {
                    DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[i]
                        = DAT_BlendingDefinedData::instance.DefaultPlayerSlotUnitColor[i];
                }
                return;
            case 9:
                // custom scenarios
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                return;
            case 6:
                // tutorial
                DAT_GameCore::instance.missionNumber1to20 = 30;
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_CRUSADER_TUTORIAL;
                DAT_GameCore::instance.xbowProducible_logic = 0;
                DAT_GameCore::instance.pikeProducible_logic = 0;
                DAT_GameCore::instance.swordProducible_logic = 0;
                DAT_GameCore::instance.bowProducible_logic = 0;
                DAT_GameCore::instance.spearProducible_logic = 0;
                DAT_GameCore::instance.maceProducible_logic = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 1;
                DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = 1;
                MACRO_CALL_MEMBER(OpenSHC::Map::MapPropertiesState_Func::loadMap, DAT_MapPropertiesState::ptr)(
                    // "Crusader_tutorial.map"
                    (char*)s_Crusader_tutorial_map_005a1ff8);
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = OpenSHC::UI::Enums::BMTT_CASTLE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_TUTORIAL_BOX, FALSE);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::InitTutorialState)();
                return;
            case 8:
                // options
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_MAIN_MENU_OPTIONS);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    OpenSHC::Audio::SFX::SEID_UNKNOWN_0x101);
                return;
            case 5:
                // quit
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 9;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
                return;
            case 7:
                // credits
                INT_00b95954::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CREDITS, 0);
                return;
            }
        }

    }
}
}
