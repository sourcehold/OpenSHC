#include "../Rendering.func.hpp"

#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df5560.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace UI {

    // Shows the animated tutorial arrow next to one UI element, unless the current menu or state rules it out.
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC910
    void Rendering::RenderTutorialFloatForUIElement(int uiElementID)
    {
        if (DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU
            || uiElementID == 8 || uiElementID == 10 || uiElementID == 11 || uiElementID == 12) {
            switch (uiElementID) {
            case 2:
                if (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_KEEP1
                    && DAT_00df5560::instance == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(120, 515);
                }
                break;
            case 5:
                if (DAT_00df5558::instance == 0
                    && DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_GRANARY
                    && DAT_00df5560::instance == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(60, 515);
                }
                break;
            case 8:
                // shown until the player has picked rations setting 4
                if (DAT_00df5558::instance == 0
                    && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .rationsSetting
                        != 4
                    && DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(395, 570);
                }
                break;
            case 10:
                // shown until the player has picked taxes setting 7
                if (DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSetting
                        != 7
                    && DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(442, 535);
                }
                break;
            case 11:
                if (DAT_00df5558::instance == 1 && DAT_00df5560::instance == 0) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(735, 528);
                }
                break;
            case 12:
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(305, 480);
                }
                break;
            case 16:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(120, 550);
                break;
            case 17:
                if (DAT_00df5560::instance == 0) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_QUARRY) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(68, 582);
                    } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(120, 518);
                    }
                }
                break;
            case 21:
                if (DAT_00df5560::instance == 0) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_WATERPOT) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(105, 582);
                    } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(77, 515);
                    }
                }
                break;
            case 23:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(727, 570);
                break;
            case 24:
                if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_HOPFARM) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(140, 582);
                } else if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(40, 515);
                }
            }
        }
    }

}
}
