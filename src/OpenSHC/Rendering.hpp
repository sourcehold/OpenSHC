/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

    void __cdecl ApplyBlending(int param_1);

    void __stdcall BlitMapImageWithVerticalClip();

    void __stdcall BlitMapImageWithVerticalClipAndYOffset();

    void __stdcall InitializeColors();

    void __stdcall TicksStartCounter();

    int __cdecl ViewportBasedTileNumber();

    void __stdcall ProcessCreditsScriptCommands();

    void __stdcall RenderActiveCreditsElements();

} // namespace Rendering
} // namespace OpenSHC
