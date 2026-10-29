#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"

namespace OpenSHC {
namespace Map {

    // The game mode is tested before the three stores (cmp at 0x415C20, je at 0x415C3F); SharedOverlayAnimationFrames entries
    // are signed (jg at 0x415C5E).
    // FUNCTION: STRONGHOLDCRUSADER 0x00415BF0
    void Buildings::UpdateTunnelersGuild()
    {
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int buildingID = DAT_CurrentBuildingID::instance;
        bool isNotSolitary = DAT_GameSynchronyState::instance.currentGameMode != Game::GM_SOLITARY;
        short* renderPtr = &DAT_BuildingsState::instance.buildings[buildingID].renderAnimation;
        *renderPtr = 0;
        DAT_BuildingsState::instance.buildings[buildingID].animationIncrement = 1;
        DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag = 0;
        if (isNotSolitary) {
            int* showOverlaysPtr = &DAT_BuildingsState::instance.buildings[buildingID].displayOwnerFlag;
            *showOverlaysPtr = 1;
            DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage += 1;
            if ((char)DAT_BuildingDefinedData::instance
                    .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2]
                <= 0) {
                DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage = 0;
            }
            DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = (char)DAT_BuildingDefinedData::instance
                .SharedOverlayAnimationFrames[DAT_BuildingsState::instance.buildings[buildingID].flagSlot.overlayImage / 2];
            return;
        }
        DAT_BuildingsState::instance.buildings[buildingID].overlayImageID = 0;
    }

}
}
