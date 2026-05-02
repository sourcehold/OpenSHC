/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/TileMapState.hpp'
*/

#pragma once

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnumInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1Int.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2Int.hpp"
#include "OpenSHC/Map/Moat.hpp"
#include "OpenSHC/Map/PitchDitch.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::CommandBuildingTypeInt;
    using OpenSHC::Commands::CommandBuildingTypeShort;
    using OpenSHC::Game::Player::PlayerID;
    using OpenSHC::IO::PackagedFileMagicNumInt;
    using OpenSHC::Map::Moat;
    using OpenSHC::Map::PitchDitch;
    using OpenSHC::Map::Buildings::BuildingFailReasonEnumInt;
    using OpenSHC::Map::Buildings::BuildingTypeInt;
    using OpenSHC::Map::LogicHelpers::Logic1Int;
    using OpenSHC::Map::LogicHelpers::Logic2Int;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x00554A88
    class TileMapState {
    public:
        int directionTranslationMatrix[400][8]; // 0x00000000 length: 12800
        int yArray1[400]; // 0x00003200 length: 1600
        int heightBasedScreenYOffset[256]; // 0x00003840 length: 1024
        int unusedTileMap[80400]; // 0x00003C40 length: 321600
        ushort GfxLayer[80400]; // 0x00052480 length: 160800
        ushort AlphaGFXLayer[80400]; // 0x000798A0 length: 160800
        ushort ConstructionGFXLayer[80400]; // 0x000A0CC0 length: 160800
        ushort PillarGFXLayer[80400]; // 0x000C80E0 length: 160800
        ushort WallGFXLayer[80400]; // 0x000EF500 length: 160800
        ushort FloatingLayer[80400]; // 0x00116920 length: 160800
        ushort RandomLayer[80400]; // 0x0013DD40 length: 160800
        int LogicLayer[80400]; // 0x00165160 length: 321600
        byte unknownData1[1600]; // 0x001B39A0 length: 1600
        byte Logic2Layer[80400]; // 0x001B3FE0 length: 80400
        byte unknownData2[400]; // 0x001C79F0 length: 400
        byte ChangedLayer[80400]; // 0x001C7B80 length: 80400
        ushort OrganismLayer[80400]; // 0x001DB590 length: 160800
        ushort BuildingLayer[80400]; // 0x002029B0 length: 160800
        uchar BuildingWasLayer[80400]; // 0x00229DD0 length: 80400
        ushort UnitLayer[80400]; // 0x0023D7E0 length: 160800
        short EntityLayer[80400]; // 0x00264C00 length: 160800
        char EntityLayerLT25[80400]; // 0x0028C020 length: 80400
        byte HeightLayer[80400]; // 0x0029FA30 length: 80400
        byte DefaultHeightLayer[80400]; // 0x002B3440 length: 80400
        byte WallOwnerLayer[80400]; // 0x002C6E50 length: 80400
        uchar LuminesenceLayer[80400]; // 0x002DA860 length: 80400
        uchar ShowHiLayer[80400]; // 0x002EE270 length: 80400
        ushort MiscDisplayLayer[80400]; // 0x00301C80 length: 160800
        byte DamageLayer[80400]; // 0x003290A0 length: 80400
        ushort MacroLayer[80400]; // 0x0033CAB0 length: 160800
        ushort PathConnectionLayer[80400]; // 0x00363ED0 length: 160800
        uchar PathLinkageLayer[80400]; // 0x0038B2F0 length: 80400
        uchar OccupancyLayer[80400]; // 0x0039ED00 length: 80400
        short CertainPathLayer[80400]; // 0x003B2710 length: 160800
        short WalkLayer[80400]; // 0x003D9B30 length: 160800
        byte AIZoneLayer[80400]; // 0x00400F50 length: 80400
        uchar AIInfoLayer[80400]; // 0x00414960 length: 80400
        uchar unitDeathHeatMap[80400]; // 0x00428370 length: 80400
        uchar SEC_TileMap1104[80400]; // 0x0043BD80 length: 80400
        uchar SEC_PathfindingCostTileMap1105[9][80400]; // 0x0044F790 length: 723600
        undefined4 someIndex; // 0x00500220 length: 4
        undefined4 someLimit; // 0x00500224 length: 4
        undefined4 someYLike; // 0x00500228 length: 4
        undefined4 someYLikeLimit; // 0x0050022C length: 4
        byte mapping40x40[40][40]; // 0x00500230 length: 1600
        Moat SEC_MoatArray[16000]; // 0x00500870 length: 256000
        undefined4 maxMoatsCount; // 0x0053F070 length: 4
        undefined4 moatTileCount; // 0x0053F074 length: 4
        undefined4 ALG_MoatXResult; // 0x0053F078 length: 4
        undefined4 ALG_MoatYResult; // 0x0053F07C length: 4
        int someMoatTile; // 0x0053F080 length: 4
        PitchDitch SEC_PitchDitches[4000]; // 0x0053F084 length: 80000
        undefined4 maxPitchDitchCount; // 0x00552904 length: 4
        undefined1 padding_0x552908[4]; // 0x00552908 length: 4
        short specialAreasArray[8]; // 0x0055290C length: 16
        undefined4 field58_0x55291c; // 0x0055291C length: 4
        undefined4 SEC_Section1052; // 0x00552920 length: 4
        undefined4 SEC_Section1053; // 0x00552924 length: 4
        undefined4 SEC_Section1054; // 0x00552928 length: 4
        int DAT_TemporaryTerrainTypeArray[1000]; // 0x0055292C length: 4000
        int DAT_TemporaryTerrainTypeBinaryArray[1000]; // 0x005538CC length: 4000
        undefined4 forceUpdateLogicalAndMiscDisplayLayers; // 0x0055486C length: 4
        undefined4 forceUpdateTextureTilemap; // 0x00554870 length: 4
        undefined4 forceUpdateGFXLayers; // 0x00554874 length: 4
        undefined4 forceUpdateMacroLayerFlag; // 0x00554878 length: 4
        undefined4 field68_0x55487c; // 0x0055487C length: 4
        undefined1 padding_0x554880[8]; // 0x00554880 length: 8
        undefined4 DAT_PlacedBuildingID; // 0x00554888 length: 4
        undefined4 field78_0x55488c; // 0x0055488C length: 4
        undefined4 rockOrientation; // 0x00554890 length: 4
        undefined4 field80_0x554894; // 0x00554894 length: 4
        undefined4 lastTime; // 0x00554898 length: 4
        int SEC_MapOrientation; // 0x0055489C length: 4
        undefined4 DAT_FutureMapOrientation; // 0x005548A0 length: 4
        undefined4 field84_0x5548a4; // 0x005548A4 length: 4
        undefined4 field85_0x5548a8; // 0x005548A8 length: 4
        undefined4 field86_0x5548ac; // 0x005548AC length: 4
        undefined4 field87_0x5548b0; // 0x005548B0 length: 4
        undefined4 field88_0x5548b4; // 0x005548B4 length: 4
        undefined4 refreshCertainTileMap; // 0x005548B8 length: 4
        undefined4 refreshCertainTileMap_old; // 0x005548BC length: 4
        undefined4 counter1; // 0x005548C0 length: 4
        undefined4 refreshRelatedOne; // 0x005548C4 length: 4
        undefined4 field93_0x5548c8; // 0x005548C8 length: 4
        undefined4 flatViewToggleValue1; // 0x005548CC length: 4
        undefined1 padding_0x5548d0[4]; // 0x005548D0 length: 4
        undefined4 flatViewToggleValue2; // 0x005548D4 length: 4
        undefined4 refreshRelatedTwo; // 0x005548D8 length: 4
        undefined4 field101_0x5548dc; // 0x005548DC length: 4
        undefined4 editorActiveBrush; // 0x005548E0 length: 4
        CommandBuildingTypeInt currentMapperCommand; // 0x005548E4 length: 4
        undefined4 DAT_BuildingSize; // 0x005548E8 length: 4
        undefined4 field105_0x5548ec; // 0x005548EC length: 4
        BOOLEnum mapperMax; // 0x005548F0 length: 4
        undefined4 rockFlagStartNumber; // 0x005548F4 length: 4
        undefined4 unknownBrushRelated; // 0x005548F8 length: 4
        undefined4 unknownZero_0x5548fc; // 0x005548FC length: 4
        undefined4 unknownZero_0x554900; // 0x00554900 length: 4
        undefined4 unknownZero_0x554904; // 0x00554904 length: 4
        undefined4 field112_0x554908; // 0x00554908 length: 4
        undefined4 dragStartX; // 0x0055490C length: 4
        undefined4 dragStartY; // 0x00554910 length: 4
        undefined4 dragEndX; // 0x00554914 length: 4
        undefined4 dragEndY; // 0x00554918 length: 4
        BOOLEnum illegalBuild; // 0x0055491C length: 4
        undefined4 field118_0x554920; // 0x00554920 length: 4
        undefined4 field119_0x554924; // 0x00554924 length: 4
        undefined4 DAT_ClickedTileX; // 0x00554928 length: 4
        undefined4 DAT_ClickedTileY; // 0x0055492C length: 4
        undefined4 field122_0x554930; // 0x00554930 length: 4
        BOOLEnum buildingPlacementFail; // 0x00554934 length: 4
        BuildingFailReasonEnumInt buildingPlacementFailReason; // 0x00554938 length: 4
        undefined4 placementWarning; // 0x0055493C length: 4
        undefined4 DAT_UIBuildingRotation; // 0x00554940 length: 4
        undefined4 field127_0x554944; // 0x00554944 length: 4
        undefined4 buildingSpriteSheetID_1; // 0x00554948 length: 4
        undefined4 buildingSpriteID1; // 0x0055494C length: 4
        undefined4 buildingSpriteID2; // 0x00554950 length: 4
        undefined4 field131_0x554954; // 0x00554954 length: 4
        undefined4 buildingHeightLimit; // 0x00554958 length: 4
        undefined4 buildingMinHeight; // 0x0055495C length: 4
        undefined4 buildingMaxHeight; // 0x00554960 length: 4
        undefined4 buildingMaxHeightDifference; // 0x00554964 length: 4
        undefined4 buildingPlacementProperty_3; // 0x00554968 length: 4
        undefined4 buildingPlacementProperty_4; // 0x0055496C length: 4
        undefined4 buildingPlacementProperty_5; // 0x00554970 length: 4
        undefined4 buildingPlacementProperty_6; // 0x00554974 length: 4
        undefined4 buildingPlacementProperty_7; // 0x00554978 length: 4
        undefined1 padding_0x55497c[4]; // 0x0055497C length: 4
        undefined4 field145_0x554980; // 0x00554980 length: 4
        int constructionTileCount; // 0x00554984 length: 4
        int DAT_WallTileCountCurrentDrag; // 0x00554988 length: 4
        undefined4 buildingX; // 0x0055498C length: 4
        undefined4 buildingY; // 0x00554990 length: 4
        undefined4 buildingRotationRelatedValue; // 0x00554994 length: 4
        undefined4 field151_0x554998; // 0x00554998 length: 4
        undefined4 field152_0x55499c; // 0x0055499C length: 4
        undefined4 field153_0x5549a0; // 0x005549A0 length: 4
        int showNoRubbleWhenDestroyingBuilding; // 0x005549A4 length: 4
        undefined4 field155_0x5549a8; // 0x005549A8 length: 4
        undefined4 field156_0x5549ac; // 0x005549AC length: 4
        undefined4 wallPlacementCost; // 0x005549B0 length: 4
        undefined4 DAT_TempBuildingRotation; // 0x005549B4 length: 4
        int field159_0x5549b8; // 0x005549B8 length: 4
        undefined4 unknownTime_0x5549bc; // 0x005549BC length: 4
        undefined4 field161_0x5549c0; // 0x005549C0 length: 4
        undefined4 field162_0x5549c4; // 0x005549C4 length: 4
        undefined4 field163_0x5549c8; // 0x005549C8 length: 4
        undefined4 field164_0x5549cc; // 0x005549CC length: 4
        undefined4 field165_0x5549d0; // 0x005549D0 length: 4
        undefined4 DAT_SelectionIconType; // 0x005549D4 length: 4
        undefined4 field167_0x5549d8; // 0x005549D8 length: 4
        undefined1 padding_0x5549dc[8]; // 0x005549DC length: 8
        int shiftRelated0or3; // 0x005549E4 length: 4
        undefined4 field177_0x5549e8; // 0x005549E8 length: 4
        undefined4 field178_0x5549ec; // 0x005549EC length: 4
        undefined4 field179_0x5549f0; // 0x005549F0 length: 4
        undefined4 field180_0x5549f4; // 0x005549F4 length: 4
        undefined4 uiSelectedUnitIDUnk; // 0x005549F8 length: 4
        undefined4 DAT_SomeUNitUIDUIRelated; // 0x005549FC length: 4
        undefined4 field183_0x554a00; // 0x00554A00 length: 4
        undefined4 field184_0x554a04; // 0x00554A04 length: 4
        undefined4 field185_0x554a08; // 0x00554A08 length: 4
        undefined4 mapSize; // 0x00554A0C length: 4
        undefined4 field187_0x554a10; // 0x00554A10 length: 4
        undefined4 field188_0x554a14; // 0x00554A14 length: 4
        undefined1 padding_0x554a18[4]; // 0x00554A18 length: 4
        undefined4 field193_0x554a1c; // 0x00554A1C length: 4
        undefined4 field194_0x554a20; // 0x00554A20 length: 4
        undefined4 field195_0x554a24; // 0x00554A24 length: 4
        undefined1 padding_0x554a28[8]; // 0x00554A28 length: 8
        int field204_0x554a30; // 0x00554A30 length: 4
        undefined4 DAT_SomeX; // 0x00554A34 length: 4
        undefined4 DAT_SomeY; // 0x00554A38 length: 4
        undefined4 DAT_SomeTile; // 0x00554A3C length: 4
        undefined1 bitFlag; // 0x00554A40 length: 1
        undefined1 padding_0x554a41[3]; // 0x00554A41 length: 3
        undefined4 DAT_CardinalTilesAroundTile; // 0x00554A44 length: 4
        undefined4 field213_0x554a48; // 0x00554A48 length: 4
        undefined1 padding_0x554a4c[4]; // 0x00554A4C length: 4
        undefined2 field218_0x554a50; // 0x00554A50 length: 2
        undefined1 padding_0x554a52[6]; // 0x00554A52 length: 6
        pointer* ptr_LogicLayer; // 0x00554A58 length: 4
        pointer* ptr_TerrainTypeTileMap; // 0x00554A5C length: 4
        pointer* ptr_TerrainHeightTileMap; // 0x00554A60 length: 4
        pointer* ptr_ChangedLayer; // 0x00554A64 length: 4
        pointer* ptr_MovementDirectionTranslationMatrix; // 0x00554A68 length: 4
        pointer* ptr_OccupancyLayer; // 0x00554A6C length: 4
        pointer* ptr_DamageLayer; // 0x00554A70 length: 4
        pointer* ptr_PathConnectionLayer; // 0x00554A74 length: 4
        pointer* ptr_AIZoneLayer; // 0x00554A78 length: 4
        pointer* ptr_SpecialAreasArray; // 0x00554A7C length: 4
        pointer* ptr_MiscDisplayLayer; // 0x00554A80 length: 4
        undefined1 padding_0x554a84[4]; // 0x00554A84 length: 4

    private:
        TileMapState(TileMapState const&);
        void operator=(TileMapState const&);

        TileMapState();
        ~TileMapState();

    public:
        // Constructor
        TileMapState* Constructor_TileMapState();

        void processEntityDamageToBuildingCollateralThunk(
            undefined4 tile, undefined4 x_2, undefined4 y_2, undefined4 damage, undefined4 playerID, undefined4 unused);

        void processDamageToBuildingThunk(undefined4 targetedTile, undefined4 targetedTileX, undefined4 targetedTileY,
            undefined4 damage, undefined4 param_5, undefined4 playerID, BOOLEnum aiBuildDelayRelated);

        void setChangedLayerToThreeAndMapping0x40x40();

        void setupMovementDirectionTranslationMatrix();

        void setupLogicalMapBorders();

        void resetHeightAndMapBorders(int mapSize);

        void setMapSize(int size);

        void triggerLoweredView(int param_1);

        void toggleFlatView(int param_1);

        void setMapRotation(undefined4 newRotation);

        void updateLogicalTileMapRelatedSections();

        void meth_0x4f7a80(int param_1, int param_2);

        void increaseHeightForTunnelSingleTile(int tile, uint x, uint y, int increment);

        int getNonFarmFieldBuildingHealthAtTileOr1000(int tile);

        void meth_0x4f81d0(int param_1, uint param_2, uint param_3);

        uint getBuildingHurtSFXID(int buildingID);

        void rotateFearFactorBuildingVariations();

        void countPropertyInSurroundingTiles(int tile, int param_2, uint param_3);

        undefined4 meth_0x4f85b0(int param_1, int param_2);

        undefined4 meth_0x4f8640(int param_1, int param_2);

        uint meth_0x4f86d0(int param_1, int param_2, int param_3);

        uint meth_0x4f8780(int param_1, int param_2, int param_3);

        undefined4 meth_0x4f8840(int param_1, int param_2, int param_3);

        undefined4 meth_0x4f8900(int param_1, int param_2);

        uint meth_0x4f89c0(int param_1, int param_2, int param_3);

        uint meth_0x4f8a40(int param_1, int param_2, int param_3);

        uint meth_0x4f8ac0(int param_1, int param_2, int param_3);

        int getOrientationThatIsWallTowerOrGatehouse(uint x, uint y);

        void previewWallDrawingUnk(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command);

        void meth_0x4f9000(int param_1, int param_2);

        void swapWallOwnership(int param_1, int param_2);

        void destroyWallsOfPlayer(int playerID);

        void isWallUnkPlacementAllowed(int playerID, uint x, uint y, CommandBuildingTypeInt param_4);

        void setupBuildingSizeIndexMappingForBuildingWithSize(int buildingSize);

        void getBuildingSizeIndexMappingData(int buildingSizeTileIndex, int buildingWidthOrHeight);

        BOOLEnum indexIsEdgeUnk(int counter, int size);

        void storeMinAndMaxHeightOfArea(uint x, uint y, int buildingWidthAndHeight);

        int isBuildingPlacementAllowedAtTile(
            int tile, int playerID, CommandBuildingTypeInt commandBuildingType, int param_4);

        void meth_0x4f9df0(int param_1, int param_2, int param_3);

        void spawnEraserEntityEffectsUnk(undefined4 param_1, int param_2);

        void meth_0x4fa000(int param_1, int param_2);

        void checkDrawbridgePlacement(int x, int y);

        undefined4 meth_0x4fa460(int param_1);

        undefined4 getBuildingSizeForCommandBuildingType(CommandBuildingTypeInt commandBuildingType);

        void meth_0x4fa760(undefined4 param_1, int param_2, int param_3, undefined4 param_4, int param_5);

        void meth_0x4fa9d0(int param_1, int param_2, int param_3);

        void updateAreaBasedOnSurrounding(int x, int y, int buildingSize);

        void meth_0x4faab0(int param_1, int param_2);

        void meth_0x4fab70(int x, int y, int size);

        void meth_0x4fac70(int x, int y, int param_3);

        void meth_0x4fad20(int param_1, int param_2, int param_3);

        void meth_0x4fad70(int x, int y, int param_3);

        void meth_0x4fae50(int param_1, int param_2);

        undefined4 meth_0x4faee0(int param_1);

        void meth_0x4faf70(int param_1, int param_2);

        void meth_0x4fb0c0(int buildingID);

        void meth_0x4fb360(int buildingID, int param_2);

        void FUN_004fb3f0(int x, int y, int type);

        void placeRock(uint x, uint y, uint param_3);

        void meth_0x4fb770(int rockID);

        void meth_0x4fb8e0(int param_1);

        void meth_0x4fb970(int param_1);

        void meth_0x4fb9e0(uint x, uint y, short param_3);

        undefined4 getCastleBuildRangeForMapSize();

        void getTileForBrush(int square, int index, int* tilePointer, int* yPointer, int baseTile, uint y);

        undefined4 meth_0x4fbe70(int param_1, uint param_2, uint param_3);

        void meth_0x4fc0b0(int param_1, int param_2, int param_3);

        void meth_0x4fc280(int param_1, int param_2, int param_3);

        void meth_0x4fc340();

        void generateDustClouds();

        int meth_0x4fc650(uint param_1);

        BOOLEnum meth_0x4fc7c0(int param_1, undefined4 param_2, int param_3);

        void meth_0x4fc810(int param_1, uint param_2, uint param_3);

        void updateGFXLayers();

        void updateMacroLayerRelated(uint param_1, uint param_2, int param_3);

        void updateMacroLayerRelated2();

        byte setBitFlagBasedOnWallTowerGatehouseOrKeep(int x, int y);

        uint returnSomeHeight(int tile, int param_2);

        uint getTotalHeightAtTile(int tile);

        int getTotalHeightAt(int tile, int playerID);

        uint getHeightAtTileIncludingOwnersBuildings(int tile, int playerID);

        void recountTotalOwnedMoats();

        void scanMoatsInGroupsOfThreeUnk();

        int countUnfinishedMoatUnk(int playerID);

        int getUnownedMoatCount();

        int returnOwnedMoatAtTile(int targetedTile);

        void clearMoatFromMemory(uint param_1);

        void clearMoat(int x, int y);

        BOOLEnum findTileInSameAreaAndNoTooHeightDifference(int area, int tile, int yUnk);

        int setXYBasedOnMoatID(int tile, int param_2, uint x, uint y);

        undefined4 meth_0x500500(int moatID);

        void clearMoatIfUnk(int tile);

        void moatRelatedUpdateFunction();

        void meth_0x500680();

        void meth_0x5006c0();

        void meth_0x500720(int param_1, undefined4 param_2);

        void meth_0x500750(int param_1, undefined4 param_2);

        void swapMoatOwnership(int param_1, int param_2);

        void meth_0x5007d0();

        int countPitchDitchesWithPlayerID0();

        int getPitchDitchIDForTile(int tile);

        void destroyPitchDitch(int pitchDitchID);

        void swapPitchOwnership(int param_1, int param_2);

        undefined4 meth_0x500980(uint x1, uint y1, uint x2, uint y2);

        int meth_0x500b50(int param_1, int param_2, uint param_3);

        void campaignRelatedNumber();

        void spreadAlgorithmForFlagsAndBraziers2Unk(int param_1, uint param_2, uint param_3);

        void spreadAlgorithmForFlagsAndBraziersUnk(int playerID, uint x, uint y);

        void clearAndSetTileMapUnknown2Plus();

        void meth_0x5017c0(uint param_1, uint param_2, int param_3);

        void updateShowHiLayerOrResetChangedLayer();

        void changeMapOrientationUnk(int mapOrientation);

        void increaseHeightForTunnelWithBrush(int tile, uint x, uint y, int increment);

        void raiseLand(int tile, uint y, uint brush, int change);

        void createPlateau(int tile, uint the_y, int param_3, int plateauHeightSetting);

        void useBrush2(int param_1, uint param_2, uint param_3);

        void setLand(int tile, uint y, uint brushType_y);

        BOOLEnum meth_0x5024f0(int x, uint y, int cbt);

        void useBrush3(int param_1, uint param_2, uint param_3, undefined4 param_4);

        byte meth_0x502950(int param_1, uint param_2);

        void checkWhetherThisWallBuildIsAllowed(int playerID, uint x1, uint y1, uint x2, uint y2, undefined4 command);

        void placeWalls(
            int playerID, uint x1, uint y1, uint x2, uint y2, CommandBuildingTypeInt wallType, int tileCountUnk);

        void placeDefensiveStructurePart2Unk(int param_1, uint x, uint y, CommandBuildingTypeInt param_4);

        void setupBuildingSizeIndexMapping();

        void checkBuildingCanBePlacedHere(int playerID, uint x, uint y__fertileLandCount,
            CommandBuildingTypeShort commandBuildingType, int buildingSize);

        void meth_0x504a30(int playerID, uint x, uint y);

        void meth_0x504ee0(int param_1, int param_2);

        int setConstructionGFXLayerBasedOnPlacementChecks(int x, int y, CommandBuildingTypeInt type, int size);

        void updateBuildingGraphicsLayer(int buildingID);

        void someUpdatePathLinkageRelatedCall(int buildingID);

        void placeWorkshopOrHovel(
            int playerID, uint x, uint y, BuildingTypeInt type, uint size, int orientation, undefined4 averageHeight);

        void placeSiegetowerPlaced(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeSiegeTentUnk(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placePositiveFearfactor(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            uint param_6, undefined4 param_7, undefined4 param_8);

        void meth_0x507060(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            uint param_6, undefined4 param_7, undefined4 param_8);

        void placeTower(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint size, int param_6, undefined4 param_7);

        void upgradeTowerLogicLayer(int param_1);

        void meth_0x507350(int tile);

        void placeGatehouseSmall(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeGatehouseLarge(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeBarracks(int playerID, uint xPosition, int* yPosition_param, undefined4 buildingType,
            uint buildingSize, int buildingOrientation, undefined4 param_7);

        void placeEngineersguild(
            int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeTunnelersguild(
            int param_1, int* param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeOilsmelter(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, undefined4 param_7);

        void placeQuarry(int playerID, uint x, uint y, undefined4 buildingType, uint buildingSize,
            int buildingOrientation, uint heightUnk);

        void placeStockpile(
            int playerID, int x, int y, undefined4 buildingType, undefined4 param_5, int variation, int averageHeight);

        void meth_0x508760(int param_1, int param_2);

        void meth_0x508870(int param_1, int param_2);

        void meth_0x508910(int param_1);

        void renderPreviewMapperWithBrush(uint x, uint y, CommandBuildingTypeInt param_3);

        void applyTreeToLogicalLayer(int treeID, int param_2);

        void meth_0x508ec0(uint param_1, uint param_2, uint param_3);

        void updateTextureTilemap();

        void updateMacroLayer();

        int createMoat(undefined4 playerID, uint x, uint y, int param_4);

        BOOLEnum findNearestFriendlyMoatTileForDigging(int playerID, int unitID, int number);

        undefined4 removeMoat(uint moatID);

        void updatePitchDitches();

        int placePitchDitch(undefined4 playerID, uint x, uint y);

        void updateGameRelatedValue();

        void upgradeMapFormatLogicLayer(
            PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

        void setupTileMapSections();

        void setupAllMapSections();

        void prepareMap();

        void resetAreaBasedOnLogicalLayer();

        void processMapOrientationChange();

        void setTerrain(int playerID, int tile, uint yParam, uint brushType, Logic1Int flags1, Logic2Int flags2);

        void placeMoat(undefined4 playerID, int tile, uint tileY);

        void placeKillingPit(
            int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int param_6, int param_7);

        void placeKeep(int playerID, uint x, uint y, BuildingTypeInt type, uint size, int orientation, int xyValue);

        void placeDrawbridge(int param_1, uint param_2, uint param_3, undefined4 param_4, uint param_5, int* param_6,
            undefined4 param_7);

        void placeWheatfarm(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            int param_6, undefined4 param_7);

        void placeHopfarm(
            int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5, int param_6, int param_7);

        void placeDairyfarm(int param_1, uint param_2, uint param_3, undefined4 param_4, undefined4 param_5,
            int* param_6, undefined4 param_7);

        void placeApplefarm(
            int playerID, uint x, uint y, BuildingTypeInt buildingType, undefined4 param_5, int param_6, int* param_7);

        void clearBuildingFromTerrain(int buildingID);

        void createMoatSize5Unk(int param_1);

        void placeTree(uint x, uint y, undefined4 treeType);

        BOOLEnum prepareAreaForBuildingPlacement(
            int playerID, uint x, uint y, CommandBuildingTypeInt commandBuildingType, int buildingWidthOrHeight);

        void placeBuilding(
            PlayerID playerID, int x, int y, CommandBuildingTypeInt cbt, int buildingSize, int buildingOrientation);

        uint processDamageToBuilding(int tile, uint xPosition, uint yPosition, int damageUnk, int param_5, int playerID,
            BOOLEnum aiBuildDelayRelated, int unitID);

        void processEntityDamageToBuildingCollateral(
            int tile, uint x_2, uint y_2, int damage, int playerID, undefined4 unused, int unitID);
    };

    static_assert_cpp98_obj(sizeof(TileMapState) == 5589640, TileMapState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(TileMapState, false, Address::SHC_3BB0A8C1_0x01A93208) pDAT_TileMapState;

} // namespace Map
} // namespace OpenSHC
