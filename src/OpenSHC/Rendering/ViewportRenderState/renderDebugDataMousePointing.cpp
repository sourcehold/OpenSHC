#include "../ViewportRenderState.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E64D0
    void ViewportRenderState::renderDebugDataMousePointing(int x, int y, int width, int height)
    {
        char text[200];

        int textX = x + 2;

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Mouse_Atom_Ref___d_005ab8a4, this->viewportState.mouseAtomRefFloorTile);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Mouse__x_d__y_d__off_d_005ab88c, DAT_ViewportRenderState::instance.viewportState.mouseX,
            DAT_ViewportRenderState::instance.viewportState.mouseY,
            DAT_ViewportRenderState::instance.viewportState.mouseTile);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 16, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Tile_centre__x_d_y_d_005ab874, DAT_ViewportRenderState::instance.viewportState.tileCenterX,
            DAT_ViewportRenderState::instance.viewportState.tileCenterY);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 32, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Chimp___d_Struct___d_Fly___d_005ab854, this->viewportState.mouseRayUnitID,
            this->viewportState.mouseRayBuildingID, this->viewportState.mouseRayEntityID);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 64, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Logic_Layer___x__x_005ab840,
            DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseAtomRefFloorTile],
            DAT_TileMapState::instance.LogicLayer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 80, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Logic2_Layer___x__x_005ab828,
            (char)DAT_TileMapState::instance.Logic2Layer[this->viewportState.mouseAtomRefFloorTile],
            (char)DAT_TileMapState::instance.Logic2Layer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX + 20, y + 80, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, TRUE, 0);

        MACRO_CALL(OpenSHC::OS_Func::_sprintf)
        (text, s_Damage_Layer___d__d_005ab810,
            (char)DAT_TileMapState::instance.DamageLayer[this->viewportState.mouseAtomRefFloorTile],
            (char)DAT_TileMapState::instance.DamageLayer[this->viewportState.mouseTile]);
        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)
        (text, textX, y + 96, OpenSHC::Text::TTA_LEFT, Colors::COL_FFFFFF, 18, FALSE, 0);
    }

}
}
