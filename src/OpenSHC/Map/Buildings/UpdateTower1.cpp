#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00418C80
    void Buildings::UpdateTower1()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someY
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y + 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 125;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 124;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 0;
        int damage[8] = { 0 };
        int cracks = 9
            - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentHealth * 9
                / DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].maxHealth;
        if (cracks > 8) {
            cracks = 8;
        }
        if (cracks != 0) {
            if (cracks > 0) {
                int seed = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1;
                int slot = seed >> 8;
                for (int i = cracks; i != 0; --i) {
                    damage[slot & 7] = (seed & 0xf) + 1;
                    ++seed;
                    ++slot;
                }
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = damage[0];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = damage[1];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = damage[2];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = damage[3];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = damage[4];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = damage[5];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = damage[6];
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = damage[7];
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileScanCountdown > 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileScanCountdown -= 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileScanCountdown == 0) {
                int i = 0;
                int unitsOnTop = 0;
                do {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Map::TileMapState_Func::getBuildingSizeIndexMappingData, DAT_TileMapState::ptr)(i, 3);
                    if (DAT_TileMapState::instance
                            .UnitLayer[DAT_ViewportRenderState::instance
                                           .translationMatrix[DAT_BuildingsState::instance
                                                                  .buildings[DAT_CurrentBuildingID::instance]
                                                                  .y
                                               + DAT_TileMapState::instance.buildingY]
                                           .addXgetTile
                                + DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x
                                + DAT_TileMapState::instance.buildingX]
                        != 0) {
                        unitsOnTop = 1;
                        break;
                    }
                    ++i;
                } while (i < DAT_TileMapState::instance.constructionTileCount);
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop = unitsOnTop;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].tileScanCountdown = 100;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].hasUnitsOntop != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 126;
        }
    }

}
}
