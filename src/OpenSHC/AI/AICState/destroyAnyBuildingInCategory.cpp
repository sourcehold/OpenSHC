#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace AI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0280
    void AICState::destroyAnyBuildingInCategory(int playerID, AINervousDestroyBuildingCategory buildingCategory)
    {
        int _buildingID = 1;
        if (1 < DAT_BuildingsState::instance.maxBuildingsCount) {
            Map::Buildings::Building* pBVar2 = &DAT_BuildingsState::instance.buildings[1];
            do {
                if (((pBVar2->logicalState != 0) && (pBVar2->logicalState != Map::Buildings::BLS_REMOVE))
                    && (pBVar2->owner == playerID)) {

                    bool _matches = false;
                    Map::Buildings::BuildingTypeShort BVar1 = pBVar2->buildingType;

                    if (buildingCategory == AINDBC_FEAR_FACTOR_BUILDINGS) {
                        _matches = (BVar1 == Map::Buildings::BT_CESSPIT || BVar1 == Map::Buildings::BT_BURNINGSTAKE
                            || BVar1 == Map::Buildings::BT_GIBBET || BVar1 == Map::Buildings::BT_DUNGEON
                            || BVar1 == Map::Buildings::BT_STRETCHINGRACK || BVar1 == Map::Buildings::BT_RACKFLOGGING
                            || BVar1 == Map::Buildings::BT_CHOPPINGBLOCK || BVar1 == Map::Buildings::BT_DUNKINGSTOOL
                            || BVar1 == Map::Buildings::BT_DOGCAGE || BVar1 == Map::Buildings::BT_STATUE
                            || BVar1 == Map::Buildings::BT_SHRINE || BVar1 == Map::Buildings::BT_DANCINGBEAR
                            || BVar1 == Map::Buildings::BT_POND || BVar1 == Map::Buildings::BT_GALLOWS
                            || BVar1 == Map::Buildings::BT_STOCKS || BVar1 == Map::Buildings::BT_WITCHHOIST
                            || BVar1 == Map::Buildings::BT_MAYPOLE || BVar1 == Map::Buildings::BT_GARDEN);
                    } else if (buildingCategory == AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS) {
                        _matches = (BVar1 == Map::Buildings::BT_FLETCHER || BVar1 == Map::Buildings::BT_BLACKSMITH
                            || BVar1 == Map::Buildings::BT_POLETURNER || BVar1 == Map::Buildings::BT_ARMOURER
                            || BVar1 == Map::Buildings::BT_TANNER || BVar1 == Map::Buildings::BT_INN
                            || BVar1 == Map::Buildings::BT_APOTHECARY || BVar1 == Map::Buildings::BT_CHAPEL
                            || BVar1 == Map::Buildings::BT_CHURCH || BVar1 == Map::Buildings::BT_CATHEDRAL);
                    } else if (buildingCategory == AINDBC_GATEHOUSES_TOWERS_GUILDS) {
                        _matches = (BVar1 == Map::Buildings::BT_GATEHOUSELARGE
                            || BVar1 == Map::Buildings::BT_GATEHOUSESMALL || BVar1 == Map::Buildings::BT_DRAWBRIDGE
                            || BVar1 == Map::Buildings::BT_TOWER1 || BVar1 == Map::Buildings::BT_TOWER2
                            || BVar1 == Map::Buildings::BT_TOWER3 || BVar1 == Map::Buildings::BT_TOWER4
                            || BVar1 == Map::Buildings::BT_TOWER5 || BVar1 == Map::Buildings::BT_ENGINEERSGUILD
                            || BVar1 == Map::Buildings::BT_TUNNELERSGUILD || BVar1 == Map::Buildings::BT_OILSMELTER);
                    } else if (buildingCategory == AINDBC_BARRACKS_MERCPOST_STABLES) {
                        _matches = (BVar1 == Map::Buildings::BT_MERCENARYPOST || BVar1 == Map::Buildings::BT_BARRACKS
                            || BVar1 == Map::Buildings::BT_STABLES);
                    } else if (buildingCategory == AINDBC_WATER_BUILDINGS) {
                        _matches = (BVar1 == Map::Buildings::BT_WELL || BVar1 == Map::Buildings::BT_WATERPOT);
                    } else if (buildingCategory == AINDBC_RESOURCE_BUILDINGS) {
                        _matches = (BVar1 == Map::Buildings::BT_OXTETHER || BVar1 == Map::Buildings::BT_IRONMINE
                            || BVar1 == Map::Buildings::BT_PITCHRIG || BVar1 == Map::Buildings::BT_BAKERY
                            || BVar1 == Map::Buildings::BT_BREWERY || BVar1 == Map::Buildings::BT_QUARRY
                            || BVar1 == Map::Buildings::BT_MILL);
                    } else if (buildingCategory == AINDBC_FARMS) {
                        _matches = (BVar1 == Map::Buildings::BT_WHEATFARM || BVar1 == Map::Buildings::BT_HOPFARM
                            || BVar1 == Map::Buildings::BT_APPLEFARM || BVar1 == Map::Buildings::BT_DAIRYFARM);
                    }

                    if (_matches) {
                        MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                            DAT_BuildingsState::ptr)(_buildingID, playerID, 0x32);
                        MACRO_CALL_MEMBER(
                            Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(_buildingID);
                    }
                }
                _buildingID = _buildingID + 1;
                pBVar2 = pBVar2 + 1;
            } while (_buildingID < DAT_BuildingsState::instance.maxBuildingsCount);
        }
    }
}
}
