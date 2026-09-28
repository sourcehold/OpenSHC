#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Player/BuildingEntryInfo.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::Player::BuildingEntryInfo;
        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;

        /*
          WARNING: Enum "MappersEnum": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004A1C40
        undefined4 PathFindingState::isTileInRangeOfKeepRange(int playerID, uint x, uint y, int range)
        {
            int* piVar1;
            int* piVar2;
            if (x < 400 && y < 400 && *(char*)(y * 400 + 0x21aec98 + x) != '\0') {
                if (DAT_GameState::instance.playerDataArray[playerID].keep.id != 0
                    && (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(x, (int)(y),
                            DAT_GameState::instance.playerDataArray[playerID].keep.xEntry,
                            DAT_GameState::instance.playerDataArray[playerID].keep.yEntry),
                        DAT_DirectionAlgorithmState::instance.distanceHigh <= range)) {
                    return (undefined4)(0);
                }
                piVar1 = &DAT_GameState::instance.playerDataArray[1].keep.yEntry;
                piVar2 = DAT_GameState::instance.mapAndTime.playerTeams + 1;
                while (*piVar2 != DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                    || ((BuildingEntryInfo*)(piVar1 + -2))->id == 0
                    || (MACRO_CALL_MEMBER(
                            OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                            DAT_DirectionAlgorithmState::ptr)(x, (int)(y), (int)(piVar1[-1]), (int)(*piVar1)),
                        range / 2 < DAT_DirectionAlgorithmState::instance.distanceHigh)) {
                    piVar2 = piVar2 + 1;
                    piVar1 = piVar1 + 0xe7d;
                    if (0x117d56b < (int)piVar2) {
                        DAT_TileMapState::instance.buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                        return (undefined4)(1);
                    }
                }
                return (undefined4)(0);
            }
            return (undefined4)(0);
        }

    }
}
}
