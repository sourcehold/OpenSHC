#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using OpenSHC::Game::GameMode;

        // FUNCTION: STRONGHOLDCRUSADER 0x00532F80
        int UnitsState::computeDistanceToNearestEnemyForLegacyMissions(int unitID)
        {
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return 10000;
            }
            if ((int)this->unitCount >= 100) {
                return 10000;
            }
            short _owner = this->units[unitID].owner;
            int _unitMicroX = this->units[unitID].microXPosition;
            int _unitMicroY = this->units[unitID].microYPosition;
            int _closestDistance = 10000;
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[_owner].enemies; ++i) {
                short _enemyUnitID = DAT_GameState::instance.playerDataArray[_owner].enemyIDArray[i];
                if (this->units[_enemyUnitID].uid
                    != DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[_owner][i]) {
                    continue;
                }
                int _distanceX = this->units[_enemyUnitID].microXPosition;
                if (_distanceX < _unitMicroX) {
                    _distanceX = _unitMicroX - _distanceX;
                } else {
                    _distanceX = _distanceX - _unitMicroX;
                }
                int _distanceY = this->units[_enemyUnitID].microYPosition;
                if (_distanceY < _unitMicroY) {
                    _distanceY = _unitMicroY - _distanceY;
                } else {
                    _distanceY = _distanceY - _unitMicroY;
                }
                if (_distanceY <= _distanceX) {
                    _distanceY = _distanceX;
                }
                if (_distanceY < _closestDistance) {
                    _closestDistance = _distanceY;
                }
            }
            return _closestDistance;
        }

    }
}
}
