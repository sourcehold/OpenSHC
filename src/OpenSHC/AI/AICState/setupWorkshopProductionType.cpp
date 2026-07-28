#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AIType.hpp"
#include "OpenSHC/AI/AITypeInt.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Game/Resources/ResourceTypeShort.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::AI::AIType;
    using OpenSHC::AI::AITypeInt;
    using OpenSHC::Game::Resources::ResourceType;
    using OpenSHC::Game::Resources::ResourceTypeShort;
    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::Map::Buildings::BuildingTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004CBE30
    void AICState ::setupWorkshopProductionType(int playerID, int buildingID)
    {
        AITypeInt AVar1 = DAT_GameState::instance.playerDataArray[playerID].aiType;

        if (AVar1 == OpenSHC::AI::AIT_NULL)
            return;

        BuildingTypeShort _buildingType = DAT_BuildingsState::instance.buildings[buildingID].buildingType;
        int _aiTypeMin1 = AVar1 + ~OpenSHC::AI::AIT_NULL;

        if (_buildingType == OpenSHC::Map::Buildings::BT_BLACKSMITH) {
            _aiTypeMin1 = *(int*)((int)this + _aiTypeMin1 * 0x2a4 + 200);
            if (_aiTypeMin1 == -999) {
                _aiTypeMin1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::chooseProductionItemType,
                    DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                    OpenSHC::Map::Buildings::BT_BLACKSMITH);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)_aiTypeMin1;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)_aiTypeMin1;
                return;
            }
            if (_aiTypeMin1 == 0x16) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_SWORD;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_SWORD;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_MACE;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_MACE;
            }
            return;
        }

        if (_buildingType == OpenSHC::Map::Buildings::BT_POLETURNER) {
            _aiTypeMin1 = *(int*)((int)this + _aiTypeMin1 * 0x2a4 + 0xd0);
            if (_aiTypeMin1 == -999) {
                _aiTypeMin1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::chooseProductionItemType,
                    DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                    OpenSHC::Map::Buildings::BT_POLETURNER);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)_aiTypeMin1;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)_aiTypeMin1;
                return;
            }
            if (_aiTypeMin1 == 0x13) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_SPEAR;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_SPEAR;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_PIKE;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_PIKE;
            }
            return;
        }

        if (_buildingType == OpenSHC::Map::Buildings::BT_FLETCHER) {
            _aiTypeMin1 = *(int*)((int)this + _aiTypeMin1 * 0x2a4 + 0xcc);
            if (_aiTypeMin1 == -999) {
                _aiTypeMin1 = MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::chooseProductionItemType,
                    DAT_BuildingsState::ptr)((int)DAT_BuildingsState::instance.buildings[buildingID].owner,
                    OpenSHC::Map::Buildings::BT_FLETCHER);
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = (ResourceTypeShort)_aiTypeMin1;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = (ResourceTypeShort)_aiTypeMin1;
                return;
            }
            if (_aiTypeMin1 == 0x11) {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_BOW;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_BOW;
            } else {
                DAT_BuildingsState::instance.buildings[buildingID].producedItemType = OpenSHC::Game::Resources::RT_CROSSBOW;
                DAT_BuildingsState::instance.buildings[buildingID].producedItemTypeNext = OpenSHC::Game::Resources::RT_CROSSBOW;
            }
        }

        return;
    }
}
}
