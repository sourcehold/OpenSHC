#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E64D0
    void ViewportRenderState::renderDebugDataMousePointing(int x, int y, int width, int height)
    {
        char text[200];
        uint securityCookie = MSVC_SecurityCookie::instance ^ (uint)text;

        int textX = x + 2;

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Mouse Atom Ref: %d", this->viewportState.mouseAtomRefFloorTile);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Mouse: x%d, y%d, off%d", DAT_ViewportRenderState::instance.viewportState.mouseX,
            DAT_ViewportRenderState::instance.viewportState.mouseY,
            DAT_ViewportRenderState::instance.viewportState.mouseTile);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 0x10, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Tile centre: x%d,y%d", DAT_ViewportRenderState::instance.viewportState.tileCenterX,
            DAT_ViewportRenderState::instance.viewportState.tileCenterY);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 0x20, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Chimp: %d  Struct: %d Fly: %d", this->viewportState.mouseRayUnitID,
            this->viewportState.mouseRayBuildingID, this->viewportState.mouseRayEntityID);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 0x40, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Logic Layer: %x  %x", DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseAtomRefFloorTile],
            DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 0x50, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Logic2 Layer: %x  %x",
            (char)DAT_TileMapState::instance.Logic2Layer[this->viewportState.mouseAtomRefFloorTile],
            (char)DAT_TileMapState::instance.Logic2Layer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX + 0x14, y + 0x50, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, TRUE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, "Damage Layer: %d  %d",
            (char)DAT_TileMapState::instance.DamageLayer[this->viewportState.mouseAtomRefFloorTile],
            (char)DAT_TileMapState::instance.DamageLayer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 0x60, OpenSHC::Text::TTA_LEFT, 0xffffff, 0x12, FALSE, 0);
    }

}
}
