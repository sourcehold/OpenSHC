#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
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

    using DE::SHCDE::eSFX;

    // FUNCTION: STRONGHOLDCRUSADER 0x00418100
    void Buildings::UpdateCampGround()
    {
        int* piVar1;
        short sVar2;
        uint uVar3;
        int iVar4;
        int _currentBuildingID;
        short _ownerPlayerIndex;
        int _vclock;
        _currentBuildingID = DAT_CurrentBuildingID::instance;
        _ownerPlayerIndex = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;
        if ((char)DAT_BuildingDefinedData::instance
                .CampGroundAnimationFrames[DAT_BuildingsState::instance.buildings[_currentBuildingID].animationIndex]
            <= '\0') {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[_currentBuildingID].animationCycleCount
                = DAT_BuildingsState::instance.buildings[_currentBuildingID].animationCycleCount + 1;
            DAT_SFX_Interval_Campfire::instance = DAT_SFX_Interval_Campfire::instance + 1;
            DAT_BuildingsState::instance.buildings[_currentBuildingID].animationCycleCompleted = 1;
            if (1 <= DAT_SFX_Interval_Campfire::instance) {
                DAT_SFX_Interval_Campfire::instance = 0;
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[_currentBuildingID].x,
                    (int)((short)DAT_BuildingsState::instance.buildings[_currentBuildingID].y), DE::SHCDE::FX_CAMPFIRE);
                _currentBuildingID = DAT_CurrentBuildingID::instance;
            }
        }
        if ((!DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile)
            || (DAT_TileMapState::instance
                    .BuildingLayer[DAT_ViewportRenderState::instance.viewportState.mouseAtomRefFloorTile]
                != _currentBuildingID)) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].displayOwnerFlag = 0;
        } else {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].displayOwnerFlag = 1;
        }
        _vclock = DAT_GameState::instance.playerDataArray[_ownerPlayerIndex].vclock;
        DAT_BuildingsState::instance.buildings[_currentBuildingID].campgroundVclock = _vclock;
        if (_vclock < 0) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campgroundVclock = 0;
        } else if (4000 < _vclock) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campgroundVclock = 4000;
        }
        iVar4 = DAT_BuildingsState::instance.buildings[_currentBuildingID].campgroundVclock / 40;
        _vclock = iVar4 + -0x32;
        DAT_BuildingsState::instance.buildings[_currentBuildingID].campgroundVclock = _vclock;
        if (_vclock < 0) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].extraAnimationSprite1
                = *(int*)((int)DAT_BuildingDefinedData::ptr + _vclock * -4 + 0xa46c) + 51;
        } else {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].extraAnimationSprite1
                = DAT_BuildingDefinedData::instance.SpawnUnitProperties[0xc][iVar4 + 6];
        }
        if (DAT_BuildingsState::instance.buildings[_currentBuildingID].field192_0x270 == 0) {
            if (DAT_BuildingsState::instance.buildings[_currentBuildingID].field193_0x272 != 0) {
                if (DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation == 0) {
                    if (0x27 < DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10) {
                        DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation = 1;
                    }
                    goto LAB_0041827d;
                }
                goto LAB_00418285;
            }
            if (DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation != 0) {
                if (DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 <= 0) {
                    DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation = 0;
                }
                DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 + -1;
                goto LAB_004182b0;
            }
            DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 = 0;
        } else {
            if (DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation == 0) {
                if (DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 < 0x28) {
                LAB_0041827d:
                    DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10
                        = DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 + 1;
                } else {
                    DAT_BuildingsState::instance.buildings[_currentBuildingID].renderAnimation = 1;
                    DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10
                        = DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 + 1;
                }
            } else {
            LAB_00418285:
                DAT_BuildingsState::instance.buildings[_currentBuildingID].extraOverlayImage10 = 0x28;
            }
        LAB_004182b0:
            DAT_BuildingsState::instance.buildings[_currentBuildingID].animationFrame
                = (char)DAT_BuildingDefinedData::instance.CampGroundAnimationFrames
                      [DAT_BuildingsState::instance.buildings[_currentBuildingID].animationIndex]
                + 0xb;
        }
        _ownerPlayerIndex = DAT_BuildingsState::instance.buildings[_currentBuildingID].field192_0x270;
        if (_ownerPlayerIndex <= 1) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = 1;
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious = 1;
            goto LAB_00418476;
        }
        if (_ownerPlayerIndex <= 4) {
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = 3;
            DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious = 3;
            goto LAB_00418476;
        }
        sVar2 = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
        if (sVar2 == 3) {
            if (1000 < DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive) {
                DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = 5;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress = 0;
            }
            goto LAB_00418476;
        }
        if (sVar2 == 2) {
            if (200 < DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive) {
                DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = 4;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress = 0;
            }
            goto LAB_00418476;
        }
        if (sVar2 == 4) {
            if (600 < DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive) {
                DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = 3;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress = 0;
            }
            goto LAB_00418476;
        }
        if (sVar2 == 5) {
            uVar3 = DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive;
            if (uVar3 != 1) {
                if ((int)uVar3 <= 0x12c)
                    goto LAB_00418476;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress + 1;
                if (5 < DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress) {
                    _ownerPlayerIndex = 6;
                    DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress = 0;
                } else {
                LAB_0041845a:
                    _ownerPlayerIndex = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
                }
            LAB_00418461:
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStagePrevious
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].campStage = _ownerPlayerIndex;
                goto LAB_00418476;
            }
            _vclock = 1;
        } else {
            if (sVar2 != 6)
                goto LAB_00418476;
            uVar3 = DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive;
            if (uVar3 != 1) {
                if ((int)uVar3 <= 0x50)
                    goto LAB_00418476;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].timeAlive = 0;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress
                    = DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress + 1;
                if (DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress <= 0xc)
                    goto LAB_0041845a;
                _ownerPlayerIndex = 2;
                DAT_BuildingsState::instance.buildings[_currentBuildingID].buildingProgress = 0;
                goto LAB_00418461;
            }
            _vclock = 100;
        }
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updatePeasantSeatingAtBuilding, DAT_TribesState::ptr)(
            _currentBuildingID, (int)(_ownerPlayerIndex), _vclock);
        _currentBuildingID = DAT_CurrentBuildingID::instance;
    LAB_00418476:
        DAT_BuildingsState::instance.buildings[_currentBuildingID].field192_0x270 = 0;
        DAT_BuildingsState::instance.buildings[_currentBuildingID].field193_0x272 = 0;
    }

}
}
