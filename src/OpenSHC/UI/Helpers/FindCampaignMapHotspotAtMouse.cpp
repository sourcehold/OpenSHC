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
        for (int element = 0; element < 24; ++element) {
            if (DAT_ARRAY_00ec0348::instance[element].type != 3 && DAT_ARRAY_00ec0348::instance[element].type != 1) {
                continue;
            }
            int const menuX = mouseX - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
            if (menuX < DAT_ARRAY_00ec0348::instance[element].x
                || menuX >= DAT_ARRAY_00ec0348::instance[element].width + DAT_ARRAY_00ec0348::instance[element].x) {
                continue;
            }
            int const menuY = mouseY - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
            if (menuY >= DAT_ARRAY_00ec0348::instance[element].y
                && menuY < DAT_ARRAY_00ec0348::instance[element].height + DAT_ARRAY_00ec0348::instance[element].y) {
                return DAT_ARRAY_00ec0348::instance[element].xSpace;
            }
        }
        return -1;
    }

}
}
