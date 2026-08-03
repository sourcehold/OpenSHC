#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/AI/TileDistancePair.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_LandscapeState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::TileDistancePair;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE200
    void AICState ::computeEnemyKeepApproachTile(int playerID)

    {

        int _shortestDistanceTile;

        int _shortestDistanceX;

        TileDistancePair* _tilePointer;

        int iVar1;

        int* _distancePointer;

        int _shortestDistance;

        int local_c;

        int _keepX;

        int _keepY;

        int _tile;

        short _y;

        _keepX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;

        _keepY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;

        this->aiBorderTilesIndex = 0;

        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            8000, '\0', (void*)((int)(this->aiBorderTiles)));

        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 1);

        local_c = 0;

        if (0 < this->aiBorderTilesIndex) {

            _distancePointer = &this->aiBorderTiles[0].distance;

            do {

                _tile = ((TileDistancePair*)(_distancePointer + -1))->tile;

                MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                    DAT_DirectionAlgorithmState::ptr)(_keepX, _keepY,
                    _tile
                        - DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_ViewportRenderState::instance
                                    .tileTranslationMatrix_YComponent[_tile]]
                            .addXgetTile,
                    (int)((int)(DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile])));

                /*
                        avoiding unit death areas */

                *_distancePointer = (uint)DAT_TileMapState::instance.unitDeathHeatMap[_tile]
                    + DAT_DirectionAlgorithmState::instance.distanceHigh;

                local_c = local_c + 1;

                _distancePointer = _distancePointer + 2;

            } while (local_c < this->aiBorderTilesIndex);
        }

        _shortestDistanceTile = 0;

        _shortestDistance = 100000;

        if (0 < this->aiBorderTilesIndex) {

            _tilePointer = this->aiBorderTiles;

            iVar1 = this->aiBorderTilesIndex;

            do {

                if (_tilePointer->distance < _shortestDistance) {

                    _shortestDistanceTile = _tilePointer->tile;

                    _shortestDistance = _tilePointer->distance;
                }

                _tilePointer = _tilePointer + 1;

                iVar1 = iVar1 + -1;

            } while (iVar1 != 0);
        }

        /*
            sets the first attack distance to the enemy keep */

        DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile = 0;

        if (0 < _shortestDistanceTile) {

            _y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_shortestDistanceTile];

            DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY = (int)_y;

            DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile = _shortestDistanceTile;

            _shortestDistanceX
                = _shortestDistanceTile - DAT_ViewportRenderState::instance.translationMatrix[_y].addXgetTile;

            DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX = _shortestDistanceX;

            DAT_GameState::instance.mapAndTime.signpostEntryData[playerID + -1][0] = _shortestDistanceX;

            DAT_GameState::instance.mapAndTime.signpostEntryData[playerID + -1][1]
                = DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY;

            if ((short)DAT_TileMapState::instance.OrganismLayer
                    [DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                            .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]
                != 0) {

                MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                    (int)(short)DAT_TileMapState::instance.OrganismLayer
                        [DAT_ViewportRenderState::instance
                                .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                                .addXgetTile
                            + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]);
            }

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
                DAT_PathFindingState::ptr)(DAT_GameState::instance.mapAndTime.signpostEntryData[playerID + -1][0],
                (uint)((int)(DAT_GameState::instance.mapAndTime.signpostEntryData[playerID + -1][1])), -1, -1, 2000,
                FALSE);

            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::storeDestinationOptionsUnk,
                DAT_PathFindingState::ptr)(playerID + -1);
        }

        return;
    }

}
}
