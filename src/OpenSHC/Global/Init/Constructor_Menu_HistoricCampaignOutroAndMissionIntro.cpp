#include "../Init.func.hpp"

#include "OpenSHC/UI/Menu.func.hpp"

#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/Menu_HistoricCampaignOutroAndMissionIntro.hpp"

namespace OpenSHC {
namespace Global {

    // FUNCTION: STRONGHOLDCRUSADER 0x0059ACB0
    void Init::Constructor_Menu_HistoricCampaignOutroAndMissionIntro()
    {
        MACRO_CALL_MEMBER(UI::Menu_Func::Constructor_Menu, Menu_HistoricCampaignOutroAndMissionIntro::ptr)(
            DAT_RenderingDefinedData::instance.MenuItems_HistoricCampaignOutroAndMissionIntro);
    }

}
}
