/**
  path: 'OpenSHC/Map/TileMapState.func.hpp'
*/

#include "OpenSHC/Commands/CommandBuildingTypeInt.hpp"
#include "OpenSHC/Commands/CommandBuildingTypeShort.hpp"
#include "OpenSHC/Game/Player/PlayerID.hpp"
#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeInt.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic1Int.hpp"
#include "OpenSHC/Map/LogicHelpers/Logic2Int.hpp"
#include "OpenSHC/Map/TileMapState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace TileMapState_Func {

        using OpenSHC::Commands::CommandBuildingTypeInt;
        using OpenSHC::Commands::CommandBuildingTypeShort;
        using OpenSHC::Game::Player::PlayerID;
        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::Buildings::BuildingTypeInt;
        using OpenSHC::Map::LogicHelpers::Logic1Int;
        using OpenSHC::Map::LogicHelpers::Logic2Int;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(undefined4, undefined4, undefined4, undefined4, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x00401060, &TileMapState::processEntityDamageToBuildingCollateralThunk)
        processEntityDamageToBuildingCollateralThunk;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(undefined4, undefined4, undefined4, undefined4, undefined4, undefined4, BOOLEnum),
            false, Address::SHC_3BB0A8C1_0x00409300, &TileMapState::processDamageToBuildingThunk)
        processDamageToBuildingThunk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F6AE0,
            &TileMapState::setChangedLayerToThreeAndMapping0x40x40)
        setChangedLayerToThreeAndMapping0x40x40;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F6B20,
            &TileMapState::setupMovementDirectionTranslationMatrix)
        setupMovementDirectionTranslationMatrix;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F6C60, &TileMapState::setupLogicalMapBorders)
        setupLogicalMapBorders;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F6CF0,
            &TileMapState::resetHeightAndMapBorders)
        resetHeightAndMapBorders;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F6F90, &TileMapState::setMapSize)
        setMapSize;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F6FD0, &TileMapState::triggerLoweredView)
        triggerLoweredView;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F70B0, &TileMapState::toggleFlatView)
        toggleFlatView;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x004F70E0, &TileMapState::setMapRotation)
        setMapRotation;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F70F0,
            &TileMapState::updateLogicalTileMapRelatedSections)
        updateLogicalTileMapRelatedSections;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F7A80, &TileMapState::meth_0x4f7a80)
        meth_0x4f7a80;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x004F80E0,
            &TileMapState::increaseHeightForTunnelSingleTile)
        increaseHeightForTunnelSingleTile;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F8160,
            &TileMapState::getNonFarmFieldBuildingHealthAtTileOr1000)
        getNonFarmFieldBuildingHealthAtTileOr1000;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x004F81D0,
            &TileMapState::meth_0x4f81d0)
        meth_0x4f81d0;

        MACRO_FUNCTION_RESOLVER(
            uint (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F8210, &TileMapState::getBuildingHurtSFXID)
        getBuildingHurtSFXID;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F8300,
            &TileMapState::rotateFearFactorBuildingVariations)
        rotateFearFactorBuildingVariations;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, uint), false, Address::SHC_3BB0A8C1_0x004F8530,
            &TileMapState::countPropertyInSurroundingTiles)
        countPropertyInSurroundingTiles;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F85B0,
            &TileMapState::meth_0x4f85b0)
        meth_0x4f85b0;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F8640,
            &TileMapState::meth_0x4f8640)
        meth_0x4f8640;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F86D0,
            &TileMapState::meth_0x4f86d0)
        meth_0x4f86d0;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F8780,
            &TileMapState::meth_0x4f8780)
        meth_0x4f8780;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F8840,
            &TileMapState::meth_0x4f8840)
        meth_0x4f8840;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F8900,
            &TileMapState::meth_0x4f8900)
        meth_0x4f8900;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F89C0,
            &TileMapState::meth_0x4f89c0)
        meth_0x4f89c0;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F8A40,
            &TileMapState::meth_0x4f8a40)
        meth_0x4f8a40;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F8AC0,
            &TileMapState::meth_0x4f8ac0)
        meth_0x4f8ac0;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x004F8B50,
            &TileMapState::getOrientationThatIsWallTowerOrGatehouse)
        getOrientationThatIsWallTowerOrGatehouse;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, uint, uint, undefined4), false,
            Address::SHC_3BB0A8C1_0x004F8BD0, &TileMapState::previewWallDrawingUnk)
        previewWallDrawingUnk;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F9000, &TileMapState::meth_0x4f9000)
        meth_0x4f9000;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F9220, &TileMapState::swapWallOwnership)
        swapWallOwnership;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F93E0, &TileMapState::destroyWallsOfPlayer)
        destroyWallsOfPlayer;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004F94A0, &TileMapState::isWallUnkPlacementAllowed)
        isWallUnkPlacementAllowed;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004F9590,
            &TileMapState::setupBuildingSizeIndexMappingForBuildingWithSize)
        setupBuildingSizeIndexMappingForBuildingWithSize;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F9880,
            &TileMapState::getBuildingSizeIndexMappingData)
        getBuildingSizeIndexMappingData;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F9930,
            &TileMapState::indexIsEdgeUnk)
        indexIsEdgeUnk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, int), false, Address::SHC_3BB0A8C1_0x004F9980,
            &TileMapState::storeMinAndMaxHeightOfArea)
        storeMinAndMaxHeightOfArea;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(int, int, CommandBuildingTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x004F9A60, &TileMapState::isBuildingPlacementAllowedAtTile)
        isBuildingPlacementAllowedAtTile;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F9DF0,
            &TileMapState::meth_0x4f9df0)
        meth_0x4f9df0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(undefined4, int), false, Address::SHC_3BB0A8C1_0x004F9F00,
            &TileMapState::spawnEraserEntityEffectsUnk)
        spawnEraserEntityEffectsUnk;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FA000, &TileMapState::meth_0x4fa000)
        meth_0x4fa000;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FA2D0,
            &TileMapState::checkDrawbridgePlacement)
        checkDrawbridgePlacement;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FA460, &TileMapState::meth_0x4fa460)
        meth_0x4fa460;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x004FA550, &TileMapState::getBuildingSizeForCommandBuildingType)
        getBuildingSizeForCommandBuildingType;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(undefined4, int, int, undefined4, int), false,
            Address::SHC_3BB0A8C1_0x004FA760, &TileMapState::meth_0x4fa760)
        meth_0x4fa760;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FA9D0,
            &TileMapState::meth_0x4fa9d0)
        meth_0x4fa9d0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FAA30,
            &TileMapState::updateAreaBasedOnSurrounding)
        updateAreaBasedOnSurrounding;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FAAB0, &TileMapState::meth_0x4faab0)
        meth_0x4faab0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FAB70,
            &TileMapState::meth_0x4fab70)
        meth_0x4fab70;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FAC70,
            &TileMapState::meth_0x4fac70)
        meth_0x4fac70;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FAD20,
            &TileMapState::meth_0x4fad20)
        meth_0x4fad20;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FAD70,
            &TileMapState::meth_0x4fad70)
        meth_0x4fad70;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FAE50, &TileMapState::meth_0x4fae50)
        meth_0x4fae50;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FAEE0, &TileMapState::meth_0x4faee0)
        meth_0x4faee0;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FAF70, &TileMapState::meth_0x4faf70)
        meth_0x4faf70;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FB0C0, &TileMapState::meth_0x4fb0c0)
        meth_0x4fb0c0;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FB360, &TileMapState::meth_0x4fb360)
        meth_0x4fb360;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FB3F0, &TileMapState::FUN_004fb3f0)
        FUN_004fb3f0;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(uint, uint, uint), false, Address::SHC_3BB0A8C1_0x004FB4D0, &TileMapState::placeRock)
        placeRock;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FB770, &TileMapState::meth_0x4fb770)
        meth_0x4fb770;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FB8E0, &TileMapState::meth_0x4fb8e0)
        meth_0x4fb8e0;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FB970, &TileMapState::meth_0x4fb970)
        meth_0x4fb970;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, short), false, Address::SHC_3BB0A8C1_0x004FB9E0,
            &TileMapState::meth_0x4fb9e0)
        meth_0x4fb9e0;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004FBC30,
            &TileMapState::getCastleBuildRangeForMapSize)
        getCastleBuildRangeForMapSize;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int*, int*, int, uint), false,
            Address::SHC_3BB0A8C1_0x004FBD80, &TileMapState::getTileForBrush)
        getTileForBrush;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x004FBE70,
            &TileMapState::meth_0x4fbe70)
        meth_0x4fbe70;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FC0B0,
            &TileMapState::meth_0x4fc0b0)
        meth_0x4fc0b0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004FC280,
            &TileMapState::meth_0x4fc280)
        meth_0x4fc280;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004FC340, &TileMapState::meth_0x4fc340)
        meth_0x4fc340;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004FC490, &TileMapState::generateDustClouds)
        generateDustClouds;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(uint), false, Address::SHC_3BB0A8C1_0x004FC650, &TileMapState::meth_0x4fc650)
        meth_0x4fc650;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, undefined4, int), false,
            Address::SHC_3BB0A8C1_0x004FC7C0, &TileMapState::meth_0x4fc7c0)
        meth_0x4fc7c0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x004FC810,
            &TileMapState::meth_0x4fc810)
        meth_0x4fc810;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004FC9E0, &TileMapState::updateGFXLayers)
        updateGFXLayers;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, int), false, Address::SHC_3BB0A8C1_0x004FDB00,
            &TileMapState::updateMacroLayerRelated)
        updateMacroLayerRelated;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004FF080, &TileMapState::updateMacroLayerRelated2)
        updateMacroLayerRelated2;

        MACRO_FUNCTION_RESOLVER(byte (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FF870,
            &TileMapState::setBitFlagBasedOnWallTowerGatehouseOrKeep)
        setBitFlagBasedOnWallTowerGatehouseOrKeep;

        MACRO_FUNCTION_RESOLVER(
            uint (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FF990, &TileMapState::returnSomeHeight)
        returnSomeHeight;

        MACRO_FUNCTION_RESOLVER(
            uint (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x004FFB10, &TileMapState::getTotalHeightAtTile)
        getTotalHeightAtTile;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FFBA0, &TileMapState::getTotalHeightAt)
        getTotalHeightAt;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004FFF10,
            &TileMapState::getHeightAtTileIncludingOwnersBuildings)
        getHeightAtTileIncludingOwnersBuildings;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005000A0, &TileMapState::recountTotalOwnedMoats)
        recountTotalOwnedMoats;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005000E0,
            &TileMapState::scanMoatsInGroupsOfThreeUnk)
        scanMoatsInGroupsOfThreeUnk;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00500180, &TileMapState::countUnfinishedMoatUnk)
        countUnfinishedMoatUnk;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00500210, &TileMapState::getUnownedMoatCount)
        getUnownedMoatCount;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00500250, &TileMapState::returnOwnedMoatAtTile)
        returnOwnedMoatAtTile;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(uint), false, Address::SHC_3BB0A8C1_0x005002D0, &TileMapState::clearMoatFromMemory)
        clearMoatFromMemory;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00500310, &TileMapState::clearMoat)
        clearMoat;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x00500370,
            &TileMapState::findTileInSameAreaAndNoTooHeightDifference)
        findTileInSameAreaAndNoTooHeightDifference;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(int, int, uint, uint), false, Address::SHC_3BB0A8C1_0x005003D0,
            &TileMapState::setXYBasedOnMoatID)
        setXYBasedOnMoatID;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00500500, &TileMapState::meth_0x500500)
        meth_0x500500;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x005005F0, &TileMapState::clearMoatIfUnk)
        clearMoatIfUnk;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00500640, &TileMapState::moatRelatedUpdateFunction)
        moatRelatedUpdateFunction;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00500680, &TileMapState::meth_0x500680)
        meth_0x500680;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005006C0, &TileMapState::meth_0x5006c0)
        meth_0x5006c0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00500720,
            &TileMapState::meth_0x500720)
        meth_0x500720;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, undefined4), false, Address::SHC_3BB0A8C1_0x00500750,
            &TileMapState::meth_0x500750)
        meth_0x500750;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00500790, &TileMapState::swapMoatOwnership)
        swapMoatOwnership;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005007D0, &TileMapState::meth_0x5007d0)
        meth_0x5007d0;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00500800,
            &TileMapState::countPitchDitchesWithPlayerID0)
        countPitchDitchesWithPlayerID0;

        MACRO_FUNCTION_RESOLVER(
            int (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00500850, &TileMapState::getPitchDitchIDForTile)
        getPitchDitchIDForTile;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00500890, &TileMapState::destroyPitchDitch)
        destroyPitchDitch;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00500940,
            &TileMapState::swapPitchOwnership)
        swapPitchOwnership;

        MACRO_FUNCTION_RESOLVER(undefined4 (TileMapState::*)(uint, uint, uint, uint), false,
            Address::SHC_3BB0A8C1_0x00500980, &TileMapState::meth_0x500980)
        meth_0x500980;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(int, int, uint), false, Address::SHC_3BB0A8C1_0x00500B50,
            &TileMapState::meth_0x500b50)
        meth_0x500b50;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00500BB0, &TileMapState::campaignRelatedNumber)
        campaignRelatedNumber;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x00501180,
            &TileMapState::spreadAlgorithmForFlagsAndBraziers2Unk)
        spreadAlgorithmForFlagsAndBraziers2Unk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x005011A0,
            &TileMapState::spreadAlgorithmForFlagsAndBraziersUnk)
        spreadAlgorithmForFlagsAndBraziersUnk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005017A0,
            &TileMapState::clearAndSetTileMapUnknown2Plus)
        clearAndSetTileMapUnknown2Plus;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, int), false, Address::SHC_3BB0A8C1_0x005017C0,
            &TileMapState::meth_0x5017c0)
        meth_0x5017c0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x004F79D0,
            &TileMapState::updateShowHiLayerOrResetChangedLayer)
        updateShowHiLayerOrResetChangedLayer;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00501B90,
            &TileMapState::changeMapOrientationUnk)
        changeMapOrientationUnk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x00501CD0,
            &TileMapState::increaseHeightForTunnelWithBrush)
        increaseHeightForTunnelWithBrush;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, int), false, Address::SHC_3BB0A8C1_0x00501D90,
            &TileMapState::raiseLand)
        raiseLand;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, int, int), false, Address::SHC_3BB0A8C1_0x00501F50,
            &TileMapState::createPlateau)
        createPlateau;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x00502110, &TileMapState::useBrush2)
        useBrush2;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x00502390, &TileMapState::setLand)
        setLand;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, uint, int), false, Address::SHC_3BB0A8C1_0x005024F0,
            &TileMapState::meth_0x5024f0)
        meth_0x5024f0;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4), false,
            Address::SHC_3BB0A8C1_0x00502680, &TileMapState::useBrush3)
        useBrush3;

        MACRO_FUNCTION_RESOLVER(
            byte (TileMapState::*)(int, uint), false, Address::SHC_3BB0A8C1_0x00502950, &TileMapState::meth_0x502950)
        meth_0x502950;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, uint, uint, undefined4), false,
            Address::SHC_3BB0A8C1_0x005029D0, &TileMapState::checkWhetherThisWallBuildIsAllowed)
        checkWhetherThisWallBuildIsAllowed;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, uint, uint, CommandBuildingTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x00502F30, &TileMapState::placeWalls)
        placeWalls;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x005034A0, &TileMapState::placeDefensiveStructurePart2Unk)
        placeDefensiveStructurePart2Unk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00503720,
            &TileMapState::setupBuildingSizeIndexMapping)
        setupBuildingSizeIndexMapping;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, CommandBuildingTypeShort, int), false,
            Address::SHC_3BB0A8C1_0x005037B0, &TileMapState::checkBuildingCanBePlacedHere)
        checkBuildingCanBePlacedHere;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x00504A30,
            &TileMapState::meth_0x504a30)
        meth_0x504a30;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00504EE0, &TileMapState::meth_0x504ee0)
        meth_0x504ee0;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(int, int, CommandBuildingTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x00504F10, &TileMapState::setConstructionGFXLayerBasedOnPlacementChecks)
        setConstructionGFXLayerBasedOnPlacementChecks;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00506370,
            &TileMapState::updateBuildingGraphicsLayer)
        updateBuildingGraphicsLayer;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00506AD0,
            &TileMapState::someUpdatePathLinkageRelatedCall)
        someUpdatePathLinkageRelatedCall;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, BuildingTypeInt, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00506BD0, &TileMapState::placeWorkshopOrHovel)
        placeWorkshopOrHovel;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00506D40, &TileMapState::placeSiegetowerPlaced)
        placeSiegetowerPlaced;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00506E10, &TileMapState::placeSiegeTentUnk)
        placeSiegeTentUnk;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, uint, uint, undefined4, undefined4, uint, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x00506F40, &TileMapState::placePositiveFearfactor)
        placePositiveFearfactor;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, uint, uint, undefined4, undefined4, uint, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507060, &TileMapState::meth_0x507060)
        meth_0x507060;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507130, &TileMapState::placeTower)
        placeTower;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00507280, &TileMapState::upgradeTowerLogicLayer)
        upgradeTowerLogicLayer;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00507350, &TileMapState::meth_0x507350)
        meth_0x507350;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507420, &TileMapState::placeGatehouseSmall)
        placeGatehouseSmall;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507560, &TileMapState::placeGatehouseLarge)
        placeGatehouseLarge;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, int*, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x005076A0, &TileMapState::placeBarracks)
        placeBarracks;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int*, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507BD0, &TileMapState::placeEngineersguild)
        placeEngineersguild;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int*, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00507E00, &TileMapState::placeTunnelersguild)
        placeTunnelersguild;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00508030, &TileMapState::placeOilsmelter)
        placeOilsmelter;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, uint), false,
            Address::SHC_3BB0A8C1_0x00508250, &TileMapState::placeQuarry)
        placeQuarry;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, int, undefined4, undefined4, int, int), false,
            Address::SHC_3BB0A8C1_0x00508540, &TileMapState::placeStockpile)
        placeStockpile;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00508760, &TileMapState::meth_0x508760)
        meth_0x508760;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00508870, &TileMapState::meth_0x508870)
        meth_0x508870;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00508910, &TileMapState::meth_0x508910)
        meth_0x508910;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, CommandBuildingTypeInt), false,
            Address::SHC_3BB0A8C1_0x00508A00, &TileMapState::renderPreviewMapperWithBrush)
        renderPreviewMapperWithBrush;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int), false, Address::SHC_3BB0A8C1_0x00508DD0,
            &TileMapState::applyTreeToLogicalLayer)
        applyTreeToLogicalLayer;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, uint), false, Address::SHC_3BB0A8C1_0x00508EC0,
            &TileMapState::meth_0x508ec0)
        meth_0x508ec0;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00509180, &TileMapState::updateTextureTilemap)
        updateTextureTilemap;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00511020, &TileMapState::updateMacroLayer)
        updateMacroLayer;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(undefined4, uint, uint, int), false,
            Address::SHC_3BB0A8C1_0x005110B0, &TileMapState::createMoat)
        createMoat;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x005111D0,
            &TileMapState::findNearestFriendlyMoatTileForDigging)
        findNearestFriendlyMoatTileForDigging;

        MACRO_FUNCTION_RESOLVER(
            undefined4 (TileMapState::*)(uint), false, Address::SHC_3BB0A8C1_0x005113F0, &TileMapState::removeMoat)
        removeMoat;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005114C0, &TileMapState::updatePitchDitches)
        updatePitchDitches;

        MACRO_FUNCTION_RESOLVER(int (TileMapState::*)(undefined4, uint, uint), false, Address::SHC_3BB0A8C1_0x005116E0,
            &TileMapState::placePitchDitch)
        placePitchDitch;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00511850, &TileMapState::updateGameRelatedValue)
        updateGameRelatedValue;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
            Address::SHC_3BB0A8C1_0x00511D70, &TileMapState::upgradeMapFormatLogicLayer)
        upgradeMapFormatLogicLayer;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00511DF0, &TileMapState::setupTileMapSections)
        setupTileMapSections;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00512100, &TileMapState::setupAllMapSections)
        setupAllMapSections;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00512450, &TileMapState::prepareMap)
        prepareMap;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x005127B0,
            &TileMapState::resetAreaBasedOnLogicalLayer)
        resetAreaBasedOnLogicalLayer;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(), false, Address::SHC_3BB0A8C1_0x00512920,
            &TileMapState::processMapOrientationChange)
        processMapOrientationChange;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, int, uint, uint, Logic1Int, Logic2Int), false,
            Address::SHC_3BB0A8C1_0x00512940, &TileMapState::setTerrain)
        setTerrain;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(undefined4, int, uint), false, Address::SHC_3BB0A8C1_0x00514480,
            &TileMapState::placeMoat)
        placeMoat;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x00514520, &TileMapState::placeKillingPit)
        placeKillingPit;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, BuildingTypeInt, uint, int, int), false,
            Address::SHC_3BB0A8C1_0x005146D0, &TileMapState::placeKeep)
        placeKeep;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, uint, int*, undefined4), false,
            Address::SHC_3BB0A8C1_0x00514DE0, &TileMapState::placeDrawbridge)
        placeDrawbridge;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, undefined4, int, undefined4), false,
            Address::SHC_3BB0A8C1_0x00514F30, &TileMapState::placeWheatfarm)
        placeWheatfarm;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, undefined4, int, int), false,
            Address::SHC_3BB0A8C1_0x005151C0, &TileMapState::placeHopfarm)
        placeHopfarm;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, undefined4, undefined4, int*, undefined4),
            false, Address::SHC_3BB0A8C1_0x005154D0, &TileMapState::placeDairyfarm)
        placeDairyfarm;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, BuildingTypeInt, undefined4, int, int*), false,
            Address::SHC_3BB0A8C1_0x00515740, &TileMapState::placeApplefarm)
        placeApplefarm;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00515A20,
            &TileMapState::clearBuildingFromTerrain)
        clearBuildingFromTerrain;

        MACRO_FUNCTION_RESOLVER(
            void (TileMapState::*)(int), false, Address::SHC_3BB0A8C1_0x00515C80, &TileMapState::createMoatSize5Unk)
        createMoatSize5Unk;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(uint, uint, undefined4), false, Address::SHC_3BB0A8C1_0x00515DA0,
            &TileMapState::placeTree)
        placeTree;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (TileMapState::*)(int, uint, uint, CommandBuildingTypeInt, int), false,
            Address::SHC_3BB0A8C1_0x005160C0, &TileMapState::prepareAreaForBuildingPlacement)
        prepareAreaForBuildingPlacement;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(PlayerID, int, int, CommandBuildingTypeInt, int, int), false,
            Address::SHC_3BB0A8C1_0x005162D0, &TileMapState::placeBuilding)
        placeBuilding;

        MACRO_FUNCTION_RESOLVER(uint (TileMapState::*)(int, uint, uint, int, int, int, BOOLEnum, int), false,
            Address::SHC_3BB0A8C1_0x00516B80, &TileMapState::processDamageToBuilding)
        processDamageToBuilding;

        MACRO_FUNCTION_RESOLVER(void (TileMapState::*)(int, uint, uint, int, int, undefined4, int), false,
            Address::SHC_3BB0A8C1_0x00517790, &TileMapState::processEntityDamageToBuildingCollateral)
        processEntityDamageToBuildingCollateral;

    } // namespace TileMapState_Func
} // namespace Map
} // namespace OpenSHC
