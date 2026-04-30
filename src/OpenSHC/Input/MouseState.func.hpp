/**
  path: 'OpenSHC/Input/MouseState.func.hpp'
*/

#include "OpenSHC/Input/Mouse/MouseClickInteractionInt.hpp"
#include "OpenSHC/Input/MouseState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"
namespace OpenSHC {
namespace Input {
    namespace MouseState_Func {

        using OpenSHC::Input::Mouse::MouseClickInteractionInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00467F80, &MouseState::makeSelectedCursorTypeCurrent)
        makeSelectedCursorTypeCurrent;

        MACRO_FUNCTION_RESOLVER(void (MouseState::*)(short, short, MouseClickInteractionInt), false,
            Address::SHC_3BB0A8C1_0x00468030, &MouseState::updateMousePositionAndClicks)
        updateMousePositionAndClicks;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(int), false, Address::SHC_3BB0A8C1_0x004680B0, &MouseState::updateMouseWheelStatus)
        updateMouseWheelStatus;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (MouseState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x004680C0,
            &MouseState::isMouseInsideBox)
        isMouseInsideBox;

        MACRO_FUNCTION_RESOLVER(void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00468100,
            &MouseState::updateMouseStateBasedOnCursorAndTime)
        updateMouseStateBasedOnCursorAndTime;

        MACRO_FUNCTION_RESOLVER(
            HCURSOR (MouseState::*)(DWORD), false, Address::SHC_3BB0A8C1_0x00468370, &MouseState::setCursor)
        setCursor;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00468420, &MouseState::meth_0x468420)
        meth_0x468420;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004684D0, &MouseState::setupHitBox)
        setupHitBox;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00468590, &MouseState::resetMouseCursorState)
        resetMouseCursorState;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x004685C0, &MouseState::renderPreviewAtMouseLocation)
        renderPreviewAtMouseLocation;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x004687F0, &MouseState::storeXYAndResetMouseState)
        storeXYAndResetMouseState;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x004689D0, &MouseState::resetMouseState2)
        resetMouseState2;

        MACRO_FUNCTION_RESOLVER(void (MouseState::*)(int, int, int, int, int, int, int, int), false,
            Address::SHC_3BB0A8C1_0x00470A00, &MouseState::loadAndSetCursor)
        loadAndSetCursor;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00470B30, &MouseState::meth_0x470b30)
        meth_0x470b30;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00470BC0, &MouseState::rightClickMenuUnk)
        rightClickMenuUnk;

        MACRO_FUNCTION_RESOLVER(
            void (MouseState::*)(), false, Address::SHC_3BB0A8C1_0x00472A90, &MouseState::drawMouseBasedBox)
        drawMouseBasedBox;

    } // namespace MouseState_Func
} // namespace Input
} // namespace OpenSHC
