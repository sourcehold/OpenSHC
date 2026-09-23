#include "../AICState.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/LandscapeState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
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

    // FUNCTION: STRONGHOLDCRUSADER 0x004CE200
    void AICState::computeEnemyKeepApproachTile(int playerID)
    {
        int keepX = DAT_GameState::instance.playerDataArray[playerID].campground.xEntry;
        int keepY = DAT_GameState::instance.playerDataArray[playerID].campground.yEntry;
        this->aiBorderTilesIndex = 0;
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            8000, '\0', this->aiBorderTiles);
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::recomputeAIPathCostToAttackedKeep, this)(playerID, 1);

        for (int i = 0; i < (int)this->aiBorderTilesIndex; i++) {
            int tile = this->aiBorderTiles[i].tile;
            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::setAxisBasedDistanceResult,
                DAT_DirectionAlgorithmState::ptr)(keepX, keepY,
                tile
                    - DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]]
                        .addXgetTile,
                DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[tile]);
            this->aiBorderTiles[i].distance = DAT_TileMapState::instance.unitDeathHeatMap[tile]
                + DAT_DirectionAlgorithmState::instance.distanceHigh;
        }

        int shortestDistanceTile = 0;
        int shortestDistance = 100000;
        for (int i = 0; i < (int)this->aiBorderTilesIndex; i++) {
            if (this->aiBorderTiles[i].distance < shortestDistance) {
                shortestDistanceTile = this->aiBorderTiles[i].tile;
                shortestDistance = this->aiBorderTiles[i].distance;
            }
        }

        DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile = 0;
        if (shortestDistanceTile <= 0)
            return;

        short y = DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[shortestDistanceTile];
        DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY = y;
        DAT_GameState::instance.playerDataArray[playerID].shortestDistanceTile = shortestDistanceTile;
        int x = shortestDistanceTile - DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile;
        DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX = x;
        DAT_GameState::instance.mapAndTime.signpostEntryData[playerID - 1].x = x;
        DAT_GameState::instance.mapAndTime.signpostEntryData[playerID - 1].y
            = DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY;

        if ((short)DAT_TileMapState::instance.OrganismLayer
                [DAT_ViewportRenderState::instance
                        .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                        .addXgetTile
                    + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]
            != 0)
            MACRO_CALL_MEMBER(OpenSHC::Map::LandscapeState_Func::removeTree, DAT_LandscapeState::ptr)(
                (short)DAT_TileMapState::instance.OrganismLayer
                    [DAT_ViewportRenderState::instance
                            .translationMatrix[DAT_GameState::instance.playerDataArray[playerID].shortestDistanceY]
                            .addXgetTile
                        + DAT_GameState::instance.playerDataArray[playerID].shortestDistanceX]);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::findLinkageBasedPathOrWalkRadius,
            DAT_PathFindingState::ptr)(DAT_GameState::instance.mapAndTime.signpostEntryData[playerID - 1].x,
            DAT_GameState::instance.mapAndTime.signpostEntryData[playerID - 1].y, -1, -1, 2000, FALSE);
        MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::storeDestinationOptionsUnk,
            DAT_PathFindingState::ptr)(playerID - 1);
    }

}
}
