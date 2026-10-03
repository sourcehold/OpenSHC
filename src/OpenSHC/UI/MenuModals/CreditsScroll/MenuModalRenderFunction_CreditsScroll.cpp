#include "../CreditsScroll.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004AAB50
        void CreditsScroll::MenuModalRenderFunction_CreditsScroll(int x, int y, int width, int height)
        {
            int left;
            int iVar1;
            int right;
            int iVar2;
            int local_58;
            int local_54;
            int local_50;
            int local_4c;
            int local_48;
            int local_44;
            int local_40;
            int local_3c;
            int local_38;
            int local_34;
            int local_30;
            int local_2c;
            int local_28;
            int local_24;
            int local_20;
            int local_1c;
            int local_18;
            int local_14;
            int local_10;
            int local_c;
            int local_8;
            if (DAT_TextEditorState::instance.pendingCreditsFadeBorder != FALSE) {
                DAT_TextEditorState::instance.pendingCreditsFadeBorder = FALSE;
                MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextEditorState_Func::setTextRenderingLogic, DAT_TextEditorState::ptr)();
                right = x + -1 + width;
                local_58 = 0;
                left = x + 1;
                local_10 = -600;
                local_14 = -0x23a;
                local_18 = -0x21c;
                local_1c = -0x1fe;
                local_20 = -0x1e0;
                local_24 = -0x1c2;
                local_28 = -0x1a4;
                local_2c = -0x186;
                local_30 = -0x168;
                local_34 = -0x14a;
                local_38 = -300;
                local_3c = -0x10e;
                local_40 = -0xf0;
                local_44 = -0xd2;
                local_48 = -0xb4;
                local_4c = -0x96;
                local_50 = -0x5a;
                local_54 = -0x3c;
                local_c = 0x1e;
                iVar2 = y;
                do {
                    iVar1 = iVar2 + 3;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x, iVar2, x, iVar1, 0x20 - local_c / 0x14);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(left, iVar2, left, iVar1, local_54 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 2, iVar2, x + 2, iVar1, local_50 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 3, iVar2, x + 3, iVar1, ((-0x78 - y) + iVar2) / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 4, iVar2, x + 4, iVar1, local_4c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 5, iVar2, x + 5, iVar1, local_48 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 6, iVar2, x + 6, iVar1, local_44 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 7, iVar2, x + 7, iVar1, local_40 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 8, iVar2, x + 8, iVar1, local_3c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 9, iVar2, x + 9, iVar1, local_38 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 10, iVar2, x + 10, iVar1, local_34 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xb, iVar2, x + 0xb, iVar1, local_30 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xc, iVar2, x + 0xc, iVar1, local_2c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xd, iVar2, x + 0xd, iVar1, local_28 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xe, iVar2, x + 0xe, iVar1, local_24 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xf, iVar2, x + 0xf, iVar1, local_20 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x10, iVar2, x + 0x10, iVar1, local_1c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x11, iVar2, x + 0x11, iVar1, local_18 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x12, iVar2, x + 0x12, iVar1, local_14 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x13, iVar2, x + 0x13, iVar1, local_10 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x14, iVar2, right, iVar1, local_58 + 2);
                    local_50 = local_50 + 3;
                    local_4c = local_4c + 5;
                    local_48 = local_48 + 6;
                    local_44 = local_44 + 7;
                    local_40 = local_40 + 8;
                    local_3c = local_3c + 9;
                    local_38 = local_38 + 10;
                    local_34 = local_34 + 0xb;
                    local_30 = local_30 + 0xc;
                    local_2c = local_2c + 0xd;
                    local_28 = local_28 + 0xe;
                    local_24 = local_24 + 0xf;
                    local_20 = local_20 + 0x10;
                    local_1c = local_1c + 0x11;
                    local_18 = local_18 + 0x12;
                    local_14 = local_14 + 0x13;
                    local_10 = local_10 + 0x14;
                    local_58 = local_58 + 1;
                    local_c = local_c + -1;
                    local_54 = local_54 + 2;
                    iVar2 = iVar2 + 4;
                } while (local_54 < 0);
                local_58 = 0;
                local_50 = -600;
                local_4c = -0x23a;
                local_48 = -0x21c;
                local_44 = -0x1fe;
                local_40 = -0x1e0;
                local_3c = -0x1c2;
                local_38 = -0x1a4;
                local_34 = -0x186;
                local_30 = -0x168;
                local_2c = -0x14a;
                local_28 = -300;
                local_24 = -0x10e;
                local_20 = -0xf0;
                local_1c = -0xd2;
                local_18 = -0xb4;
                local_14 = -0x96;
                local_54 = -0x78;
                local_10 = -0x5a;
                local_c = -0x3c;
                local_8 = 0x1e;
                iVar2 = y + height;
                do {
                    iVar1 = iVar2 + 3;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x, iVar2, x, iVar1, 0x20 - local_8 / 0x14);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(left, iVar2, left, iVar1, local_c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 2, iVar2, x + 2, iVar1, local_10 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 3, iVar2, x + 3, iVar1, local_54 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 4, iVar2, x + 4, iVar1, local_14 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 5, iVar2, x + 5, iVar1, local_18 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 6, iVar2, x + 6, iVar1, local_1c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 7, iVar2, x + 7, iVar1, local_20 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 8, iVar2, x + 8, iVar1, local_24 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 9, iVar2, x + 9, iVar1, local_28 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 10, iVar2, x + 10, iVar1, local_2c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xb, iVar2, x + 0xb, iVar1, local_30 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xc, iVar2, x + 0xc, iVar1, local_34 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xd, iVar2, x + 0xd, iVar1, local_38 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xe, iVar2, x + 0xe, iVar1, local_3c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0xf, iVar2, x + 0xf, iVar1, local_40 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x10, iVar2, x + 0x10, iVar1, local_44 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x11, iVar2, x + 0x11, iVar1, local_48 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x12, iVar2, x + 0x12, iVar1, local_4c / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x13, iVar2, x + 0x13, iVar1, local_50 / 0x14 + 0x20);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                        DAT_PencilRenderCore::ptr)(x + 0x14, iVar2, right, iVar1, local_58 + 2);
                    local_10 = local_10 + 3;
                    local_14 = local_14 + 5;
                    local_18 = local_18 + 6;
                    local_1c = local_1c + 7;
                    local_20 = local_20 + 8;
                    local_24 = local_24 + 9;
                    local_28 = local_28 + 10;
                    local_2c = local_2c + 0xb;
                    local_30 = local_30 + 0xc;
                    local_34 = local_34 + 0xd;
                    local_38 = local_38 + 0xe;
                    local_3c = local_3c + 0xf;
                    local_40 = local_40 + 0x10;
                    local_44 = local_44 + 0x11;
                    local_48 = local_48 + 0x12;
                    local_4c = local_4c + 0x13;
                    local_50 = local_50 + 0x14;
                    local_54 = local_54 + 4;
                    local_58 = local_58 + 1;
                    local_8 = local_8 + -1;
                    local_c = local_c + 2;
                    iVar2 = iVar2 + -4;
                } while (local_c < 0);
            }
        }

    }
}
}
