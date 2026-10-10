#include "../../Map.func.hpp"
#include "../Version.func.hpp"

#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Buildings/Building.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/Map/Buildings/BuildingTypeShort.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"

namespace OpenSHC {
namespace Map {

    using Map::Buildings::Building;
    using Map::Buildings::BuildingLogicalState;
    using Map::Buildings::BuildingType;
    using Map::Buildings::BuildingTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x0041A2E0
    void Version::UpgradeTowerLogicLayer()
    {
        BuildingTypeShort BVar1;
        Building* pBVar2;
        int iVar2;
        iVar2 = 1;
        pBVar2 = &DAT_BuildingsState::instance.buildings[1];
        do {
            if (pBVar2->logicalState != (BuildingLogicalState)0
                && (((BVar1 = pBVar2->buildingType,
                         BVar1 == Map::Buildings::BT_TOWER2 || (BVar1 == Map::Buildings::BT_TOWER3))
                        || (BVar1 == Map::Buildings::BT_TOWER4))
                    || (BVar1 == Map::Buildings::BT_TOWER5))) {
                MACRO_CALL_MEMBER(Map::TileMapState_Func::upgradeTowerLogicLayer, DAT_TileMapState::ptr)(iVar2);
            }
            pBVar2 = pBVar2 + 0x196;
            iVar2 = iVar2 + 1;
        } while ((int)pBVar2 < 0x1124dc6);
    }

}
}
