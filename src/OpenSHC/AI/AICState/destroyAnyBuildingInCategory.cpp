#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/AI/AICState.hpp"
#include "OpenSHC/Map/Buildings/BuildingLogicalState.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"

namespace OpenSHC {
namespace AI {

    using namespace OpenSHC::Map::Buildings;

    // FUNCTION: STRONGHOLDCRUSADER 0x004D0280
    void AICState::destroyAnyBuildingInCategory(int playerID, AINervousDestroyBuildingCategory buildingCategory)
    {
        for (int buildingID = 1; buildingID < DAT_BuildingsState::instance.maxBuildingsCount; buildingID++) {
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == 0)
                continue;
            if (DAT_BuildingsState::instance.buildings[buildingID].logicalState == BLS_REMOVE)
                continue;
            if (DAT_BuildingsState::instance.buildings[buildingID].owner != playerID)
                continue;

            bool matches = false;
            if (buildingCategory == AINDBC_FEAR_FACTOR_BUILDINGS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_CESSPIT || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_BURNINGSTAKE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GIBBET || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DUNGEON
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STRETCHINGRACK || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_RACKFLOGGING || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_CHOPPINGBLOCK
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DUNKINGSTOOL || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DOGCAGE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STATUE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_SHRINE
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DANCINGBEAR || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_POND || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GALLOWS || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STOCKS
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WITCHHOIST || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_MAYPOLE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GARDEN;
            else if (buildingCategory == AINDBC_WORKSHOPS_AND_RELIGIOUS_BUILDINGS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_FLETCHER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_BLACKSMITH || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_POLETURNER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_ARMOURER
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TANNER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_INN || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_APOTHECARY || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_CHAPEL
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_CHURCH || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_CATHEDRAL;
            else if (buildingCategory == AINDBC_GATEHOUSES_TOWERS_GUILDS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSELARGE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_GATEHOUSESMALL || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DRAWBRIDGE
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TOWER1 || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TOWER2 || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TOWER3 || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TOWER4
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TOWER5 || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_ENGINEERSGUILD || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_TUNNELERSGUILD
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_OILSMELTER;
            else if (buildingCategory == AINDBC_BARRACKS_MERCPOST_STABLES)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_MERCENARYPOST || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_BARRACKS || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_STABLES;
            else if (buildingCategory == AINDBC_WATER_BUILDINGS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WELL || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WATERPOT;
            else if (buildingCategory == AINDBC_RESOURCE_BUILDINGS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_OXTETHER || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_IRONMINE || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_PITCHRIG || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_BAKERY
                    || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_BREWERY || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_QUARRY || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_MILL;
            else if (buildingCategory == AINDBC_FARMS)
                matches = DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_WHEATFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_HOPFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_APPLEFARM || DAT_BuildingsState::instance.buildings[buildingID].buildingType == BT_DAIRYFARM;

            if (!matches)
                continue;

            MACRO_CALL_MEMBER(BuildingsState_Func::giveBackResourceForDestroyedBuilding, DAT_BuildingsState::ptr)(
                buildingID, playerID, 50);
            MACRO_CALL_MEMBER(BuildingsState_Func::destroyBuilding, DAT_BuildingsState::ptr)(buildingID);
        }
    }
}
}
