/**
  path: 'OpenSHC/Map/WildlifeState.func.hpp'
*/

#include "OpenSHC/Map/WildlifeState.hpp"
namespace OpenSHC {
namespace Map {
    namespace WildlifeState_Func {

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052B9F0, &WildlifeState::clearWildlifeState)
        clearWildlifeState;

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(int), false, Address::SHC_3BB0A8C1_0x0052BA10, &WildlifeState::updateWildlifeGrid)
        updateWildlifeGrid;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int, int), false, Address::SHC_3BB0A8C1_0x0052BF40,
            &WildlifeState::renderDebugDataMapData)
        renderDebugDataMapData;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052C570,
            &WildlifeState::meth_0x52c570)
        meth_0x52c570;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052C810,
            &WildlifeState::meth_0x52c810)
        meth_0x52c810;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052CAB0,
            &WildlifeState::findAndSetNewRallyPointForDeerAndLions)
        findAndSetNewRallyPointForDeerAndLions;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (WildlifeState::*)(int), false, Address::SHC_3BB0A8C1_0x0052CFE0, &WildlifeState::meth_0x52cfe0)
        meth_0x52cfe0;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D620,
            &WildlifeState::meth_0x52d620)
        meth_0x52d620;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D690,
            &WildlifeState::meth_0x52d690)
        meth_0x52d690;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052D720,
            &WildlifeState::meth_0x52d720)
        meth_0x52d720;

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052D9D0, &WildlifeState::meth_0x52d9d0)
        meth_0x52d9d0;

        MACRO_FUNCTION_RESOLVER(
            int (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052DD20, &WildlifeState::meth_0x52dd20)
        meth_0x52dd20;

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052DF30, &WildlifeState::updateWildlife)
        updateWildlife;

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052E020, &WildlifeState::updateSection1034Info)
        updateSection1034Info;

        MACRO_FUNCTION_RESOLVER(
            void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052E120, &WildlifeState::updateNofFpoints)
        updateNofFpoints;

    } // namespace WildlifeState_Func
} // namespace Map
} // namespace OpenSHC
