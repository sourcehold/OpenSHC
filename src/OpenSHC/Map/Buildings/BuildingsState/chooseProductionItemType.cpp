#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;
        using OpenSHC::Map::Buildings::BuildingLogicalState;
        using OpenSHC::Map::Buildings::BuildingType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A8A0
        int BuildingsState::chooseProductionItemType(int playerID, BuildingType buildingType)
        {
            // Produce the item that the player's workshops of this type currently produce the least
            int first = 0;
            int second = 0;
            for (int i = 1; i < this->maxBuildingsCount; ++i) {
                if (this->buildings[i].logicalState == BLS_NORMAL && this->buildings[i].owner == playerID
                    && this->buildings[i].buildingType == buildingType) {
                    bool producesFirst;
                    if (buildingType == BT_BLACKSMITH) {
                        producesFirst = this->buildings[i].producedItemTypeNext == OpenSHC::Game::Resources::RT_SWORD;
                    } else if (buildingType == BT_POLETURNER) {
                        producesFirst = this->buildings[i].producedItemTypeNext == OpenSHC::Game::Resources::RT_SPEAR;
                    } else if (buildingType == BT_FLETCHER) {
                        producesFirst = this->buildings[i].producedItemTypeNext == OpenSHC::Game::Resources::RT_BOW;
                    } else {
                        continue;
                    }
                    if (producesFirst) {
                        ++first;
                    } else {
                        ++second;
                    }
                }
            }

            if (buildingType == BT_BLACKSMITH) {
                return first <= second ? OpenSHC::Game::Resources::RT_SWORD : OpenSHC::Game::Resources::RT_MACE;
            }
            if (buildingType == BT_POLETURNER) {
                return first > second ? OpenSHC::Game::Resources::RT_PIKE : OpenSHC::Game::Resources::RT_SPEAR;
            }
            if (buildingType == BT_FLETCHER) {
                return first > second ? OpenSHC::Game::Resources::RT_CROSSBOW : OpenSHC::Game::Resources::RT_BOW;
            }
            return 0;
        }

    }
}
}
