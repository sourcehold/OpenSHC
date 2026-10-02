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

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::Game::Resources::ResourceType;
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
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BCEC0
        void TutorialBox::MenuItemActionHandler_TutorialBox_Main(int param_1, ...)
        {
            int iVar1;
            int amount;
            char local_24[32];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_24;
            if (param_1 == 2) {
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
                ;
            }
            if (((param_1 == 1) && (DAT_00df5560::instance != 0)) && (DAT_00df5540::instance == 0)) {
                DAT_00df5558::instance = DAT_00df5558::instance + 1;
                DAT_00df5560::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2);
                if (((DAT_TutorialCurrentStep::instance == 2) && (DAT_00df5558::instance == 1))
                    && (0
                        < DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .keep.id)) {
                    DAT_00df5558::instance = 2;
                }
                MACRO_CALL(OpenSHC::UI::Helpers_Func::ResetTutorialActionTrackers)();
                if (DAT_00df555c::instance <= DAT_00df5558::instance) {
                    DAT_00df5558::instance = DAT_00df5558::instance + -1;
                    MACRO_CALL(OpenSHC::UI::Helpers_Func::InitTutorialStepTransition)(2);
                    DAT_00df5560::instance = 0;
                    if (DAT_00df5554::instance + -1 <= DAT_TutorialCurrentStep::instance) {
                        INT_DisableTutorialRestrictions::instance = 1;
                    }
                    if (DAT_MissionAestheticsDefinedData::instance.field1251_0x5464[DAT_TutorialCurrentStep::instance]
                        == 1) {
                        iVar1 = DAT_00df556c::instance * 0x60;
                        DAT_00df556c::instance = DAT_00df556c::instance + 1;
                        MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_24, "%s%s", "fx\\speech\\", iVar1 + 0xb3d810);
                        MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
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
                        amount = 0x4b - DAT_GameState::instance.playerDataArray[iVar1].totalFood;
                        if (0 < amount) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::processResourceGain,
                                DAT_BuildingsState::ptr)(iVar1, OpenSHC::Game::Resources::RT_MEAT, amount);
                        }
                    }
                }
            };
        }

    }
}
}
