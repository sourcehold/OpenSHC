/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Commands/GameCommand.hpp'
*/

#pragma once

#include "OpenSHC/Commands/GameCommandStateByte.hpp"

namespace OpenSHC {
namespace Commands {

    using OpenSHC::Commands::GameCommandStateByte;

#pragma pack(push, 1)
    // SIZE: 0x000004F8
    typedef struct GameCommand {

        dword time; // 0x00000000 length: 4
        int playerUnk; // 0x00000004 length: 4
        char commandType; // 0x00000008 length: 1
        GameCommandStateByte stateUnk; // 0x00000009 length: 1
        undefined1 parameters; // 0x0000000A length: 1
        undefined1 padding_0xb[1261]; // 0x0000000B length: 1261

    } GameCommand;
#pragma pack(pop)

    static_assert_cpp98_obj(sizeof(GameCommand) == 1272, GameCommand);
} // namespace Commands
} // namespace OpenSHC
