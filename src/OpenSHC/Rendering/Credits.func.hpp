/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Credits.func.hpp'
*/

#pragma once

#include "OpenSHC/Rendering/Credits.hpp"
namespace OpenSHC {
namespace Rendering {
    namespace Credits_Func {

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int state, undefined4 xSpace, undefined4 param_3, undefined4 ySpace, undefined4 someX,
                undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9),
            false, Address::SHC_3BB0A8C1_0x004DAD40, &OpenSHC::Rendering::Credits::InsertElementIntoAnArrayAt_ec0348)
        InsertElementIntoAnArrayAt_ec0348;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                                    undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
            false, Address::SHC_3BB0A8C1_0x004DAE00, &OpenSHC::Rendering::Credits::InsertElementIntoArrayAt_ec0348_3)
        InsertElementIntoArrayAt_ec0348_3;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int param_1, undefined4 xSpace, undefined4 param_3, undefined4 param_4, undefined4 ySpace,
                undefined4 someX, int param_7, undefined4 someY, undefined4 param_9),
            false, Address::SHC_3BB0A8C1_0x004DAE90, &OpenSHC::Rendering::Credits::InsertElementIntoArrayAt_ec0348_2)
        InsertElementIntoArrayAt_ec0348_2;

    } // namespace Credits_Func
} // namespace Rendering
} // namespace OpenSHC
