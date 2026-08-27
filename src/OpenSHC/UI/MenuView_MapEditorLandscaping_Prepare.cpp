#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {

using OpenSHC::UI::Enums::DisplayElementID;

// FUNCTION: STRONGHOLDCRUSADER 0x00430CC0
void UI::MenuView_MapEditorLandscaping_Prepare()
{
    DAT_WindowAndDirectDraw::instance.field37_0xdc = 1;
    MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_PEOPLE_LEFT_TO_PLACE, 0);
    MACRO_CALL(OpenSHC::UI::Helpers_Func::CheckDisplayElementByIDAndSetForUnlimitedDisplay)(
        OpenSHC::UI::Enums::DEID_PLAYER_INFO_ON_HOVER, 1);
}

}
