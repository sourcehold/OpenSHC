#include "../TextEditorState.func.hpp"

#include "OpenSHC/UI/Rendering/WindowAndDirectDraw.func.hpp"

#include "OpenSHC/Globals/DAT_TextEditorState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace Text {

    // FUNCTION: STRONGHOLDCRUSADER 0x0045D690
    void TextEditorState::bltTextToScreenIfNeedBe()
    {
        if (!DAT_TextEditorState::instance.unknown_0x23960) {
            return;
        }
        if (this->savedMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING
            || this->savedMenuViewType == UI::Enums::MVT_BUILD_MENU
            || this->savedMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
            MACRO_CALL_MEMBER(UI::Rendering::WindowAndDirectDraw_Func::bltMapGameSurfaceToScreenMenuSurfaceComplete,
                DAT_WindowAndDirectDraw::ptr)();
        }
        DAT_TextEditorState::instance.unknown_0x23960 = FALSE;
    }

}
}
