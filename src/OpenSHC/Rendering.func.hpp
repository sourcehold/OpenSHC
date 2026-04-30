/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Rendering.func.hpp'
*/

#pragma once

#include "OpenSHC/Rendering.hpp"
namespace OpenSHC {
namespace Rendering_Func {

    MACRO_FUNCTION_RESOLVER(
        void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x00453600, &OpenSHC::Rendering::ApplyBlending)
    ApplyBlending;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00453B00, &OpenSHC::Rendering::FUN_00453b00)
    FUN_00453b00;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00454080, &OpenSHC::Rendering::FUN_00454080)
    FUN_00454080;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0046CF10, &OpenSHC::Rendering::TicksStartCounter)
    TicksStartCounter;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B2A60, &OpenSHC::Rendering::viewportBasedTileNumber)
    viewportBasedTileNumber;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E0A50, &OpenSHC::Rendering::FUN_004e0a50)
    FUN_004e0a50;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E12C0, &OpenSHC::Rendering::FUN_004e12c0)
    FUN_004e12c0;

} // namespace Rendering_Func
} // namespace OpenSHC
