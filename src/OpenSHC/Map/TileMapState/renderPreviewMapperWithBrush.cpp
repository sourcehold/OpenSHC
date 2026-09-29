
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Commands/MappersEnum.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TerrainDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    using OpenSHC::Commands::MappersEnum;
    using OpenSHC::Game::GameMode;
    using OpenSHC::Game::GameMode2;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      whenever terrain is selected and you try to place it   decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00508A00
    void TileMapState::renderPreviewMapperWithBrush(uint x, uint y, MappersEnum mapper)
    {
        if (x > 399) {
            return;
        }
        if (y > 399) {
            return;
        }
        if (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[y * 400 + x] == 0) {
            return;
        }

        int brushSize = DAT_TerrainDefinedData::instance.BrushSizeArray[this->editorActiveBrush];
        int baseTile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        if (mapper == OpenSHC::Commands::M_MAPPER_POND1 || mapper == OpenSHC::Commands::M_MAPPER_POND2_SMALL
            || mapper == OpenSHC::Commands::M_MAPPER_POND3_LARGE1 || mapper == OpenSHC::Commands::M_MAPPER_POND4_LARGE2) {
            this->buildingPlacementFail = FALSE;
            return;
        }
        this->buildingPlacementFail = TRUE;
        if (mapper == OpenSHC::Commands::M_MAPPER_SIGNPOST) {
            return;
        }

        /* every mapper draws its own preview colour */
        ushort gfx;
        if ((int)mapper > OpenSHC::Commands::M_MAPPER_DUNES) {
            gfx = 0x38;
        } else if (mapper == OpenSHC::Commands::M_MAPPER_DUNES) {
            gfx = 0x3c;
        } else {
            switch (mapper) {
            case OpenSHC::Commands::M_MAPPER_SEA:
            case OpenSHC::Commands::M_MAPPER_SHALLOWS:
            case OpenSHC::Commands::M_MAPPER_RIVER:
            case OpenSHC::Commands::M_MAPPER_MARSH:
            case OpenSHC::Commands::M_MAPPER_DUGMOAT:
            case OpenSHC::Commands::M_MAPPER_MOAT:
            gfx = 0x39;
            break;
            case OpenSHC::Commands::M_MAPPER_SCRUB:
            case OpenSHC::Commands::M_MAPPER_DIRT:
            gfx = 0x3c;
            break;
            case OpenSHC::Commands::M_MAPPER_BEACH:
            case OpenSHC::Commands::M_MAPPER_FORD:
            gfx = 0x3a;
            break;
            case OpenSHC::Commands::M_MAPPER_ROCKY:
            case OpenSHC::Commands::M_MAPPER_STONES:
            case OpenSHC::Commands::M_MAPPER_BOULDERS:
            case OpenSHC::Commands::M_MAPPER_PEBBLES:
            case OpenSHC::Commands::M_MAPPER_IRON:
            gfx = 0x3b;
            break;
            case OpenSHC::Commands::M_MAPPER_CHESTNUT:
            case OpenSHC::Commands::M_MAPPER_OAK:
            case OpenSHC::Commands::M_MAPPER_PINE:
            case OpenSHC::Commands::M_MAPPER_BIRCH:
            case OpenSHC::Commands::M_MAPPER_SHRUB1A:
            case OpenSHC::Commands::M_MAPPER_SHRUB1B:
            case OpenSHC::Commands::M_MAPPER_SHRUB1C:
            case OpenSHC::Commands::M_MAPPER_SHRUB1D:
            case OpenSHC::Commands::M_MAPPER_SHRUB1E:
            case OpenSHC::Commands::M_MAPPER_SHRUB2A:
            case OpenSHC::Commands::M_MAPPER_SHRUB2B:
            case OpenSHC::Commands::M_MAPPER_SHRUB2C:
            case OpenSHC::Commands::M_MAPPER_SHRUB2D:
            case OpenSHC::Commands::M_MAPPER_SHRUB2E:
            case OpenSHC::Commands::M_MAPPER_SHRUB3A:
            case OpenSHC::Commands::M_MAPPER_SHRUB3B:
            case OpenSHC::Commands::M_MAPPER_SHRUB3C:
            case OpenSHC::Commands::M_MAPPER_SHRUB3D:
            case OpenSHC::Commands::M_MAPPER_DEER:
            case OpenSHC::Commands::M_MAPPER_LION:
            case OpenSHC::Commands::M_MAPPER_RABBIT:
            case OpenSHC::Commands::M_MAPPER_CAMEL:
            case OpenSHC::Commands::M_MAPPER_CROW_SEAGULL:
            case OpenSHC::Commands::M_MAPPER_SEAGULL:
            /* a single organism is placed on one tile, whatever the brush size */
            brushSize = 1;
            case OpenSHC::Commands::M_MAPPER_RAISE:
            case OpenSHC::Commands::M_MAPPER_LOWER:
            case OpenSHC::Commands::M_MAPPER_EQUALISE:
            case OpenSHC::Commands::M_MAPPER_MOUNTAIN:
            case OpenSHC::Commands::M_MAPPER_HILL:
            case OpenSHC::Commands::M_MAPPER_DELETE:
            gfx = 0x3e;
            break;
            case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
            case OpenSHC::Commands::M_MAPPER_OIL:
            gfx = 0x3d;
            break;
        default:
            gfx = 0x38;
        }
        }

        switch (mapper) {
        case OpenSHC::Commands::M_MAPPER_UNDUGMOAT:
        case OpenSHC::Commands::M_MAPPER_DUGMOAT:
        case OpenSHC::Commands::M_MAPPER_MOAT:
        case OpenSHC::Commands::M_MAPPER_ANTIMOAT:
            /* a moat may not be dug too near an enemy, a signpost, or an opponent's buildings */
            if (DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_EDITOR
                && DAT_GameCore::instance.gameMode_2 != OpenSHC::Game::GM_SIEGE_THAT) {
                int enemyRange;
                int searchRange;
                if (DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY) {
                    enemyRange = 0x1e;
                    searchRange = 30;
                } else {
                    enemyRange = 0xf;
                    searchRange = 7;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isEnemyTooCloseUnk, DAT_PathFindingState::ptr)(
                        DAT_GameSynchronyState::instance.currentPlayerSlotID, x, y, enemyRange)
                    != FALSE) {
                    gfx = 0x3e;
                }
                if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isSignPostWithinDistance, DAT_PathFindingState::ptr)(
                        x, y, DAT_GameState::instance.mapAndTime.unk_signpostDistance + 5)
                    != FALSE) {
                    gfx = 0x3e;
                }
                if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                    int buildRange = MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getCastleBuildRangeForMapSize, this)();
                    if (MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::PathFindingState_Func::isOpponentBuildingInRange, DAT_PathFindingState::ptr)(
                            DAT_GameSynchronyState::instance.currentPlayerSlotID, x, y, searchRange, -1, -1, buildRange + 5)
                        != 0) {
                        gfx = 0x3e;
                    }
                }
            }
        }

        int tile = DAT_ViewportRenderState::instance.translationMatrix[y].addXgetTile + x;
        uint brushY = y;
        if (mapper == OpenSHC::Commands::M_MAPPER_DUGMOAT || mapper == OpenSHC::Commands::M_MAPPER_UNDUGMOAT
            || mapper == OpenSHC::Commands::M_MAPPER_MOAT || mapper == OpenSHC::Commands::M_MAPPER_ANTIMOAT) {
            /* a moat preview always covers the nine tiles around the cursor */
            int index = 0;
            do {
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(0, index, &tile, (int*)&brushY, baseTile, y);
                index++;
                this->ConstructionGFXLayer[tile] = gfx;
            } while (index < 9);
            return;
        }
        if (brushSize < 1) {
            return;
        }
        int index = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getTileForBrush, this)(1, index, &tile, (int*)&brushY, baseTile, y);
            index++;
            this->ConstructionGFXLayer[tile] = gfx;
        } while (index < brushSize);
    }

}
}
