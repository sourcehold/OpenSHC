#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x0041EB00
    void Buildings::UpdateTower3()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int const buildingID = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[buildingID].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite1 = 4;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
        DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10 = 0;
        DAT_BuildingsState::instance.buildings[buildingID].someX
            = DAT_BuildingsState::instance.buildings[buildingID].x + 2;
        DAT_BuildingsState::instance.buildings[buildingID].someY
            = DAT_BuildingsState::instance.buildings[buildingID].y + 2;
        DAT_BuildingsState::instance.buildings[buildingID].buildingProgress += 1;
        if (DAT_BuildingsState::instance.buildings[buildingID].buildingProgress >= 40) {
            DAT_BuildingsState::instance.buildings[buildingID].buildingProgress = 0;
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::computeBuildingEntranceFlagsForOrientations,
                DAT_BuildingsState::ptr)(buildingID);
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingExitFlagForOrientation,
                DAT_BuildingsState::ptr)(buildingID)
            != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite2 = 81;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        if (MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::hasBuildingEntranceFlagForOrientation,
                DAT_BuildingsState::ptr)(buildingID)
            != 0) {
            DAT_BuildingsState::instance.buildings[buildingID].extraAnimationSprite4 = 90;
            DAT_BuildingsState::instance.buildings[buildingID].animationFrame = 1;
        }
        int damage[8] = { 0 };
        int cracks = 9
            - DAT_BuildingsState::instance.buildings[buildingID].currentHealth * 9
                / DAT_BuildingsState::instance.buildings[buildingID].maxHealth;
        if (cracks > 8) {
            cracks = 8;
        }
        if (cracks != 0) {
            if (cracks > 0) {
                int seed = DAT_BuildingsState::instance.buildings[buildingID].fireRelatedRNG1;
                int slot = seed >> 8;
                for (int i = cracks; i != 0; --i) {
                    damage[slot & 7] = (seed & 0xf) + 1;
                    ++seed;
                    ++slot;
                }
            }
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage5 = damage[0];
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage6 = damage[1];
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage7 = damage[2];
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage8 = damage[3];
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage9 = damage[4];
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = damage[5];
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = damage[6];
            DAT_BuildingsState::instance.buildings[buildingID].extraOverlayImage10 = damage[7];
        }
        if (DAT_BuildingsState::instance.field34_0x18e074 == 0) {
            return;
        }
        // Mark the tiles listed for the current map orientation, clear the rest
        int i = 0;
        do {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(
                i, 5);
            int const tile
                = DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y
                          + DAT_TileMapState::instance.buildingY]
                      .addXgetTile
                + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                + DAT_TileMapState::instance.buildingX;
            DAT_TileMapState::instance.MiscDisplayLayer[tile] &= ~0x10;
            for (int j = 0; j < 6; ++j) {
                if (DAT_BuildingDefinedData::instance
                        .field420_0xa77c[DAT_TileMapState::instance.mapOrientation / 2 * 6 + j]
                    == i) {
                    DAT_TileMapState::instance.MiscDisplayLayer[tile] |= 0x10;
                    break;
                }
            }
            ++i;
        } while (i < DAT_TileMapState::instance.constructionTileCount);
    }

}
}
