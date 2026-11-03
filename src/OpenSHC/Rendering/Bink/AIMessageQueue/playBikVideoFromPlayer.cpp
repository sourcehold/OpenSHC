#include "../../../Rendering.func.hpp"

#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        using DE::SHCDE::eTextSections;

        // FUNCTION: STRONGHOLDCRUSADER 0x004BEA90
        void AIMessageQueue::playBikVideoFromPlayer(int playerIndex, int aiType, int messageType)
        {
            if (aiType < 1 || aiType > 16 || messageType < 1 || messageType > 33) {
                return;
            }
            // zero-based from here on: a separate local for it costs the match
            messageType = messageType - 1;
            // The header has no arrays here yet: the speech tables are char*[33][17] (message, AI type) at 0x184
            // and 0xa64, and the greeting sounds are char*[17] (AI type) at 0x12c.
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)(
                "", "", (char*)(&DAT_MissionAestheticsDefinedData::instance.field75_0x12c)[aiType], playerIndex);
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_HOT_KEYS, aiType * 34 + messageType - 33),
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field661_0xa64)[messageType * 17 + aiType],
                (char*)(&DAT_MissionAestheticsDefinedData::instance.field93_0x184)[messageType * 17 + aiType],
                -playerIndex);
        }

    }
}
}
