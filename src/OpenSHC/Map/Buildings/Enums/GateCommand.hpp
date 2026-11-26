/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Map/Buildings/Enums/GateCommand.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Map {
    namespace Buildings {
        namespace Enums {
            typedef enum GateCommand {

                GC_CLOSE = 10, // 0x0000000A
                GC_OPEN = 11, // 0x0000000B
                GC_NONE = 12 // 0x0000000C

            } GateCommand;

            static_assert_cpp98_obj(sizeof(GateCommand) == 4, GateCommand);
        } // namespace Enums
    } // namespace Buildings
} // namespace Map
} // namespace OpenSHC
