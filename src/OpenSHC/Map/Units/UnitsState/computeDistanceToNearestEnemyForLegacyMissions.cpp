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
            int _owner = this->units[unitID].owner;
            int _unitMicroY = this->units[unitID].microYPosition;
            int _unitMicroX = this->units[unitID].microXPosition;
            /* kept in step with the result but never read back */
            int _closestWithinThousand = 1000;
            int _closestDistance = 10000;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                return 10000;
            }
            if ((int)this->unitCount > 100) {
                return 10000;
            }
            for (int i = 0; i < DAT_GameState::instance.playerDataArray[_owner].enemies; ++i) {
                int _enemyUnitID = DAT_GameState::instance.playerDataArray[_owner].enemyIDArray[i];
                if (this->units[_enemyUnitID].uid
                    != DAT_GameState::instance.mapAndTime.playerEnemenyUnitUIDShortList[_owner][i]) {
                    continue;
                }
                int _distanceX;
                if (_unitMicroX > this->units[_enemyUnitID].microXPosition) {
                    _distanceX = _unitMicroX - this->units[_enemyUnitID].microXPosition;
                } else {
                    _distanceX = this->units[_enemyUnitID].microXPosition - _unitMicroX;
                }
                int _distance;
                if (_unitMicroY > this->units[_enemyUnitID].microYPosition) {
                    _distance = _unitMicroY - this->units[_enemyUnitID].microYPosition;
                } else {
                    _distance = this->units[_enemyUnitID].microYPosition - _unitMicroY;
                }
                if (_distanceX >= _distance) {
                    _distance = _distanceX;
                }
                if (_distance < _closestWithinThousand) {
                    _closestWithinThousand = _distance;
                }
                if (_distance < _closestDistance) {
                    _closestDistance = _distance;
                }
            }
            return _closestDistance;
        }

    }
}
}
