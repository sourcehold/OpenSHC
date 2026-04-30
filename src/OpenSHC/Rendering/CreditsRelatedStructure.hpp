/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Rendering/CreditsRelatedStructure.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Rendering {

#pragma pack(push, 1)
    // SIZE: 0x00000034
    typedef struct CreditsRelatedStructure {

        int isValid; // 0x00000000 length: 4
        int xSpace; // 0x00000004 length: 4
        int ySpace; // 0x00000008 length: 4
        int someX; // 0x0000000C length: 4
        int someY; // 0x00000010 length: 4
        int field5_0x14; // 0x00000014 length: 4
        int field6_0x18; // 0x00000018 length: 4
        int field7_0x1c; // 0x0000001C length: 4
        int field8_0x20; // 0x00000020 length: 4
        int field9_0x24; // 0x00000024 length: 4
        int field10_0x28; // 0x00000028 length: 4
        int field11_0x2c; // 0x0000002C length: 4
        int flag; // 0x00000030 length: 4

    } CreditsRelatedStructure;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(CreditsRelatedStructure) == 52, CreditsRelatedStructure);
} // namespace Rendering
} // namespace OpenSHC
