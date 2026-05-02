/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Game/Skirmish/SkirmishLobbySetupStructureLongName.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)
        // SIZE: 0x000004A0
        typedef struct SkirmishLobbySetupStructureLongName {

            dword mapu4int2; // 0x00000000 length: 4
            dword mbr_0x4; // 0x00000004 length: 4
            char mapName[1000]; // 0x00000008 length: 1000
            byte roundTableOrderArray[9]; // 0x000003F0 length: 9
            byte playerGroupArray[9]; // 0x000003F9 length: 9
            byte slot1Position; // 0x00000402 length: 1
            byte slot2Position; // 0x00000403 length: 1
            byte slot3Position; // 0x00000404 length: 1
            byte slot4Position; // 0x00000405 length: 1
            byte slot5Position; // 0x00000406 length: 1
            byte slot6Position; // 0x00000407 length: 1
            byte slot7Position; // 0x00000408 length: 1
            byte slot8Position; // 0x00000409 length: 1
            undefined1 padding_0x40a[2]; // 0x0000040A length: 2
            int currentPlayerSlotID; // 0x0000040C length: 4
            int currentAdvantageBalance; // 0x00000410 length: 4
            int currentAdvantageGroup; // 0x00000414 length: 4
            dword mbr_0x80; // 0x00000418 length: 4
            int currentAIArray[9]; // 0x0000041C length: 36
            int aiVariationArray[9]; // 0x00000440 length: 36
            int playerLordTypeArray[9]; // 0x00000464 length: 36
            dword mbr_0xf0; // 0x00000488 length: 4
            dword selectedLordType; // 0x0000048C length: 4
            dword popularity; // 0x00000490 length: 4
            dword mbr_0xfc; // 0x00000494 length: 4
            dword mapSelectionScrollOffset; // 0x00000498 length: 4
            dword mapSelectionRelativeSelected; // 0x0000049C length: 4

        } SkirmishLobbySetupStructureLongName;
#pragma pack(pop)

        static_assert_cpp98_obj(
            sizeof(SkirmishLobbySetupStructureLongName) == 1184, SkirmishLobbySetupStructureLongName);
    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
