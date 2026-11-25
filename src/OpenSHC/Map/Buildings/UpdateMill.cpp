#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00416F80
    void Buildings::UpdateMill()
    {
        int workerCount = 0;
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter += 1;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter > 1) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter = 0;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationTickCounter == 1) {
            return;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[0] != 0) {
            workerCount = 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[1] != 0) {
            workerCount += 1;
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].workers[2] != 0) {
            workerCount += 1;
        }
        int const unitID = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID;
        if (unitID != 0) {
            if (DAT_UnitsState::instance.units[unitID].logicalState != OpenSHC::Map::Units::ULS_NORMAL) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].unitType != OpenSHC::Map::Units::UT_MILLER) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID = 0;
            }
            if (DAT_UnitsState::instance.units[unitID].state.generic != OpenSHC::Map::Units::States::US_AIM_WEAPONUnk) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID = 0;
            }
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            }
        }
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 1;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive = 0;
        }
        int const firstTickInLoop = DAT_BuildingsState::instance.isFirstTickInLoop;
        DAT_BuildingsState::instance.isFirstTickInLoop = 1;
        MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::updateVisuallyActiveState,
            DAT_BuildingsState::ptr)(DAT_CurrentBuildingID::instance);
        int const visuallyActive
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        DAT_BuildingsState::instance.isFirstTickInLoop = (BOOLEnum)firstTickInLoop;
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive
            != DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState) {
            MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::updateBuildingGraphicsLayer, DAT_TileMapState::ptr)(
                DAT_CurrentBuildingID::instance);
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].oldVisualActiveState
                = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingIsVisuallyActive;
        }

        // The sails slow down as outpostRelatedUnk4 counts down; MillAnimationFrames2..5 are declared byte, but the
        // original reads them signed
        if (workerCount <= 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 1;
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 -= 1;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 50) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4
                > 30) {
                if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 1)
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4
                > 20) {
                if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 3)
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
                }
            } else if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 7)
                == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 += 1;
            }
            if (DAT_BuildingDefinedData::instance.MillAnimationFrames1
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4
                = DAT_BuildingDefinedData::instance.MillAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 1;
        }

        int cycleDone = 0;
        if (workerCount > 0 && visuallyActive == 0
            && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 > 50) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4
                > 30) {
                if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 1)
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                }
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4
                > 20) {
                if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 3)
                    == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
                }
            } else if ((DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 & 7)
                == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock += 1;
            }
            if ((char)DAT_BuildingDefinedData::instance.MillAnimationFrames2
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
                cycleDone = 1;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1
                = (char)DAT_BuildingDefinedData::instance.MillAnimationFrames2
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock]
                + 15;
            if (cycleDone != 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].campgroundVclock = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        }
        if (workerCount > 0 && visuallyActive != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 += 1;
            if ((char)DAT_BuildingDefinedData::instance.MillAnimationFrames3
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                = (char)DAT_BuildingDefinedData::instance.MillAnimationFrames3
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1]
                + 30;
            // The original overwrites the sprite it just animated
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2
                = DAT_BuildingDefinedData::instance.MillAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame3]
                + 30;
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame1 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        }

        int stageDone = 0;
        if (workerCount > 0 && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].unitID != 0) {
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 46;
                stageDone = 1;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 1) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if ((char)DAT_BuildingDefinedData::instance.MillAnimationFrames4
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    stageDone = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = (char)DAT_BuildingDefinedData::instance.MillAnimationFrames4
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    + 45;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 += 1;
                if ((char)DAT_BuildingDefinedData::instance.MillAnimationFrames5
                        [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    <= 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                    stageDone = 1;
                }
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3
                    = (char)DAT_BuildingDefinedData::instance.MillAnimationFrames5
                          [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2]
                    + 61;
            } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 3) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 46;
                stageDone = 1;
            }
            if (stageDone != 0) {
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 0) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 1;
                } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 1
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 2
                    || DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField == 3) {
                    DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 3;
                }
            }
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationFrame2 = 0;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].outpostRelatedUnk4 == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].killingPitField = 0;
            }
        }
        if (DAT_GameSynchronyState::instance.currentGameMode != 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage += 1;
            if (DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                    [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID
                = DAT_BuildingDefinedData::instance.SharedOverlayAnimationFrames
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].flagSlot.overlayImage
                          / 2];
        } else {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].overlayImageID = 0;
        }
    }

}
}
