#include "../DisplayElements.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/DAT_CurrentFramerate.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopDurationBuffer.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TickRateBuffer.hpp"
#include "OpenSHC/Globals/INT_GameLoopTimeDataIndex.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004AF860
    void DisplayElements::RenderDebugNumbersDisplayElement(int posX, int posY, DWORD elementState)
    {
        // Declared first, ahead of the two buffer writes (declared at the wrap test, the sums take other registers).
        int durationSum = 0;
        int tickRateSum = 0;
        dword const lastGameTickRate = DAT_GameCore::instance.gameTicksThisLoop;
        dword const lastGameLoopDuration = DAT_GameLoopStopwatch::instance.duration_0x0;
        DAT_GameLoopDurationBuffer::instance[INT_GameLoopTimeDataIndex::instance] = lastGameLoopDuration;
        DAT_TickRateBuffer::instance[INT_GameLoopTimeDataIndex::instance] = lastGameTickRate;
        ++INT_GameLoopTimeDataIndex::instance;
        if (INT_GameLoopTimeDataIndex::instance == 100) {
            INT_GameLoopTimeDataIndex::instance = 0;
        }
        for (int i = 0; i < countof(DAT_GameLoopDurationBuffer::instance); ++i) {
            durationSum += DAT_GameLoopDurationBuffer::instance[i];
            tickRateSum += DAT_TickRateBuffer::instance[i];
        }
        int averageDuration = durationSum / 100;
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                lastGameLoopDuration, posX, posY + 5, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF,
                0, 15, FALSE, 0);
        }
        // The maximum is never used, but the original computes it. A pointer walk five entries at a time, as in the
        // original (a plain loop over the entries loses the match)
        int maxDuration = -1;
        for (int* entry = DAT_GameLoopDurationBuffer::instance; entry < DAT_GameLoopDurationBuffer::instance + 100;
            entry += 5) {
            if (entry[0] > maxDuration) {
                maxDuration = entry[0];
            }
            if (entry[1] > maxDuration) {
                maxDuration = entry[1];
            }
            if (entry[2] > maxDuration) {
                maxDuration = entry[2];
            }
            if (entry[3] > maxDuration) {
                maxDuration = entry[3];
            }
            if (entry[4] > maxDuration) {
                maxDuration = entry[4];
            }
        }
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                averageDuration, posX + 48, posY, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_0080FF, 0,
                17, FALSE, 0);
        }
        if (averageDuration == 0) {
            averageDuration = 1;
        }
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                1000 / averageDuration, posX + 48, posY + 20, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
        }
        DAT_CurrentFramerate::instance = 1000 / averageDuration;
        if (tickRateSum == 0) {
            tickRateSum = 1;
        }
        int durationPerTick = durationSum / tickRateSum;
        if (durationPerTick == 0) {
            durationPerTick = 1;
        }
        if ((int)elementState != -1000) {
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                1000 / durationPerTick, posX + 48, posY + 40, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_0080FF, 0, 17, FALSE, 0);
        }
    }

}
}
