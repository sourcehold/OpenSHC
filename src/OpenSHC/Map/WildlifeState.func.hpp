/**
  path: 'OpenSHC/Map/WildlifeState.func.hpp'
*/

#include "OpenSHC/Map/WildlifeState.hpp"
namespace OpenSHC {
namespace Map {
    namespace WildlifeState_Func {

        // Constructor

        MACRO_FUNCTION_RESOLVER(WildlifeState* (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052DF10,
            &WildlifeState::Constructor_WildlifeState)
        Constructor_WildlifeState;

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
            &WildlifeState::floodFillField13FromCell)
        floodFillField13FromCell;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052C810,
            &WildlifeState::floodFillField20FromCell)
        floodFillField20FromCell;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052CAB0,
            &WildlifeState::findAndSetNewRallyPointForDeerAndLions)
        findAndSetNewRallyPointForDeerAndLions;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int), false, Address::SHC_3BB0A8C1_0x0052CFE0,
            &WildlifeState::buildRallyPointPathForTribe)
        buildRallyPointPathForTribe;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D620,
            &WildlifeState::hasAdjacentCellWithField24Or25)
        hasAdjacentCellWithField24Or25;

        MACRO_FUNCTION_RESOLVER(undefined4 (WildlifeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x0052D690,
            &WildlifeState::isSuitableWildlifeSpawnCell)
        isSuitableWildlifeSpawnCell;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x0052D720,
            &WildlifeState::floodFillUnknownNonZero01FromCell)
        floodFillUnknownNonZero01FromCell;

        MACRO_FUNCTION_RESOLVER(void (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052D9D0,
            &WildlifeState::floodFillCasDisFromSignpost)
        floodFillCasDisFromSignpost;

        MACRO_FUNCTION_RESOLVER(int (WildlifeState::*)(), false, Address::SHC_3BB0A8C1_0x0052DD20,
            &WildlifeState::getDistanceToNearestUnknownNonZero01FromSignpost)
        getDistanceToNearestUnknownNonZero01FromSignpost;

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
