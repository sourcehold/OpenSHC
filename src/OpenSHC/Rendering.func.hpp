/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

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
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00453B00, &OpenSHC::Rendering::BlitMapImageWithVerticalClip)
    BlitMapImageWithVerticalClip;

    MACRO_FUNCTION_RESOLVER(void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x00454080,
        &OpenSHC::Rendering::BlitMapImageWithVerticalClipAndYOffset)
    BlitMapImageWithVerticalClipAndYOffset;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0046CF10, &OpenSHC::Rendering::TicksStartCounter)
    TicksStartCounter;

    MACRO_FUNCTION_RESOLVER(
        int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004B2A60, &OpenSHC::Rendering::viewportBasedTileNumber)
    viewportBasedTileNumber;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E0A50, &OpenSHC::Rendering::ProcessCreditsScriptCommands)
    ProcessCreditsScriptCommands;

    MACRO_FUNCTION_RESOLVER(
        void(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x004E12C0, &OpenSHC::Rendering::RenderActiveCreditsElements)
    RenderActiveCreditsElements;

} // namespace Rendering_Func
} // namespace OpenSHC
