#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameLoopStopwatch.hpp"
#include "OpenSHC/Globals/DAT_MillisecCarry.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x00487A30
    int GameSynchronyState::determineGameTicksToPerform(int currentPlayerSlotID)
    {
        int iVar1;
        int extraout_ECX;
        int _durationOfOneTick;
        int _relativeTickTime;
        dword _gameSpeedLevel = this->skirmishGameSpeedLevel;
        if (!DAT_GameCore::instance.gameSpeedLevel) {
            DAT_GameCore::instance.gameSpeedLevel = 40;
        }
        if ((DAT_GameCore::instance.currentlyInGameUnk_0xa4 != TRUE) || (this->DAT_GameHalted)) {
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
            this->relativeTickTime = 0;
            MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::computeLatencyAdjustmentFromMatchTimes, this)(
                currentPlayerSlotID);
            _relativeTickTime = *(int*)(extraout_ECX + 0x109eac);
            if (-1 < *(int*)(extraout_ECX + 0x109eac)
                && (iVar1 = *(int*)(extraout_ECX + 0x109ea8), _relativeTickTime = this->relativeTickTime, 0 < iVar1)) {
                int iVar2 = *(int*)(extraout_ECX + 0x109ea8);
                if (*(int*)(extraout_ECX + 0x109ee8) + 0x4b < iVar2) {
                    this->relativeTickTime = iVar1;
                    if (*(int*)(extraout_ECX + 0x109260) < 1) {
                        *(undefined4*)(extraout_ECX + 0x109260) = 1;
                    }
                    _gameSpeedLevel = *(dword*)(extraout_ECX + 0x109260);
                    _relativeTickTime = this->relativeTickTime;
                    if ((int)*(dword*)(extraout_ECX + 0x106e38) < (int)*(dword*)(extraout_ECX + 0x109260)) {
                        _gameSpeedLevel = *(dword*)(extraout_ECX + 0x106e38);
                    }
                } else {
                    _relativeTickTime = iVar1;
                    if (5 < iVar2
                        && (_gameSpeedLevel = ((5 - iVar2) * 2) / 3 + *(int*)(extraout_ECX + 0x106e38),
                            (int)_gameSpeedLevel < 15)) {
                        _gameSpeedLevel = 15;
                    }
                }
            }
        }
        this->relativeTickTime = _relativeTickTime;
        if (DAT_GameCore::instance.gameSpeedMultiplicator < 0) {
            _durationOfOneTick
                = (int)(-1000 / (longlong)(int)_gameSpeedLevel) * DAT_GameCore::instance.gameSpeedMultiplicator;
        } else {
            _durationOfOneTick = (int)(1000 / (longlong)(int)_gameSpeedLevel);
            if (1 < DAT_GameCore::instance.gameSpeedMultiplicator) {
                _durationOfOneTick = (int)((longlong)((ulonglong)(uint)(_durationOfOneTick >> 0x1f) << 0x20
                                               | 1000 / (longlong)(int)_gameSpeedLevel & 0xffffffffU)
                    / (longlong)DAT_GameCore::instance.gameSpeedMultiplicator);
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
            if (_durationOfOneTick < DAT_GameCore::instance.averageTimePerGameTick
                && _durationOfOneTick * 2 <= _relativeTickTime
                && _durationOfOneTick == (int)(1000 / (longlong)(int)_gameSpeedLevel)) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 2;
            }
            if ((_durationOfOneTick * 7) / 10 < DAT_GameCore::instance.averageTimePerGameTick
                && _durationOfOneTick * 2 <= _relativeTickTime
                && _durationOfOneTick == (int)(1000 / (longlong)(int)_gameSpeedLevel)) {
                /*
                  Slow down
                 */
                DAT_MillisecCarry::instance = 0;
                return 3;
            }
            if (_durationOfOneTick * 10 < _relativeTickTime) {
                /*
                  Cap game ticks per rendering
                 */
                DAT_MillisecCarry::instance = 0;
                return (int)(11);
            }
            if (_durationOfOneTick < _relativeTickTime) {
                DAT_MillisecCarry::instance
                    = _relativeTickTime - (_relativeTickTime / _durationOfOneTick) * _durationOfOneTick;
                return _relativeTickTime / _durationOfOneTick + 1;
            }
        }
        return 1;
    }

}
}
