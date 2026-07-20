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
        Map::Buildings::BuildingTypeShort BVar1;
        int _buildingID;
        bool bVar2;

        _buildingID = 1;
        if (1 < DAT_BuildingsState::instance.maxBuildingsCount) {
            Map::Buildings::Building* pBVar2 = &DAT_BuildingsState::instance.buildings[1];
            do {
                if (((pBVar2->logicalState != 0) && (pBVar2->logicalState != Map::Buildings::BLS_REMOVE))
                    && (pBVar2->owner == playerID)) {
                    if (buildingCategory == AINDBC_FEAR_FACTOR_BUILDINGS) {
                        BVar1 = pBVar2->buildingType;
                        if (((BVar1 != Map::Buildings::BT_CESSPIT) && (BVar1 != Map::Buildings::BT_BURNINGSTAKE))
                            && (((BVar1 != Map::Buildings::BT_GIBBET
                                     && (((BVar1 != Map::Buildings::BT_DUNGEON
                                              && (BVar1 != Map::Buildings::BT_STRETCHINGRACK))
                                         && (BVar1 != Map::Buildings::BT_RACKFLOGGING))))
                                && (((BVar1 != Map::Buildings::BT_CHOPPINGBLOCK
                                         && (BVar1 != Map::Buildings::BT_DUNKINGSTOOL))
                                    && ((BVar1 != Map::Buildings::BT_DOGCAGE
                                        && ((
                                            (BVar1 != Map::Buildings::BT_STATUE && (BVar1 != Map::Buildings::BT_SHRINE))
                                            && ((BVar1 != Map::Buildings::BT_DANCINGBEAR
                                                && ((((BVar1 != Map::Buildings::BT_POND
                                                          && (BVar1 != Map::Buildings::BT_GALLOWS))
                                                         && (BVar1 != Map::Buildings::BT_STOCKS))
                                                    && ((BVar1 != Map::Buildings::BT_WITCHHOIST
                                                        && (BVar1 != Map::Buildings::BT_MAYPOLE)))))))))))))))) {
                            bVar2 = BVar1 == Map::Buildings::BT_GARDEN;
                            goto LAB_004d04de;
                        }
                    } else if (buildingCategory == AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS) {
                        BVar1 = pBVar2->buildingType;
                        if (((BVar1 != Map::Buildings::BT_FLETCHER) && (BVar1 != Map::Buildings::BT_BLACKSMITH))
                            && (((BVar1 != Map::Buildings::BT_POLETURNER
                                     && (((BVar1 != Map::Buildings::BT_ARMOURER && (BVar1 != Map::Buildings::BT_TANNER))
                                         && (BVar1 != Map::Buildings::BT_INN))))
                                && (((BVar1 != Map::Buildings::BT_APOTHECARY && (BVar1 != Map::Buildings::BT_CHAPEL))
                                    && (BVar1 != Map::Buildings::BT_CHURCH)))))) {
                            bVar2 = BVar1 == Map::Buildings::BT_CATHEDRAL;
                            goto LAB_004d04de;
                        }
                    } else if (buildingCategory == AINDBC_GATEHOUSES_TOWERS_GUILDS) {
                        BVar1 = pBVar2->buildingType;
                        if (((((BVar1 != Map::Buildings::BT_GATEHOUSELARGE)
                                  && (BVar1 != Map::Buildings::BT_GATEHOUSESMALL))
                                 && ((BVar1 != Map::Buildings::BT_DRAWBRIDGE
                                     && ((((BVar1 != Map::Buildings::BT_TOWER1 && (BVar1 != Map::Buildings::BT_TOWER2))
                                              && (BVar1 != Map::Buildings::BT_TOWER3))
                                         && ((BVar1 != Map::Buildings::BT_TOWER4
                                             && (BVar1 != Map::Buildings::BT_TOWER5))))))))
                                && (BVar1 != Map::Buildings::BT_ENGINEERSGUILD))
                            && (BVar1 != Map::Buildings::BT_TUNNELERSGUILD)) {
                            bVar2 = BVar1 == Map::Buildings::BT_OILSMELTER;
                            goto LAB_004d04de;
                        }
                    } else if (buildingCategory == AINDBC_BARRACKS_MERCPOST_STABLES) {
                        BVar1 = pBVar2->buildingType;
                        if ((BVar1 != Map::Buildings::BT_MERCENARYPOST) && (BVar1 != Map::Buildings::BT_BARRACKS)) {
                            bVar2 = BVar1 == Map::Buildings::BT_STABLES;
                            goto LAB_004d04de;
                        }
                    } else if (buildingCategory == AINDBC_WATER_BUILDINGS) {
                        if (pBVar2->buildingType != Map::Buildings::BT_WELL) {
                            bVar2 = pBVar2->buildingType == Map::Buildings::BT_WATERPOT;
                            goto LAB_004d04de;
                        }
                    } else if (buildingCategory == AINDBC_RESOURCE_BUILDINGS) {
                        BVar1 = pBVar2->buildingType;
                        if (((BVar1 != Map::Buildings::BT_OXTETHER) && (BVar1 != Map::Buildings::BT_IRONMINE))
                            && ((BVar1 != Map::Buildings::BT_PITCHRIG
                                && (((BVar1 != Map::Buildings::BT_BAKERY && (BVar1 != Map::Buildings::BT_BREWERY))
                                    && (BVar1 != Map::Buildings::BT_QUARRY)))))) {
                            bVar2 = BVar1 == Map::Buildings::BT_MILL;
                        LAB_004d04de:
                            if (!bVar2)
                                goto LAB_004d04f9;
                        }
                    } else {
                        if (((buildingCategory == AINDBC_FARMS)
                                && (BVar1 = pBVar2->buildingType, BVar1 != Map::Buildings::BT_WHEATFARM))
                            && ((BVar1 != Map::Buildings::BT_HOPFARM && (BVar1 != Map::Buildings::BT_APPLEFARM)))) {
                            bVar2 = BVar1 == Map::Buildings::BT_DAIRYFARM;
                            goto LAB_004d04de;
                        }
                    }
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::giveBackResourceForDestroyedBuilding,
                        DAT_BuildingsState::ptr)(_buildingID, playerID, 0x32);
                    MACRO_CALL_MEMBER(Map::Buildings::BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(
                        _buildingID);
                }
            LAB_004d04f9:
                _buildingID = _buildingID + 1;
                pBVar2 = pBVar2 + 1;
            } while (_buildingID < DAT_BuildingsState::instance.maxBuildingsCount);
        }
    }
}
}
