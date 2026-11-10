// disable deprecation warnings for strcpy
#pragma warning(disable : 4996)

#include "../AIMessageQueue.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCountBitwiseFlagEnum.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/BuildMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using UI::Enums::MenuViewType;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7AF0
        void AIMessageQueue::playVideoOverMap(char* binkFileName, char* sfxFileName)
        {
            strcpy(this->currentMessageVfxFile_0xc, binkFileName);
            strcpy(this->currentMessageSfxFile_0x70, sfxFileName);
            this->mbr_0x928 = this->currentMessageUnknownValue2_0xd4;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE, DAT_MenuHandlerState::instance.x + 725,
                DAT_WindowAndDirectDraw::instance.resolutionY - 153);
            if (this->currentMessageVfxFile_0xc[0] != '\0') {
                DAT_GameCore::instance.isBinkVideoPlaying = 1;
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                    && (DAT_GameCore::instance.activeMenuTab.buildMenuTab == UI::Enums::BMTT_MENU_HIDDEN
                        || DAT_GameCore::instance.activeMenuTab.buildMenuTab == 62)) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::swapBuildMenuTab, DAT_GameCore::ptr)();
                    if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab == UI::Enums::BMTT_MENU_HIDDEN) {
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.buildMenuTab = UI::Enums::BMTT_CASTLE;
                        } else if (DAT_GameCore::instance.currentMenuViewType
                            == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo.buildMenuTab = 231;
                        }
                    }
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        (UI::Enums::MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
                }
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(1,
                    binkFileName, 0, 0, DAT_MenuHandlerState::instance.x + 571, DAT_MenuHandlerState::instance.y + 465,
                    1);
            }
            if (this->currentMessageSfxFile_0x70[0] != '\0') {
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    IO::FRT_GFX_SPEECH, this->currentMessageSfxFile_0x70);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_2);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                    MACRO_CALL_MEMBER(
                        IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)(),
                    Audio::MSS::FLAG_SOUND_UNINTERRUPTABLE | Audio::MSS::FLAG_SOUND_UNKNOWN_FLAG_2
                        | Audio::MSS::FLAG_SOUND_UNKNOWN_FLAG_1 | 1);
                this->mbr_0x92c = 0;
                if (this->currentMessageVfxFile_0xc[0] != '\0'
                    && MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_1)) {
                    MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::setBinkSndStreamAndStartTime,
                        DAT_BinkControlState::ptr)(1, Audio::MSS::enums::SND_STR_SPEECH_1);
                }
            }
            this->messagePlaying_0x0 = TRUE;
            this->videoStartTimeUnk_0xd8 = timeGetTime();
        }

    }
}
}
