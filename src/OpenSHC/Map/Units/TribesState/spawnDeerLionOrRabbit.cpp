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
            ushort* psVar1;
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
            /*
              Two early-return guards, which is where the original puts its own
              `xor eax, eax` epilogues.
             */
            if (DAT_GameCore::instance.currentMenuViewType == UI::Enums::MVT_MAP_EDITOR_LANDSCAPING) {
                return FALSE;
            }
            if (tribeID <= 0) {
                return FALSE;
            }
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
            /*
              Masked here, not at the use. The original does `and edx, 0x7f` right after
              reading the byte, before it reads the herd size and the coordinates; leaving
              the mask on the comparison forty lines down makes MSVC do it there instead.
              The value is only ever read masked - it is overwritten by the spawn result
              straight afterwards - so this is the same program.
             */
            _rng2 = (uint)(byte)SEC_RNG::instance.currentNumber2 & 0x7f;
            _terrainHeight = DAT_UnitsState::instance.units[_finalTargetUnitID].terrainOrClimbHeight;
            /*
              Both of these reads are `movzx` in the original, not `movsx`. They stay
              `int`s cast on the way in rather than `ushort` locals, although the original
              compares them against each other sixteen bits wide (`cmp cx, di`): as
              `ushort` the function measures 74.1% -> 70.2%.
             */
            _unknown = (ushort)this->tribes[tribeID].herdMinSize;
            _tribeSize = (ushort)this->tribes[tribeID].size;
            _unitX = DAT_UnitsState::instance.units[_finalTargetUnitID].x;
            _unitY = DAT_UnitsState::instance.units[_finalTargetUnitID].y;
            if (_tribeSize <= _unknown) {
                param_2 = param_2 / 4;
            }
            /*
              Keeping the pointer rather than naming the field: resolving it costs one
              instruction here (quick_diff 0.7295 -> 0.7265), because the field form
              re-evaluates tribes[tribeID] while the pointer freezes the address.
             */
            psVar1 = &this->tribes[tribeID].field138_0x284;
            *psVar1 = *psVar1 + 1;
            if ((this->tribes[tribeID].field138_0x284 >= param_2)
                && (sVar2 = this->tribes[tribeID].herdMaxSize, this->tribes[tribeID].field138_0x284 = 0,
                    _tribeSize < sVar2)) {
                if ((unitType == Map::Units::UT_RABBIT)
                    && (DAT_GameState::instance.mapAndTime.eventCountdownRabbitInfestation)) {
                    iVar3 = 110;
                } else {
                    iVar3 = _tribeSize < _unknown ? 25 : 100;
                }
                if (iVar3 <= (int)_rng2) {
                    _rng2 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::spawnUnit, DAT_UnitsState::ptr)(
                        0, 0, (int)(_unitX * 8), (int)(_unitY * 8), (int)(_terrainHeight), unitType);
                    /*
                      The `if (_rng2)` stays. The original returns FALSE through an
                      epilogue of its own right here - `test esi, esi; jne 0xc` over
                      `pop/pop/pop/xor eax,eax/pop/add esp,0xc/ret 0xc` - where ours jumps
                      to the shared one at the end, so a flat `if (!_rng2) return FALSE;`
                      looks like the fix. Measured 73.0% -> 73.0%, raw and normalized both
                      unchanged.
                     */
                    if (_rng2) {
                        MACRO_CALL_MEMBER(Map::Units::TribesState_Func::addUnitToTribe, this)(_rng2, tribeID);
                        DAT_UnitsState::instance.units[_rng2].substate
                            = (byte)DAT_UnitsState::instance.units[_rng2].fixedRng & 3;
                        if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                            DAT_UnitsState::instance.units[_rng2].antelopeBasedRngValue = 2;
                        }
                        DAT_UnitsState::instance.units[_rng2].disappearFadeAlphaCountdown = 0x20;
                        if (unitType == Map::Units::UT_ANTELOPESHDEER) {
                            MACRO_CALL_MEMBER(Map::Units::TribesState_Func::updateAnimalHerdBehaviorState, this)(
                                tribeID);
                        }
                        return TRUE;
                    }
                }
            }
            return FALSE;
        }

    }
}
}
