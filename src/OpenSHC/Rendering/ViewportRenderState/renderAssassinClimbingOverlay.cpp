#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Rendering {

    // FUNCTION: STRONGHOLDCRUSADER 0x004E2630
    void ViewportRenderState::renderAssassinClimbingOverlay(int unitID)
    {
        short facingDirection = DAT_UnitsState::instance.units[unitID].facingDirectionMapOrientationCorrected;
        short assassinHeightDifference = DAT_UnitsState::instance.units[unitID].assassinHeightDifference;
        if (assassinHeightDifference <= 0) {
            return;
        }
        int imageID = DAT_UnitsState::instance.units[unitID].imageIDUnk;
        if (imageID <= 0) {
            return;
        }

        if (DAT_UnitsState::instance.units[unitID].assassinClimbingUpUnk_OR_previousFacingDirection == 0) {
            if (facingDirection != 4 && facingDirection != 2 && facingDirection != 3 && facingDirection != 1
                && facingDirection != 5) {
                return;
            }
        } else {
            if (facingDirection != 0 && facingDirection != 6 && facingDirection != 7 && facingDirection != 1
                && facingDirection != 5) {
                return;
            }
        }

        MACRO_CALL_MEMBER(
            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending, DAT_TextureRenderCoreObject::ptr)
        ((OpenSHC::IO::Graphics::GmID)DAT_UnitsState::instance.units[unitID].gmIDUnk, imageID,
            DAT_UnitsState::instance.units[unitID].field308_0x41c,
            DAT_UnitsState::instance.units[unitID].field309_0x420 - assassinHeightDifference,
            (short)DAT_UnitsState::instance.units[unitID].field307_0x41a);
    }

}
}
