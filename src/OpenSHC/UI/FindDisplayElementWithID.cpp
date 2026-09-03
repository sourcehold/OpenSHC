#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"

#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"

namespace OpenSHC {

using OpenSHC::UI::DisplayElement;

// FUNCTION: STRONGHOLDCRUSADER 0x004AF630
DisplayElement* UI::FindDisplayElementWithID(int elementID)
{
    DisplayElement* _pCurrent = DAT_PointerToDisplayElementStackTop::instance;
    while (_pCurrent != NULL) {
        if (_pCurrent->elementID_0x8 == elementID)
            return _pCurrent;
        _pCurrent = _pCurrent->nextDisplayElement_0x20;
    }
    return NULL;
}

}
