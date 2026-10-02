#include "../LoadMap.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x00494210
        void LoadMap::MenuModalRenderFunction_LoadMap(int x, int y, int width, int height)
        {
            int y1;
            int x2;
            int x1;
            int y2;
            /*
              added by script: "Load"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0x4a, 2, x, y, 0x130, height);
            y1 = y + 0x22;
            x2 = x + 0x29f;
            x1 = x + 0x135;
            y2 = y + 0x177;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x21, x2, y + 0x21, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x178, x2, y + 0x178, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x36, x2, y + 0x36, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x28a, y1, x + 0x28a, y2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x28b, y + 0x163, x + 0x29e, y + 0x163, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetupPreviewMinimapDataUnk)();
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                x + 0x37, y + 0x5f);
            (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
            if (DAT_MenuTextInputState::instance.field0_0x0 == 1) {
                DAT_MenuTextInputState::instance.field2_0x8
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.field1_0x4
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.field3_0xc = DAT_MenuTextInputState::instance.field33_0x78;
            }
            if (DAT_MenuTextInputState::instance.field0_0x0 == 2) {
                DAT_MenuTextInputState::instance.field8_0x20
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.field7_0x1c
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.field9_0x24 = DAT_MenuTextInputState::instance.field33_0x78;
            }
            if (DAT_MenuTextInputState::instance.field0_0x0 == 3) {
                DAT_MenuTextInputState::instance.field5_0x14
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.field4_0x10
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.field6_0x18 = DAT_MenuTextInputState::instance.field33_0x78;
            }
        }

    }
}
}
