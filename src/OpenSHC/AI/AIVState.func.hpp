/**
  path: 'OpenSHC/AI/AIVState.func.hpp'
*/

#include "OpenSHC/AI/AIGridComputationResourceTypeInt.hpp"
#include "OpenSHC/AI/AIV/AIVBuildingType2Int.hpp"
#include "OpenSHC/AI/AIVState.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace AI {
    namespace AIVState_Func {

        using OpenSHC::AI::AIGridComputationResourceTypeInt;
        using OpenSHC::AI::AIV::AIVBuildingType2Int;
        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004ECAD0, &AIVState::setAvailableAIV)
        setAvailableAIV;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004ECBC0, &AIVState::hostChecksLobbyAIVAvailability)
        hostChecksLobbyAIVAvailability;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004ECDB0,
            &AIVState::setAIVFilePresenceByFileHashArray)
        setAIVFilePresenceByFileHashArray;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004ECE60,
            &AIVState::syncAIPlayerNamesAndBuildIntervals)
        syncAIPlayerNamesAndBuildIntervals;

        MACRO_FUNCTION_RESOLVER(
            int (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004ECEF0, &AIVState::setupAIVMetadata)
        setupAIVMetadata;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004ECF70,
            &AIVState::setKeepOffsetAndOrientation)
        setKeepOffsetAndOrientation;

        MACRO_FUNCTION_RESOLVER(CommandBuildingTypeInt (AIVState::*)(AIVBuildingType2Int), false,
            Address::SHC_3BB0A8C1_0x004ECFE0, &AIVState::convertAIVBuildingTypeToCommandBuildingType)
        convertAIVBuildingTypeToCommandBuildingType;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004ED0B0, &AIVState::rotateAIV)
        rotateAIV;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004ED240, &AIVState::aiPlaceFlag)
        aiPlaceFlag;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004ED300, &AIVState::aiPlaceBrazier)
        aiPlaceBrazier;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004ED3B0,
            &AIVState::incrementBuildingHeatMapTile)
        incrementBuildingHeatMapTile;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AIVState::*)(PlayerID, int, int), false, Address::SHC_3BB0A8C1_0x004ED410,
            &AIVState::aiPlaceAIVBuilding)
        aiPlaceAIVBuilding;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004EDC90, &AIVState::clearTheHeatmaps)
        clearTheHeatmaps;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004EDCB0, &AIVState::set0x13ValueTo10InHeatMap)
        set0x13ValueTo10InHeatMap;

        MACRO_FUNCTION_RESOLVER(int (AIVState::*)(PlayerID, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004EDDF0, &AIVState::findSuitableLocationCloseToKeepAndPlaceBuilding)
        findSuitableLocationCloseToKeepAndPlaceBuilding;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EE140,
            &AIVState::findAppropriateWoodCutterLocation)
        findAppropriateWoodCutterLocation;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(int, AIGridComputationResourceTypeInt), false,
            Address::SHC_3BB0A8C1_0x004EE430, &AIVState::findAppropriateBuildingLocationForResourceType)
        findAppropriateBuildingLocationForResourceType;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EE830, &AIVState::recomputeAIAvailableGridTiles)
        recomputeAIAvailableGridTiles;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x004EEBD0, &AIVState::find2by2Location)
        find2by2Location;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x004EEE10,
            &AIVState::findAppropriateBuildingLocation)
        findAppropriateBuildingLocation;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004EF090, &AIVState::wipeAIVsAndHeatMaps)
        wipeAIVsAndHeatMaps;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004EF0D0, &AIVState::applyAIV)
        applyAIV;

        MACRO_FUNCTION_RESOLVER(
            int (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EF8C0, &AIVState::computeAIVPlacementFit)
        computeAIVPlacementFit;

        MACRO_FUNCTION_RESOLVER(int (AIVState::*)(int, CommandBuildingTypeInt), false, Address::SHC_3BB0A8C1_0x004EFA60,
            &AIVState::aiPlaceFarm)
        aiPlaceFarm;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EFAB0, &AIVState::aiPlaceWoodcuttershut)
        aiPlaceWoodcuttershut;

        MACRO_FUNCTION_RESOLVER(undefined4 (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EFB90,
            &AIVState::findSpotNearEngineersGuild)
        findSpotNearEngineersGuild;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004EFC30, &AIVState::aiPlaceAdditionalOxtether)
        aiPlaceAdditionalOxtether;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EFD90, &AIVState::aiPlacePitchrig)
        aiPlacePitchrig;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EFE30, &AIVState::aiPlaceIronMine)
        aiPlaceIronMine;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004EFED0, &AIVState::aiPlaceQuarryAndOxtether)
        aiPlaceQuarryAndOxtether;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (AIVState::*)(PlayerID, int), false, Address::SHC_3BB0A8C1_0x004F0060,
            &AIVState::executeDefaultCastleAIV)
        executeDefaultCastleAIV;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004F0E80, &AIVState::recomputeHeatmaps)
        recomputeHeatmaps;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(int), false, Address::SHC_3BB0A8C1_0x004F13F0, &AIVState::selectBestAIVwithRandomStart)
        selectBestAIVwithRandomStart;

        MACRO_FUNCTION_RESOLVER(int (AIVState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F14F0,
            &AIVState::tryPlaceAIVAndReturnFitPercentage)
        tryPlaceAIVAndReturnFitPercentage;

        MACRO_FUNCTION_RESOLVER(
            void (AIVState::*)(PlayerID), false, Address::SHC_3BB0A8C1_0x004F15C0, &AIVState::aiDecideOnNewBuildings)
        aiDecideOnNewBuildings;

        MACRO_FUNCTION_RESOLVER(void (AIVState::*)(), false, Address::SHC_3BB0A8C1_0x004F1860,
            &AIVState::updateBuildingsStateAndUpdateAIBuildingDecisions)
        updateBuildingsStateAndUpdateAIBuildingDecisions;

    } // namespace AIVState_Func
} // namespace AI
} // namespace OpenSHC
