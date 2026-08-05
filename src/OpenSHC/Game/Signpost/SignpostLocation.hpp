/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Signpost/SignpostLocation.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Signpost {

#pragma pack(push, 1)
        // SIZE: 0x00000010
        typedef struct SignpostLocation {

            int x; // 0x00000000 length: 4
            int y; // 0x00000004 length: 4
            int tile; // 0x00000008 length: 4
            int unknown; // 0x0000000C length: 4

        } SignpostLocation;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(SignpostLocation) == 16, SignpostLocation);
    } // namespace Signpost
} // namespace Game
} // namespace OpenSHC
