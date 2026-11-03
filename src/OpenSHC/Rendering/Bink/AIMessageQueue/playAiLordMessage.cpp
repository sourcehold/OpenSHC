#include "../../../Rendering.func.hpp"
#include "../AIMessageQueue.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuModalComposition.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition2.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using Audio::MSS::enums::SHC_SoundStream;
        using DE::SHCDE::eGM;
        using UI::Enums::BuildingsAndStatusMenuTabType;
        using UI::Enums::DisplayElementID;
        using UI::Enums::MenuModalType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004B7C90
        void AIMessageQueue::playAiLordMessage(int x, int y)
        {
            DWORD const now = timeGetTime();
            int yOffset = 0;
            if (!MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)()) {
                return;
            }
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                    yOffset = -40;
                } else if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_MERCENARYPOST) {
                    yOffset = -40;
                } else {
                    yOffset = -20;
                }
            }
            if (MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO)) {
                yOffset = yOffset - 40;
            }
            int textHeight;
            int textWidth;
            if (!this->currentMessageUnknownValue_0x4) {
                textHeight = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineWideTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    (WCHAR*)this->currentMessageText_0x8, 0, 0, 580, 0, 0, 1);
                textWidth = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineWideTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    (WCHAR*)this->currentMessageText_0x8, 0, 0, 580, 0, 0, 2);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineWideTextUnk, DAT_TextManagerObject::ptr)(
                    (WCHAR*)this->currentMessageText_0x8, x - textWidth, yOffset - textHeight + y, 580, 0xccfaff, 0, 18,
                    0);
            } else {
                textHeight = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    this->currentMessageText_0x8, 0, 0, 580, 0, 0, 1);
                textWidth = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    this->currentMessageText_0x8, 0, 0, 580, 0, 0, 2);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    this->currentMessageText_0x8, x - textWidth, yOffset - textHeight + y, 580, 0xccfaff, 0, 18, 0);
            }
            if ((int)this->currentMessageUnknownValue2_0xd4 > 0) {
                int const nameHeight = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4], 0, 0, 580,
                    0, 0, 1);
                int const nameWidth = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4], 0, 0, 580,
                    0, 0, 2);
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4],
                    x - nameWidth, yOffset - nameHeight + y, 580, 0xccfaff, 0, 18, 0);
                int aiCharacter = 0;
                if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[this->currentMessageUnknownValue2_0xd4]
                    == -1) {
                    aiCharacter
                        = DAT_GameSynchronyState::instance.currentAIArray[this->currentMessageUnknownValue2_0xd4];
                }
                int const faceX = x - nameWidth - 80;
                int const faceY = y - nameHeight - 48;
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                    DE::SHCDE::GM_INTERFACE_ICONS2, this->currentMessageUnknownValue2_0xd4 + 546, faceX, faceY);
                if (!aiCharacter) {
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, 539, faceX, faceY);
                } else {
                    MACRO_CALL_MEMBER(
                        UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        DE::SHCDE::GM_INTERFACE_ICONS2, aiCharacter + 522, faceX, faceY);
                }
            }
            if (!MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying, DAT_SoundSystemState::ptr)(
                    Audio::MSS::enums::SND_STR_SPEECH_1)) {
                this->mbr_0x92c = 1;
            }
            if ((int)(now - this->videoStartTimeUnk_0xd8) <= 10000 && textWidth != 0) {
                return;
            }
            if (this->currentMessageVfxFile_0xc[0] != '\0') {
                if (DAT_BinkControlState::instance.binkObjPtrArray[1] != NULL) {
                    return;
                }
            } else if (this->currentMessageSfxFile_0x70[0] != '\0' && DAT_SoundSystemState::instance.waveOutOpenUnk_0x8
                && DAT_SoundSystemState::instance.soundActiveUnk_0x0 && !this->mbr_0x92c) {
                return;
            }
            if (DAT_GameCore::instance.gamePausedLogical) {
                return;
            }
            this->mbr_0x928 = 0;
            DAT_GameCore::instance.countdown = 2;
            MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog, DAT_MenuModalComposition2::ptr)(
                UI::Enums::MMT_NONE, FALSE);
        }

    }
}
}
