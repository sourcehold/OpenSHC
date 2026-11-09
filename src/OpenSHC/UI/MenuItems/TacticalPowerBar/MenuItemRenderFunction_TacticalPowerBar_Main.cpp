#include "../TacticalPowerBar.func.hpp"

#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TacticalPowersHelpTextDisplayBool.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004D9EC0
        void TacticalPowerBar::MenuItemRenderFunction_TacticalPowerBar_Main(int slot, ...)
        {
            int const buttonY = DAT_ButtonY::instance;
            int const buttonX = DAT_ButtonX::instance;
            int const level
                = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                      .tacticalPowersBarLevel;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                buttonX + 20, buttonY + 10, buttonX + 30, buttonY + 10, COL_VERY_SOFT_YELLOW::instance.shortValue);
            // the bar's ten slots show the powers' icons in this order
            int icon = slot;
            switch (slot) {
            case 0:
                icon = 5;
                break;
            case 1:
                icon = 6;
                break;
            case 2:
                icon = 1;
                break;
            case 3:
                icon = 3;
                break;
            case 5:
                icon = 7;
                break;
            case 6:
                icon = 2;
                break;
            case 7:
                icon = 4;
                break;
            case 4:
            case 8:
            case 9:
                icon = 0;
                break;
            }
            if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY
                || DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                || DAT_GameState::instance.mapAndTime.skirmishNoRushTicks == 0) {
                // each slot fills over 636 points of the bar
                if (level >= (slot + 1) * 636) {
                    if (!DAT_GameCore::instance.tacticalPowersDisplayFlag) {
                        DAT_TacticalPowersHelpTextDisplayBool::instance = true;
                        DAT_GameCore::instance.tacticalPowersDisplayFlag = 1;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, icon + 289,
                        DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonBlendStrength::instance);
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 297,
                            DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonBlendStrength::instance);
                    }
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, icon + 298,
                    DAT_ButtonX::instance, DAT_ButtonY::instance, DAT_ButtonBlendStrength::instance);
            } else {
                // during the no-rush time of a multiplayer game the icons are dimmed further
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, icon + 298,
                    DAT_ButtonX::instance, DAT_ButtonY::instance, 32 - (32 - DAT_ButtonBlendStrength::instance) / 2);
            }
        }

    }
}
}
