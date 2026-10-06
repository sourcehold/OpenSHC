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
        for (int slot = 0; slot < 8; slot++) {
            if ((this->mapAndTime.signpostIDs[slot] == 0)
                || (DAT_BuildingsState::instance.buildings[this->mapAndTime.signpostIDs[slot]].buildingType
                    != OpenSHC::Map::Buildings::BT_SIGNPOST)) {
                this->mapAndTime.signpostIDs[slot] = 0;
                this->mapAndTime.signpostEntryData[slot].x = 0;
                this->mapAndTime.signpostEntryData[slot].y = 0;
                this->mapAndTime.signpostEntryData[slot].tile = 0;
            }
        }
        /*
          close the holes by bubbling the remaining signposts to the front
         */
        int signpostMoved;
        do {
            signpostMoved = 0;
            for (int slot = 0; slot < 7; slot++) {
                if ((this->mapAndTime.signpostIDs[slot] == 0) && (this->mapAndTime.signpostIDs[slot + 1] != 0)) {
                    this->mapAndTime.signpostIDs[slot] = this->mapAndTime.signpostIDs[slot + 1];
                    this->mapAndTime.signpostIDs[slot + 1] = 0;
                    signpostMoved = 1;
                }
            }
        } while (signpostMoved != 0);
        for (int signpostSlot = 0; signpostSlot < 8; signpostSlot++) {
            int buildingID = this->mapAndTime.signpostIDs[signpostSlot];
            if (buildingID == 0) {
                continue;
            }
            MACRO_CALL_MEMBER(OpenSHC::Map::Buildings::BuildingsState_Func::determineBuildingEntranceFromKeepArea,
                DAT_BuildingsState::ptr)(buildingID, 1, FALSE);
            this->mapAndTime.signpostEntryData[signpostSlot].x
                = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX;
            this->mapAndTime.signpostEntryData[signpostSlot].y
                = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY;
            this->mapAndTime.signpostEntryData[signpostSlot].tile
                = DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX
                + DAT_ViewportRenderState::instance
                      .translationMatrix[DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY]
                      .addXgetTile;
            MACRO_CALL_MEMBER(
                OpenSHC::Map::Navigation::PathFindingState_Func::findMapBorderEdgeTileAndStoreInSignpostData,
                DAT_PathFindingState::ptr)(signpostSlot, 0x13a10,
                DAT_BuildingsState::instance.buildings[buildingID].buildingEntryX,
                DAT_BuildingsState::instance.buildings[buildingID].buildingEntryY);
        }
    }
}
}
