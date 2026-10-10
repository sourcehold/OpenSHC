#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;

    // FUNCTION: STRONGHOLDCRUSADER 0x00418740
    void Buildings::UpdateGoodBuildingMaypole()
    {
        int* piVar1;
        byte bVar2;
        int sVar3;
        int iVar4;
        int iVar5;
        iVar4 = DAT_CurrentBuildingID::instance;
        sVar3 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk
            = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].fireRelatedRNG1 % 9;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar4);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar4 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
            iVar4, 1);
        DAT_BuildingsState::instance.buildings[iVar4].renderAnimation
            = (ushort)(0 < DAT_GameState::instance.playerDataArray[sVar3].fearFactorLevel);
        DAT_BuildingsState::instance.buildings[iVar4].spriteOffetX = -0x23;
        DAT_BuildingsState::instance.buildings[iVar4].spriteOffetY = -0x4f;
        if (DAT_GameState::instance.playerDataArray[sVar3].popularity
            < (int)((DAT_BuildingsState::instance.buildings[iVar4].fireRelatedRNG1 & 0xffU) + 5000)) {
            iVar5
                = (char)DAT_BuildingDefinedData::instance
                      .GoodBuildingMaypoleAnimationFrames2[DAT_BuildingsState::instance.buildings[iVar4].animationIndex]
                + 0x20;
            DAT_BuildingsState::instance.buildings[iVar4].animationFrame = iVar5;
            if (iVar5 < 0x21) {
                DAT_BuildingsState::instance.buildings[iVar4].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar4].animationFrame = 0x21;
            }
        } else {
            bVar2 = DAT_BuildingDefinedData::instance.GoodBuildingMaypoleAnimationFrames1
                        [DAT_BuildingsState::instance.buildings[iVar4].animationIndex];
            DAT_BuildingsState::instance.buildings[iVar4].animationFrame = (int)(char)bVar2;
            if ((char)bVar2 <= 0) {
                piVar1 = &DAT_BuildingsState::instance.buildings[iVar4].animationCycleCount;
                *piVar1 = *piVar1 + 1;
                DAT_BuildingsState::instance.buildings[iVar4].animationIndex = 0;
                DAT_BuildingsState::instance.buildings[iVar4].animationFrame = 1;
                if (!(DAT_BuildingsState::instance.buildings[iVar4].animationCycleCount & 7)) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                        (int)(short)DAT_BuildingsState::instance.buildings[iVar4].x,
                        (int)((short)DAT_BuildingsState::instance.buildings[iVar4].y), DE::SHCDE::FX_MAYPOLE);
                }
            }
        }
    }

}
}
