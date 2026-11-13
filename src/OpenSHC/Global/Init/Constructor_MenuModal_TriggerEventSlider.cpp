#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/Meta.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/UI/MenuModal.func.hpp"
#include "OpenSHC/UI/MenuModals/TriggerEventSlider.func.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/MenuModal_TriggerEventSlider.hpp"
#include "OpenSHC/Globals/Menu_TriggerEventSlider.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059BFE0
    void Init::Constructor_MenuModal_TriggerEventSlider()
    {
        MACRO_CALL_MEMBER(UI::MenuModal_Func::Constructor_MenuModal, MenuModal_TriggerEventSlider::ptr)(
            UI::Enums::MMT_TRIGGER_EVENT_SLIDER, -1, -1, 408, 168, 512, 6,
            UI::MenuModals::TriggerEventSlider_Func::MenuModalRenderFunction_TriggerEventSlider::get(),
            Menu_TriggerEventSlider::ptr);
        MACRO_CALL(OS_Func::_atexit)(Meta_Func::Destructor_MenuModal_TriggerEventSlider::get());
    }

}
}
