#include "../AIMessageQueue.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/AI/AITypeA.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace Rendering {
    namespace Bink {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BEA90
        void AIMessageQueue::playBikVideoFromPlayer(int playerIndex, int aiType, int messageType)
        {
            if (aiType < AI::AITA_RAT || aiType > AI::AITA_ABBOT || messageType < 1 || messageType > 33) {
                return;
            }
            // zero-based from here on (the original decrements the parameter itself)
            --messageType;
            // "" (both text arguments)
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)((char*)s__005a5339,
                (char*)s__005a5339, DAT_MissionAestheticsDefinedData::instance.field75_0x12c[aiType], playerIndex);
            MACRO_CALL_MEMBER(Rendering::Bink::AIMessageQueue_Func::prepareSFXandVFX, this)(
                MACRO_CALL_MEMBER(Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    DE::SHCDE::TEXT_HOT_KEYS, aiType * 34 + messageType - 33),
                DAT_MissionAestheticsDefinedData::instance.field85_0xa64[messageType][aiType],
                DAT_MissionAestheticsDefinedData::instance.field77_0x184[messageType][aiType], -playerIndex);
        }

    }
}
}
