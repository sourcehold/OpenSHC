#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00423CD0
    void Buildings::UpdateGateHouseSmall()
    {
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int variation = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateGateDrawBridgeOpenCloseLogic,
            DAT_BuildingsState::ptr)();
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someX
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x + 3;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].someY
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y + 2;
        if (DAT_TileMapState::instance.mapOrientation == 2 || DAT_TileMapState::instance.mapOrientation == 6) {
            variation += 1;
        }
        if (variation > 81) {
            variation = 80;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        if (variation == 80) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 11;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 12;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 0;
        int damage[4] = { 0 };
        int cracks = 5
            - DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].currentHealth * 5
                / DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].maxHealth;
        if (cracks > 4) {
            cracks = 4;
        }
        if (cracks != 0) {
            if (cracks > 0) {
                int seed = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1;
                int slot = seed >> 8;
                for (int i = cracks; i != 0; --i) {
                    damage[slot & 3] = (seed & 0xf) + 1;
                    ++seed;
                    ++slot;
                }
            }
            if (variation == 80) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage5 = damage[0];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage6 = damage[1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage7 = damage[2];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage8 = damage[3];
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage9 = damage[0];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                    = damage[1];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = damage[2];
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = damage[3];
            }
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;

        // GateHouse*AnimationFrames are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState == 10) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState = 12;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            }
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 2) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState == 11) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 3;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].gateState = 12;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            }
            if (variation == 80) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 12;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 6;
            }
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 1) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PC_DROP);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 20) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_PC_SLAM);
                }
            }
            char const frame
                = (char)DAT_BuildingDefinedData::instance.GateHouseOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 2;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(DAT_CurrentBuildingID::instance);
                if (variation == 80) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = 12;
                } else {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = 6;
                }
                return;
            }
            if (variation == 80) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = frame + 6;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = frame;
            }
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 == 3) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0
                && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_PC_LIFT);
            }
            char const frame
                = (char)DAT_BuildingDefinedData::instance.GateHouseLargeAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].pathLinkageRelated2 = 0;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::updatePathLinkageTileMapRelatedToGates,
                    DAT_PathFindingState::ptr)(DAT_CurrentBuildingID::instance);
                return;
            }
            if (variation == 80) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage1 = frame + 6;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage2 = frame;
            }
        }
    }

}
}
