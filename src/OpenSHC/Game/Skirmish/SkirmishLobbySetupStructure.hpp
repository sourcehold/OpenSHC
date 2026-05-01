/**
  AUTO_GENERATED: DO NOT TOUCH THIS FILE
  path: 'OpenSHC/Game/Skirmish/SkirmishLobbySetupStructure.hpp'
*/

#pragma once

namespace OpenSHC {
namespace Game {
    namespace Skirmish {

#pragma pack(push, 1)

        // SIZE: 0x00000108
        class SkirmishLobbySetupStructure {
        public:
            dword mapu4int2; // 0x00000000 length: 4
            dword mbr_0x4; // 0x00000004 length: 4
            char mapName[80]; // 0x00000008 length: 80
            byte roundTableOrderArray[9]; // 0x00000058 length: 9
            byte playerGroupArray[9]; // 0x00000061 length: 9
            byte slot1Position; // 0x0000006A length: 1
            byte slot2Position; // 0x0000006B length: 1
            byte slot3Position; // 0x0000006C length: 1
            byte slot4Position; // 0x0000006D length: 1
            byte slot5Position; // 0x0000006E length: 1
            byte slot6Position; // 0x0000006F length: 1
            byte slot7Position; // 0x00000070 length: 1
            byte slot8Position; // 0x00000071 length: 1
            undefined1 padding_0x72[2]; // 0x00000072 length: 2
            int currentPlayerSlotID; // 0x00000074 length: 4
            int currentAdvantageBalance; // 0x00000078 length: 4
            int currentAdvantageGroup; // 0x0000007C length: 4
            dword mbr_0x80; // 0x00000080 length: 4
            int currentAIArray[9]; // 0x00000084 length: 36
            int aiVariationArray[9]; // 0x000000A8 length: 36
            int playerLordTypeArray[9]; // 0x000000CC length: 36
            dword mbr_0xf0; // 0x000000F0 length: 4
            dword selectedLordType; // 0x000000F4 length: 4
            dword popularity; // 0x000000F8 length: 4
            dword mbr_0xfc; // 0x000000FC length: 4
            dword mapSelectionScrollOffset; // 0x00000100 length: 4
            dword mapSelectionRelativeSelected; // 0x00000104 length: 4

        private:
            SkirmishLobbySetupStructure(SkirmishLobbySetupStructure const&);
            void operator=(SkirmishLobbySetupStructure const&);

            SkirmishLobbySetupStructure();
            ~SkirmishLobbySetupStructure();

        public:
            void commitSkirmishSettings();

            void restoreSkirmishLobbySetup();
        };

        static_assert_cpp98_obj(sizeof(SkirmishLobbySetupStructure) == 264, SkirmishLobbySetupStructure);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(SkirmishLobbySetupStructure, false, Address::SHC_3BB0A8C1_0x00DF4118)
        pDAT_SkirmishLobbySetupStructure;

    } // namespace Skirmish
} // namespace Game
} // namespace OpenSHC
