/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/LandscapeState.hpp'
*/

#pragma once

#include "OpenSHC/IO/PackagedFileMagicNumInt.hpp"
#include "OpenSHC/Map/Rocks/Rock.hpp"
#include "OpenSHC/Map/Trees/Tree.hpp"
#include "OpenSHC/Map/Trees/TreeTypeInt.hpp"
#include "OpenSHC/Map/WindState.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
#include "WinDef.h"

namespace OpenSHC {
namespace Map {

    using OpenSHC::IO::PackagedFileMagicNumInt;
    using OpenSHC::Map::WindState;
    using OpenSHC::Map::Rocks::Rock;
    using OpenSHC::Map::Trees::Tree;
    using OpenSHC::Map::Trees::TreeTypeInt;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

    // SIZE: 0x0006B700
    class LandscapeState {
    public:
        undefined4 field0_0x0; // 0x00000000 length: 4
        undefined4 field1_0x4; // 0x00000004 length: 4
        undefined4 DAT_TotalOrganisms; // 0x00000008 length: 4
        int field3_0xc; // 0x0000000C length: 4
        int maxTreeCount; // 0x00000010 length: 4
        undefined4 x; // 0x00000014 length: 4
        undefined4 y; // 0x00000018 length: 4
        Tree trees[2000]; // 0x0000001C length: 312000
        WindState wind; // 0x0004C2DC length: 28
        Rock SEC_RockArray1038[4000]; // 0x0004C2F8 length: 128000
        DWORD creationTime; // 0x0006B6F8 length: 4
        undefined1 padding_0x6b6fc[4]; // 0x0006B6FC length: 4

    private:
        LandscapeState(LandscapeState const&);
        void operator=(LandscapeState const&);

        LandscapeState();
        ~LandscapeState();

    public:
        // Constructor
        LandscapeState* Constructor_LandscapeState();

        undefined4 mapUITreeTypeToLogicalTreeTypeUnk(undefined4 param_1);

        undefined4 getValueFrom0UpTo3ForTreeTypeAndTreeSeason(undefined4 treeType, int treeStage);

        void clearRocksAndTrees();

        int createTree(undefined4 x, undefined4 y, TreeTypeInt treeType, undefined4 size, int stageRelatedValue,
            undefined4 param_6, int stage);

        void setTreeStageRelatedValues(int treeID, int stage);

        void removeTreeUnk(int treeID);

        void setCurrentTimeOnSomeTrees();

        int createRock(undefined4 x, undefined4 y, int rockType, undefined4 size, undefined4 orientation);

        void meth_0x4f2220(int param_1);

        BOOLEnum lightUpTree(int tile, int playerID);

        int FUN_004f2a10(int param_1);

        undefined4 FUN_004f2c20(int param_1);

        void setTreeSpreadInterval();

        void killEveryFifthTree();

        undefined4 setupBabyTreeLocation(uint treeID, int treeType, uint x, uint y);

        uint meth_0x4f2fb0(int treeID, int param_2);

        BOOLEnum isTreeMatchingUIDAndOfCertainState(int treeID, int treeUID);

        undefined4 meth_0x4f3010(int treeID, undefined4 param_2, int param_3);

        void meth_0x4f3080(int treeID, int param_2);

        void meth_0x4f30d0(int x, int y);

        void spawnACrowUnk(int unitID);

        void placeAppleTree(int buildingID, undefined4 treeX, undefined4 treeY);

        int selectClosestTree(int xPosition, int yPosition, int param_3);

        void resetWind();

        void updateWind();

        void updateTreeStage(uint treeID, uint rng);

        int findTree(int playerID, uint unitXPosition, uint unitYPosition);

        void FUN_004f3d30(PackagedFileMagicNumInt receivedMapVersion, PackagedFileMagicNumInt packagerMapVersion);

        void updateTrees();
    };

    static_assert_cpp98_obj(sizeof(LandscapeState) == 440064, LandscapeState);

#pragma pack(pop)

    MACRO_STRUCT_RESOLVER(LandscapeState, false, Address::SHC_3BB0A8C1_0x00F2CC38) pDAT_LandscapeState;

} // namespace Map
} // namespace OpenSHC
