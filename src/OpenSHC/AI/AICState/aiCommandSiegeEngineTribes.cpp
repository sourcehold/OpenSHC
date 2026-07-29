#include "OpenSHC/AI/AICState.func.hpp"
#include "OpenSHC/Map/Navigation/DirectionAlgorithmState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/Instructions/UnitMatchSpeedEnum.hpp"
#include "OpenSHC/Map/Units/SomeTribeBehaviorType.hpp"
#include "OpenSHC/Map/Units/Unit.hpp"
#include "OpenSHC/Map/Units/UnitLogicState.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/DAT_DirectionAlgorithmState.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_TroopValueState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"

namespace OpenSHC {
namespace AI {

    using OpenSHC::Map::Units::SomeTribeBehaviorType;
    using OpenSHC::Map::Units::Unit;
    using OpenSHC::Map::Units::UnitLogicState;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::Map::Units::Instructions::UnitMatchSpeedEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000 */

    // FUNCTION: STRONGHOLDCRUSADER 0x004CFCD0
    void AICState ::aiCommandSiegeEngineTribes(int playerID)

    {

        UnitTypeShort UVar1;

        int iVar2;

        uint x1;

        int _sectionID2;

        int iVar3;

        int iVar4;

        uint y1;

        Unit* local_14;

        int local_c[3];

        int _tile;

        short _sectionID;

        short _targetUnitID;

        iVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xba];

        iVar4 = 0;

        iVar3 = 0;

        local_c[0] = 0;

        local_c[1] = 0;

        local_c[2] = 0;

        if ((iVar2 != 0)
            && (DAT_TribesState::instance.tribes[iVar2].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xba])) {

            local_c[0] = iVar2;

            iVar3 = 1;
        }

        iVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xbb];

        if ((iVar2 != 0)
            && (DAT_TribesState::instance.tribes[iVar2].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xbb])) {

            local_c[iVar3] = iVar2;

            iVar3 = iVar3 + 1;
        }

        iVar2 = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xbc];

        if ((iVar2 != 0)
            && (DAT_TribesState::instance.tribes[iVar2].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xbc])) {

            local_c[iVar3] = iVar2;
        }

        local_14 = &DAT_UnitsState::instance.units[1];

        do {

            if ((local_14->logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                && ((((UVar1 = local_14->unitType,
                          UVar1 == OpenSHC::Map::Units::UT_S_TOWER || (UVar1 == OpenSHC::Map::Units::UT_S_BATTERINGRAM))
                         || (UVar1 == OpenSHC::Map::Units::UT_S_SHIELD))
                    && ((local_14->unknownSiegeTentRelated02 == 3 && (local_14->aiUnitBehaviourType != 0x15)))))) {

                if (UVar1 == OpenSHC::Map::Units::UT_S_TOWER) {

                    if ((local_14->tribeID != 0)
                        && (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + playerID * 0x177bc
                                + -4)
                            != 0)) {

                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)((int)local_14->tribeID, OpenSHC::Map::Units::STBT_0x414);
                    }

                }

                else if (UVar1 == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {

                    iVar3 = (int)local_14->tribeID;

                    if (iVar3 != 0) {

                        if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + playerID * 0x177bc
                                + -4)
                            == 0) {

                            if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray
                                    + playerID * 0x177bc + -4)
                                != 0) {

                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                                    DAT_TribesState::ptr)(iVar3, OpenSHC::Map::Units::STBT_0x413);
                            }

                        }

                        else {

                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                                DAT_TribesState::ptr)(iVar3, OpenSHC::Map::Units::STBT_0x3f6);
                        }
                    }

                }

                else if (UVar1 == OpenSHC::Map::Units::UT_S_SHIELD) {

                    _sectionID = local_14->tribeID;

                    _sectionID2 = (int)_sectionID;

                    if ((_sectionID2 != 0) && (iVar4 < 3)) {

                        iVar3 = local_c[iVar4];

                        DAT_TribesState::instance.tribes[_sectionID2].field56_0x1f2 = (short)iVar3;

                        DAT_TribesState::instance.tribes[_sectionID2].uid2
                            = DAT_TribesState::instance.tribes[iVar3].uid;

                        _targetUnitID = DAT_TribesState::instance.tribes[iVar3].selectionTargetUnitID;

                        DAT_TribesState::instance.tribes[iVar3].tribeID = _sectionID;

                        _tile = DAT_UnitsState::instance.units[_targetUnitID].tile;

                        iVar4 = iVar4 + 1;

                        if (0 < _tile) {

                            y1 = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_tile];

                            x1 = _tile - DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;

                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                _sectionID2, x1, y1, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);

                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                  calculatePreferredRelativeOrientation,
                                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_targetUnitID].x,
                                (int)((int)(DAT_UnitsState::instance.units[_targetUnitID].y)), (int)((int)(x1)),
                                (int)((int)(y1)));

                            DAT_TribesState::instance.tribes[_sectionID2].orientation
                                = (short)DAT_DirectionAlgorithmState::instance.orientation;
                        }
                    }
                }
            }

            local_14 = local_14 + 0x248;

        } while ((int)local_14 < 0x165141a);

        return;
    }

}
}
