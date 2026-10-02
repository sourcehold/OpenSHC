#include "../../Global.func.hpp"
#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_Unknown27CampaignUnk.hpp"

namespace OpenSHC {
namespace Global {

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC80
    void Init::Constructor_Menu_Unknown27CampaignUnk()
    {
        MACRO_CALL_MEMBER(OpenSHC::UI::Menu_Func::Constructor_Menu, Menu_Unknown27CampaignUnk::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Unknown27CampaignUnk);
    }

}
}
