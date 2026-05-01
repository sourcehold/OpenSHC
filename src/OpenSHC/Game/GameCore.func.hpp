/**
  path: 'OpenSHC/Game/GameCore.func.hpp'
*/

#include "OpenSHC/Game/GameCore.hpp"
#include "OpenSHC/UI/Enums/MenuViewTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Game {
    namespace GameCore_Func {

        using OpenSHC::UI::Enums::MenuViewTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B2F0, &GameCore::setViewOnExitUnk)
        setViewOnExitUnk;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B300, &GameCore::setTabToSwitchTo)
        setTabToSwitchTo;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B320, &GameCore::meth_0x46b320)
        meth_0x46b320;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(MenuViewTypeInt, int), false, Address::SHC_3BB0A8C1_0x0046B340,
            &GameCore::switchToMenuView)
        switchToMenuView;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B980, &GameCore::processMenuViewSwitch)
        processMenuViewSwitch;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB20, &GameCore::viewportAndScrollingRelated)
        viewportAndScrollingRelated;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB60, &GameCore::getAreWeInAInGameMenu)
        getAreWeInAInGameMenu;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB80, &GameCore::isInBuildingTab)
        isInBuildingTab;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BBD0,
            &GameCore::removeJesterAndLadyUnitsInCertainMissions)
        removeJesterAndLadyUnitsInCertainMissions;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BC90, &GameCore::FUN_0046bc90)
        FUN_0046bc90;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BD20, &GameCore::isGameHaltingMenuOpen)
        isGameHaltingMenuOpen;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(int), false, Address::SHC_3BB0A8C1_0x0046BD50, &GameCore::setStartDateUnk)
        setStartDateUnk;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x004718F0, &GameCore::incrementMissionProgress)
        incrementMissionProgress;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x004719E0,
            &GameCore::switchToScenarioDescriptionMenuView)
        switchToScenarioDescriptionMenuView;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x00471A00, &GameCore::meth_0x471a00)
        meth_0x471a00;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x00471AA0, &GameCore::hideOrUnhideUI)
        hideOrUnhideUI;

    } // namespace GameCore_Func
} // namespace Game
} // namespace OpenSHC
