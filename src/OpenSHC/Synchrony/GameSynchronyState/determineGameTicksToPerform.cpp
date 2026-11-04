#include "../GameSynchronyState.func.hpp"

#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MillisecCarry.hpp"

namespace OpenSHC {
namespace Synchrony {

    // FUNCTION: STRONGHOLDCRUSADER 0x00487A30
    int GameSynchronyState::determineGameTicksToPerform(int currentPlayerSlotID)
    {
        if (!DAT_GameCore::instance.gameSpeedLevel) {
            DAT_GameCore::instance.gameSpeedLevel = 40;
        }
        if (DAT_GameCore::instance.currentlyInGameUnk_0xa4 != TRUE) {
            return 0;
        }
        if (this->DAT_GameHalted) {
            return 0;
        }
        dword gameSpeed;
        int tickTimeOffset;
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->mapTimeInTicksSinglePlayer = DAT_GameCore::instance.mapTimeInTicks;
            gameSpeed = DAT_GameCore::instance.gameSpeedLevel;
            tickTimeOffset = this->relativeTickTime;
        } else {
            // Calculate multiplayer game speed.
            DAT_GameCore::instance.gameSpeedMultiplicator = 1;
            gameSpeed = this->skirmishGameSpeedLevel;
            DAT_GameSynchronyState::instance.relativeTickTime = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeLatencyAdjustmentFromMatchTimes, this)(
                currentPlayerSlotID);
            if ((int)this->ticksBehindFastestPlayer < 0) {
                DAT_GameSynchronyState::instance.relativeTickTime = (int)this->ticksBehindFastestPlayer;
            } else {
                if (0 < (int)this->ticksAheadOfSlowestPlayer) {
                    DAT_GameSynchronyState::instance.relativeTickTime = (int)this->ticksAheadOfSlowestPlayer;
                    if ((int)this->ticksAheadOfSlowestPlayer > (int)this->commandDelay + 75) {
                        if ((int)this->unknownIncrementBy40_01 < 1) {
                            this->unknownIncrementBy40_01 = 1;
                        }
                        gameSpeed = this->unknownIncrementBy40_01;
                        if ((int)this->unknownIncrementBy40_01 > this->skirmishGameSpeedLevel) {
                            gameSpeed = this->skirmishGameSpeedLevel;
                        }
                    } else if (5 < (int)this->ticksAheadOfSlowestPlayer) {
                        gameSpeed = ((5 - (int)this->ticksAheadOfSlowestPlayer) * 2) / 3 + this->skirmishGameSpeedLevel;
                        if ((int)gameSpeed < 15) {
                            gameSpeed = 15;
                        }
                    }
                }
            }
            tickTimeOffset = DAT_GameSynchronyState::instance.relativeTickTime;
        }
        DAT_GameSynchronyState::instance.relativeTickTime = tickTimeOffset;
        int tickDuration;
        if (DAT_GameCore::instance.gameSpeedMultiplicator < 0) {
            tickDuration = -1000 / (int)gameSpeed * DAT_GameCore::instance.gameSpeedMultiplicator;
        } else {
            tickDuration = 1000 / (int)gameSpeed;
            if (1 < DAT_GameCore::instance.gameSpeedMultiplicator) {
                tickDuration /= DAT_GameCore::instance.gameSpeedMultiplicator;
            }
        }
        int const millisecCarry
            = DAT_MillisecCarry::instance + (DAT_GameLoopStopwatch::instance.duration_0x0 - tickDuration);
        DAT_MillisecCarry::instance = millisecCarry;
        if (millisecCarry < 0) {
            // Wait
            if (millisecCarry < -tickDuration) {
                DAT_MillisecCarry::instance = millisecCarry + tickDuration;
                return 0;
            }
        } else {
            // Execute game ticks
            if (DAT_GameCore::instance.averageTimePerGameTick > tickDuration && millisecCarry >= tickDuration * 2
                && tickDuration == 1000 / (int)gameSpeed) {
                // Slow down
                DAT_MillisecCarry::instance = 0;
                return 2;
            }
            if (DAT_GameCore::instance.averageTimePerGameTick > (tickDuration * 7) / 10
                && millisecCarry >= tickDuration * 2 && tickDuration == 1000 / (int)gameSpeed) {
                // Slow down
                DAT_MillisecCarry::instance = 0;
                return 3;
            }
            if (millisecCarry > tickDuration * 10) {
                // Cap game ticks per rendering
                DAT_MillisecCarry::instance = 0;
                return 11;
            }
            if (millisecCarry > tickDuration) {
                DAT_MillisecCarry::instance = millisecCarry - (millisecCarry / tickDuration) * tickDuration;
                return millisecCarry / tickDuration + 1;
            }
        }
        return 1;
    }

}
}
