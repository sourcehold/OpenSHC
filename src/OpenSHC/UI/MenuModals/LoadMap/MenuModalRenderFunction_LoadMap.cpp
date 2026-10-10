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

        // FUNCTION: STRONGHOLDCRUSADER 0x00494210
        void LoadMap::MenuModalRenderFunction_LoadMap(int x, int y, int width, int height)
        {
            /*
              added by script: "Load"
             */
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                0x4a, 2, x, y, 0x130, height);
            int y1 = y + 0x22;
            int x2 = x + 0x29f;
            int x1 = x + 0x135;
            int y2 = y + 0x177;
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x21, x2, y + 0x21, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x178, x2, y + 0x178, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y + 0x36, x2, y + 0x36, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x28a, y1, x + 0x28a, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x + 0x28b, y + 0x163, x + 0x29e, y + 0x163, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL(UI::Helpers_Func::SetupPreviewMinimapDataUnk)();
            MACRO_CALL_MEMBER(UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                x + 0x37, y + 0x5f);
            (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
            if (DAT_MenuTextInputState::instance.fileListContext == 1) {
                DAT_MenuTextInputState::instance.savedListSelection1
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset1
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder1
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
            if (DAT_MenuTextInputState::instance.fileListContext == 2) {
                DAT_MenuTextInputState::instance.savedListSelection3
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset3
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder3
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
            if (DAT_MenuTextInputState::instance.fileListContext == 3) {
                DAT_MenuTextInputState::instance.savedListSelection2
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset2
                    = DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder2
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
        }

    }
}
}
