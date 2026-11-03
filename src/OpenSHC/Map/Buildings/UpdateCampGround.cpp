#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_SFX_Interval_Campfire.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00418100
    void Buildings::UpdateCampGround()
    {
        // CampGroundAnimationFrames is declared byte, but the original reads it signed
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        if ((char)DAT_BuildingDefinedData::instance.CampGroundAnimationFrames
                [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
            <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCount += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationCycleCompleted = 1;
            DAT_SFX_Interval_Campfire::instance += 1;
            if ((int)DAT_SFX_Interval_Campfire::instance >= 1) {
                DAT_SFX_Interval_Campfire::instance = 0;
                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                    OpenSHC::DE::SHCDE::FX_CAMPFIRE);
            }
        }
        if (DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile != 0
            && DAT_TileMapState::instance
                    .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                == DAT_CurrentBuildingID::instance) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        }

        // The fire burns according to the owner's popularity clock
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock
            = DAT_GameState::instance.playerDataArray[owner].vclock;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock > 4000) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 4000;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock / 40 - 50;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock < 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                = DAT_BuildingDefinedData::instance.field416_0xa46c
                      [-DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                + 51;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                = DAT_BuildingDefinedData::instance.field415_0xa39c
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock];
        }

        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270 != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 >= 40) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 40;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.CampGroundAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 11;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field156_0x272 != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation == 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 >= 40) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 += 1;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 40;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.CampGroundAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 11;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 -= 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = (char)DAT_BuildingDefinedData::instance.CampGroundAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex]
                + 11;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraOverlayImage10 = 0;
        }

        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270 <= 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious = 1;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270 <= 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = 3;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious = 3;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage == 3) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive > 1000) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = 5;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage == 2) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive > 200) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = 4;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage == 4) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive > 600) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = 3;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage == 5) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updatePeasantSeatingAtBuilding,
                    DAT_TribesState::ptr)(DAT_CurrentBuildingID::instance,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270, 1);
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive > 300) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress += 1;
                int nextStage;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress > 5) {
                    nextStage = 6;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                } else {
                    nextStage = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = nextStage;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage == 6) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive == 1) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::updatePeasantSeatingAtBuilding,
                    DAT_TribesState::ptr)(DAT_CurrentBuildingID::instance,
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270, 100);
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive > 80) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress += 1;
                int nextStage;
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress > 12) {
                    nextStage = 2;
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingProgress = 0;
                } else {
                    nextStage = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campStage = nextStage;
            }
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field155_0x270 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].field156_0x272 = 0;
    }

}
}
