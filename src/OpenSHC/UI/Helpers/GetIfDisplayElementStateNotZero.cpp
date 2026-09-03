#include "OpenSHC/UI.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::UI::DisplayElement;
    using OpenSHC::UI::Enums::DisplayElementID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF6E0
    BOOLEnum Helpers::GetIfDisplayElementStateNotZero(DisplayElementID displayElementID)
    {
        DisplayElement* _displayElementPtr = MACRO_CALL(OpenSHC::UI_Func::FindDisplayElementWithID)(displayElementID);
        if (_displayElementPtr != NULL) {
            return _displayElementPtr->elementStateUnk_0xc != 0;
        }
        return FALSE;
    }

}
}
