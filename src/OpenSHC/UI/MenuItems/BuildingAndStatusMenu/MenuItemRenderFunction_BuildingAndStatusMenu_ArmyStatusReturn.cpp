#include "../BuildingAndStatusMenu.func.hpp"

#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/UI/DisplayElements.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/Map/MapType2.hpp"
#include "OpenSHC/UI/Enums/DisplayElementID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode2;
        using OpenSHC::Map::MapType2;
        using OpenSHC::UI::Enums::DisplayElementID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
         */
        /*
          WARNING: Enum "DPERRInt": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x0043FCB0
        void BuildingAndStatusMenu::MenuItemRenderFunction_BuildingAndStatusMenu_ArmyStatusReturn(int param_1, ...)
        {
            int iVar1;
            BOOLEnum BVar2;
            if (((((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk)
                      || (DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_CRUSADER_TUTORIAL))
                     && (DAT_GameSynchronyState::instance.currentPlayerSlotID == 2))
                    || ((((DAT_GameSynchronyState::instance.currentPlayerSlotID == 1
                              && (iVar1 = MACRO_CALL_MEMBER(
                                      OpenSHC::Game::GameStateStructures_Func::singlePlayerHasKeepAndGranaryCheck,
                                      DAT_GameState::ptr)(),
                                  iVar1 == 0))
                             && (iVar1 = MACRO_CALL_MEMBER(OpenSHC::Map::Units::UnitsState_Func::getArmySize,
                                     DAT_UnitsState::ptr)(DAT_GameSynchronyState::instance.currentPlayerSlotID),
                                 iVar1 != 0))
                        || ((DAT_GameCore::instance.gameMode_2 == OpenSHC::Game::GM_BUILDERUnk
                            && (DAT_MapPropertiesState::instance.SEC_U3_MapType2_1 == OpenSHC::Map::MT_SIEGE))))))
                && (BVar2 = MACRO_CALL(OpenSHC::UI::DisplayElements_Func::GetIfDisplayElementStateNotZero)(
                        OpenSHC::UI::Enums::DEID_KEEP_AND_GRANERY_PLACEMENT_INFO),
                    BVar2 == FALSE)) {
                DAT_ButtonUnknownZero::instance = 1;
            }
            DAT_ButtonUnknownZero::instance = 0;
            MACRO_CALL(OpenSHC::UI::MenuItems::General_Func::
                    MenuItemRenderFunction_General_RenderCurrentButtonWithPossibleAlphaTexOnScreenMenuSurface)();
        }

    }
}
}
