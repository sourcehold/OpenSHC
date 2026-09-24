#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF680
        void ActivateGameSpeedAndResourceLackDisplayElementUnk(
            DisplayElementID elementId, dword elementState, int displayDuration)
        {
            DisplayElement* const displayElement
                = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::FindDisplayElementWithID)(elementId);
            if (displayElement != NULL) {
                displayElement->elementStateUnk_0xc = elementState;
                displayElement->displayDuration_0x14 = displayDuration;
                displayElement->activationTime_0x10 = timeGetTime();
            }
        }

    }
}
}
