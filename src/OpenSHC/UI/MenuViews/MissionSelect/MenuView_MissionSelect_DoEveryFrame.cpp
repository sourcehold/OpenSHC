#include "../MissionSelect.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::UI::Enums::MenuModalType;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004268C0
        void MissionSelect::MenuView_MissionSelect_DoEveryFrame()
        {
            int y1;
            int x2;
            int iVar1;
            int y2;
            int x1;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            iVar1 = DAT_MenuHandlerState::instance.y;
            if ((DAT_MenuTextInputState::instance.currentModalDialog == OpenSHC::UI::Enums::MMT_NO_MENU)
                && (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE)) {
                y1 = DAT_MenuHandlerState::instance.y + 0xbe;
                x2 = DAT_MenuHandlerState::instance.x + 0x23a;
                x1 = DAT_MenuHandlerState::instance.x + 0xe5;
                y2 = DAT_MenuHandlerState::instance.y + 0x121;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, DAT_MenuHandlerState::instance.y + 0xbd, x2, DAT_MenuHandlerState::instance.y + 0xbd,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, iVar1 + 0x122, x2, iVar1 + 0x122, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, y1, x1, y2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2, y1, x2, y2, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                /*
                  added by script: "Mission"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(5,
                    0xf, DAT_MenuHandlerState::instance.x + 0xb8, DAT_MenuHandlerState::instance.y + 100, 0x1b0, 0x32);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            }
            return;
        }

    }
}
}
