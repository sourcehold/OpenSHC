/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/State/MapAndTimeSubStateUnk.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace State {

#pragma pack(push, 1)
        // SIZE: 0x000038E6
        typedef struct MapAndTimeSubStateUnk {

            undefined1 padding_0x0[4]; // 0x00000000 length: 4
            int field4_0x4; // 0x00000004 length: 4
            undefined1 padding_0x8[380]; // 0x00000008 length: 380
            int cathedralRelated1; // 0x00000184 length: 4
            undefined1 padding_0x188[14174]; // 0x00000188 length: 14174

        } MapAndTimeSubStateUnk;
#pragma pack(pop)

        static_assert_cpp98_obj(sizeof(MapAndTimeSubStateUnk) == 14566, MapAndTimeSubStateUnk);
    } // namespace State
} // namespace Game
} // namespace OpenSHC
