#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::DisplayElement;
    using OpenSHC::UI::Enums::DisplayElementID;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF6B0
    void Rendering::TogglePlayerPingDisplayElementUnk(DisplayElementID displayElementID, uint toggleValue)
    {
        DisplayElement* _displayElement = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(displayElementID);
        if (_displayElement != NULL) {
            _displayElement->displayDuration_0x14 = -1;
            _displayElement->elementStateUnk_0xc = _displayElement->elementStateUnk_0xc != 0 ? 0 : toggleValue;
        }
    }

}
}
