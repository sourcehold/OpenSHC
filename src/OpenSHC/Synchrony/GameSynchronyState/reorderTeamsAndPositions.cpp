#include "../../Synchrony.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using Commands::GameCommandType;
    using Game::GameMode;
    using WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x0048C7B0
    undefined4 GameSynchronyState::reorderTeamsAndPositions()
    {
        char* pcVar1;
        char* _playerGroupArray;
        char* pcVar2;
        int iVar3;
        byte bVar4;
        int _counter2;
        int _counter3;
        int* piVar5;
        int _counter;
        int* piVar6;
        int local_4c;
        char* local_44;
        int local_38[6];
        int local_20[8];
        int* _currentPlayerFullIdArray;
        byte _group;
        _counter2 = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[1] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[2] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[3] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[4] = 0;
        local_20[0] = 0;
        local_20[1] = 0;
        local_20[2] = 0;
        local_20[3] = 0;
        local_20[4] = 0;
        local_20[5] = 0;
        local_20[6] = 0;
        local_20[7] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[5] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[6] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[7] = 0;
        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[8] = 0;
        local_38[0] = 0;
        local_38[1] = 0;
        local_38[2] = 0;
        local_38[3] = 0;
        local_38[4] = 0;
        _playerGroupArray = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray;
        _currentPlayerFullIdArray = DAT_GameSynchronyState::instance.currentPlayerFullIDArray;
        _counter = 8;
        do {
            _currentPlayerFullIdArray = _currentPlayerFullIdArray + 1;
            _playerGroupArray = _playerGroupArray + 1;
            /*
              fullIdArray == -1 && AI == 0
             */
            if ((*_currentPlayerFullIdArray == -1) && (_currentPlayerFullIdArray[0x1b] == 0)) {
                *_playerGroupArray = (char)0xff;
            } else {
                if ((char)*_playerGroupArray < '\0') {
                    *_playerGroupArray = 0;
                }
                _group = *_playerGroupArray;
                local_38[(char)_group] = local_38[(char)_group] + 1;
                if ((char)_group != 0) {
                    local_38[0] = local_38[0] + 1;
                }
                _counter2 = _counter2 + 1;
            }
            _counter = _counter + -1;
        } while (_counter);
        _counter = 1;
    LAB_0048c857:
        iVar3 = local_38[_counter];
        if (0 < iVar3) {
            if (iVar3 == local_38[0]) {
                _playerGroupArray = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray;
                iVar3 = 8;
                do {
                    _playerGroupArray = _playerGroupArray + 1;
                    if (-1 < (char)*_playerGroupArray) {
                        *_playerGroupArray = 0;
                    }
                    iVar3 = iVar3 + -1;
                } while (iVar3);
                local_38[_counter] = 0;
            LAB_0048c8b5:
                _counter3 = 1;
                _currentPlayerFullIdArray = local_38 + 2;
                do {
                    if ((_currentPlayerFullIdArray[-1] == 0) && (*_currentPlayerFullIdArray != 0)) {
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[1] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[2] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[3] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[4] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[5] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[6] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[7] - 1;
                        }
                        if (_counter3 < (char)DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]) {
                            DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8]
                                = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[8] - 1;
                        }
                        if (_counter3 + 1 < 5) {
                            piVar5 = _currentPlayerFullIdArray;
                            piVar6 = _currentPlayerFullIdArray + -1;
                            for (_counter = 5 - (_counter3 + 1); _counter != 0; _counter = _counter + -1) {
                                *piVar6 = *piVar5;
                                piVar5 = piVar5 + 1;
                                piVar6 = piVar6 + 1;
                            }
                        }
                    }
                    _counter3 = _counter3 + 1;
                    _currentPlayerFullIdArray = _currentPlayerFullIdArray + 1;
                } while (_counter3 < 4);
                local_4c = 1;
                if (0 < _counter2) {
                    local_44 = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray + 2;
                    do {
                        pcVar2 = (char*)0xffffffff;
                        _group = 0xff;
                        _currentPlayerFullIdArray = local_38 + 7;
                        _playerGroupArray = local_44;
                        do {
                            bVar4 = _playerGroupArray[-1];
                            if ((-1 < (char)bVar4) && (_currentPlayerFullIdArray[-1] == 0)) {
                                if (!bVar4) {
                                    bVar4 = 10;
                                }
                                if ((char)bVar4 < (char)_group || pcVar2 == (char*)0xffffffff) {
                                    pcVar2 = (char*)(_playerGroupArray + -0x1a275b6);
                                    _group = bVar4;
                                }
                            }
                            bVar4 = *_playerGroupArray;
                            if ((-1 < (char)bVar4) && (*_currentPlayerFullIdArray == 0)) {
                                if (!bVar4) {
                                    bVar4 = 10;
                                }
                                if ((char)bVar4 < (char)_group || pcVar2 == (char*)0xffffffff) {
                                    pcVar2 = (char*)(_playerGroupArray + -0x1a275b5);
                                    _group = bVar4;
                                }
                            }
                            bVar4 = _playerGroupArray[1];
                            if ((-1 < (char)bVar4) && (_currentPlayerFullIdArray[1] == 0)) {
                                if (!bVar4) {
                                    bVar4 = 10;
                                }
                                if ((char)bVar4 < (char)_group || pcVar2 == (char*)0xffffffff) {
                                    pcVar2 = (char*)(_playerGroupArray + -0x1a275b4);
                                    _group = bVar4;
                                }
                            }
                            bVar4 = _playerGroupArray[2];
                            if ((-1 < (char)bVar4) && (_currentPlayerFullIdArray[2] == 0)) {
                                if (!bVar4) {
                                    bVar4 = 10;
                                }
                                if ((char)bVar4 < (char)_group || pcVar2 == (char*)0xffffffff) {
                                    pcVar2 = (char*)(_playerGroupArray + -0x1a275b3);
                                    _group = bVar4;
                                }
                            }
                            pcVar1 = (char*)(_playerGroupArray + -0x1a275b2);
                            _currentPlayerFullIdArray = _currentPlayerFullIdArray + 4;
                            _playerGroupArray = _playerGroupArray + 4;
                        } while ((int)pcVar1 < 9);
                        if ((int)pcVar2 < 0)
                            break;
                        DAT_GameSynchronyState::instance.DAT_RoundTableOrderArray[local_4c] = (byte)pcVar2;
                        local_4c = local_4c + 1;
                        local_38[(int)(pcVar2 + 5)] = 1;
                    } while (local_4c <= _counter2);
                }
                if ((DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SKIRMISH_SINGLE_PLAYER)
                    && (DAT_GameSynchronyState::instance.isHost)) {
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                        (Commands::GameCommandType)(Commands::GCT_START_OR_STOP_SEND_MAP_FILEUnk
                            | Commands::GCT_HOST_SHARE_LOBBY_STATE));
                    MACRO_CALL_MEMBER(Synchrony::GameSynchronyState_Func::queueCommand, this)(
                        Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
                }
                return (undefined4)(1);
            }
            if (iVar3 == 1) {
                _playerGroupArray = DAT_GameSynchronyState::instance.DAT_PlayerGroupArray;
                iVar3 = 8;
                do {
                    _playerGroupArray = _playerGroupArray + 1;
                    if ((char)*_playerGroupArray == _counter) {
                        *_playerGroupArray = 0;
                    }
                    iVar3 = iVar3 + -1;
                } while (iVar3);
                local_38[_counter] = 0;
            }
        }
        _counter = _counter + 1;
        if (4 < _counter)
            goto LAB_0048c8b5;
        goto LAB_0048c857;
    }

}
}
