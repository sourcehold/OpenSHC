/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/AI/AIVState.hpp'
*/

#pragma once

#include "OpenSHC/AI/AIGridComputationResourceTypeInt.hpp"
#include "OpenSHC/AI/AIMapExtraInfo.hpp"
#include "OpenSHC/AI/AIV/AIV.hpp"
#include "OpenSHC/AI/AIV/AIVBuildingType2Int.hpp"
#include "OpenSHC/AI/AIV/AIVBuildingType2Short.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/Map/HeatMap1114.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIGridComputationResourceTypeInt;
    using OpenSHC::AI::AIMapExtraInfo;
    using OpenSHC::AI::AIV::AIV;
    using OpenSHC::AI::AIV::AIVBuildingType2Int;
    using OpenSHC::AI::AIV::AIVBuildingType2Short;
    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::Map::HeatMap1114;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x000B6C70
    class AIVState {
    public:
        int totalSteps; // 0x00000000 length: 4
        AIV SEC_AIVS[9]; // 0x00000004 length: 252504
        int DAT_AIVFileHash[16][8]; // 0x0003DA5C length: 512
        int DAT_AIVFilePresent[16][8]; // 0x0003DC5C length: 512
        byte DAT_ReceivedAIVFileHash[9][512]; // 0x0003DE5C length: 4608
        int DAT_AIVFileAvailabilityPerAIArray[20]; // 0x0003F05C length: 80
        int DAT_NumberOfAIsWithCastle; // 0x0003F0AC length: 4
        int keepX; // 0x0003F0B0 length: 4
        int keepY; // 0x0003F0B4 length: 4
        int counter; // 0x0003F0B8 length: 4
        undefined1 typeInfo; // 0x0003F0BC length: 1
        undefined1 defensesHeightAndEdgeInformation; // 0x0003F0BD length: 1
        undefined1 unusedUnk; // 0x0003F0BE length: 1
        undefined1 noise; // 0x0003F0BF length: 1
        AIVBuildingType2Short constructions[10000]; // 0x0003F0C0 length: 20000
        int steps[100][100]; // 0x00043EE0 length: 40000
        short rotatedConstructions[100][100]; // 0x0004DB20 length: 20000
        int rotatedSteps[100][100]; // 0x00052940 length: 40000
        int pauses[20]; // 0x0005C580 length: 80
        int unusedPauses[30]; // 0x0005C5D0 length: 120
        int pauseDelay; // 0x0005C648 length: 4
        int unitLocations[24][10]; // 0x0005C64C length: 960
        undefined4 buildingCounter; // 0x0005CA0C length: 4
        undefined4 invalidTileCounter; // 0x0005CA10 length: 4
        AIMapExtraInfo mapExtraInfo; // 0x0005CA14 length: 816
        HeatMap1114 SEC_HeatMaps[80][80]; // 0x0005CD44 length: 307200
        int visitCount; // 0x000A7D44 length: 4
        undefined4 _valueAIndex; // 0x000A7D48 length: 4
        undefined4 _valueBIndex; // 0x000A7D4C length: 4
        int DAT_HeatMapXArray[6400]; // 0x000A7D50 length: 25600
        int DAT_HeatMapYArray[6400]; // 0x000AE150 length: 25600
        int DAT_BuildingApproriateGridXPosition; // 0x000B4550 length: 4
        int DAT_BuildingAppropriateGridYPosition; // 0x000B4554 length: 4
        byte isHandled[10000]; // 0x000B4558 length: 10000
        int aivCount; // 0x000B6C68 length: 4
        int unused01; // 0x000B6C6C length: 4

    private:
        AIVState(AIVState const&);
        void operator=(AIVState const&);

        AIVState();
        ~AIVState();

    public:
        // Constructor
        AIVState* Constructor_AIVState();

        void setAvailableAIV();

        void hostChecksLobbyAIVAvailability();

        void setAIVFilePresenceByFileHashArray(int param_1);

        void syncAIPlayerNamesAndBuildIntervals();

        int setupAIVMetadata(int playerID);

        void setKeepOffsetAndOrientation(int aiID, int keepX, int keepY);

        CommandBuildingTypeInt convertAIVBuildingTypeToCommandBuildingType(AIVBuildingType2Int param_1);

        void rotateAIV(int orientation);

        void aiPlaceFlag(PlayerID playerID);

        void aiPlaceBrazier(PlayerID playerID);

        void incrementBuildingHeatMapTile(int param_1, int param_2);

        BOOLEnum aiPlaceAIVBuilding(PlayerID playerID, int step, int isPausing);

        void clearTheHeatmaps();

        void set0x13ValueTo10InHeatMap(int x, int y);

        int findSuitableLocationCloseToKeepAndPlaceBuilding(
            PlayerID playerID, CommandBuildingTypeInt commandBuildingType);

        void findAppropriateWoodCutterLocation(int playerID);

        void findAppropriateBuildingLocationForResourceType(
            int playerID, AIGridComputationResourceTypeInt resourceTypeNumber);

        void recomputeAIAvailableGridTiles(int playerID);

        void find2by2Location(uint gridX, uint gridY);

        void findAppropriateBuildingLocation(uint param_1, uint param_2);

        void wipeAIVsAndHeatMaps();

        void applyAIV(int playerIDUnk, int playerID2Unk);

        int computeAIVPlacementFit(int playerID);

        int aiPlaceFarm(int playerID, CommandBuildingTypeInt buildingType);

        void aiPlaceWoodcuttershut(int playerID);

        undefined4 findSpotNearEngineersGuild(int param_1);

        void aiPlaceAdditionalOxtether(PlayerID playerID);

        void aiPlacePitchrig(int playerID);

        void aiPlaceIronMine(int playerID);

        void aiPlaceQuarryAndOxtether(int playerID);

        BOOLEnum executeDefaultCastleAIV(PlayerID playerID, int param_2);

        void recomputeHeatmaps(int terrainOnlyUnk);

        void selectBestAIVwithRandomStart(int playerID);

        int tryPlaceAIVAndReturnFitPercentage(int playerID, int castleID);

        void aiDecideOnNewBuildings(PlayerID playerID);

        void updateBuildingsStateAndUpdateAIBuildingDecisions();
    };

    static_assert_cpp98_obj(sizeof(AIVState) == 748656, AIVState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(AIVState, false, Address::SHC_3BB0A8C1_0x01866AB0) pDAT_AIVState;

} // namespace AI
} // namespace OpenSHC
