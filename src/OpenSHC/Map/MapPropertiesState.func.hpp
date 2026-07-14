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

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7930,
            &MapPropertiesState::activateMatchingScenarioEvents)
        activateMatchingScenarioEvents;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7980,
            &MapPropertiesState::checkScenarioSiegeEvents)
        checkScenarioSiegeEvents;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B7FA0, &MapPropertiesState::sumUnitPoints)
        sumUnitPoints;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004B8000, &MapPropertiesState::sumUnitCounts)
        sumUnitCounts;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BA7D0,
            &MapPropertiesState::sortScenarioEvents)
        sortScenarioEvents;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BA8B0,
            &MapPropertiesState::removeScenarioEvent)
        removeScenarioEvent;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BAEC0,
            &MapPropertiesState::commitBuildingAvailability)
        commitBuildingAvailability;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (MapPropertiesState::*)(eMappersInt), false, Address::SHC_3BB0A8C1_0x004BB010,
            &MapPropertiesState::isMapperAvailable)
        isMapperAvailable;

        MACRO_FUNCTION_RESOLVER(int (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BB0B0,
            &MapPropertiesState::isMercRecruitable)
        isMercRecruitable;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BB900,
            &MapPropertiesState::resetEuroUnitRestrictions)
        resetEuroUnitRestrictions;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BB990,
            &MapPropertiesState::cleanupType3ScenarioEvents)
        cleanupType3ScenarioEvents;

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
            Address::SHC_3BB0A8C1_0x004BC1C0, &MapPropertiesState::spawnScenarioInvasionWave)
        spawnScenarioInvasionWave;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BD980,
            &MapPropertiesState::createScenarioEvent)
        createScenarioEvent;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004BDA80,
            &MapPropertiesState::createLinkedScenarioEvents)
        createLinkedScenarioEvents;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BDE40,
            &MapPropertiesState::computeSomeKindOfMissionCompletionScore)
        computeSomeKindOfMissionCompletionScore;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BE590,
            &MapPropertiesState::setStartingYearAndStartingResources)
        setStartingYearAndStartingResources;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004BEB20,
            &MapPropertiesState::setupStartingYear)
        setupStartingYear;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C1320,
            &MapPropertiesState::migrateScenarioEventData)
        migrateScenarioEventData;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C13F0,
            &MapPropertiesState::setupScenarioInvasionData)
        setupScenarioInvasionData;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C2280,
            &MapPropertiesState::updateVictoryDefeatState)
        updateVictoryDefeatState;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(), false, Address::SHC_3BB0A8C1_0x004C31A0,
            &MapPropertiesState::processSingleplayerEvents)
        processSingleplayerEvents;

        MACRO_FUNCTION_RESOLVER(
            void (MapPropertiesState::*)(char*), false, Address::SHC_3BB0A8C1_0x004C62C0, &MapPropertiesState::loadMap)
        loadMap;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(char*), false, Address::SHC_3BB0A8C1_0x004C6820,
            &MapPropertiesState::loadMissionMapSiegeInfo)
        loadMissionMapSiegeInfo;

        MACRO_FUNCTION_RESOLVER(void (MapPropertiesState::*)(int), false, Address::SHC_3BB0A8C1_0x004C6880,
            &MapPropertiesState::loadMissionMapByNumber)
        loadMissionMapByNumber;

    } // namespace MapPropertiesState_Func
} // namespace Map
} // namespace OpenSHC
