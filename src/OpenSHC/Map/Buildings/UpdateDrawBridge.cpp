#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x00417B90
    void Buildings::UpdateDrawBridge()
    {
        int const owner = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        int direction = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].buildingVariation
            - DAT_TileMapState::instance.mapOrientation;
        if (direction < 0) {
            direction += 8;
        }
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 0;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIncrement = 1;

        // DrawBridgeAnimationFrames1/2 are declared byte, but the original reads them signed
        if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[direction / 2];
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeState2 == 10
                && !MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::isUnitBlockingSizeFiveFootprint,
                    DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance)) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 = 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::floodMoatUnderRemovedBuilding,
                    DAT_TileMapState::ptr)(DAT_CurrentBuildingID::instance);
                DAT_GameState::instance.playerDataArray[owner].someCount31 += 1;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeState2 = 12;
            }
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 1;
            if (direction == 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite1 = 79;
            } else if (direction == 2) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite2 = 80;
            } else if (direction == 4) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite3 = 77;
            } else if (direction == 6) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].extraAnimationSprite4 = 78;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 == 2) {
            DAT_GameState::instance.playerDataArray[owner].someCount31 += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                = DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[direction / 2] + 7;
            if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeState2 == 11) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 = 3;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawbridgeState2 = 12;
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 == 1) {
            DAT_GameState::instance.playerDataArray[owner].someCount31 += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            char const frame
                = (char)DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames1
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 = 2;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    = frame + DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[direction / 2];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_RAISING);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 24
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_RAISED);
                }
            }
        } else if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 == 3) {
            DAT_GameState::instance.playerDataArray[owner].someCount31 += 1;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderAnimation = 1;
            char const frame
                = (char)DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames2
                      [DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex];
            if (frame <= 0) {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].drawBridgeState1 = 0;
                MACRO_CALL_MEMBER(OpenSHC::Map::TileMapState_Func::createWaterForDrawBridge, DAT_TileMapState::ptr)(
                    DAT_CurrentBuildingID::instance);
            } else {
                DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationFrame
                    = frame + DAT_BuildingDefinedData::instance.DrawBridgeAnimationFrames[direction / 2];
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 1
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_CONTROL);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 5
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_LOWERING);
                }
                if (DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationIndex == 28
                    && DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].animationActive != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].x,
                        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].y,
                        OpenSHC::DE::SHCDE::FX_DRAWBRIDGE_LOWERED);
                }
            }
        }
        if (direction == 0) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -89;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -154;
        } else if (direction == 2) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -87;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -152;
        } else if (direction == 4) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -101;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -153;
        } else if (direction == 6) {
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetX = -98;
            DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].spriteOffetY = -156;
        }
    }

}
}
