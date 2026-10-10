#include "../../../Map.func.hpp"

#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/SEC_RNG.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;
        using UI::Enums::MenuViewType;
        using WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x00525F20
        BOOLEnum TribesState::spawnDeerLionOrRabbit(int tribeID, int param_2, UnitType unitType)
        {
            short* psVar1;
            int sVar2;
            int _finalTargetUnitID;
            int iVar3;
            uint _rng2;
            int _terrainHeight;
            int _unknown;
            int _tribeSize;
            int _unitX;
            int _targetUnitID;
            int _unitY;
            if ((DAT_GameCore::instance.currentMenuViewType != UI::Enums::MVT_MAP_EDITOR_LANDSCAPING)
                && (0 < tribeID)) {
                if (this->tribes[tribeID].predatorNearby != 0) {
                    return FALSE;
                }
                _targetUnitID = this->tribes[tribeID].selectionTargetUnitID;
                _finalTargetUnitID = (int)_targetUnitID;
                if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                    _finalTargetUnitID
                        = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getNonDyingUnit, this)(tribeID);
                    if (!_finalTargetUnitID) {
                        _finalTargetUnitID = (int)_targetUnitID;
                    }
                }
                _rng2 = (uint)(byte)SEC_RNG::instance.currentNumber2;
                _terrainHeight = DAT_UnitsState::instance.units[_finalTargetUnitID].terrainOrClimbHeight;
                _unknown = this->tribes[tribeID].herdMinSize;
                _tribeSize = this->tribes[tribeID].size;
                _unitX = DAT_UnitsState::instance.units[_finalTargetUnitID].x;
                _unitY = DAT_UnitsState::instance.units[_finalTargetUnitID].y;
                if (_tribeSize <= _unknown) {
                    param_2 = (int)(param_2 + (param_2 >> 0x1f & 3U)) >> 2;
                }
                psVar1 = (short*)&this->tribes[tribeID].field139_0x284;
                *psVar1 = *psVar1 + 1;
                if ((param_2 <= this->tribes[tribeID].field139_0x284)
                    && (sVar2 = this->tribes[tribeID].herdMaxSize, this->tribes[tribeID].field139_0x284 = 0,
                        _tribeSize < sVar2)) {
                    if ((unitType == Map::Units::UT_RABBIT)
                        && (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation)) {
                        iVar3 = 110;
                    } else {
                        iVar3 = ((_unknown <= _tribeSize) - 1 & 0xffffffb5) + 100;
                    }
                    if (iVar3 <= (int)(_rng2 & 0x7f)) {
                        _rng2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                            0, 0, (int)((int)(_unitX * 8)), (int)((int)(_unitY * 8)), (int)((int)(_terrainHeight)),
                            unitType);
                        if (_rng2) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(
                                _rng2, tribeID);
                            DAT_UnitsState::instance.units[_rng2].substate
                                = (byte)DAT_UnitsState::instance.units[_rng2].fixedRng & 3;
                            if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                                DAT_UnitsState::instance.units[_rng2].antelopeBasedRngValue = 2;
                            }
                            DAT_UnitsState::instance.units[_rng2].disappearFadeAlphaCountdown = 0x20;
                            if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                                MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateAnimalHerdBehaviorState,
                                    this)(tribeID);
                            }
                            return TRUE;
                        }
                    }
                }
                return FALSE;
            }
            return FALSE;
        }

    }
}
}
