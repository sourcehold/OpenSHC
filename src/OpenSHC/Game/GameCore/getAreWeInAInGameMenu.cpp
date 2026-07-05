#include "..\GameCore.func.hpp"

namespace OpenSHC {
namespace Game {

    // FUNCTION: STRONGHOLDCRUSADER 0x0046BB60
    BOOLEnum GameCore::getAreWeInAInGameMenu()
    {
        return this->currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING
            || this->currentMenuViewType == UI::Enums::MVT_BUILD_MENU
            || this->currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU;
    }

}
}
