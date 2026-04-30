/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Map/Trees/Tree.hpp'
*/

#pragma once

#include "OpenSHC/Map/Trees/TreeTypeShort.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Map {
    namespace Trees {

        using OpenSHC::Map::Trees::TreeTypeShort;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)
        // SIZE: 0x0000009C
        typedef struct Tree {

            int animationFrameUnk; // 0x00000000 length: 4
            short treeTypeBasedValue1; // 0x00000004 length: 2
            undefined1 padding_0x6[2]; // 0x00000006 length: 2
            int appleTreeColorVariation; // 0x00000008 length: 4
            short gmOriginX; // 0x0000000C length: 2
            short gmOriginY; // 0x0000000E length: 2
            int treeTypeRelated2; // 0x00000010 length: 4
            dword field8_0x14; // 0x00000014 length: 4
            int zero; // 0x00000018 length: 4
            short animationFrameIndex; // 0x0000001C length: 2
            undefined1 padding_0x1e[26]; // 0x0000001E length: 26
            BOOLEnum flag; // 0x00000038 length: 4
            int animationFrame2Unk; // 0x0000003C length: 4
            undefined1 padding_0x40[4]; // 0x00000040 length: 4
            short state; // 0x00000044 length: 2
            TreeTypeShort treeType; // 0x00000046 length: 2
            undefined1 padding_0x48[4]; // 0x00000048 length: 4
            int uid; // 0x0000004C length: 4
            undefined1 padding_0x50[12]; // 0x00000050 length: 12
            short microX; // 0x0000005C length: 2
            short microY; // 0x0000005E length: 2
            undefined1 padding_0x60[2]; // 0x00000060 length: 2
            ushort xPosition; // 0x00000062 length: 2
            ushort yPosition; // 0x00000064 length: 2
            undefined1 padding_0x66[2]; // 0x00000066 length: 2
            uint tile; // 0x00000068 length: 4
            short size; // 0x0000006C length: 2
            short param_6; // 0x0000006E length: 2
            undefined1 padding_0x70[2]; // 0x00000070 length: 2
            undefined2 stageRelated1; // 0x00000072 length: 2
            undefined2 stageRelated2; // 0x00000074 length: 2
            short zeroUpTo2; // 0x00000076 length: 2
            undefined2 stageRelatedVisual3; // 0x00000078 length: 2
            undefined2 stageRelated4; // 0x0000007A length: 2
            short one; // 0x0000007C length: 2
            undefined1 padding_0x7e[2]; // 0x0000007E length: 2
            int stage; // 0x00000080 length: 4
            int stageTracker; // 0x00000084 length: 4
            int rng1; // 0x00000088 length: 4
            short appleFarmID; // 0x0000008C length: 2
            undefined1 padding_0x8e[2]; // 0x0000008E length: 2
            int appleFarmUID; // 0x00000090 length: 4
            short unknownDistanceRelatedToCrow; // 0x00000094 length: 2
            short rng200till300; // 0x00000096 length: 2
            short field92_0x98; // 0x00000098 length: 2
            short igniterPlayer; // 0x0000009A length: 2

        } Tree;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Tree) == 156, Tree);
    } // namespace Trees
} // namespace Map
} // namespace OpenSHC
