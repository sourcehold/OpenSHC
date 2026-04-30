/**
  path: 'OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp'
*/

#include "OpenSHC/Rendering/Bink/AIMessageQueue.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"
namespace OpenSHC {
namespace Rendering {
    namespace Bink {
        namespace AIMessageQueue_Func {

            using OpenSHC::WindowsHelper::Enums::BOOLEnum;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(char*, char*), false, Address::SHC_3BB0A8C1_0x004B7AF0,
                &AIMessageQueue::playVideoOverMap)
            playVideoOverMap;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(int, int), false, Address::SHC_3BB0A8C1_0x004B7C90,
                &AIMessageQueue::playAiLordMessage)
            playAiLordMessage;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(char*, char*, char*), false,
                Address::SHC_3BB0A8C1_0x004BE7E0, &AIMessageQueue::playEventVideoBik)
            playEventVideoBik;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(char*, char*, char*, int), false,
                Address::SHC_3BB0A8C1_0x004BE8A0, &AIMessageQueue::prepareSFXandVFX)
            prepareSFXandVFX;

            MACRO_FUNCTION_RESOLVER(BOOLEnum (AIMessageQueue::*)(), false, Address::SHC_3BB0A8C1_0x004BE960,
                &AIMessageQueue::playNextStoredAIMessage)
            playNextStoredAIMessage;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(int, int, int), false, Address::SHC_3BB0A8C1_0x004BEA90,
                &AIMessageQueue::playBikVideoFromPlayer)
            playBikVideoFromPlayer;

            MACRO_FUNCTION_RESOLVER(void (AIMessageQueue::*)(), false, Address::SHC_3BB0A8C1_0x004C62A0,
                &AIMessageQueue::playNextStoredBinkVideo)
            playNextStoredBinkVideo;

        } // namespace AIMessageQueue_Func
    } // namespace Bink
} // namespace Rendering
} // namespace OpenSHC
