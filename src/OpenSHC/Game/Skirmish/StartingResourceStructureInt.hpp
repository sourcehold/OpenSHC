/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/StartingResourceStructureInt.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)
        // SIZE: 0x00000064
        typedef struct StartingResourceStructureInt {

            int invalid1; // 0x00000000 length: 4
            int invalid2; // 0x00000004 length: 4
            int wood; // 0x00000008 length: 4
            int hops; // 0x0000000C length: 4
            int stone; // 0x00000010 length: 4
            int partialstone; // 0x00000014 length: 4
            int iron; // 0x00000018 length: 4
            int pitch; // 0x0000001C length: 4
            int partialpitch; // 0x00000020 length: 4
            int wheat; // 0x00000024 length: 4
            int bread; // 0x00000028 length: 4
            int cheese; // 0x0000002C length: 4
            int meat; // 0x00000030 length: 4
            int apple; // 0x00000034 length: 4
            int beer; // 0x00000038 length: 4
            int gold; // 0x0000003C length: 4
            int flour; // 0x00000040 length: 4
            int bows; // 0x00000044 length: 4
            int crossbows; // 0x00000048 length: 4
            int spear; // 0x0000004C length: 4
            int pike; // 0x00000050 length: 4
            int mace; // 0x00000054 length: 4
            int sword; // 0x00000058 length: 4
            int leatherarmor; // 0x0000005C length: 4
            int metalarmor; // 0x00000060 length: 4

        } StartingResourceStructureInt;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(StartingResourceStructureInt) == 100, StartingResourceStructureInt);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
