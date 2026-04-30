/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Skirmish/AttackVector.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct AttackVector {

            int x; // 0x00000000 length: 4
            int y; // 0x00000004 length: 4
            int tribeID; // 0x00000008 length: 4
            int tribeUIDUnk; // 0x0000000C length: 4

        } AttackVector;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(AttackVector) == 16, AttackVector);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
