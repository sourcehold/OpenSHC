#include "../GameStateStructures.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Entities/EntityState.func.hpp"
#include "OpenSHC/Random/RNG.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/Map/Entities/EntityType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_EntityState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::DE::SHCDE::eSFX;
    using OpenSHC::Map::Entities::EntityType;

    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00459A20
    void GameStateStructures::spawnPoisonCloudsAroundBuilding(int buildingID)
    {
        int attemptsLeft = 20;
        uint xPosition;
        uint yPosition;
        int rowTile;
        while (true) {
            xPosition = (int)SEC_RNG::instance.currentNumber2 % 30 - 15
                + (short)DAT_BuildingsState::instance.buildings[buildingID].x;
            yPosition = ((int)SEC_RNG::instance.currentNumber2 >> 8) % 30 - 15
                + (short)DAT_BuildingsState::instance.buildings[buildingID].y;
            MACRO_CALL_MEMBER(OpenSHC::Random::RNG_Func::nextRandomNumber2, SEC_RNG::ptr)();
            if ((xPosition <= 399) && (yPosition <= 399)
                && (DAT_ViewportRenderState::instance.DAT_BinaryTileMap400x400[yPosition * 400 + xPosition] != 0)) {
                rowTile = DAT_ViewportRenderState::instance.translationMatrix[yPosition].addXgetTile;
                if ((DAT_TileMapState::instance.LogicLayer[rowTile + xPosition] & 0x4a5014b1U) == 0) {
                    break;
                }
            }
            attemptsLeft = attemptsLeft - 1;
            if (attemptsLeft <= 0) {
                return;
            }
        }
        int cloudCount = (int)SEC_RNG::instance.currentNumber2 % 5 - 2;
        if (cloudCount < 8) {
            for (cloudCount = 8 - cloudCount; cloudCount != 0; cloudCount = cloudCount - 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Entities::EntityState_Func::spawnProjectileEntity,
                    DAT_EntityState::ptr)(0, 0, 0, xPosition * 8, yPosition * 8,
                    DAT_TileMapState::instance.EntityLayerLT25[rowTile + xPosition + 0x13a10], 0, 0, 0,
                    OpenSHC::Map::Entities::ET_COW_POISON_CLOUD, 0);
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
            xPosition, yPosition, OpenSHC::DE::SHCDE::FX_FLIES);
        MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::setSpawnMoment, DAT_MinimapViewState::ptr)(
            xPosition, yPosition);
    }
}
}
