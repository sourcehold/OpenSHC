/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Entities/Entity.hpp'
*/

#pragma once

#include "OpenSHC/Map/Entities/EntityTypeShort.hpp"

namespace OpenSHC {
namespace Map {
    namespace Entities {

        using OpenSHC::Map::Entities::EntityTypeShort;

#pragma pack(push, 1)
        // SIZE: 0x000000E8
        typedef struct Entity {

            int graphicType2; // 0x00000000 length: 4
            short graphicType2RelatedOffset; // 0x00000004 length: 2
            short gmID; // 0x00000006 length: 2
            int colorUnk; // 0x00000008 length: 4
            short x1; // 0x0000000C length: 2
            short y1; // 0x0000000E length: 2
            short unkOne_1; // 0x00000010 length: 2
            short field7_0x12; // 0x00000012 length: 2
            short unknownAnimationFrameRelated; // 0x00000014 length: 2
            short unkThree_1; // 0x00000016 length: 2
            short originX; // 0x00000018 length: 2
            short originY; // 0x0000001A length: 2
            short field12_0x1c; // 0x0000001C length: 2
            short nextEntityOnThisTileByID; // 0x0000001E length: 2
            short imageID; // 0x00000020 length: 2
            byte unused_0x22[6]; // 0x00000022 length: 6
            short logicalState; // 0x00000028 length: 2
            EntityTypeShort entityType; // 0x0000002A length: 2
            short owner; // 0x0000002C length: 2
            byte unused_0x2e[2]; // 0x0000002E length: 2
            int uid; // 0x00000030 length: 4
            int field21_0x34; // 0x00000034 length: 4
            short microX; // 0x00000038 length: 2
            short microY; // 0x0000003A length: 2
            short height; // 0x0000003C length: 2
            short targetX; // 0x0000003E length: 2
            short targetY; // 0x00000040 length: 2
            short targetZ; // 0x00000042 length: 2
            short xPosition; // 0x00000044 length: 2
            short yPosition; // 0x00000046 length: 2
            byte unused_0x48[4]; // 0x00000048 length: 4
            int tile; // 0x0000004C length: 4
            short x_2; // 0x00000050 length: 2
            short y_2; // 0x00000052 length: 2
            short startingHeight_2; // 0x00000054 length: 2
            short height_2; // 0x00000056 length: 2
            short startingHeight; // 0x00000058 length: 2
            short field37_0x5a; // 0x0000005A length: 2
            short field38_0x5c; // 0x0000005C length: 2
            short field39_0x5e; // 0x0000005E length: 2
            short someMicroX; // 0x00000060 length: 2
            short field41_0x62; // 0x00000062 length: 2
            short field42_0x64; // 0x00000064 length: 2
            short someMicroY; // 0x00000066 length: 2
            short field44_0x68; // 0x00000068 length: 2
            short field45_0x6a; // 0x0000006A length: 2
            short someCounter_OR_hitGround; // 0x0000006C length: 2
            short field47_0x6e; // 0x0000006E length: 2
            short field48_0x70; // 0x00000070 length: 2
            short field49_0x72; // 0x00000072 length: 2
            short field50_0x74; // 0x00000074 length: 2
            byte unused_0x76[2]; // 0x00000076 length: 2
            int field52_0x78; // 0x00000078 length: 4
            float vCos; // 0x0000007C length: 4
            float vSin; // 0x00000080 length: 4
            short travelledDistance; // 0x00000084 length: 2
            byte field56_0x86[2]; // 0x00000086 length: 2
            int orientation; // 0x00000088 length: 4
            short field58_0x8c; // 0x0000008C length: 2
            undefined1 padding_0x8e[2]; // 0x0000008E length: 2
            int heightDifference; // 0x00000090 length: 4
            short field62_0x94; // 0x00000094 length: 2
            short velocityUnk; // 0x00000096 length: 2
            float field64_0x98; // 0x00000098 length: 4
            short startingAngle; // 0x0000009C length: 2
            word graphicRotationUnk; // 0x0000009E length: 2
            short unitID; // 0x000000A0 length: 2
            short unitID_OR_seaGullID; // 0x000000A2 length: 2
            undefined1 padding_0xa4[2]; // 0x000000A4 length: 2
            short gmLookupValue; // 0x000000A6 length: 2
            short field72_0xa8; // 0x000000A8 length: 2
            EntityTypeShort entityType2; // 0x000000AA length: 2
            int rng_1; // 0x000000AC length: 4
            short unkMinusOne; // 0x000000B0 length: 2
            short hasDoneEffectUnk; // 0x000000B2 length: 2
            short someTracker; // 0x000000B4 length: 2
            short fireParameter_0xb6; // 0x000000B6 length: 2
            short field79_0xb8; // 0x000000B8 length: 2
            short field80_0xba; // 0x000000BA length: 2
            short rng_2; // 0x000000BC length: 2
            short field82_0xbe; // 0x000000BE length: 2
            short field83_0xc0; // 0x000000C0 length: 2
            byte unused_0xc2[2]; // 0x000000C2 length: 2
            int displayValue; // 0x000000C4 length: 4
            short field86_0xc8; // 0x000000C8 length: 2
            short field87_0xca; // 0x000000CA length: 2
            short field88_0xcc; // 0x000000CC length: 2
            short field89_0xce; // 0x000000CE length: 2
            short field90_0xd0; // 0x000000D0 length: 2
            short unitID_healer; // 0x000000D2 length: 2
            int unitUID; // 0x000000D4 length: 4
            short fireIntensity; // 0x000000D8 length: 2
            short unknownDistanceRelatedValue; // 0x000000DA length: 2
            int uidRef; // 0x000000DC length: 4
            byte unused_0xe0[8]; // 0x000000E0 length: 8

        } Entity;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(Entity) == 232, Entity);
    } // namespace Entities
} // namespace Map
} // namespace OpenSHC
