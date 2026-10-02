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
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00b95954.hpp"
#include "OpenSHC/Globals/DAT_00df5554.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df5564.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/DAT_UserTextHandlerState.hpp"
#include "OpenSHC/Globals/INT_00b95b64.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00df5598.hpp"
#include "OpenSHC/Globals/INT_DisableTutorialRestrictions.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Audio::SFX::SoundEffectID;
        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::GameMode2;
        using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
        using OpenSHC::UI::Enums::BuildMenuTabType;
        using OpenSHC::UI::Enums::MenuModalType;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "UnsortedBinkFlagInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004251A0
        void MainMenu::MenuItemActionHandler_MainMenu_Main(int param_1, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            MenuViewType menuID;
            switch (param_1) {
            case 1:
                /*
                  historical campagins
                 */
                DAT_GameCore::instance.field22_0x64 = 0;
                DAT_GameState::instance.mapAndTime.difficulty = DAT_GameCore::instance.missionDifficulty;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_HISTORIC_CAMPAIGN_SELECT, 0);
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
                /*
                  crusader
                 */
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_SELECT_CRUSADE, 0);
                return;
            case 3:
                /*
                  castle builder
                 */
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
                DAT_GameCore::instance.menuTabToSwitchTo.tabType = ((BuildingsAndStatusMenuTabType)0);
                menuID = OpenSHC::UI::Enums::MVT_SINGLEPLAYER_MAP_CHOICE;
                break;
            case 4:
                /*
                  multiplayer
                 */
                if ((int)DAT_GameCore::instance.directDrawStatus < 0x700) {}
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
                menuID = OpenSHC::UI::Enums::MVT_MP_CONNECTION;
                break;
            case 5:
                /*
                  quit
                 */
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 9;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_YES_NO_DIALOG);
                MACRO_CALL_MEMBER(
                    OpenSHC::Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
                return;
            case 6:
                /*
                  tutorial
                 */
                DAT_GameCore::instance.missionNumber1to20 = 0x1e;
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
                    "Crusader_tutorial.map");
                DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = OpenSHC::UI::Enums::BMTT_CASTLE;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_BUILD_MENU, 0);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::MenuTextInputState_Func::clearModalDialog2to6, DAT_MenuTextInputState::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_TUTORIAL_BOX, FALSE);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::InitTutorialStepTransition)(1);
                DAT_00df555c::instance = DAT_MissionAestheticsDefinedData::instance.field1249_0x5324[0];
                INT_DisableTutorialRestrictions::instance = 0;
                DAT_TutorialCurrentStep::instance = 0;
                DAT_00df5554::instance = 0x20;
                DAT_00df5558::instance = 0;
                DAT_00df5560::instance = 0;
                DAT_00df5564::instance = 0;
                DAT_00df556c::instance = 0x24;
                iVar2 = 1;
                iVar3 = 0;
                do {
                    iVar1 = *(int*)((int)DAT_MissionAestheticsDefinedData::instance.field1249_0x5324 + iVar3);
                    *(int*)((int)INT_ARRAY_00df5598::instance + iVar3) = iVar2 + 1;
                    iVar3 = iVar3 + 4;
                    iVar2 = iVar2 + 2 + iVar1;
                } while (iVar3 < 128);
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetTutorialActionTrackers)();
                return;
            case 7:
                /*
                  credits
                 */
                DAT_00b95954::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CREDITS, 0);
                return;
            case 8:
                /*
                  options
                 */
                DAT_GameSynchronyState::instance.currentPlayerSlotID = 0;
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_ASK_FOR_SLOT_ASSIGNMENT);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuTextInputState_Func::activateModalDialogAndClearText,
                    DAT_MenuTextInputState::ptr)(OpenSHC::UI::Enums::MMT_MAIN_MENU_OPTIONS);
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                    ((SoundEffectID)0x101));
                return;
            case 9:
                /*
                  custom scenarios
                 */
                DAT_GameCore::instance.gameMode_2 = OpenSHC::Game::GM_EDITOR;
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_CUSTOM_SCENARIOS, 0);
                return;
            default:
                break;
            }
            /*
              castle builder or multiplayer
             */
            MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(menuID, 0);
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
        }

    }
}
}
