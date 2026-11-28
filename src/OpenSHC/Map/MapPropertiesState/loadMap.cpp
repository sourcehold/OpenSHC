#include "../../Map.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/TroopValueState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Rendering/Bink/AIMessageQueue.func.hpp"
#include "OpenSHC/Game/GameMode2.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_VideoBikQueue.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"
#include "OpenSHC/Globals/TIME_ReceivedMessage_2.hpp"
#include "OpenSHC/Game/GameMode2Int.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

namespace OpenSHC {
namespace Map {

    using Game::GameMode2;
    using IO::FileResourceType;
    using Map::Units::UnitLogicState;
    using Map::Units::UnitType;
    using WindowsHelper::Enums::BOOLEnum;
    using Game::GameMode2Int;
    using Map::Units::UnitTypeShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004C62C0
    void MapPropertiesState::loadMap(char* mapName)
    {
        char cVar1;
        GameMode2Int GVar2;
        UnitTypeShort* pUVar3;
        int* piVar4;
        SiegeUnitCounts* pSVar5;
        int iVar6;
        int* piVar7;
        SiegeUnitCounts* pSVar8;
        int* pIVar9;
        int local_34;
        int local_30;
        int local_2c;
        int local_28;
        int local_24;
        int local_20;
        int local_1c;
        int local_18;
        int local_14;
        int local_10;
        int local_c;
        int local_8;
        uint local_4;
        GVar2 = DAT_GameCore::instance.gameMode_2;
        iVar6 = DAT_GameCore::instance.missionNumber1to20;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_34;
        local_14 = DAT_GameSynchronyState::instance.currentPlayerSlotID;
        local_30 = DAT_GameState::instance.mapAndTime.difficulty;
        local_10 = DAT_GameCore::instance.xbowProducible_logic;
        local_18 = DAT_GameCore::instance.swordProducible_logic;
        local_28 = DAT_GameCore::instance.pikeProducible_logic;
        local_20 = DAT_GameCore::instance.bowProducible_logic;
        local_24 = (int)DAT_GameState::instance.mapAndTime.unitJesterRelated;
        local_2c = DAT_GameCore::instance.maceProducible_logic;
        local_34 = DAT_GameCore::instance.spearProducible_logic;
        local_1c = (int)DAT_GameState::instance.mapAndTime.unitLadyRelated;
        local_c = DAT_GameState::instance.mapAndTime.field43_0xf0;
        local_8 = DAT_GameState::instance.mapAndTime.field44_0xf4;
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::resetTeams, DAT_GameState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::setupAllMapSections, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
            IO::FRT_MAPS, (char const*)((int)(mapName)));
        MACRO_CALL_MEMBER(IO::FilePackager_Func::readMapOrSavFile, FilePackagerObj::ptr)(
            DAT_MapDefinedData::instance.MapSectionAddressArray);
        MACRO_CALL_MEMBER(
            Audio::MSS::SoundSystem_Func::mapLoadingAndLaunchGameRelated1, DAT_SoundSystemState::ptr)();
        DAT_GameState::instance.mapAndTime.difficulty = local_30;
        DAT_GameCore::instance.xbowProducible_logic = local_10;
        DAT_GameCore::instance.pikeProducible_logic = local_28;
        DAT_GameCore::instance.swordProducible_logic = local_18;
        DAT_GameCore::instance.bowProducible_logic = local_20;
        DAT_GameCore::instance.mapTimeInTicks = 1;
        DAT_GameCore::instance.section1127 = 1;
        DAT_GameCore::instance.spearProducible_logic = local_34;
        DAT_GameCore::instance.maceProducible_logic = local_2c;
        DAT_GameCore::instance.missionNumber1to20 = iVar6;
        DAT_GameCore::instance.gameMode_2 = GVar2;
        if (iVar6 == 1) {
            iVar6 = 8;
            pUVar3 = &DAT_UnitsState::instance.units[1].unitType;
            do {
                if (((pUVar3[-1] != Map::Units::ULS_INVISIBLE)
                        && (*pUVar3 == Map::Units::UT_E_ARCHER))
                    && (pUVar3[4] == 1)) {
                    iVar6 = iVar6 + -1;
                    *(int*)(pUVar3 + -0x3f) = 3;
                    if (!iVar6)
                        break;
                }
                pUVar3 = pUVar3 + 0x248;
            } while ((int)pUVar3 < 0x165141a);
        }
        DAT_GameState::instance.mapAndTime.unitLadyRelated = (short)local_1c;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[0] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[1] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[2] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[3] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[4] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[5] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[6] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[7] = -1;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[8] = -1;
        DAT_GameState::instance.mapAndTime.unitJesterRelated = (short)local_24;
        DAT_GameSynchronyState::instance.currentPlayerSlotID = local_14;
        DAT_GameState::instance.mapAndTime.field44_0xf4 = local_8;
        DAT_GameSynchronyState::instance.currentPlayerFullIDArray[local_14] = 1;
        DAT_GameState::instance.mapAndTime.field43_0xf0 = local_c;
        DAT_GameState::instance.playerDataArray[1].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[2].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[3].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[4].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[5].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[6].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[7].tacticalPowersBarLevel = 0;
        DAT_GameState::instance.playerDataArray[8].tacticalPowersBarLevel = 0;
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameCore::instance.section1095 = 0;
        iVar6 = (int)this - (int)mapName;
        do {
            cVar1 = *mapName;
            mapName[iVar6] = cVar1;
            mapName = mapName + 1;
        } while (cVar1 != '\0');
        if (DAT_GameCore::instance.gameMode_2 == Game::GM_CAMPAIGN_MISSION) {
            MACRO_CALL_MEMBER(
                Game::GameCore_Func::removeJesterAndLadyUnitsInCertainMissions, DAT_GameCore::ptr)();
        } else if (DAT_GameCore::instance.gameMode_2 == Game::GM_ECONOMIC_CAMPAIGN_SH1) {
            MACRO_CALL_MEMBER(Game::GameCore_Func::removeLadyAndJester, DAT_GameCore::ptr)();
        }
        pIVar9 = this->SEC_EventsExtra[0].conditionIsTrue;
        for (iVar6 = 8000; iVar6 != 0; iVar6 = iVar6 + -1) {
            *pIVar9 = 0;
            pIVar9 = pIVar9 + 1;
        }
        DAT_GameState::instance.mapAndTime.month = this->SEC_StartingMonth;
        DAT_GameState::instance.mapAndTime.year = this->SEC_StartingYear;
        if (DAT_GameCore::instance.missionNumber1to20 - 4294967280 < 5) {
            MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::adjustEventMonthAndYearForSection1047, this)();
        }
        if ((DAT_GameState::instance.mapAndTime.month == this->SEC_StartingMonth)
            && (DAT_GameState::instance.mapAndTime.year == this->SEC_StartingYear)) {
            piVar4 = DAT_GameState::instance.mapAndTime.startGoods;
            piVar7 = this->SEC_StartingResources;
            do {
                *piVar4 = *piVar7;
                piVar4 = piVar4 + 1;
                piVar7 = piVar7 + 1;
            } while ((int)piVar4 < 0x117ce50);
            DAT_GameState::instance.mapAndTime.startGoods[7] = DAT_GameState::instance.mapAndTime.startGoods[8];
            DAT_GameState::instance.mapAndTime.startGoods[8] = 0;
            pSVar5 = &DAT_GameState::instance.mapAndTime.siegeInformation;
            pSVar8 = &this->SEC_SiegeInformation;
            do {
                pSVar5->archers = pSVar8->archers;
                pSVar5 = (SiegeUnitCounts*)&pSVar5->crossbowmen;
                pSVar8 = (SiegeUnitCounts*)&pSVar8->crossbowmen;
            } while ((int)pSVar5 < 0x117cea0);
            DAT_GameState::instance.mapAndTime.startingPopularity = this->SEC_StartingPopularity * 10;
            MACRO_CALL_MEMBER(Game::GameStateStructures_Func::setMonthAndYear, DAT_GameState::ptr)(
                this->SEC_StartingMonth, this->SEC_StartingYear);
        }
        this->SEC_Section1080 = 0;
        this->SEC_Section1081 = 0;
        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::countDeerEfficiently, DAT_TribesState::ptr)();
        MACRO_CALL_MEMBER(Map::TileMapState_Func::prepareMap, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(Game::GameStateStructures_Func::clearEnemyRelatedStructures, DAT_GameState::ptr)();
        DAT_UnitsState::instance.lastSelectedUnitID = 0;
        MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::deselectAllUnitsOneByOne, DAT_UnitsState::ptr)();
        MACRO_CALL_MEMBER(
            Map::Units::UnitsState_Func::clearSelectionCountsAndPlayerIDs, DAT_UnitsState::ptr)();
        DAT_GameState::instance.mapAndTime.euroRecruitable[4]
            = (int)this->barracksRecruitability.recruitability.macemen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[5]
            = (int)this->barracksRecruitability.recruitability.swordsmen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[6]
            = (int)this->barracksRecruitability.recruitability.knights;
        DAT_GameState::instance.mapAndTime.mercRecruitable[0] = (int)this->SEC_MercRecruitable[0];
        DAT_GameState::instance.mapAndTime.euroRecruitable[0]
            = (int)this->barracksRecruitability.recruitability.archers;
        DAT_GameState::instance.mapAndTime.euroRecruitable[1]
            = (int)this->barracksRecruitability.recruitability.crossbowmen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[2]
            = (int)this->barracksRecruitability.recruitability.spearmen;
        DAT_GameState::instance.mapAndTime.euroRecruitable[3]
            = (int)this->barracksRecruitability.recruitability.pikemen;
        DAT_GameState::instance.mapAndTime.mercRecruitable[1] = (int)this->SEC_MercRecruitable[1];
        DAT_GameState::instance.mapAndTime.mercRecruitable[2] = (int)this->SEC_MercRecruitable[2];
        DAT_GameState::instance.mapAndTime.mercRecruitable[3] = (int)this->SEC_MercRecruitable[3];
        DAT_GameState::instance.mapAndTime.mercRecruitable[4] = (int)this->SEC_MercRecruitable[4];
        DAT_GameState::instance.mapAndTime.mercRecruitable[5] = (int)this->SEC_MercRecruitable[5];
        DAT_GameState::instance.mapAndTime.mercRecruitable[6] = (int)this->SEC_MercRecruitable[6];
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_0
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[0] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[1] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_2
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[2] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_b
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[3] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_1_a = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_4
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[4] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[5] != 0);
        if (DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0) {
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_a = 1;
            DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_3_a_and_6_b = 1;
        }
        DAT_GameState::instance.mapAndTime.euroRecruitableCopy_index_6_c
            = (int)(DAT_GameState::instance.mapAndTime.euroRecruitable[6] != 0);
        DAT_GameState::instance.mapAndTime.countUpTo201 = 0;
        DAT_GameState::instance.mapAndTime.cathedralRelated1 = 0;
        MACRO_CALL_MEMBER(Map::MapPropertiesState_Func::importTradingCosts, this)();
        MACRO_CALL_MEMBER(Map::Units::TroopValueState_Func::clearAttackInfo, DAT_TroopValueState::ptr)();
        MACRO_CALL_MEMBER(AI::AICState_Func::recomputeAIZonerLayer, DAT_AICState::ptr)();
        MACRO_CALL_MEMBER(
            Map::TileMapState_Func::setSignpostDistanceForCampaignMission, DAT_TileMapState::ptr)();
        MACRO_CALL_MEMBER(
            Rendering::Bink::AIMessageQueue_Func::playNextStoredBinkVideo, DAT_VideoBikQueue::ptr)();
        DAT_GameCore::instance.xbowProducible_logic = (int)this->SEC_XbowProducible_save;
        DAT_GameCore::instance.bowProducible_logic = (int)this->SEC_BowProducible_save;
        DAT_GameCore::instance.pikeProducible_logic = (int)this->SEC_PikeProducible_save;
        DAT_GameCore::instance.spearProducible_logic = (int)this->SEC_SpearProducible_save;
        DAT_GameCore::instance.swordProducible_logic = (int)this->SEC_SwordProducible_save;
        DAT_GameCore::instance.maceProducible_logic = (int)this->SEC_MaceProducible_save;
        DAT_GameCore::instance.timeSum_2 = timeGetTime();
        DAT_GameCore::instance.gameDuration = 0;
        TIME_ReceivedMessage_2::instance = 0;
        ;
    }

}
}
