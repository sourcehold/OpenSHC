#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace Map {

    // FUNCTION: STRONGHOLDCRUSADER 0x004196D0
    void Buildings::UpdateGoodBuildingDancingBear()
    {
        byte bVar1;
        int sVar2 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(
            DAT_CurrentBuildingID::instance);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        int iVar3 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[iVar3].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
            iVar3, 1);
        DAT_BuildingsState::instance.buildings[iVar3].renderAnimation
            = (ushort)(2 < DAT_GameState::instance.playerDataArray[sVar2].fearFactorLevel);
        bVar1
            = DAT_BuildingDefinedData::instance
                  .GoodBuildingDancingBearAnimationFrames[DAT_BuildingsState::instance.buildings[iVar3].animationIndex];
        DAT_BuildingsState::instance.buildings[iVar3].animationFrame = (int)(char)bVar1;
        if ((char)bVar1 <= 0) {
            DAT_BuildingsState::instance.buildings[iVar3].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar3].animationFrame = 1;
        }
    }

}
}
