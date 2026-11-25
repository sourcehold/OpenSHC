#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_Unknown26CampaignRelatedUnk.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059AC70
    void Init::Constructor_Menu_Unknown26CampaignRelatedUnk()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_Unknown26CampaignRelatedUnk::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_Unknown26CampaignRelatedUnk);
    }

}
}
