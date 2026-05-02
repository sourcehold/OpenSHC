/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/DirectDraw/IDirectDrawSurfaceInterface/functions/Blt.hpp'
*/

#pragma once

#include "WinDef.h"
#include "ddraw.h"
#include "winnt.h"
namespace OpenSHC {
namespace DirectDraw {
    namespace IDirectDrawSurfaceInterface {
        namespace functions {

            typedef HRESULT(__stdcall Blt)(IDirectDrawSurface*, LPRECT, IDirectDrawSurface*, LPRECT, DWORD, LPVOID);
        } // namespace functions
    } // namespace IDirectDrawSurfaceInterface
} // namespace DirectDraw
} // namespace OpenSHC
