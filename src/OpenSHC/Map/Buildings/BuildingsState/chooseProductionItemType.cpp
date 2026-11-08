#include "../BuildingsState.func.hpp"

#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

namespace OpenSHC {
namespace Map {
    namespace Buildings {

        using OpenSHC::Game::Resources::ResourceType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0040A8A0
        int BuildingsState::chooseProductionItemType(int playerID, BuildingType buildingType)
        {
            int matchingCount = 0;
            int otherCount = 0;
            for (int buildingID = 1; buildingID < this->maxBuildingsCount; ++buildingID) {
                if (this->buildings[buildingID].logicalState == BLS_NORMAL
                    && this->buildings[buildingID].owner == playerID
                    && this->buildings[buildingID].buildingType == buildingType) {
                    if (buildingType == BT_BLACKSMITH) {
                        if (this->buildings[buildingID].producedItemTypeNext == Game::Resources::RT_SWORD) {
                            ++matchingCount;
                        } else {
                            ++otherCount;
                        }
                    } else if (buildingType == BT_POLETURNER) {
                        if (this->buildings[buildingID].producedItemTypeNext == Game::Resources::RT_SPEAR) {
                            ++matchingCount;
                        } else {
                            ++otherCount;
                        }
                    } else if (buildingType == BT_FLETCHER) {
                        if (this->buildings[buildingID].producedItemTypeNext == Game::Resources::RT_BOW) {
                            ++matchingCount;
                        } else {
                            ++otherCount;
                        }
                    }
                }
            }
            if (buildingType == BT_BLACKSMITH) {
                return matchingCount <= otherCount ? Game::Resources::RT_SWORD : Game::Resources::RT_MACE;
            }
            if (buildingType == BT_POLETURNER) {
                return matchingCount > otherCount ? Game::Resources::RT_PIKE : Game::Resources::RT_SPEAR;
            }
            if (buildingType == BT_FLETCHER) {
                return matchingCount > otherCount ? Game::Resources::RT_CROSSBOW : Game::Resources::RT_BOW;
            }
            return 0;
        }

    }
}
}
