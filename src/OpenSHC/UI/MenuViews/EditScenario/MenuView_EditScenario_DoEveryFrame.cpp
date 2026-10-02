#include "../EditScenario.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
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
        // FUNCTION: STRONGHOLDCRUSADER 0x004B8080
        void EditScenario::MenuView_EditScenario_DoEveryFrame()
        {
            int top;
            int x2;
            int iVar1;
            int iVar2;
            int x1;
            int x2_00;
            int bottom;
            DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8
                = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                DAT_TextureRenderCoreObject::ptr)(0,
                (DAT_WindowAndDirectDraw::instance.resolutionX
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                    / 2,
                (DAT_WindowAndDirectDraw::instance.resolutionY
                    - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                    / 2);
            if (DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_NONE) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                /*
                  added by script: "Scenario Editor"
                 */
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                    199, 2, DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y, 800, 0x3c);
                iVar2 = DAT_MenuHandlerState::instance.y;
                iVar1 = DAT_MenuHandlerState::instance.x;
                top = DAT_MenuHandlerState::instance.y + 0x5a;
                x2_00 = DAT_MenuHandlerState::instance.x + 0x302;
                bottom = DAT_MenuHandlerState::instance.y + 0x1e9;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::dimBox, DAT_PencilRenderCore::ptr)(
                    DAT_MenuHandlerState::instance.x + 0x10e, top, DAT_MenuHandlerState::instance.x + 0x2ee, bottom);
                x2 = iVar1 + 0x303;
                x1 = iVar1 + 0x10d;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, iVar2 + 0x59, x2, iVar2 + 0x59, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, iVar2 + 0x1ea, x2, iVar2 + 0x1ea, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1 + 0x2ee, iVar2 + 0x6e, x2, iVar2 + 0x6e,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x1, top, x1, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    x2, top, x2, bottom, (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1 + 0x2ee, top, iVar1 + 0x2ee, bottom,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                    iVar1 + 0x2ef, iVar2 + 0x1d5, x2_00, iVar2 + 0x1d5,
                    (ushort)((int)(COL_VERY_SOFT_YELLOW::instance.shortValue)));
            }
            return;
        }

    }
}
}
