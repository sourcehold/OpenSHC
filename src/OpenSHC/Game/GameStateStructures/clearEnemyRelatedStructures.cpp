#include "../GameStateStructures.func.hpp"

#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Game/GameStateStructures.func.hpp"
#include "OpenSHC/Map/MapPropertiesState.func.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_AICState.hpp"
#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
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
        /*
          field2_0x8 to field11_0x2c, field12_0x30 to field21_0x54, field22_0x58 and field23_0x80 to field32_0xa4 are
          four arrays of ten entries that are reset together, exactly as the original binary does
         */
        for (int index = 0; index < 10; index++) {
            (&this->mapAndTime.field2_0x8)[index] = 0;
            (&this->mapAndTime.field12_0x30)[index] = 0;
            this->mapAndTime.field22_0x58[0][index] = -1;
            (&this->mapAndTime.field23_0x80)[index] = -1;
        }
        /*
          field33_0xa8 to field41_0xc8 is an array of nine entries next to emenyHitArray
         */
        for (int index = 0; index < 9; index++) {
            (&this->mapAndTime.field33_0xa8)[index] = 0;
            this->mapAndTime.emenyHitArray[index] = 0;
        }
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
        MACRO_CALL_MEMBER(OpenSHC::Game::GameStateStructures_Func::fillWith0xFF, DAT_GameState::ptr)();
    }
}
}
