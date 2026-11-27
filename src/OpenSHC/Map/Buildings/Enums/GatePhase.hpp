/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/Enums/GatePhase.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace Enums {
            typedef enum GatePhase {

                GP_OPEN = 0, // 0x00000000
                GP_CLOSING = 1, // 0x00000001
                GP_CLOSED = 2, // 0x00000002
                GP_OPENING = 3 // 0x00000003

            } GatePhase;

            static_assert_cpp98_obj(sizeof(GatePhase) == 4, GatePhase);
        } // namespace Enums
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
