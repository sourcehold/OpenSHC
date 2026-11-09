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
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(74, 2, x, y, 304, height);
            int rightColumnX = x + 670;
            int y1 = y + 34;
            int y2 = y + 375;
            int x2 = rightColumnX + 1;
            int x1 = x + 309;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1 - 1, x2, y1 - 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y2 + 1, x2, y2 + 1, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1 + 20, x2, y1 + 20, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x1, y1, x1, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                x2, y1, x2, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 20, y1, rightColumnX - 20, y2, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                rightColumnX - 19, y2 - 20, rightColumnX, y2 - 20, (ushort)(COL_VERY_SOFT_YELLOW::instance.shortValue));
            MACRO_CALL(OpenSHC::UI::Helpers_Func::SetupPreviewMinimapDataUnk)();
            MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                x + 55, y + 95);
            (DAT_MenuHandlerState::instance.currentMenu)->zero = 0;
            if (DAT_MenuTextInputState::instance.fileListContext == 1) {
                DAT_MenuTextInputState::instance.savedListSelection1
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset1
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder1
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
            if (DAT_MenuTextInputState::instance.fileListContext == 2) {
                DAT_MenuTextInputState::instance.savedListSelection3
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset3
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder3
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
            if (DAT_MenuTextInputState::instance.fileListContext == 3) {
                DAT_MenuTextInputState::instance.savedListSelection2
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex;
                DAT_MenuTextInputState::instance.savedListOffset2
                    = DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset;
                DAT_MenuTextInputState::instance.savedListSortOrder2
                    = DAT_MenuTextInputState::instance.fileListSortOrder;
            }
        }

    }
}
}
