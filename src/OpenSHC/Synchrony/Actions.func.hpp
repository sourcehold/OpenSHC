/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Actions.func.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Synchrony/Actions.hpp"
namespace OpenSHC {
namespace Synchrony {
    namespace Actions_Func {

        using OpenSHC::Game::Resources::ResourceType;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID), false, Address::SHC_3BB0A8C1_0x004285C0,
            &OpenSHC::Synchrony::Actions::RemovePositionOfPlayer)
        RemovePositionOfPlayer;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int unitType, undefined4 recruitmentBuildingID), false,
            Address::SHC_3BB0A8C1_0x00464EF0, &OpenSHC::Synchrony::Actions::ProcessRecruitUnit)
        ProcessRecruitUnit;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(undefined4 playerID, int buildingID, ushort producedItemType, int buildingUID), false,
            Address::SHC_3BB0A8C1_0x004652A0, &OpenSHC::Synchrony::Actions::SetBuildingProductionType)
        SetBuildingProductionType;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, int buildingID, int value, int buildingUID), false,
            Address::SHC_3BB0A8C1_0x004653B0, &OpenSHC::Synchrony::Actions::OpenOrCloseDrawbridge)
        OpenOrCloseDrawbridge;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 playerID, int buildingID, int newGateState, int buildingUID),
            false, Address::SHC_3BB0A8C1_0x004654F0, &OpenSHC::Synchrony::Actions::GateOpenOrClose)
        GateOpenOrClose;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int taxesSetting), false, Address::SHC_3BB0A8C1_0x00465800,
            &OpenSHC::Synchrony::Actions::ChangeTaxes)
        ChangeTaxes;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int rationsSetting), false,
            Address::SHC_3BB0A8C1_0x00465890, &OpenSHC::Synchrony::Actions::ChangeRations)
        ChangeRations;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int buyOrSell, ResourceType resourceType), false,
            Address::SHC_3BB0A8C1_0x00465E60, &OpenSHC::Synchrony::Actions::ProcessBuyOrSell)
        ProcessBuyOrSell;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x00465F20,
            &OpenSHC::Synchrony::Actions::TryAcquireAmmunitionOrPlanToBuyStone)
        TryAcquireAmmunitionOrPlanToBuyStone;

        MACRO_FUNCTION_RESOLVER(short*(__cdecl*)(int playerID, int param_2), false, Address::SHC_3BB0A8C1_0x00465F90,
            &OpenSHC::Synchrony::Actions::SelectionReplenishAmmo)
        SelectionReplenishAmmo;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int playerID, int buildingType), false, Address::SHC_3BB0A8C1_0x004660F0,
            &OpenSHC::Synchrony::Actions::ProcessBuildingSleepUpdate)
        ProcessBuildingSleepUpdate;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID), false,
            Address::SHC_3BB0A8C1_0x00466260, &OpenSHC::Synchrony::Actions::ProcessTowerRepair)
        ProcessTowerRepair;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int buildingID, int buildingUID), false,
            Address::SHC_3BB0A8C1_0x00466430, &OpenSHC::Synchrony::Actions::ProcessReleaseDogs)
        ProcessReleaseDogs;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AD110,
            &OpenSHC::Synchrony::Actions::ProcessAllyAcceptsRequest)
        ProcessAllyAcceptsRequest;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AD1E0,
            &OpenSHC::Synchrony::Actions::ProcessAllyDeniesRequest2)
        ProcessAllyDeniesRequest2;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int targetPlayerID, int playerID, int requestedByPlayerID, int param_4),
            false, Address::SHC_3BB0A8C1_0x004AD2F0, &OpenSHC::Synchrony::Actions::ProcessAllyRequestAttackDefense)
        ProcessAllyRequestAttackDefense;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int askedPlayerID, int param_2, int amount, int askee), false,
            Address::SHC_3BB0A8C1_0x004AD7C0, &OpenSHC::Synchrony::Actions::ProcessAllyRequestingGoods)
        ProcessAllyRequestingGoods;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, ResourceType param_2, int param_3, int param_4), false,
            Address::SHC_3BB0A8C1_0x004ADDD0, &OpenSHC::Synchrony::Actions::ProcessAllyGoodsRequest)
        ProcessAllyGoodsRequest;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004AE010,
            &OpenSHC::Synchrony::Actions::ProcessAllyDeniesRequest)
        ProcessAllyDeniesRequest;

    } // namespace Actions_Func
} // namespace Synchrony
} // namespace OpenSHC
