#include "../../../Rendering.func.hpp"
#include "../AIMessageQueue.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

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

        using Audio::MSS::SoundFlagsAndLoopCount;
        using Audio::MSS::enums::SHC_SoundStream;
        using IO::FileResourceType;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7AF0
        void AIMessageQueue::playVideoOverMap(char* binkFileName, char* sfxFileName)
        {
            char* _binkFileName;
            char* _filename;
            BOOLEnum _isSpeech1Playing;
            int _sfxFileNameIndex;
            char* _currentSfxFilePtr;
            SoundFlagsAndLoopCount _flagsAndLoopCount;
            char _runChar;
            _binkFileName = binkFileName;
            do {
                _runChar = *_binkFileName;
                _binkFileName[0xee10ac - (int)binkFileName] = _runChar;
                _binkFileName = _binkFileName + 1;
            } while (_runChar != '\0');
            _sfxFileNameIndex = 0xee1110 - (int)sfxFileName;
            do {
                _runChar = *sfxFileName;
                sfxFileName[_sfxFileNameIndex] = _runChar;
                sfxFileName = sfxFileName + 1;
            } while (_runChar != '\0');
            this->mbr_0x928 = this->currentMessageUnknownValue2_0xd4;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::setExtraActiveModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_DISPLAY_AI_LORD_MESSAGE, DAT_MenuHandlerState::instance.x + 0x2d5,
                DAT_WindowAndDirectDraw::instance.resolutionY + -0x99);
            if (this->currentMessageVfxFile_0xc[0] != '\0') {
                DAT_GameCore::instance.isBinkVideoPlaying = 1;
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU
                    && (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                        || (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_SIEGETENT_SHIELD))) {
                    MACRO_CALL_MEMBER(Game::GameCore_Func::swapBuildMenuTab, DAT_GameCore::ptr)();
                    if (DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType
                        == UI::Enums::BASMTT_SIEGETENT_SIEGETOWER) {
                        if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILD_MENU) {
                            DAT_GameCore::instance.buildmenuMenuTabToSwitchTo.tabType = UI::Enums::BASMTT_HUNTERSHUT;
                        } else if (DAT_GameCore::instance.currentMenuViewType
                            == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                            DAT_GameCore::instance.landscapingmenuMenuTabToSwitchTo = 0xe7;
                        }
                    }
                    MACRO_CALL_MEMBER(Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(
                        (UI::Enums::MenuViewType)DAT_GameCore::instance.currentMenuViewType, 0);
                }
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(1,
                    binkFileName, 0, 0, DAT_MenuHandlerState::instance.x + 0x23b,
                    DAT_MenuHandlerState::instance.y + 0x1d1, 1);
            }
            if (this->currentMessageSfxFile_0x70[0] != '\0') {
                MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    IO::FRT_GFX_SPEECH, (char const*)((int)(this->currentMessageSfxFile_0x70)));
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1);
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_2);
                _flagsAndLoopCount = -536870911;
                _filename = MACRO_CALL_MEMBER(
                    IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk, DAT_SoundSystemState::ptr)(
                    _filename, _flagsAndLoopCount);
                this->mbr_0x92c = 0;
                if (this->currentMessageVfxFile_0xc[0] != '\0') {
                    _isSpeech1Playing = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_1);
                    if (_isSpeech1Playing) {
                        MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::setBinkSndStreamAndStartTime,
                            DAT_BinkControlState::ptr)(1, Audio::MSS::enums::SND_STR_SPEECH_1);
                    }
                }
            }
            this->messagePlaying_0x0 = TRUE;
            this->videoStartTimeUnk_0xd8 = timeGetTime();
        }

    }
}
}
