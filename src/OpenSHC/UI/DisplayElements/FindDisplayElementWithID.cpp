#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"

#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF630
        DisplayElement* FindDisplayElementWithID(int elementID)
        {
            for (DisplayElement* element = DAT_PointerToDisplayElementStackTop::instance; element != NULL;
                element = element->nextDisplayElement_0x20) {
                if (element->elementID_0x8 == elementID) {
                    return element;
                }
            }
            return NULL;
        }

    }
}
}
