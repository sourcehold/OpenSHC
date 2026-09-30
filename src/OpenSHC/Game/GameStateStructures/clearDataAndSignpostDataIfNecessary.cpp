#include "../GameStateStructures.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingsState.func.hpp"
#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/Buildings/BuildingType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace Game {

    using OpenSHC::Map::Buildings::BuildingType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00456C50
    void GameStateStructures::clearDataAndSignpostDataIfNecessary()
    {
        /*
          fixme: current data type specifies length 128, not 256
         */
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            256, '\0', this->mapAndTime.signpostEntryData);
        /*
          fixme: multiple data?
         */
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            6400, '\0', this->mapAndTime.signpostsMapEdge);
        /*
          fixme: wrong?
         */
        MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ByteValue, DAT_LowLevelMemory::ptr)(
            2560, '\0', this->mapAndTime.unitMoveDestinationXYPairs);
        /*
          the eight signpost slots are checked one by one, exactly as the original binary does
         */
        if ((this->mapAndTime.signpostIDs[0] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[0]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[0] = 0;
            this->mapAndTime.signpostEntryData[0].x = 0;
            this->mapAndTime.signpostEntryData[0].y = 0;
            this->mapAndTime.signpostEntryData[0].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[1] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[1]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[1] = 0;
            this->mapAndTime.signpostEntryData[1].x = 0;
            this->mapAndTime.signpostEntryData[1].y = 0;
            this->mapAndTime.signpostEntryData[1].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[2] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[2]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[2] = 0;
            this->mapAndTime.signpostEntryData[2].x = 0;
            this->mapAndTime.signpostEntryData[2].y = 0;
            this->mapAndTime.signpostEntryData[2].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[3] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[3]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[3] = 0;
            this->mapAndTime.signpostEntryData[3].x = 0;
            this->mapAndTime.signpostEntryData[3].y = 0;
            this->mapAndTime.signpostEntryData[3].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[4] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[4]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[4] = 0;
            this->mapAndTime.signpostEntryData[4].x = 0;
            this->mapAndTime.signpostEntryData[4].y = 0;
            this->mapAndTime.signpostEntryData[4].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[5] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[5]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[5] = 0;
            this->mapAndTime.signpostEntryData[5].x = 0;
            this->mapAndTime.signpostEntryData[5].y = 0;
            this->mapAndTime.signpostEntryData[5].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[6] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[6]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[6] = 0;
            this->mapAndTime.signpostEntryData[6].x = 0;
            this->mapAndTime.signpostEntryData[6].y = 0;
            this->mapAndTime.signpostEntryData[6].tile = 0;
        }
        if ((this->mapAndTime.signpostIDs[7] == 0)
            || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[7]].buildingType
                != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
            this->mapAndTime.signpostIDs[7] = 0;
            this->mapAndTime.signpostEntryData[7].x = 0;
            this->mapAndTime.signpostEntryData[7].y = 0;
            this->mapAndTime.signpostEntryData[7].tile = 0;
        }
        /*
          close the holes by bubbling the remaining signposts to the front
         */
        bool signpostMoved;
        do {
            signpostMoved = false;
            for (int slot = 0; slot < 7; slot++) {
                if ((this->mapAndTime.signpostIDs[slot] == 0)
                    && (this->mapAndTime.signpostIDs[slot + 1] != 0)) {
                    this->mapAndTime.signpostIDs[slot] = this->mapAndTime.signpostIDs[slot + 1];
                    this->mapAndTime.signpostIDs[slot + 1] = 0;
                    signpostMoved = true;
                }
            }
        } while (signpostMoved);
        for (int signpostSlot = 0; signpostSlot < 8; signpostSlot++) {
            if (this->mapAndTime.signpostIDs[signpostSlot] != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                    DAT_BuildingsState::ptr)(this->mapAndTime.signpostIDs[signpostSlot], 1, FALSE);
                this->mapAndTime.signpostEntryData[signpostSlot].x
                    = DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]]
                          .buildingEntryX;
                this->mapAndTime.signpostEntryData[signpostSlot].y
                    = DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]]
                          .buildingEntryY;
                this->mapAndTime.signpostEntryData[signpostSlot].tile
                    = DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]]
                          .buildingEntryX
                    + DAT_ViewportRenderState::instance
                          .translationMatrix[DAT_BuildingsState::instance
                                  .buildings[this->mapAndTime.signpostIDs[signpostSlot]]
                                  .buildingEntryY]
                          .addXgetTile;
                MACRO_CALL_MEMBER(
                    OpenSHC::Map::Navigation::PathFindingState_Func::findMapBorderEdgeTileAndStoreInSignpostData,
                    DAT_PathFindingState::ptr)(signpostSlot, 0x13a10,
                    DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]].buildingEntryX,
                    DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[signpostSlot]].buildingEntryY);
            }
        }
    }
}
}
