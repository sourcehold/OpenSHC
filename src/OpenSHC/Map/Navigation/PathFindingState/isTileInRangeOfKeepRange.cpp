#include "../PathFindingState.func.hpp"

#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Game/Player/BuildingEntryInfo.hpp"
#include "OpenSHC/Game/Player/Enums/BuildingEntryInfoEnum.hpp"
#include "OpenSHC/Map/Buildings/BuildingFailReasonEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Navigation {

        using OpenSHC::Game::Player::BuildingEntryInfo;
        using OpenSHC::Map::Buildings::BuildingFailReasonEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004A1C40
        BOOLEnum PathFindingState::isTileInRangeOfKeepRange(int playerID, uint x, uint y, int range)
        {
            int* piVar1;
            int* piVar2;
            if (x > 399 || y > 399) {
                return (undefined4)(0);
            }
            if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == '\0') {
                return (undefined4)(0);
            }
            if (DAT_GameState::instance.playerDataArray[playerID]
                        .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                        .id
                    != 0
                && (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(x, (int)(y),
                        DAT_GameState::instance.playerDataArray[playerID]
                            .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                            .xEntry,
                        DAT_GameState::instance.playerDataArray[playerID]
                            .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                            .yEntry),
                    DAT_DirectionAlgorithmState::instance.distanceHigh <= range)) {
                return (undefined4)(0);
            }
            piVar1 = &DAT_GameState::instance.playerDataArray[1]
                          .buildingEntryInfos[OpenSHC::Game::Player::Enums::BEIE_KEEP]
                          .tileEntry;
            piVar2 = DAT_GameState::instance.mapAndTime.playerTeams + 1;
            while (*piVar2 != DAT_GameState::instance.mapAndTime.playerTeams[playerID]
                || ((BuildingEntryInfo*)(piVar1 + -3))->id == 0
                || (MACRO_CALL_MEMBER(
                        OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                        DAT_DirectionAlgorithmState::ptr)(x, (int)(y), (int)(piVar1[-2]), (int)(piVar1[-1])),
                    DAT_DirectionAlgorithmState::instance.distanceHigh > range / 2)) {
                piVar2 = piVar2 + 1;
                piVar1 = piVar1 + 0xe7d;
                if ((int)&DAT_GameState::instance.mapAndTime.playerTeams[9] <= (int)piVar2) {
                    DAT_TileMapState::instance.buildingPlacementFailReason = ((BuildingFailReasonEnum)0x12);
                    return (undefined4)(1);
                }
            }
            return (undefined4)(0);
        }

    }
}
}
