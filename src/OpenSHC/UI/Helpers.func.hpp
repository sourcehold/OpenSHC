/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Helpers.func.hpp'
*/

#pragma once

#include "OpenSHC/UI/Helpers.hpp"
namespace OpenSHC {
namespace UI {
    namespace Helpers_Func {

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C1E0,
            &OpenSHC::UI::Helpers::SomeSiegeUnitsComputation)
        SomeSiegeUnitsComputation;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x0042C540,
            &OpenSHC::UI::Helpers::SomeSiegeRelatedCopying)
        SomeSiegeRelatedCopying;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int taxesSettingUnk), false, Address::SHC_3BB0A8C1_0x00433560,
            &OpenSHC::UI::Helpers::SetTaxesSetting_unknown)
        SetTaxesSetting_unknown;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x00434340,
            &OpenSHC::UI::Helpers::SetTribesStateField_0x1C)
        SetTribesStateField_0x1C;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x004347F0,
            &OpenSHC::UI::Helpers::SomeUnitAndViewportCheck)
        SomeUnitAndViewportCheck;

        MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E540,
            &OpenSHC::UI::Helpers::SomePopularityRelatedComputation)
        SomePopularityRelatedComputation;

        MACRO_FUNCTION_RESOLVER(undefined4(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x0043E5A0,
            &OpenSHC::UI::Helpers::SomeFearFactorComputation)
        SomeFearFactorComputation;

        MACRO_FUNCTION_RESOLVER(int(__stdcall*)(), false, Address::SHC_3BB0A8C1_0x0043E5F0,
            &OpenSHC::UI::Helpers::SomeGoldRelatedComputation)
        SomeGoldRelatedComputation;

    } // namespace Helpers_Func
} // namespace UI
} // namespace OpenSHC
