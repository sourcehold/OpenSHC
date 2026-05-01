/**
  path: 'OpenSHC/Map/MapPropertiesState.func.hpp'
*/

#include "OpenSHC/DE/SHCDE/eMappersInt.hpp"
#include "OpenSHC/Map/MapPropertiesState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace MapPropertiesState_Func {

        using OpenSHC::DE::SHCDE::eMappersInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004B77E0,
            &MapPropertiesState::isParam1LessThan21)
        isParam1LessThan21;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7800,
            &MapPropertiesState::importTradingCosts)
        importTradingCosts;

        MACRO_FUNCTION_RESOLVER(undefined4 (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7890,
            &MapPropertiesState::mapHasCertainEvent)
        mapHasCertainEvent;

        MACRO_FUNCTION_RESOLVER(int (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B78D0,
            &MapPropertiesState::getEventIDForTimeUntilDefeatEventType)
        getEventIDForTimeUntilDefeatEventType;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7930, &MapPropertiesState::FUN_004b7930)
        FUN_004b7930;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7980, &MapPropertiesState::meth_0x4b7980)
        meth_0x4b7980;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7FA0, &MapPropertiesState::sumUnitPoints)
        sumUnitPoints;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B8000, &MapPropertiesState::sumUnitCounts)
        sumUnitCounts;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BA7D0, &MapPropertiesState::meth_0x4ba7d0)
        meth_0x4ba7d0;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BA8B0,
            &MapPropertiesState::meth_0x4ba8b0)
        meth_0x4ba8b0;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BAEC0,
            &MapPropertiesState::commitBuildingAvailability)
        commitBuildingAvailability;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (MapPropertiesState::*)(eMappersInt), false, Address::SHC_3BB0A8C1_0x004BB010,
            &MapPropertiesState::isMapperAvailable)
        isMapperAvailable;

        MACRO_FUNCTION_RESOLVER(int (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BB0B0,
            &MapPropertiesState::FUN_004bb0b0)
        FUN_004bb0b0;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BB900,
            &MapPropertiesState::resetEuroUnitRestrictions)
        resetEuroUnitRestrictions;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BB990, &MapPropertiesState::meth_0x4bb990)
        meth_0x4bb990;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x004BB9F0,
            &MapPropertiesState::openEventTriggerMenu)
        openEventTriggerMenu;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BBA20,
            &MapPropertiesState::sumInvasionEventUnitCount)
        sumInvasionEventUnitCount;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BC110,
            &MapPropertiesState::tweakMonthAndYearBasedOnSection1047)
        tweakMonthAndYearBasedOnSection1047;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int, int, int, int, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x004BC1C0, &MapPropertiesState::FUN_004bc1c0)
        FUN_004bc1c0;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BD980, &MapPropertiesState::meth_0x4bd980)
        meth_0x4bd980;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BDA80,
            &MapPropertiesState::meth_0x4bda80)
        meth_0x4bda80;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BDE40,
            &MapPropertiesState::computeSomeKindOfMissionCompletionScore)
        computeSomeKindOfMissionCompletionScore;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BE590,
            &MapPropertiesState::setStartingYearAndStartingResources)
        setStartingYearAndStartingResources;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BEB20, &MapPropertiesState::meth_0x4beb20)
        meth_0x4beb20;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C1320, &MapPropertiesState::meth_0x4c1320)
        meth_0x4c1320;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C13F0, &MapPropertiesState::meth_0x4c13f0)
        meth_0x4c13f0;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C2280, &MapPropertiesState::FUN_004c2280)
        FUN_004c2280;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C31A0,
            &MapPropertiesState::processSingleplayerEvents)
        processSingleplayerEvents;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(char*), false, Address::SHC_3BB0A8C1_0x004C62C0, &MapPropertiesState::loadMap)
        loadMap;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(char*), false, Address::SHC_3BB0A8C1_0x004C3110,
            &MapPropertiesState::FUN_004c6820)
        FUN_004c6820;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004C6880,
            &MapPropertiesState::FUN_004c6880)
        FUN_004c6880;

    } // namespace MapPropertiesState_Func
} // namespace Map
} // namespace OpenSHC
