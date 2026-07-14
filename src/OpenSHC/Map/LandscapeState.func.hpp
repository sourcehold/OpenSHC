/**
  path: 'OpenSHC/Map/LandscapeState.func.hpp'
*/

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/LandscapeState.hpp"
#include "OpenSHC/Map/Trees/TreeTypeInt.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Map {
    namespace LandscapeState_Func {

        using OpenSHC::IO::PackagedFileMagicNumInt;
        using OpenSHC::Map::Trees::TreeTypeInt;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        MACRO_FUNCTION_RESOLVER(undefined4 (LandscapeState::*)(undefined4), false, Address::SHC_3BB0A8C1_0x004F1A60,
            &LandscapeState::mapTreeBrushIDToLogicalType)
        mapTreeBrushIDToLogicalType;

        MACRO_FUNCTION_RESOLVER(undefined4 (LandscapeState::*)(undefined4, int), false,
            Address::SHC_3BB0A8C1_0x004F1BE0, &LandscapeState::getValueFrom0UpTo3ForTreeTypeAndTreeSeason)
        getValueFrom0UpTo3ForTreeTypeAndTreeSeason;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F1C60, &LandscapeState::clearRocksAndTrees)
        clearRocksAndTrees;

        MACRO_FUNCTION_RESOLVER(
            int (LandscapeState::*)(undefined4, undefined4, TreeTypeInt, undefined4, int, undefined4, int), false,
            Address::SHC_3BB0A8C1_0x004F1CE0, &LandscapeState::createTree)
        createTree;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F2020,
            &LandscapeState::setTreeGrowthStageValues)
        setTreeGrowthStageValues;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(int), false, Address::SHC_3BB0A8C1_0x004F2070, &LandscapeState::removeTree)
        removeTree;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F20E0,
            &LandscapeState::setCurrentTimeOnSomeTrees)
        setCurrentTimeOnSomeTrees;

        MACRO_FUNCTION_RESOLVER(int (LandscapeState::*)(undefined4, undefined4, int, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x004F2140, &LandscapeState::createRock)
        createRock;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(int), false, Address::SHC_3BB0A8C1_0x004F2220, &LandscapeState::removeRock)
        removeRock;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F2280,
            &LandscapeState::lightUpTree)
        lightUpTree;

        MACRO_FUNCTION_RESOLVER(int (LandscapeState::*)(int), false, Address::SHC_3BB0A8C1_0x004F2A10,
            &LandscapeState::getRandomRockGfxOffset)
        getRandomRockGfxOffset;

        MACRO_FUNCTION_RESOLVER(undefined4 (LandscapeState::*)(int), false, Address::SHC_3BB0A8C1_0x004F2C20,
            &LandscapeState::getTreeVisualStage)
        getTreeVisualStage;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F2CC0, &LandscapeState::setTreeSpreadInterval)
        setTreeSpreadInterval;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F2DA0, &LandscapeState::killEveryFifthTree)
        killEveryFifthTree;

        MACRO_FUNCTION_RESOLVER(undefined4 (LandscapeState::*)(uint, int, uint, uint), false,
            Address::SHC_3BB0A8C1_0x004F2E00, &LandscapeState::setupBabyTreeLocation)
        setupBabyTreeLocation;

        MACRO_FUNCTION_RESOLVER(uint (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F2FB0,
            &LandscapeState::isTreeChoppable)
        isTreeChoppable;

        MACRO_FUNCTION_RESOLVER(BOOLEnum (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F2FE0,
            &LandscapeState::isTreeMatchingUIDAndOfCertainState)
        isTreeMatchingUIDAndOfCertainState;

        MACRO_FUNCTION_RESOLVER(undefined4 (LandscapeState::*)(int, undefined4, int), false,
            Address::SHC_3BB0A8C1_0x004F3010, &LandscapeState::chopTreeProgress)
        chopTreeProgress;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F3080,
            &LandscapeState::advanceTreeStumpRemoval)
        advanceTreeStumpRemoval;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(int, int), false, Address::SHC_3BB0A8C1_0x004F30D0,
            &LandscapeState::markTreesNearTile)
        markTreesNearTile;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(int), false, Address::SHC_3BB0A8C1_0x004F3150,
            &LandscapeState::spawnCrowsFromNearbyTrees)
        spawnCrowsFromNearbyTrees;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(int, undefined4, undefined4), false,
            Address::SHC_3BB0A8C1_0x004F3560, &LandscapeState::placeAppleTree)
        placeAppleTree;

        MACRO_FUNCTION_RESOLVER(int (LandscapeState::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004F3610,
            &LandscapeState::selectClosestTree)
        selectClosestTree;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F3700, &LandscapeState::resetWind)
        resetWind;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F3730, &LandscapeState::updateWind)
        updateWind;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(uint, uint), false, Address::SHC_3BB0A8C1_0x004F3960,
            &LandscapeState::updateTreeStage)
        updateTreeStage;

        MACRO_FUNCTION_RESOLVER(int (LandscapeState::*)(int, uint, uint), false, Address::SHC_3BB0A8C1_0x004F3B90,
            &LandscapeState::findTree)
        findTree;

        MACRO_FUNCTION_RESOLVER(void (LandscapeState::*)(PackagedFileMagicNumInt, PackagedFileMagicNumInt), false,
            Address::SHC_3BB0A8C1_0x004F3D30, &LandscapeState::migrateLandscapeForMapVersion)
        migrateLandscapeForMapVersion;

        MACRO_FUNCTION_RESOLVER(
            void (LandscapeState::*)(), false, Address::SHC_3BB0A8C1_0x004F3D60, &LandscapeState::updateTrees)
        updateTrees;

    } // namespace LandscapeState_Func
} // namespace Map
} // namespace OpenSHC
