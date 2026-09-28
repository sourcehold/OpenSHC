#include "../PathFindingState.func.hpp"

#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A15B0
        BOOLEnum PathFindingState::isEnemyTooCloseUnk(int playerID, uint x, uint y, int requiredDistance)
        {
            short* _enemyIdPtr;
            int _xEnemyDistance;
            int _enemyLoopCounter;
            int _yEnemyDistance;
            int _enemies;
            short _enemyID;
            if (399 < x || 399 < y || DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return FALSE;
            }
            _enemies = DAT_GameState::instance.playerDataArray[playerID].enemies;
            _enemyLoopCounter = 0;
            if (0 < _enemies) {
                _enemyIdPtr = DAT_GameState::instance.playerDataArray[playerID].enemyIDArray;
                do {
                    _enemyID = *_enemyIdPtr;
                    if (DAT_UnitsState::instance.units[_enemyID].dying == 0
                        && DAT_UnitsState::instance.units[_enemyID].uid
                            == *(int*)(playerID * 10000 + 0x11a66f0 + _enemyLoopCounter * 4)
                        && (_xEnemyDistance = x - (int)DAT_UnitsState::instance.units[_enemyID].x,
                            _yEnemyDistance = y - (int)DAT_UnitsState::instance.units[_enemyID].y,
                            _yEnemyDistance * _yEnemyDistance + _xEnemyDistance * _xEnemyDistance
                                    < requiredDistance * requiredDistance
                                && ((DAT_UnitsState::instance.units[_enemyID].unknownTestAgainst0_2 == 0
                                    && (DAT_UnitsState::instance.units[_enemyID].moveRelatedFlag != 1))))
                        && DAT_UnitsState::instance.units[_enemyID].isStalked == 0
                        && DAT_UnitsState::instance.units[_enemyID].owner != 0) {
                        return TRUE;
                    }
                    _enemyLoopCounter = _enemyLoopCounter + 1;
                    _enemyIdPtr = _enemyIdPtr + 1;
                } while (_enemyLoopCounter < _enemies);
            }
            return FALSE;
        }

    }
}
}
