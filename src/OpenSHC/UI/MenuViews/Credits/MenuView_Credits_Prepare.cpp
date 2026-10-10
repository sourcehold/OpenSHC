#include "../Credits.func.hpp"

#include "OpenSHC/Text/TextEditorState.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00b95954.hpp"
#include "OpenSHC/Globals/DAT_00b95b3c.hpp"
#include "OpenSHC/Globals/DAT_00b95b70.hpp"
#include "OpenSHC/Globals/DAT_00b9610c.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00b960d0.hpp"
#include "OpenSHC/Globals/INT_00b960d4.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        // FUNCTION: STRONGHOLDCRUSADER 0x004261E0
        void Credits::MenuView_Credits_Prepare()
        {
            int iVar1;
            char* tgxFileName;
            DAT_TextureRenderCoreObject::instance.totalLoadedGfx = 0;
            if (!DAT_00b95954::instance) {
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "credits_1.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "credits_2.tgx");
                MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                    "credits_3.tgx");
                tgxFileName = "credits_4.tgx";
            } else {
                tgxFileName = "end_credit.tgx";
            }
            MACRO_CALL_MEMBER(UI::Rendering::TextureRenderCore_Func::loadGfxFile, DAT_TextureRenderCoreObject::ptr)(
                tgxFileName);
            iVar1 = MACRO_CALL_MEMBER(Text::TextEditorState_Func::findOrAddHelpSectionName, DAT_TextEditorState::ptr)(
                "credits.hlp");
            MACRO_CALL_MEMBER(Text::TextEditorState_Func::openCreditsScrollDialog, DAT_TextEditorState::ptr)(iVar1);
            DAT_TextEditorState::instance.helpContentScrollOffsetY = 0xfffffda8;
            DAT_00b95b3c::instance = 0;
            INT_00b960d0::instance = timeGetTime();
            DAT_00b95b70::instance = 0;
            DAT_00b9610c::instance = 1;
            MACRO_CALL(UI::Helpers_Func::LoadTGX_shc_back)();
            INT_00b960d4::instance = timeGetTime();
            MACRO_CALL_MEMBER(UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(0, 0,
                DAT_WindowAndDirectDraw::instance.resolutionX, DAT_WindowAndDirectDraw::instance.resolutionY,
                (ushort)(COL_BLACK::instance.shortValue));
        }

    }
}
}
