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
        void AIMessageQueue::playAiLordMessage(int param_1, int param_2)
        {
            int iVar3;
            int iVar4;
            int iVar5;
            DWORD DVar1 = timeGetTime();
            int iVar6 = 0;
            BOOLEnum BVar2 = MACRO_CALL_MEMBER(Game::GameCore_Func::getAreWeInAInGameMenu, DAT_GameCore::ptr)();
            if (BVar2) {
                if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BARRACKS_OR_MPMENU_MODEM) {
                        iVar6 = -0x28;
                    } else {
                        iVar6
                            = (-(uint)(DAT_GameCore::instance.activeMenuTab.tabType != UI::Enums::BASMTT_MERCENARYPOST)
                                  & 0x14)
                            - 0x28;
                    }
                }
                BVar2 = MACRO_CALL(UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                    UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO);
                if (BVar2) {
                    iVar6 = iVar6 + -0x28;
                }
                if (!this->currentMessageUnknownValue_0x4) {
                    iVar3 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineWideTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        (WCHAR*)this->currentMessageText_0x8, 0, 0, 0x244, 0, 0, 1);
                    iVar4 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineWideTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        (WCHAR*)this->currentMessageText_0x8, 0, 0, 0x244, 0, 0, 2);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineWideTextUnk, DAT_TextManagerObject::ptr)(
                        (WCHAR*)this->currentMessageText_0x8, param_1 - iVar4, (iVar6 - iVar3) + param_2, 0x244,
                        0xccfaff, 0, 0x12, 0);
                } else {
                    iVar3 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        this->currentMessageText_0x8, 0, 0, 0x244, 0, 0, 1);
                    iVar4 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        this->currentMessageText_0x8, 0, 0, 0x244, 0, 0, 2);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                        this->currentMessageText_0x8, param_1 - iVar4, (iVar6 - iVar3) + param_2, 0x244, 0xccfaff, 0,
                        0x12, 0);
                }
                if (0 < (int)this->currentMessageUnknownValue2_0xd4) {
                    iVar3 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4], 0, 0,
                        0x244, 0, 0, 1);
                    iVar5 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4], 0, 0,
                        0x244, 0, 0, 2);
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[this->currentMessageUnknownValue2_0xd4],
                        param_1 - iVar5, (iVar6 - iVar3) + param_2, 0x244, 0xccfaff, 0, 0x12, 0);
                    iVar6 = 0;
                    if (DAT_GameSynchronyState::instance
                            .currentPlayerFullIDArray[this->currentMessageUnknownValue2_0xd4]
                        == -1) {
                        iVar6 = DAT_GameSynchronyState::instance.currentAIArray[this->currentMessageUnknownValue2_0xd4];
                    }
                    iVar5 = (param_1 - iVar5) + -0x50;
                    iVar3 = (param_2 - iVar3) + -0x30;
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2,
                        (int)(this->currentMessageUnknownValue2_0xd4 + 0x222), iVar5, iVar3);
                    if (!iVar6) {
                        iVar6 = 0x21b;
                    } else {
                        iVar6 = iVar6 + 0x20a;
                    }
                    MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(DE::SHCDE::GM_INTERFACE_ICONS2, iVar6, iVar5, iVar3);
                }
                BVar2 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                    DAT_SoundSystemState::ptr)(Audio::MSS::enums::SND_STR_SPEECH_1);
                if (!BVar2) {
                    this->mbr_0x92c = 1;
                }
                if (10000 < (int)(DVar1 - this->videoStartTimeUnk_0xd8) || !iVar4) {
                    if (this->currentMessageVfxFile_0xc[0] == '\0') {
                        if (this->currentMessageSfxFile_0x70[0] != '\0'
                            && DAT_SoundSystemState::instance.waveOutOpenUnk_0x8
                            && DAT_SoundSystemState::instance.soundActiveUnk_0x0 && !this->mbr_0x92c) {}
                    } else if (DAT_BinkControlState::instance.binkObjPtrArray[1] != (HBINK)0x0) {
                    }
                    if (!DAT_GameCore::instance.gamePausedLogical) {
                        this->mbr_0x928 = 0;
                        DAT_GameCore::instance.countdown = 2;
                        MACRO_CALL_MEMBER(UI::MenuModalComposition_Func::activateModalDialog,
                            DAT_MenuModalComposition2::ptr)(UI::Enums::MMT_NONE, FALSE);
                    }
                }
            }
        }

    }
}
}
