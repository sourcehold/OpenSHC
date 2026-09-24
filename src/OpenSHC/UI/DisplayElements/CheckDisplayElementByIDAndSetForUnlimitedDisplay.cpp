#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/DisplayElement.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/BOOL_RelatedToInitialGranaryAndKeepPlacement.hpp"

namespace OpenSHC {
namespace UI {
    namespace DisplayElements {

        using OpenSHC::UI::DisplayElement;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AF650
        void CheckDisplayElementByIDAndSetForUnlimitedDisplay(DisplayElementID displayElementID, dword elementState)
        {
            DisplayElement* _displayElementPtr
                = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::FindDisplayElementWithID)(displayElementID);
            if (_displayElementPtr != NULL) {
                if (_displayElementPtr->elementStateUnk_0xc != elementState) {
                    BOOL_RelatedToInitialGranaryAndKeepPlacement::instance = FALSE;
                }
                _displayElementPtr->elementStateUnk_0xc = elementState;
                _displayElementPtr->displayDuration_0x14 = -1;
            }
        }

    }
}
}
