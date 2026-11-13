#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/ConnectAndPathLinkageInfoTextDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C440
    void Init::CreateConnectAndPathLinkageInfoTextDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            ConnectAndPathLinkageInfoTextDisplayElement::ptr)((DE::SHCDE::eOnScreenText)2, 630, 9, 0,
            UI::DisplayElements_Func::RenderConnectAndPathLinkageInfoTextDisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)9);
    }

}
}
