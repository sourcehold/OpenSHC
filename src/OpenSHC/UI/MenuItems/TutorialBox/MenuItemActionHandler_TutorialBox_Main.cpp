#include "../TutorialBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition3.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/INT_00df5554.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BCEC0
        void TutorialBox::MenuItemActionHandler_TutorialBox_Main(int button, ...)
        {
            if (button == 2) {
                MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition1::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition2::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::UI::MenuModalComposition_Func::activateModalDialog,
                    DAT_MenuModalComposition3::ptr)(OpenSHC::UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    OpenSHC::UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
                return;
            }
            if (button != 1 || !DAT_00df5560::instance || DAT_00df5540::instance != 0) {
                return;
            }
            ++DAT_00df5558::instance;
            DAT_00df5560::instance = FALSE;
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
            MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
            if (DAT_TutorialCurrentStep::instance == 2 && DAT_00df5558::instance == 1
                && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                        .id
                    > 0) {
                DAT_00df5558::instance = 2;
            }
            MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetTutorialActionTrackers)();
            if (DAT_00df5558::instance < DAT_00df555c::instance) {
                return;
            }
            --DAT_00df5558::instance;
            MACRO_CALL(OpenSHC::UI::Helpers_Func::InitTutorialStepTransition)(2);
            DAT_00df5560::instance = FALSE;
            // the original compares the step counters signed
            if ((int)DAT_TutorialCurrentStep::instance >= (int)INT_00df5554::instance - 1) {
                DAT_DisableTutorialRestrictions::instance = TRUE;
            }
            if (DAT_MissionAestheticsDefinedData::instance.TutorialStepSpeechTrigger[DAT_TutorialCurrentStep::instance]
                == 1) {
                char speechPath[32];
                // "%s%s", "fx\\speech\\"
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(speechPath, s__s_s_005aa800, s_fx_speech__005a64cc,
                    DAT_MissionAestheticsDefinedData::instance.field_0x41e4[DAT_00df556c::instance++][0]);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                    DAT_SoundSystemState::ptr)(speechPath);
                // after the last speech, 39, it plays 36 to 39 again
                if (DAT_00df556c::instance > 39) {
                    DAT_00df556c::instance = 36;
                }
            }
            if (DAT_TutorialCurrentStep::instance != 14) {
                return;
            }
            // 3: no taxes, 2: normal rations
            // the slot is read at each use: with a local, the totalFood read moves above the stores
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSetting
                = 3;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSetting2
                = 3;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].taxesSliderUI
                = 3;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].rationsSetting
                = 2;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .rationsSetting2 = 2;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                .rationsSetting3 = 2;
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].popularity
                = 10000;
            int const missingFood = 75
                - DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .totalFood;
            if (missingFood > 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                    DAT_BuildingsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID,
                    OpenSHC::Game::Resources::RT_MEAT, missingFood);
            }
        }

    }
}
}
