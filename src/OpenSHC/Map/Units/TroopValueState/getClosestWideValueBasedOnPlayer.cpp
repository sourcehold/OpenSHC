#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        // FUNCTION: STRONGHOLDCRUSADER 0x0051A5B0
        int TroopValueState::getClosestWideValueBasedOnPlayer(int unitID)
        {
            int const owner = DAT_UnitsState::instance.units[unitID].owner;
            int minDistance = 1000;
            int bestIndex = -1;
            int const attackedPlayerID = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1]
                                             .currentPlayerID_OR_attackedPlayerID_OR_one;
            int const destinationXPosition = DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                                 .buildingEntryInfos[Game::Player::Enums::BEIE_CAMPGROUND]
                                                 .xEntry;
            int const destinationYPosition = DAT_GameState::instance.playerDataArray[attackedPlayerID]
                                                 .buildingEntryInfos[Game::Player::Enums::BEIE_CAMPGROUND]
                                                 .yEntry;
            int i = 0;
            if (0 < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wide2) {
                for (; i < DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wide2; ++i) {
                    if (DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[i].buildingID
                            >= 5999
                        || DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[i].unitID) {
                        continue;
                    }
                    int const fromYPosition
                        = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent
                              [DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[i].tile2];
                    int const fromXPosition
                        = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[i].tile2
                        - DAT_ViewportRenderState::instance.translationMatrix[fromYPosition].addXgetTile;
                    MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(DAT_UnitsState::instance.units[unitID].x,
                        DAT_UnitsState::instance.units[unitID].y, fromXPosition, fromYPosition);
                    int distance = DAT_DirectionAlgorithmState::instance.distanceHigh;
                    MACRO_CALL_MEMBER(Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(
                        destinationXPosition, destinationYPosition, fromXPosition, fromYPosition);
                    distance += DAT_DirectionAlgorithmState::instance.distanceHigh;
                    if (distance < minDistance) {
                        this->y = fromYPosition;
                        this->x = fromXPosition;
                        this->tile
                            = DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[i].tile;
                        minDistance = distance;
                        bestIndex = i;
                    }
                }
                if (bestIndex <= -1) {
                    return 0;
                }
                DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[bestIndex].unitID
                    = unitID;
                return DAT_TroopValueState::instance.attackInfo.playerInfo[owner - 1].wideValuesArray[bestIndex].tile2;
            }
            return 0;
        }

    }
}
}
