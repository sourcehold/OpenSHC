#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A5B0
        undefined4 TroopValueState::getClosestWideValueBasedOnPlayer(int playerID)
        {
            int destinationXPosition;
            int destinationYPosition;
            int iVar1;
            AttackInfoSubArrayElement1* _ptr;
            int fromXPosition;
            int iVar2;
            int fromYPosition;
            int local_1c;
            int local_18;
            int local_10;
            int _playerID_2;
            iVar2 = DAT_UnitsState::instance.units[playerID].owner * 0x177bc;
            _playerID_2 = *(int*)((int)this->attackInfo.hackValuesArray + iVar2 + -0x10);
            destinationXPosition = DAT_GameState::instance.playerDataArray[_playerID_2].campground.xEntry;
            destinationYPosition = DAT_GameState::instance.playerDataArray[_playerID_2].campground.yEntry;
            local_18 = 1000;
            local_10 = -1;
            local_1c = 0;
            if (0 < *(int*)((int)this->attackInfo.wideValuesArray + iVar2 + -8)) {
                _ptr = (AttackInfoSubArrayElement1*)((int)&this->attackInfo.wideValuesArray + iVar2 + 4);
                do {
                    if ((_ptr->buildingID < 5999) && (!_ptr->unitID)) {
                        fromYPosition
                            = (int)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_ptr->tile2];
                        fromXPosition = _ptr->tile2
                            - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[playerID].x,
                            (int)((int)(DAT_UnitsState::instance.units[playerID].y)), fromXPosition, fromYPosition);
                        iVar1 = DAT_DirectionAlgorithmState::instance.distanceHigh;
                        MACRO_CALL_MEMBER(
                            Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(
                            destinationXPosition, destinationYPosition, fromXPosition, fromYPosition);
                        if (iVar1 + DAT_DirectionAlgorithmState::instance.distanceHigh < local_18) {
                            this->tile = _ptr->tile;
                            local_10 = local_1c;
                            local_18 = iVar1 + DAT_DirectionAlgorithmState::instance.distanceHigh;
                            this->x = fromXPosition;
                            this->y = fromYPosition;
                        }
                    }
                    local_1c = local_1c + 1;
                    _ptr = _ptr + 4;
                } while (local_1c < *(int*)((int)this->attackInfo.wideValuesArray + iVar2 + -8));
                if (-1 < local_10) {
                    iVar2 = local_10 * 0x10 + iVar2;
                    *(int*)((int)this->attackInfo.wideValuesArray + iVar2 + 0xc) = playerID;
                    return *(undefined4*)((int)this->attackInfo.wideValuesArray + iVar2 + 4);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
