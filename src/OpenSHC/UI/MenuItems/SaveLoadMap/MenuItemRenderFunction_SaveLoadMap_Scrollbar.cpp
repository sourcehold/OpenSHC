#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {
        namespace SaveLoadMap {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            // FUNCTION: STRONGHOLDCRUSADER 0x00492C60
            void MenuItemRenderFunction_SaveLoadMap_Scrollbar(
                int param_1, int thumbYPos, int param_3, int thumbHeight, BOOLEnum isDragged)
            {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawScrollbar,
                    DAT_PencilRenderCore::ptr)(DAT_ButtonX::instance, (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonH::instance)), thumbYPos, isDragged, thumbHeight, 0);
            }

        }
    }
}
}
