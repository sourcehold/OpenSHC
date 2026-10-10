#include "../../Map.func.hpp"
#include "../Buildings.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/DE/SHCDE/eSFX.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_CurrentBuildingID.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace Map {

    using DE::SHCDE::eSFX;
    using UI::Enums::BuildingsAndStatusMenuTabType;
    using UI::Enums::MenuViewType;

    // FUNCTION: STRONGHOLDCRUSADER 0x00418F90
    void Buildings::UpdateBadBuildingBurningStake()
    {
        short sVar1;
        int iVar2;
        int iVar3;
        iVar2 = DAT_CurrentBuildingID::instance;
        sVar1 = DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].owner;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].playerColorUnk = 0;
        MACRO_CALL_MEMBER(AI::AICState_Func::addBuildingToTargetableBuildings, DAT_AICState::ptr)(iVar2);
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::addBuildingInRegistry, DAT_GameState::ptr)(
            DAT_CurrentBuildingID::instance);
        iVar3 = DAT_CurrentBuildingID::instance;
        DAT_BuildingsState::instance.buildings[DAT_CurrentBuildingID::instance].displayOwnerFlag = 0;
        DAT_BuildingsState::instance.buildings[iVar3].renderBlendStrength = 0;
        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::updateBuildingSignpostCounter, DAT_BuildingsState::ptr)(
            iVar3, 1);
        iVar2 = DAT_GameState::instance.playerDataArray[sVar1].fearFactorLevel;
        DAT_BuildingsState::instance.buildings[iVar3].renderAnimation = (ushort)(iVar2 < -4);
        if (iVar2 < -4) {
            DAT_BuildingsState::instance.buildings[iVar3].animationFrame
                = (int)(char)DAT_BuildingDefinedData::instance.BadBuildingBurningStakeAnimationFrames
                      [DAT_BuildingsState::instance.buildings[iVar3].animationIndex];
        }
        if (DAT_BuildingsState::instance.buildings[iVar3].animationFrame < 1) {
            DAT_BuildingsState::instance.buildings[iVar3].animationIndex = 0;
            DAT_BuildingsState::instance.buildings[iVar3].animationFrame = 1;
        }
        if (DAT_BuildingsState::instance.buildings[iVar3].animationActive != 0
            && DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_BUILDING_AND_STATUS_MENU
            && DAT_GameCore::instance.activeMenuTab.tabType == UI::Enums::BASMTT_BURNINGSTAKE
            && iVar3 == DAT_BuildingsState::instance.menuSelectedBuildingID) {
            if (DAT_BuildingsState::instance.buildings[iVar3].animationIndex == 0x2f) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar3].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar3].y)), DE::SHCDE::FX_WITCH_BURN);
                iVar3 = DAT_CurrentBuildingID::instance;
            }
            if (DAT_BuildingsState::instance.buildings[iVar3].animationIndex == 0x31) {
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocation, DAT_SFXState::ptr)(
                    (int)(short)DAT_BuildingsState::instance.buildings[iVar3].x,
                    (int)((int)((short)DAT_BuildingsState::instance.buildings[iVar3].y)), DE::SHCDE::FX_WITCH_SCREAM);
            }
        }
    }

}
}
