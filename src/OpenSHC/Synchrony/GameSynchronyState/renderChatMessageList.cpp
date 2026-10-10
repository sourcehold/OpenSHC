#include "../../Synchrony.func.hpp"
#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Text::TextAlignment;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0047FB50
    void GameSynchronyState::renderChatMessageList(int xPos, int yPos, int param_3)
    {
        this->chatMessageRenderIndex = this->DAT_ChatMessageArrayIndex - param_3;
        if (this->chatMessageRenderIndex < 0) {
            this->chatMessageRenderIndex = this->chatMessageRenderIndex + 0x14;
        }
        int iVar2 = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
            DAT_TextureRenderCoreObject::ptr)(yPos + -0x48, yPos + 0x12);
        DAT_TextManagerObject::instance.field13_0x34 = 0x11;
        param_3 = 0;
        do {
            if (this->DAT_ChatEventArray[this->chatMessageRenderIndex].flag == 1) {
                int iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                    this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], xPos, yPos,
                    Text::TTA_LEFT,
                    (uint)(DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                    [this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]]),
                    0, 0x13, FALSE, (iVar1 / 32) + 0x20);
                iVar1 = MACRO_CALL_MEMBER(Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[0x13])(
                    this->DAT_ChatMessageArray[this->chatMessageRenderIndex], 0, 0,
                    0x1ee - DAT_TextManagerObject::instance.currentXOffset_0x0, 0, 0, 1);
                if (0x18 < iVar1) {
                    iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                    yPos = yPos + -0x12;
                    iVar2 = iVar2 + 1;
                    MACRO_CALL_MEMBER(Text::TextManager_Func::renderInGameTextWithShadow, DAT_TextManagerObject::ptr)(
                        this->DAT_ChatMessageSubjectPlayerNameArray[this->chatMessageRenderIndex], xPos, yPos,
                        Text::TTA_LEFT,
                        (uint)(DAT_RenderingDefinedData::instance
                                .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor
                                        [this->DAT_ChatEventArray[this->chatMessageRenderIndex].subjectPlayer]]),
                        0, 0x13, FALSE, (iVar1 / 32) + 0x20);
                }
                iVar1 = (DAT_ButtonBackgroundBlendStrength::instance + -0x20) * 0x20;
                MACRO_CALL_MEMBER(Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    this->DAT_ChatMessageArray[this->chatMessageRenderIndex],
                    DAT_TextManagerObject::instance.currentXOffset_0x0 + 6 + xPos, yPos,
                    0x1ee - DAT_TextManagerObject::instance.currentXOffset_0x0, 0xa2ff, 0x3e66, 0x13,
                    (iVar1 / 32) + 0x20);
            }
            this->chatMessageRenderIndex = this->chatMessageRenderIndex + -1;
            if (this->chatMessageRenderIndex < 0) {
                this->chatMessageRenderIndex = 0x13;
            }
            iVar2 = iVar2 + 1;
            yPos = yPos + -0x11;
        } while ((iVar2 < 5) && (param_3 = param_3 + 1, param_3 < 5));
        DAT_TextManagerObject::instance.field13_0x34 = 0;
        MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
            DAT_TextureRenderCoreObject::ptr)();
    }

}
}
