#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MapPropertiesState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x0045B1C0
    void GameStateStructures::clearEnemyRelatedStructures()
    {
        DAT_BuildingsState::instance.unknownCountdown01 = 2000;
        this->gameTicksLoadBalancer = 0;
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::computeSignPostEntryData, this)();
        MACRO_CALL_MEMBER(OpenSHC::AI::AICState_Func::clearPlayerDataInformationChunk, DAT_AICState::ptr)();
        MACRO_CALL_MEMBER(
            OpenSHC::Game::GameStateStructures_Func::resetVariousCountsAndStatisticsAndStartGoodsAndResources, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::setVariousGameStateToInitialValues, this)();
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::resetSomethingBuildingRelatedForAllPlayers, this)();
        MACRO_CALL_MEMBER(
            OpenSHC::Map::MapPropertiesState_Func::commitBuildingAvailability, DAT_MapPropertiesState::ptr)();
        DAT_GameCore::instance.isTimeHalted = FALSE;
        DAT_GameCore::instance.section1076 = 0;
        this->mapAndTime.field2_0x8 = 0;
        this->mapAndTime.field12_0x30 = 0;
        this->mapAndTime.field22_0x58[0][0] = -1;
        this->mapAndTime.field23_0x80 = -1;
        this->mapAndTime.field3_0xc = 0;
        this->mapAndTime.field13_0x34 = 0;
        this->mapAndTime.field22_0x58[0][1] = -1;
        this->mapAndTime.field24_0x84 = -1;
        this->mapAndTime.field4_0x10 = 0;
        this->mapAndTime.field14_0x38 = 0;
        this->mapAndTime.field22_0x58[0][2] = -1;
        this->mapAndTime.field25_0x88 = -1;
        this->mapAndTime.field5_0x14 = 0;
        this->mapAndTime.field15_0x3c = 0;
        this->mapAndTime.field22_0x58[0][3] = -1;
        this->mapAndTime.field26_0x8c = -1;
        this->mapAndTime.field6_0x18 = 0;
        this->mapAndTime.field16_0x40 = 0;
        this->mapAndTime.field22_0x58[0][4] = -1;
        this->mapAndTime.field27_0x90 = -1;
        this->mapAndTime.field7_0x1c = 0;
        this->mapAndTime.field17_0x44 = 0;
        this->mapAndTime.field22_0x58[1][0] = -1;
        this->mapAndTime.field28_0x94 = -1;
        this->mapAndTime.field8_0x20 = 0;
        this->mapAndTime.field18_0x48 = 0;
        this->mapAndTime.field22_0x58[1][1] = -1;
        this->mapAndTime.field29_0x98 = -1;
        this->mapAndTime.field9_0x24 = 0;
        this->mapAndTime.field19_0x4c = 0;
        this->mapAndTime.field22_0x58[1][2] = -1;
        this->mapAndTime.field30_0x9c = -1;
        this->mapAndTime.field10_0x28 = 0;
        this->mapAndTime.field20_0x50 = 0;
        this->mapAndTime.field22_0x58[1][3] = -1;
        this->mapAndTime.field31_0xa0 = -1;
        this->mapAndTime.field11_0x2c = 0;
        this->mapAndTime.field21_0x54 = 0;
        this->mapAndTime.field22_0x58[1][4] = -1;
        this->mapAndTime.field32_0xa4 = -1;
        this->mapAndTime.field33_0xa8 = 0;
        this->mapAndTime.emenyHitArray[0] = 0;
        this->mapAndTime.field34_0xac = 0;
        this->mapAndTime.emenyHitArray[1] = 0;
        this->mapAndTime.field35_0xb0 = 0;
        this->mapAndTime.emenyHitArray[2] = 0;
        this->mapAndTime.field36_0xb4 = 0;
        this->mapAndTime.emenyHitArray[3] = 0;
        this->mapAndTime.field37_0xb8 = 0;
        this->mapAndTime.emenyHitArray[4] = 0;
        this->mapAndTime.field38_0xbc = 0;
        this->mapAndTime.emenyHitArray[5] = 0;
        this->mapAndTime.field39_0xc0 = 0;
        this->mapAndTime.emenyHitArray[6] = 0;
        this->mapAndTime.field40_0xc4 = 0;
        this->mapAndTime.emenyHitArray[7] = 0;
        this->mapAndTime.field41_0xc8 = 0;
        this->mapAndTime.emenyHitArray[8] = 0;
        for (int playerID = 0; playerID < 9; playerID++) {
            this->mapAndTime.playerBuildingInfoIndex[playerID] = 0;
            for (int buildingSlot = 0; buildingSlot < 2000; buildingSlot++) {
                this->mapAndTime.playerEnemyBuildingIDs[playerID][buildingSlot] = 0;
                this->mapAndTime.playerEnemyBuildingUID[playerID][buildingSlot] = 0;
            }
            for (int unitSlot = 0; unitSlot < 2500; unitSlot++) {
                this->mapAndTime.playerEnemenyUnitUIDShortList[playerID][unitSlot] = 0;
            }
        }
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::fillWith0xFF, this)();
    }
}
}
