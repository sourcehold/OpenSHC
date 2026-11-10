#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_TriggerEventSlider.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059B110
    void Init::Constructor_Menu_TriggerEventSlider()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_TriggerEventSlider::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_TriggerEventSlider);
    }

}
}
