/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Rendering/Bink/AIMessageQueue.hpp'
*/

#pragma once

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

#pragma pack(push, 1)

        // SIZE: 0x00000930
        class AIMessageQueue {
        public:
            BOOLEnum messagePlaying_0x0; // 0x00000000 length: 4
            dword currentMessageUnknownValue_0x4; // 0x00000004 length: 4
            char* currentMessageText_0x8; // 0x00000008 length: 4
            char currentMessageVfxFile_0xc[100]; // 0x0000000C length: 100
            char currentMessageSfxFile_0x70[100]; // 0x00000070 length: 100
            dword currentMessageUnknownValue2_0xd4; // 0x000000D4 length: 4
            dword videoStartTimeUnk_0xd8; // 0x000000D8 length: 4
            char* savedMessageTextPtr_0xdc[10]; // 0x000000DC length: 40
            int savedMessageUnknownValue_0x104[10]; // 0x00000104 length: 40
            char savedMessageVfxFile_0x12c[10][100]; // 0x0000012C length: 1000
            char savedMessageSfxFile_0x514[10][100]; // 0x00000514 length: 1000
            int savedMessageUnknownValue2_0x8fc[10]; // 0x000008FC length: 40
            int storedMessages_0x924; // 0x00000924 length: 4
            dword mbr_0x928; // 0x00000928 length: 4
            dword mbr_0x92c; // 0x0000092C length: 4

        private:
            AIMessageQueue(AIMessageQueue const&);
            void operator=(AIMessageQueue const&);

            AIMessageQueue();
            ~AIMessageQueue();

        public:
            void playVideoOverMap(char* binkFileName, char* sfxFileName);

            void playAiLordMessage(int param_1, int param_2);

            void playEventVideoBik(char* eventText, char* eventVideoBik, char* eventWavFile);

            void prepareSFXandVFX(char* messageText, char* messageVfxFile, char* messageSfxFile, int param_4);

            BOOLEnum playNextStoredAIMessage();

            void playBikVideoFromPlayer(int playerIndex, int aiType, int messageType);

            void playNextStoredBinkVideo();
        };

        static_assert_cpp98_obj(sizeof(AIMessageQueue) == 2352, AIMessageQueue);

#pragma pack(pop)

        MACRO_STRUCT_RESOLVER(AIMessageQueue, false, Address::SHC_3BB0A8C1_0x00EE10A0) pDAT_AIMessageQueue;

    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
