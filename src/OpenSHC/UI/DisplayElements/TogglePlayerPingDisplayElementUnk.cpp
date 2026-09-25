#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF6B0
        void TogglePlayerPingDisplayElementUnk(DisplayElementID displayElementID, uint toggleValue)
        {
            DisplayElement* const displayElement
                = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::FindDisplayElementWithID)(displayElementID);
            if (displayElement != NULL) {
                displayElement->displayDuration_0x14 = -1;
                displayElement->elementStateUnk_0xc = displayElement->elementStateUnk_0xc != 0 ? 0 : toggleValue;
            }
        }

    }
}
}
