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
        int _targetTribeIDs[3];
        _targetTribeIDs[0] = 0;
        _targetTribeIDs[1] = 0;
        _targetTribeIDs[2] = 0;
        int _validCount = 0;
        int _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xba];
        if ((_tribeID != 0)
            && (DAT_TribesState::instance.tribes[_tribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xba])) {
            _targetTribeIDs[0] = _tribeID;
            _validCount = 1;
        }
        _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xbb];
        if ((_tribeID != 0)
            && (DAT_TribesState::instance.tribes[_tribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xbb])) {
            _targetTribeIDs[_validCount] = _tribeID;
            _validCount += 1;
        }
        _tribeID = (int)DAT_GameState::instance.playerDataArray[playerID].aiTribeIDs[0xbc];
        if ((_tribeID != 0)
            && (DAT_TribesState::instance.tribes[_tribeID].uid
                == DAT_GameState::instance.playerDataArray[playerID].aiTribeUIDs[0xbc])) {
            _targetTribeIDs[_validCount] = _tribeID;
        }
        int _shieldCount = 0;
        for (int _unitID = 1; _unitID < 2500; _unitID++) {
            UnitTypeShort _unitType;
            if ((DAT_UnitsState::instance.units[_unitID].logicalState != OpenSHC::Map::Units::ULS_INVISIBLE)
                && ((((_unitType = DAT_UnitsState::instance.units[_unitID].unitType,
                          _unitType == OpenSHC::Map::Units::UT_S_TOWER
                              || (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM))
                         || (_unitType == OpenSHC::Map::Units::UT_S_SHIELD))
                    && ((DAT_UnitsState::instance.units[_unitID].unknownSiegeTentRelated02 == 3
                        && (DAT_UnitsState::instance.units[_unitID].aiUnitBehaviourType != 0x15)))))) {
                if (_unitType == OpenSHC::Map::Units::UT_S_TOWER) {
                    int _engineTribeID = (int)DAT_UnitsState::instance.units[_unitID].tribeID;
                    if ((_engineTribeID != 0)
                        && (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray + playerID * 0x177bc
                                + -4)
                            != 0)) {
                        MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                            DAT_TribesState::ptr)(_engineTribeID, OpenSHC::Map::Units::STBT_0x414);
                    }
                } else if (_unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM) {
                    int _engineTribeID = (int)DAT_UnitsState::instance.units[_unitID].tribeID;
                    if (_engineTribeID != 0) {
                        if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.gateValuesArray + playerID * 0x177bc
                                + -4)
                            != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                                DAT_TribesState::ptr)(_engineTribeID, OpenSHC::Map::Units::STBT_0x3f6);
                        } else {
                            if (*(int*)((int)DAT_TroopValueState::instance.attackInfo.wideValuesArray
                                    + playerID * 0x177bc + -4)
                                != 0) {
                                MACRO_CALL_MEMBER(OpenSHC::Map::Units::TribesState_Func::assignAttackTargetsForTribe,
                                    DAT_TribesState::ptr)(_engineTribeID, OpenSHC::Map::Units::STBT_0x413);
                            }
                        }
                    }
                } else if (_unitType == OpenSHC::Map::Units::UT_S_SHIELD) {
                    int _shieldTribeID = (int)DAT_UnitsState::instance.units[_unitID].tribeID;
                    if ((_shieldTribeID != 0) && (_shieldCount < 3)) {
                        int _targetTribeID = _targetTribeIDs[_shieldCount];
                        DAT_TribesState::instance.tribes[_shieldTribeID].field56_0x1f2 = (short)_targetTribeID;
                        DAT_TribesState::instance.tribes[_shieldTribeID].uid2
                            = DAT_TribesState::instance.tribes[_targetTribeID].uid;
                        int _targetUnitID = (int)DAT_TribesState::instance.tribes[_targetTribeID].selectionTargetUnitID;
                        DAT_TribesState::instance.tribes[_targetTribeID].tribeID = (short)_shieldTribeID;
                        int _targetTile = DAT_UnitsState::instance.units[_targetUnitID].tile;
                        _shieldCount = _shieldCount + 1;
                        if (0 < _targetTile) {
                            uint y1
                                = (uint)DAT_ViewportRenderState::instance.tileTranslationMatrix_YComponent[_targetTile];
                            uint x1 = _targetTile - DAT_ViewportRenderState::instance.translationMatrix[y1].addXgetTile;
                            MACRO_CALL_MEMBER(
                                OpenSHC::Map::Units::TribesState_Func::giveTribeMoveInstruction, DAT_TribesState::ptr)(
                                _shieldTribeID, x1, y1, 0, 0, OpenSHC::Map::Units::Instructions::UMSE_0);
                            MACRO_CALL_MEMBER(OpenSHC::Map::Navigation::DirectionAlgorithmState_Func::
                                                  calculatePreferredRelativeOrientation,
                                DAT_DirectionAlgorithmState::ptr)((int)DAT_UnitsState::instance.units[_targetUnitID].x,
                                (int)((int)(DAT_UnitsState::instance.units[_targetUnitID].y)), (int)((int)(x1)),
                                (int)((int)(y1)));
                            DAT_TribesState::instance.tribes[_shieldTribeID].orientation
                                = (short)DAT_DirectionAlgorithmState::instance.orientation;
                        }
                    }
                }
            }
        }
    }
}
}
