#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/InGameChatDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C460
    void Init::CreateInGameChatDisplayElementUnk()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement, InGameChatDisplayElement::ptr)(
            DE::SHCDE::OST_MULTI_CHAT, 4, 367, 1, UI::DisplayElements_Func::RenderInGameChatDisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)6);
    }

}
}
