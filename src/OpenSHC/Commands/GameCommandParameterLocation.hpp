/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Commands/GameCommandParameterLocation.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Commands {
    typedef enum GameCommandParameterLocation {

        GCPL_FIXED_COMMAND_DATA_ADDRESS = 0, // 0x00000000
        GCPL_DYNAMIC_COMMAND_DATA_ADDRESS = 1 // 0x00000001

    } GameCommandParameterLocation;

    static_assert_cpp98_obj(sizeof(GameCommandParameterLocation) == 4, GameCommandParameterLocation);
} // namespace Commands
} // namespace OpenSHC
