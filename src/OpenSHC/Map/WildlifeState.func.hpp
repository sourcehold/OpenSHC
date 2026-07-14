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

        MACRO_FUNCTION_RESOLVER(undefined (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052C570,
            &WildlifeState::floodFillWildlifeDangerField)
        floodFillWildlifeDangerField;

        MACRO_FUNCTION_RESOLVER(undefined (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052C810,
            &WildlifeState::floodFillWildlifeGrazingField)
        floodFillWildlifeGrazingField;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052CAB0,
            &WildlifeState::findAndSetNewRallyPointForDeerAndLions)
        findAndSetNewRallyPointForDeerAndLions;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int), false, Address::SHC_3BB0A8C1_0x0052CFE0,
            &WildlifeState::buildWildlifeGrazingPath)
        buildWildlifeGrazingPath;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D620,
            &WildlifeState::hasAdjacentWildlifeMarker)
        hasAdjacentWildlifeMarker;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D690,
            &WildlifeState::isGoodGrazingCell)
        isGoodGrazingCell;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052D720,
            &WildlifeState::floodFillWildlifeClaimField)
        floodFillWildlifeClaimField;

        MACRO_FUNCTION_RESOLVER(undefined (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052D9D0,
            &WildlifeState::mapWildlifeFromAttackSignpost)
        mapWildlifeFromAttackSignpost;

        MACRO_FUNCTION_RESOLVER(int (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052DD20,
            &WildlifeState::distanceFromSignpostToClaimedCell)
        distanceFromSignpostToClaimedCell;

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
