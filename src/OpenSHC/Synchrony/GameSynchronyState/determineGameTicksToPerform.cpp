#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MillisecCarry.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487A30
    int GameSynchronyState::determineGameTicksToPerform(int currentPlayerSlotID)
    {
        int _durationOfOneTick;
        int _relativeTickTime;
        dword _gameSpeedLevel;
        if (!DAT_GameCore::instance.gameSpeedLevel) {
            DAT_GameCore::instance.gameSpeedLevel = 40;
        }
        if (DAT_GameCore::instance.currentlyInGameUnk_0xa4 != TRUE) {
            return 0;
        }
        if (this->DAT_GameHalted) {
            return 0;
        }
        if ((this->currentGameMode == Game::GM_SOLITARY)
            || (this->currentGameMode == Game::GM_SKIRMISH_SINGLE_PLAYER)) {
            this->mapTimeInTicksSinglePlayer = DAT_GameCore::instance.mapTimeInTicks;
            _gameSpeedLevel = DAT_GameCore::instance.gameSpeedLevel;
            _relativeTickTime = this->relativeTickTime;
        } else {
            /*
              Calculate multiplayer game speed.
             */
            DAT_GameCore::instance.gameSpeedMultiplicator = 1;
            _gameSpeedLevel = this->skirmishGameSpeedLevel;
            DAT_GameSynchronyState::instance.relativeTickTime = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeLatencyAdjustmentFromMatchTimes, this)(
                currentPlayerSlotID);
            if ((int)this->ticksBehindFastestPlayer < 0) {
                DAT_GameSynchronyState::instance.relativeTickTime = (int)this->ticksBehindFastestPlayer;
            } else {
                if (0 < (int)this->ticksAheadOfSlowestPlayer) {
                    DAT_GameSynchronyState::instance.relativeTickTime = (int)this->ticksAheadOfSlowestPlayer;
                    if ((int)this->ticksAheadOfSlowestPlayer > (int)this->commandDelay + 0x4b) {
                        if ((int)this->unknownIncrementBy40_01 < 1) {
                            this->unknownIncrementBy40_01 = 1;
                        }
                        _gameSpeedLevel = this->unknownIncrementBy40_01;
                        if ((int)this->unknownIncrementBy40_01 > this->skirmishGameSpeedLevel) {
                            _gameSpeedLevel = this->skirmishGameSpeedLevel;
                        }
                    } else if (5 < (int)this->ticksAheadOfSlowestPlayer) {
                        _gameSpeedLevel
                            = ((5 - (int)this->ticksAheadOfSlowestPlayer) * 2) / 3 + this->skirmishGameSpeedLevel;
                        if ((int)_gameSpeedLevel < 15) {
                            _gameSpeedLevel = 15;
                        }
                    }
                }
            }
            _relativeTickTime = DAT_GameSynchronyState::instance.relativeTickTime;
        }
        DAT_GameSynchronyState::instance.relativeTickTime = _relativeTickTime;
        if (DAT_GameCore::instance.gameSpeedMultiplicator < 0) {
            _durationOfOneTick = -1000 / (int)_gameSpeedLevel * DAT_GameCore::instance.gameSpeedMultiplicator;
        } else {
            _durationOfOneTick = 1000 / (int)_gameSpeedLevel;
            if (1 < DAT_GameCore::instance.gameSpeedMultiplicator) {
                _durationOfOneTick = _durationOfOneTick / DAT_GameCore::instance.gameSpeedMultiplicator;
            }
        }
        _relativeTickTime
            = DAT_MillisecCarry::instance + (DAT_GameLoopStopwatch::instance.duration_0x0 - _durationOfOneTick);
        DAT_MillisecCarry::instance = _relativeTickTime;
        if (_relativeTickTime < 0) {
            /*
              Wait
             */
            if (_relativeTickTime < -_durationOfOneTick) {
                DAT_MillisecCarry::instance = _relativeTickTime + _durationOfOneTick;
                return 0;
            }
        } else {
            /*
              Execute game ticks
             */
            if (DAT_GameCore::instance.averageTimePerGameTick > _durationOfOneTick
                && _relativeTickTime >= _durationOfOneTick * 2 && _durationOfOneTick == 1000 / (int)_gameSpeedLevel) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 2;
            }
            if (DAT_GameCore::instance.averageTimePerGameTick > (_durationOfOneTick * 7) / 10
                && _relativeTickTime >= _durationOfOneTick * 2 && _durationOfOneTick == 1000 / (int)_gameSpeedLevel) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 3;
            }
            if (_relativeTickTime > _durationOfOneTick * 10) {
                /*
                  Cap game ticks per rendering
                 */
                DAT_MillisecCarry::instance = 0;
                return 11;
            }
            if (_relativeTickTime > _durationOfOneTick) {
                DAT_MillisecCarry::instance
                    = _relativeTickTime - (_relativeTickTime / _durationOfOneTick) * _durationOfOneTick;
                return _relativeTickTime / _durationOfOneTick + 1;
            }
        }
        return 1;
    }

}
}
