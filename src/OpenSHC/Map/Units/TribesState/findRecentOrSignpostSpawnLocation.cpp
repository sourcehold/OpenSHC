#include "../TribesState.func.hpp"

#include "OpenSHC/Map/MapConstants.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00523410
        BOOLEnum TribesState::findRecentOrSignpostSpawnLocation(uint* _outX, uint* _outY)
        {
            int _slotOffset = 0;
            while (true) {
                uint _slot = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + _slotOffset) % 4;
                short const _spawnX = DAT_GameState::instance.mapAndTime.lionLocationsXY[_slot].x;
                if (_spawnX) {
                    *_outX = _spawnX;
                    _slot = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + _slotOffset) % 4;
                    uint const _spawnY = DAT_GameState::instance.mapAndTime.lionLocationsXY[_slot].y;
                    *_outY = _spawnY;
                    uint const _candidateX = *_outX;
                    if (_candidateX <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
                        && _spawnY <= OpenSHC::Map::MC_MAP_XY_LIMIT_MIN_1
                        && DAT_ViewportRenderState::instance
                                .DAT_BinaryTileMap400x400[_spawnY * OpenSHC::Map::MC_MAP_XY_LIMIT + _candidateX]
                            != 0
                        && !(DAT_TileMapState::instance
                                 .LogicLayer[DAT_ViewportRenderState::instance.translationMatrix[_spawnY].addXgetTile
                                     + _candidateX]
                            & (LogicHelpers::L_SEA | LogicHelpers::L_BORDER | LogicHelpers::L_BORDER_EDGE
                                | LogicHelpers::L_ROCKY | LogicHelpers::L_BUILDING | LogicHelpers::L_TREE
                                | LogicHelpers::L_RIVER | LogicHelpers::L_CRENEL_VARIATIONUnk
                                | LogicHelpers::L_FARM_FIELD_HOP | LogicHelpers::L_FARM_FIELD_DAIRY
                                | LogicHelpers::L_MOAT))) {
                        _slot = (DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor + 1 + _slotOffset) % 4;
                        DAT_GameState::instance.mapAndTime.animalSpawnSlotCursor = _slot;
                        return TRUE;
                    }
                }
                ++_slotOffset;
                if (4 <= _slotOffset) {
                    for (int _signpostSlot = 0;
                        _signpostSlot < countof(DAT_GameState::instance.mapAndTime.signpostsMapEdge); ++_signpostSlot) {
                        if (DAT_GameState::instance.mapAndTime.signpostIDs[_signpostSlot] != 0) {
                            *_outX = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_signpostSlot][0].x;
                            *_outY = DAT_GameState::instance.mapAndTime.signpostsMapEdge[_signpostSlot][0].y;
                            return TRUE;
                        }
                    }
                    return FALSE;
                }
            }
        }

    }
}
}
