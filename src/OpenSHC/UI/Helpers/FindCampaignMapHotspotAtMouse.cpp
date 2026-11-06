#include "../Helpers.func.hpp"

#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004DC140
    int Helpers::FindCampaignMapHotspotAtMouse()
    {
        int const mouseY = DAT_MouseState::instance.screenSpaceY;
        int const mouseX = DAT_MouseState::instance.screenSpaceX;
        for (int i = 0; i < 24; ++i) {
            // Only image (1) and hover image (3) elements can be hit.
            if (DAT_ARRAY_00ec0348::instance[i].type != 3 && DAT_ARRAY_00ec0348::instance[i].type != 1) {
                continue;
            }
            int const menuX = mouseX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            if (menuX < DAT_ARRAY_00ec0348::instance[i].x
                || menuX >= DAT_ARRAY_00ec0348::instance[i].width + DAT_ARRAY_00ec0348::instance[i].x) {
                continue;
            }
            int const menuY = mouseY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            if (menuY >= DAT_ARRAY_00ec0348::instance[i].y
                && menuY < DAT_ARRAY_00ec0348::instance[i].height + DAT_ARRAY_00ec0348::instance[i].y) {
                return DAT_ARRAY_00ec0348::instance[i].xSpace;
            }
        }
        return -1;
    }

}
}
