#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Commands::GameCommandType;
        using OpenSHC::Game::Resources::ResourceType;

        // FUNCTION: STRONGHOLDCRUSADER 0x00465200
        void BuildingAndStatusMenu::MenuItemActionHandler_BuildingAndStatusMenu_WorkshopWeaponSelection(
            ResourceType weapon, ...)
        {
            if (weapon == OpenSHC::Game::Resources::RT_CROSSBOW) {
                if (DAT_GameCore::instance.xbowProducible_logic == 0) {
                    return;
                }
            } else if (weapon == OpenSHC::Game::Resources::RT_BOW) {
                if (DAT_GameCore::instance.bowProducible_logic == 0) {
                    return;
                }
            } else if (weapon == OpenSHC::Game::Resources::RT_PIKE) {
                if (DAT_GameCore::instance.pikeProducible_logic == 0) {
                    return;
                }
            } else if (weapon == OpenSHC::Game::Resources::RT_SPEAR) {
                if (DAT_GameCore::instance.spearProducible_logic == 0) {
                    return;
                }
            } else if (weapon == OpenSHC::Game::Resources::RT_SWORD) {
                if (DAT_GameCore::instance.swordProducible_logic == 0) {
                    return;
                }
            } else if (weapon == OpenSHC::Game::Resources::RT_MACE) {
                if (DAT_GameCore::instance.maceProducible_logic == 0) {
                    return;
                }
            }
            DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                = DAT_BuildingsState::instance.menuSelectedBuildingID;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam1 = weapon;
            DAT_GameSynchronyState::instance.DAT_GameCommandParam2
                = DAT_BuildingsState::instance.buildings[DAT_BuildingsState::instance.menuSelectedBuildingID].uid;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand, DAT_GameSynchronyState::ptr)(
                ((GameCommandType)0x21));
            DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID].weaponRelated
                = weapon;
        }

    }
}
}
