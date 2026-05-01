/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/UI/DisplayElement.hpp'
*/

#pragma once

#include "OpenSHC/DE/SHCDE/eOnScreenTextInt.hpp"
#include "OpenSHC/UI/DisplayElementRenderFunc.hpp"
#include "OpenSHC/UI/Enums/DisplayElementIDInt.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifierInt.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eOnScreenTextInt;
    using OpenSHC::UI::DisplayElementRenderFunc;
    using OpenSHC::UI::Enums::DisplayElementIDInt;
    using OpenSHC::UI::Enums::DisplayElementPositionModifierInt;

#pragma pack(push, 1)

    // SIZE: 0x00000024
    class DisplayElement {
    public:
        int x_0x0; // 0x00000000 length: 4
        int y_0x4; // 0x00000004 length: 4
        DisplayElementIDInt elementID_0x8; // 0x00000008 length: 4
        dword elementStateUnk_0xc; // 0x0000000C length: 4
        dword activationTime_0x10; // 0x00000010 length: 4
        int displayDuration_0x14; // 0x00000014 length: 4
        DisplayElementRenderFunc* renderFunction_0x18; // 0x00000018 length: 4
        DisplayElementPositionModifierInt positionModifier_0x1c; // 0x0000001C length: 4
        DisplayElement* nextDisplayElement_0x20; // 0x00000020 length: 4

    private:
        DisplayElement(DisplayElement const&);
        void operator=(DisplayElement const&);

        DisplayElement();
        ~DisplayElement();

    public:
        // Constructor
        DisplayElement* Constructor_DisplayElement(eOnScreenTextInt elementID, int xPos, int yPos, dword elementState,
            DisplayElementRenderFunc* renderFunction, DisplayElementPositionModifierInt positionModifier);
    };

    static_assert_cpp98_obj(sizeof(DisplayElement) == 36, DisplayElement);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(DisplayElement, false, Address::SHC_3BB0A8C1_0x00DF517C) pDAT_DisplayElement;

} // namespace UI
} // namespace OpenSHC
