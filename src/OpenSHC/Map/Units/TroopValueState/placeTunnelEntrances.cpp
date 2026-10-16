#include "../../../Map.func.hpp"
#include "../TroopValueState.func.hpp"

#include "OpenSHC/Map/Navigation/PathFindingState.func.hpp"
#include "OpenSHC/Map/TileMapState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitInstructionType.hpp"

#include "OpenSHC/Globals/DAT_BuildingsState.hpp"
#include "OpenSHC/Globals/DAT_PathFindingState.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitInstructionType;

        // FUNCTION: STRONGHOLDCRUSADER 0x0051B570
        int TroopValueState::placeTunnelEntrances(int tribeID)
        {
            short sVar1;
            int iVar2;
            int iVar3;
            PlayerID playerID;
            int iVar4;
            sVar1 = DAT_TribesState::instance.tribes[tribeID].selectionTargetUnitID;
            /*
              finds a route from target to siege engine location?
             */
            iVar4 = MACRO_CALL_MEMBER(Map::Navigation::PathFindingState_Func::algFindAttackAngle,
                DAT_PathFindingState::ptr)(200, (uint)((int)((int)DAT_UnitsState::instance.units[sVar1].x)),
                (uint)((int)((int)DAT_UnitsState::instance.units[sVar1].y)), tribeID);
            if (iVar4) {
                sVar1 = DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1;
                iVar2 = DAT_TribesState::instance.tribes[tribeID].uid;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue2 = sVar1;
                this->attackInfo.tentPointsValues[sVar1].tribeID = 0;
                this->attackInfo.tentPointsValues[sVar1].tribeUID = 0;
                iVar3 = this->attackInfo.tentPointsValues[iVar4].y;
                this->attackInfo.tentPointsValues[iVar4].tribeUID = iVar2;
                playerID = DAT_TribesState::instance.tribes[tribeID].owner;
                this->attackInfo.tentPointsValues[iVar4].tribeID = tribeID;
                this->attackInfo.tentPointsValues[iVar4].three = 3;
                iVar2 = this->attackInfo.tentPointsValues[iVar4].x;
                DAT_TribesState::instance.tribes[tribeID].siegeIndexValue1 = (short)iVar4;
                MACRO_CALL_MEMBER(Map::TileMapState_Func::placeBuilding, DAT_TileMapState::ptr)(
                    playerID, iVar2 + -1, iVar3 + -1, (MappersEnum)((int)(66)), 3, 0xf);
                iVar2 = DAT_TileMapState::instance.placedBuildingID;
                if (0 < DAT_TileMapState::instance.placedBuildingID) {
                    DAT_BuildingsState::instance.buildings[DAT_TileMapState::instance.placedBuildingID].attackWave
                        = (int)DAT_TribesState::instance.tribes[tribeID].attackWave;
                    MACRO_CALL_MEMBER(
                        Map::Units::TribesState_Func::giveTribeAnInstruction, DAT_TribesState::ptr)(tribeID,
                        ((UnitInstructionType)0x15), iVar2, DAT_BuildingsState::instance.buildings[iVar2].uid, 0);
                    return iVar4;
                }
            }
            return 0;
        }

    }
}
}
