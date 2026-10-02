#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering.func.hpp"
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

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      Given a UI element ID (param_1), renders the animated tutorial float overlay at a hardcoded   screen position
      matching that element (e.g. granary, taxes slider, rations, quarry, hop farm   etc). Guards against showing while
      in incorrect menu states or when certain conditions aren't   met. Delegates to renderAnimatedTutorialFloatOverlay
      with per-element x/y positions.      renamed by: Claude Sonnet 4.6
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004BC910
    void Rendering::RenderTutorialFloatForUIElement(int param_1)
    {
        if ((((DAT_GameCore::instance.currentMenuViewType != OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU)
                 || (param_1 == 8))
                || (param_1 == 10))
            || ((param_1 == 0xb || (param_1 == 0xc)))) {
            switch (param_1) {
            case 2:
                if ((DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_KEEP1)
                    && (DAT_00df5560::instance == 0)) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x78, 0x203);
                }
                break;
            case 5:
                if (((DAT_00df5558::instance == 0)
                        && (DAT_TileMapState::instance.currentMapperCommand != OpenSHC::Commands::M_MAPPER_GRANARY))
                    && (DAT_00df5560::instance == 0)) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x3c, 0x203);
                }
                break;
            case 8:
                if (((DAT_00df5558::instance == 0)
                        && (DAT_GameState::instance
                                .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .rationsSetting
                            != 4))
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_GRANARY_OR_MPMENU_TCPIP)) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x18b, 0x23a);
                }
                break;
            case 10:
                if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .taxesSetting
                        != 7)
                    && (DAT_GameCore::instance.activeMenuTab.tabType
                        == OpenSHC::UI::Enums::BASMTT_KEEP_OR_MPMENU_IPX)) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x1ba, 0x217);
                }
                break;
            case 0xb:
                if ((DAT_00df5558::instance == 1) && (DAT_00df5560::instance == 0)) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x2df, 0x210);
                }
                break;
            case 0xc:
                if (DAT_GameCore::instance.activeMenuTab.tabType == OpenSHC::UI::Enums::BASMTT_STATUS_OVERVIEW) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x131, 0x1e0);
                }
                break;
            case 0x10:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x78, 0x226);
                return;
            case 0x11:
                if (DAT_00df5560::instance == 0) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_QUARRY) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x44, 0x246);
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x78, 0x206);
                    }
                }
                break;
            case 0x15:
                if (DAT_00df5560::instance == 0) {
                    if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_WATERPOT) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x69, 0x246);
                    }
                    if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                        MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x4d, 0x203);
                    }
                }
                break;
            case 0x17:
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x2d7, 0x23a);
                return;
            case 0x18:
                if (DAT_GameCore::instance.activeMenuTab.tabType != OpenSHC::UI::Enums::BASMTT_HOPFARM) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x8c, 0x246);
                }
                if (DAT_TileMapState::instance.currentMapperCommand == OpenSHC::Commands::M_MAPPER_NULL) {
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderAnimatedTutorialFloatOverlay)(0x28, 0x203);
                }
            }
        }
    }

}
}
