#include "../Rendering.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00ed2784.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ed26d0.hpp"
#include "OpenSHC/Globals/DAT_ArrayOfStoredMenuStrings.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/INT_00eb0e28.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DB0D0
    void Rendering::DisplayFullScreenTextPage(int stringIndex)
    {
        RenderTargetInt const previousPencilTarget = DAT_PencilRenderCore::instance.surfaceTarget;
        RenderTargetInt const previousTextTarget = DAT_TextManagerObject::instance.textSurfaceTarget;
        DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        DAT_PencilRenderCore::instance.surfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox, DAT_PencilRenderCore::ptr)(
            0, 0, 600, 800, COL_BLACK::instance.shortValue);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
            DAT_ArrayOfStoredMenuStrings::instance[stringIndex], 15, 205, 525, OpenSHC::Rendering::Colors::COL_CCFAFF,
            17, 0);
        DAT_TextManagerObject::instance.textSurfaceTarget = previousTextTarget;
        DAT_PencilRenderCore::instance.surfaceTarget = previousPencilTarget;
        INT_00eb0e28::instance = DAT_TextManagerObject::instance.field_0x4 + 215;
        if (INT_00eb0e28::instance < 220) {
            INT_00eb0e28::instance = 220;
        }
        DAT_00ed2784::instance = 0;
        DAT_ARRAY_00ed26d0::instance[0].x = timeGetTime();
    }

}
}
