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
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B2F0, &GameCore::setMenuViewOnExit)
        setMenuViewOnExit;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B300, &GameCore::setTabToSwitchTo)
        setTabToSwitchTo;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B320, &GameCore::toggleSiegeTentBuildTab)
        toggleSiegeTentBuildTab;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(MenuViewTypeInt, int), false, Address::SHC_3BB0A8C1_0x0046B340,
            &GameCore::switchToMenuView)
        switchToMenuView;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046B980, &GameCore::processMenuViewSwitch)
        processMenuViewSwitch;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB20, &GameCore::updateViewportScrollCountdown)
        updateViewportScrollCountdown;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB60, &GameCore::getAreWeInAInGameMenu)
        getAreWeInAInGameMenu;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BB80, &GameCore::isInBuildingTab)
        isInBuildingTab;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BBD0,
            &GameCore::removeJesterAndLadyUnitsInCertainMissions)
        removeJesterAndLadyUnitsInCertainMissions;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BC90, &GameCore::removePlayerLadyAndJester)
        removePlayerLadyAndJester;

        MACRO_FUNCTION_RESOLVER(
            BOOLEnum (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x0046BD20, &GameCore::isGameHaltingMenuOpen)
        isGameHaltingMenuOpen;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(int), false, Address::SHC_3BB0A8C1_0x0046BD50, &GameCore::computeTrailMissionStartDates)
        computeTrailMissionStartDates;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x004718F0, &GameCore::incrementMissionProgress)
        incrementMissionProgress;

        MACRO_FUNCTION_RESOLVER(void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x004719E0,
            &GameCore::switchToScenarioDescriptionMenuView)
        switchToScenarioDescriptionMenuView;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x00471A00, &GameCore::advanceToNextMission)
        advanceToNextMission;

        MACRO_FUNCTION_RESOLVER(
            void (GameCore::*)(), false, Address::SHC_3BB0A8C1_0x00471AA0, &GameCore::hideOrUnhideUI)
        hideOrUnhideUI;

    } // namespace GameCore_Func
} // namespace Game
} // namespace OpenSHC
