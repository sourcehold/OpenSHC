#include "../MenuModalComposition.func.hpp"

#include "OpenSHC/Globals/MenuModal_UnusedWinCondition.hpp"
#include "OpenSHC/Globals/Menu_OverlaySlider.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AA930
    void MenuModalComposition::setModalSliderParameters(int textGroup, int textIndex, dword itemCount,
        dword sliderValue, int* destination, NoArgCallback* sliderCallbackFunction)
    {
        this->textGroup = textGroup;
        this->textIndex = textIndex;
        this->mbr_0x64 = itemCount;
        this->sliderValue = sliderValue;
        this->destination = destination;
        Menu_OverlaySlider::instance.one = 1;
        this->sliderCallbackFunction = sliderCallbackFunction;
        MenuModal_UnusedWinCondition::instance.height = itemCount * 25;
    }

}
}
