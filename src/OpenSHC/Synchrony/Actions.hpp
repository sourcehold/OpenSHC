/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/Synchrony/Actions.hpp'
*/

#pragma once

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeMin1.hpp"
namespace OpenSHC {
namespace Synchrony {
    namespace Actions {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Game::Resources::ResourceTypeMin1;

        void __cdecl RemovePositionOfPlayer(int playerID);

        void __cdecl ProcessRecruitUnit(int playerID, int unitType, undefined4 recruitmentBuildingID);

        void __cdecl SetBuildingProductionType(
            undefined4 playerID, int buildingID, int producedItemType, int buildingUID);

        void __cdecl OpenOrCloseDrawbridge(undefined4 param_1, int buildingID, int value, int buildingUID);

        void __cdecl GateOpenOrClose(undefined4 playerID, int buildingID, int newGateState, int buildingUID);

        void __cdecl ChangeTaxes(int playerID, int taxesSetting);

        void __cdecl ChangeRations(int playerID, int rationsSetting);

        void __cdecl ProcessBuyOrSell(int playerID, int buyOrSell, ResourceType resourceType);

        void __cdecl TryAcquireAmmunitionOrPlanToBuyStone(int param_1, int param_2);

        short* __cdecl SelectionReplenishAmmo(int playerID, int param_2);

        void __cdecl ProcessBuildingSleepUpdate(int playerID, int buildingType);

        void __cdecl ProcessTowerRepair(
            int playerID, int buildingID, int requiredWood, int requiredStone, int gameObjectID);

        void __cdecl ProcessReleaseDogs(int displayColor, int buildingID, int buildingUID);

        void __cdecl ProcessAllyAcceptsRequest(int param_1, int param_2);

        void __cdecl ProcessAllyDeniesRequest2(int param_1, int param_2);

        void __cdecl ProcessAllyRequestAttackDefense(
            int targetPlayerID, int playerID, int requestedByPlayerID, int param_4);

        void __cdecl ProcessAllyRequestingGoods(
            int askedPlayerID, ResourceTypeMin1 requestedResource, int amount, int askee);

        void __cdecl ProcessAllyGoodsRequest(
            int receiverPlayerID, ResourceType requestedResource, int amount, int senderPlayerID);

        void __cdecl ProcessAllyDeniesRequest(int param_1, int param_2);

    } // namespace Actions
} // namespace Synchrony
} // namespace OpenSHC
