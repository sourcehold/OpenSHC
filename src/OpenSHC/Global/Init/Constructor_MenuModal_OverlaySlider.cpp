#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/OverlaySlider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_OverlaySlider.hpp"
#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B120
    void Init::Constructor_MenuModal_OverlaySlider()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_OverlaySlider::ptr)(
            UI::Enums::MMT_OVERLAY_SLIDER, 0, 0, 204, 17, 0, 0,
            UI::MenuModals::OverlaySlider_Func::MenuModalRenderFunction_OverlaySlider::get(), Menu_OverlaySlider::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_OverlaySlider::get());
    }

}
}
