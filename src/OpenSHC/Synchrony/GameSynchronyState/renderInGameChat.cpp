#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using DE::SHCDE::eTextSections;
    using Map::Units::UnitLogicState;
    using Rendering::Enums::RenderTarget;
    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047F860
    void GameSynchronyState::renderInGameChat(int param_1, int param_2, int param_3)
    {
        DWORD DVar1;
        int iVar2;
        int iVar3;
        char* pcVar4;
        int iVar5;
        TextAlignment alignment;
        uint foregroundColor;
        uint backgroundColor;
        BOOLEnum keepOffsetX;
        int blendStrength;
        int local_4;
        int _lordID;
        this->chatMessageRenderIndex = this->DAT_ChatMessageArrayIndex;
        local_4 = 4;
        do {
            iVar3 = this->chatMessageRenderIndex;
            if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].flag == 1) {
                DVar1 = timeGetTime();
                if ((int)(DVar1 - this->DAT_ChatEventArray[iVar3].time) < 0x2711) {
                    iVar5 = this->DAT_ChatEventArray[iVar3].subjectPlayer;
                    _lordID = DAT_GameState::instance.playerDataArray[iVar5].lordID;
                    iVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[iVar3], 0x13);
                    iVar3 = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageArray[this->chatMessageRenderIndex], 0x13);
                    iVar3 = iVar2 + 0xc + iVar3;
                    if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].objectPlayer != 0) {
                        iVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                            this->DAT_ChatMessageObjectPlayerNameArray[this->chatMessageRenderIndex], 0x13);
                        iVar3 = iVar3 + 6 + iVar2;
                    }
                    if ((((!_lordID)
                             || (DAT_UnitsState::instance.units[_lordID].uid
                                 != DAT_GameState::instance.playerDataArray[iVar5].lordUID))
                            || (DAT_UnitsState::instance.units[_lordID].logicalState != Map::Units::ULS_NORMAL))
                        && 200 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
                        iVar2 = 0x13;
                        /*
                          added by script: "(deceased)"
                         */
                        pcVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x2c);
                        iVar2 = MACRO_CALL_MEMBER(Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                            pcVar4, iVar2);
                        iVar3 = iVar3 + 6 + iVar2;
                    }
                    DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_MAP_GAME;
                    MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(param_1 + -5, param_2 + -4, iVar3 + param_1, param_2 + 9, 0x10);
                    DAT_PencilRenderCore::instance.surfaceTarget = Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], param_1, param_2,
                        Text::TTA_LEFT,
                        (uint)((int)(DAT_RenderingDefinedData::instance
                                .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                        [this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]])),
                        0, 0x13, FALSE, 0);
                    iVar3 = param_1;
                    if ((((!_lordID)
                             || (DAT_UnitsState::instance.units[_lordID].uid
                                 != DAT_GameState::instance.playerDataArray[iVar5].lordUID))
                            || (DAT_UnitsState::instance.units[_lordID].logicalState != Map::Units::ULS_NORMAL))
                        && 200 < (int)(DAT_GameCore::instance.mapTimeInTicks - DAT_GameCore::instance.section1127)) {
                        blendStrength = 0;
                        keepOffsetX = TRUE;
                        iVar2 = 0x13;
                        backgroundColor = 0;
                        foregroundColor = 0xb8eefb;
                        alignment = Text::TTA_LEFT;
                        iVar3 = param_1 + 6;
                        iVar5 = iVar3;
                        _lordID = param_2;
                        /*
                          added by script: "(deceased)"
                         */
                        pcVar4 = MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(DE::SHCDE::TEXT_MULTIPLAYER_CONNECTION, 0x2c);
                        MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow,
                            DAT_TextManagerObject::ptr)(pcVar4, iVar5, _lordID, alignment, foregroundColor,
                            backgroundColor, iVar2, keepOffsetX, blendStrength);
                    }
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageArray[this->chatMessageRenderIndex], iVar3 + 6, param_2, Text::TTA_LEFT,
                        0xb8eefb, 0, 0x13, TRUE, 0);
                    iVar5 = this->DAT_ChatEventArray[this->chatMessageRenderIndex].objectPlayer;
                    if (iVar5) {
                        MACRO_CALL_MEMBER(
                            Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                            this->DAT_ChatMessageObjectPlayerNameArray[this->chatMessageRenderIndex], iVar3 + 0xc,
                            param_2, Text::TTA_LEFT,
                            (uint)((int)(DAT_RenderingDefinedData::instance
                                    .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[iVar5]])),
                            0, 0x13, TRUE, 0);
                    }
                } else {
                    this->DAT_ChatEventArray[iVar3].flag = 0;
                }
            }
            this->chatMessageRenderIndex = this->chatMessageRenderIndex + -1;
            if (this->chatMessageRenderIndex < 0) {
                this->chatMessageRenderIndex = 0x13;
            }
            param_2 = param_2 + -0xe;
            local_4 = local_4 + -1;
        } while (local_4);
    }

}
}
