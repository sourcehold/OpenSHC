#include "../TutorialBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5554.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df555c.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_00df556c.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
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
#include "OpenSHC/Globals/INT_DisableTutorialRestrictions.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using Audio::MSS::enums::SHC_SoundStream;
        using Game::Resources::ResourceType;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BCEC0
        void TutorialBox::MenuItemActionHandler_TutorialBox_Main(int param_1, ...)
        {
            int iVar1;
            char local_24[32];
            uint local_4 = MSVC_SecurityCookie::instance ^ (uint)local_24;
            if (param_1 == 2) {
                MACRO_CALL_MEMBER(Input::MouseState_Func::resetMouseState2, DAT_MouseState::ptr)();
                DAT_VideoBikQueue::instance.storedMessages_0x924 = 0;
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition1::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition3::ptr)(
                    UI::Enums::MMT_NONE, FALSE);
                MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                    UI::Enums::MVT_MAIN_MENU, 0);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_2);
                ;
            }
            if (param_1 == 1 && DAT_00df5560::instance && !DAT_00df5540::instance) {
                DAT_00df5558::instance = DAT_00df5558::instance + 1;
                DAT_00df5560::instance = 0;
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_2);
                if (DAT_TutorialCurrentStep::instance == 2 && DAT_00df5558::instance == 1
                    && 0 < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .keep.id) {
                    DAT_00df5558::instance = 2;
                }
                MACRO_CALL(UI::Helpers_Func::ResetTutorialActionTrackers)();
                if (DAT_00df555c::instance <= DAT_00df5558::instance) {
                    DAT_00df5558::instance = DAT_00df5558::instance + -1;
                    MACRO_CALL(UI::Helpers_Func::InitTutorialStepTransition)(2);
                    DAT_00df5560::instance = 0;
                    if (DAT_00df5554::instance + -1 <= DAT_TutorialCurrentStep::instance) {
                        INT_DisableTutorialRestrictions::instance = 1;
                    }
                    if (DAT_MissionAestheticsDefinedData::instance
                            .TutorialStepSpeechTrigger[DAT_TutorialCurrentStep::instance]
                        == 1) {
                        iVar1 = DAT_00df556c::instance * 0x60;
                        DAT_00df556c::instance = DAT_00df556c::instance + 1;
                        MACRO_CALL(OS_Func::_sprintf)(local_24, "%s%s", "fx\\speech\\", iVar1 + 0xb3d810);
                        MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                            DAT_SoundSystemState::ptr)(local_24);
                        if (0x27 < DAT_00df556c::instance) {
                            DAT_00df556c::instance = 0x24;
                        }
                    }
                    iVar1 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    if (DAT_TutorialCurrentStep::instance == 14) {
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSetting = 3;
                        DAT_GameState::instance.playerDataArray[iVar1].taxesSetting2 = 3;
                        DAT_GameState::instance.playerDataArray[iVar1].taxesSliderUI = 3;
                        DAT_GameState::instance.playerDataArray[iVar1].rationsSetting = 2;
                        DAT_GameState::instance.playerDataArray[iVar1].rationsSetting2 = 2;
                        DAT_GameState::instance.playerDataArray[iVar1].rationsSetting3 = 2;
                        DAT_GameState::instance.playerDataArray[iVar1].popularity = 10000;
                        int amount = 0x4b - DAT_GameState::instance.playerDataArray[iVar1].totalFood;
                        if (0 < amount) {
                            MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::processResourceGain,
                                DAT_BuildingsState::ptr)(iVar1, Game::Resources::RT_MEAT, amount);
                        }
                    }
                }
            };
        }

    }
}
}
