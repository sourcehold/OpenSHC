#include "OpenSHC/Global/Init.func.hpp"
#include "OpenSHC/UI/DisplayElement.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/DE/SHCDE/eOnScreenText.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"

#include "OpenSHC/Globals/InGameStartingGoodsCounterDisplayElement.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059C420
    void Init::CreateInGameStartingGoodsCounterDisplayElement()
    {
        MACRO_CALL_MEMBER(UI::DisplayElement_Func::Constructor_DisplayElement,
            InGameStartingGoodsCounterDisplayElement::ptr)(DE::SHCDE::OST_STARTING_GOODS, 4, 4, 1,
            UI::DisplayElements_Func::RenderStartingGoodDisplayElement::get(),
            (UI::Enums::DisplayElementPositionModifier)5);
    }

}
}
