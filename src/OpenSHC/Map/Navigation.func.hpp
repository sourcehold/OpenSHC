/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Navigation.func.hpp'
*/

#pragma once

#include "OpenSHC/Map/Navigation.hpp"
namespace OpenSHC {
namespace Map {
    namespace Navigation_Func {

        MACRO_FUNCTION_RESOLVER(int(__cdecl*)(int param_1, int param_2, int param_3, int param_4), false,
            Address::SHC_3BB0A8C1_0x0049B8C0, &OpenSHC::Map::Navigation::calcApproxEuclideanDistance)
        calcApproxEuclideanDistance;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004A4D60,
            &OpenSHC::Map::Navigation::UpdateClimbDataState01)
        UpdateClimbDataState01;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004A4E40,
            &OpenSHC::Map::Navigation::UpdateClimbDataState03)
        UpdateClimbDataState03;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004A4F90,
            &OpenSHC::Map::Navigation::UpdateClimbDataState04)
        UpdateClimbDataState04;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004A50E0,
            &OpenSHC::Map::Navigation::UpdateClimbDataState05)
        UpdateClimbDataState05;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004A5230,
            &OpenSHC::Map::Navigation::UpdateClimbDataState07)
        UpdateClimbDataState07;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int unitID), false, Address::SHC_3BB0A8C1_0x00530720,
            &OpenSHC::Map::Navigation::UpdateLadderman_SetClimbData)
        UpdateLadderman_SetClimbData;

    } // namespace Navigation_Func
} // namespace Map
} // namespace OpenSHC
