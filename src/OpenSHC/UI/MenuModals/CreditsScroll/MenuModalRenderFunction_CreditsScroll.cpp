#include "../CreditsScroll.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AAB50
        void CreditsScroll::MenuModalRenderFunction_CreditsScroll(int x, int y, int width, int height)
        {
            int iVar1;
            if (DAT_TextEditorState::instance.pendingCreditsFadeBorder) {
                DAT_TextEditorState::instance.pendingCreditsFadeBorder = FALSE;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                int right = x - 1 + width;
                int local_58 = 0;
                int left = x + 1;
                int local_10 = -600;
                int local_14 = -570;
                int local_18 = -540;
                int local_1c = -0x1fe;
                int local_20 = -0x1e0;
                int local_24 = -450;
                int local_28 = -420;
                int local_2c = -390;
                int local_30 = -360;
                int local_34 = -330;
                int local_38 = -300;
                int local_3c = -270;
                int local_40 = -0xf0;
                int local_44 = -210;
                int local_48 = -180;
                int local_4c = -150;
                int local_50 = -90;
                int local_54 = -0x3c;
                int local_c = 0x1e;
                int fadeCol3 = -0x78;
                int iVar2 = y;
                do {
                    iVar1 = iVar2 + 3;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x, iVar2, x, iVar1, 32 - local_c / 20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(left, iVar2, left, iVar1, local_54 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 2, iVar2, x + 2, iVar1, local_50 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 3, iVar2, x + 3, iVar1, fadeCol3 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 4, iVar2, x + 4, iVar1, local_4c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 5, iVar2, x + 5, iVar1, local_48 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 6, iVar2, x + 6, iVar1, local_44 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 7, iVar2, x + 7, iVar1, local_40 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 8, iVar2, x + 8, iVar1, local_3c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 9, iVar2, x + 9, iVar1, local_38 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 10, iVar2, x + 10, iVar1, local_34 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 11, iVar2, x + 11, iVar1, local_30 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 12, iVar2, x + 12, iVar1, local_2c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 13, iVar2, x + 13, iVar1, local_28 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 14, iVar2, x + 14, iVar1, local_24 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xf, iVar2, x + 0xf, iVar1, local_20 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 16, iVar2, x + 16, iVar1, local_1c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 17, iVar2, x + 17, iVar1, local_18 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 18, iVar2, x + 18, iVar1, local_14 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 19, iVar2, x + 19, iVar1, local_10 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 20, iVar2, right, iVar1, local_58 + 2);
                    local_50 += 3;
                    fadeCol3 += 4;
                    local_4c += 5;
                    local_48 += 6;
                    local_44 += 7;
                    local_40 += 8;
                    local_3c += 9;
                    local_38 += 10;
                    local_34 += 11;
                    local_30 += 12;
                    local_2c += 13;
                    local_28 += 14;
                    local_24 += 0xf;
                    local_20 += 16;
                    local_1c += 17;
                    local_18 += 18;
                    local_14 += 19;
                    local_10 += 20;
                    ++local_58;
                    --local_c;
                    local_54 += 2;
                    iVar2 += 4;
                } while (local_54 < 0);
                local_58 = 0;
                local_50 = -600;
                local_4c = -570;
                local_48 = -540;
                local_44 = -0x1fe;
                local_40 = -0x1e0;
                local_3c = -450;
                local_38 = -420;
                local_34 = -390;
                local_30 = -360;
                local_2c = -330;
                local_28 = -300;
                local_24 = -270;
                local_20 = -0xf0;
                local_1c = -210;
                local_18 = -180;
                local_14 = -150;
                local_54 = -0x78;
                local_10 = -90;
                local_c = -0x3c;
                int local_8 = 0x1e;
                iVar2 = y + height;
                do {
                    iVar1 = iVar2 + 3;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x, iVar2, x, iVar1, 32 - local_8 / 20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(left, iVar2, left, iVar1, local_c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 2, iVar2, x + 2, iVar1, local_10 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 3, iVar2, x + 3, iVar1, local_54 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 4, iVar2, x + 4, iVar1, local_14 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 5, iVar2, x + 5, iVar1, local_18 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 6, iVar2, x + 6, iVar1, local_1c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 7, iVar2, x + 7, iVar1, local_20 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 8, iVar2, x + 8, iVar1, local_24 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 9, iVar2, x + 9, iVar1, local_28 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 10, iVar2, x + 10, iVar1, local_2c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 11, iVar2, x + 11, iVar1, local_30 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 12, iVar2, x + 12, iVar1, local_34 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 13, iVar2, x + 13, iVar1, local_38 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 14, iVar2, x + 14, iVar1, local_3c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xf, iVar2, x + 0xf, iVar1, local_40 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 16, iVar2, x + 16, iVar1, local_44 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 17, iVar2, x + 17, iVar1, local_48 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 18, iVar2, x + 18, iVar1, local_4c / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 19, iVar2, x + 19, iVar1, local_50 / 20 + 32);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 20, iVar2, right, iVar1, local_58 + 2);
                    local_10 += 3;
                    local_14 += 5;
                    local_18 += 6;
                    local_1c += 7;
                    local_20 += 8;
                    local_24 += 9;
                    local_28 += 10;
                    local_2c += 11;
                    local_30 += 12;
                    local_34 += 13;
                    local_38 += 14;
                    local_3c += 0xf;
                    local_40 += 16;
                    local_44 += 17;
                    local_48 += 18;
                    local_4c += 19;
                    local_50 += 20;
                    local_54 += 4;
                    ++local_58;
                    --local_8;
                    local_c += 2;
                    iVar2 -= 4;
                } while (local_c < 0);
            }
        }

    }
}
}
