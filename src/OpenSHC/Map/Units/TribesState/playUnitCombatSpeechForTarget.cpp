#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeInt.hpp"

#include "OpenSHC/Globals/DAT_EntityDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_TribesState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;
        using Map::Units::UnitTypeInt;

        // FUNCTION: STRONGHOLDCRUSADER 0x00521A90
        void TribesState::playUnitCombatSpeechForTarget(int selectionID, int unitID)
        {
            UnitTypeShort UVar2;
            int _otherUnitID;
            UnitTypeInt _ptrptrCurrentSelectionID;
            int _yDifference;
            int _otherX;
            int _xDifference;
            int _otherY;
            int sfxOffsetInArray;
            TribesState* _ptrCurrentSelectionID;
            uint _actionID;
            int _distance;
            TribesState* _ptrCurrentSelectionID_2;
            _ptrCurrentSelectionID = this;
            _otherUnitID
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            _ptrptrCurrentSelectionID = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType,
                this)(selectionID, (int*)&_ptrCurrentSelectionID);
            _ptrCurrentSelectionID_2 = _ptrCurrentSelectionID;
            short sVar1 = DAT_TribesState::instance.tribes[selectionID].size;
            /*
              Arm order comes from the dispatch at 0x521e50: eight dword entries with a
              55-entry byte index table at 0x521e70, indexed by `unitType - 0x16`. The
              labels the import had are all correct; the order was not. By address the
              arms run

                0x521ae3 the archer group, 0x521c2d knight, 0x521cd3 swordsman,
                0x521d5b spearman, 0x521d7e pike/mace/monk, 0x521dc8 Arabian swordsman,
                0x521df7 the default, and 0x521e48 engineer

              so knight and swordsman come before the spearman, and the engineer arm is
              last of all - past the default block. The import had the engineer arm
              sitting between the knight's body and the Arabian swordsman, where the
              knight fell through into its bare `return`; moved to the end it needs the
              knight's own `return` made explicit, exactly as UIT_LIGHT_PITCH did in
              giveTribeAnInstruction once it stopped being the final arm.
             */
            switch (_ptrptrCurrentSelectionID) {
            case Map::Units::UT_E_ARCHER:
            case Map::Units::UT_E_XBOW:
            case Map::Units::UT_A_ARCHER:
            case Map::Units::UT_A_SLINGER:
            case Map::Units::UT_A_HARCHER:
            case Map::Units::UT_A_FIRETHROWER:
                if (_ptrptrCurrentSelectionID == Map::Units::UT_E_ARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_E_XBOW) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[7];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_ARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_SLINGER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x21];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_HARCHER) {
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[1];
                } else if (_ptrptrCurrentSelectionID == Map::Units::UT_A_FIRETHROWER) {
                    /*
                      The firethrower range is tested before the fallback, not after it:
                      the chain at 0x521ae3 is six `cmp`/`jnz` pairs with
                      `mov ecx, [esp + 0x1c]` only on the fall-through.
                     */
                    _distance = DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22]
                        * DAT_EntityDefinedData::instance.EntityTypeArrayForProjectileRange[0x22];
                } else {
                    _distance = unitID;
                }
                _xDifference = (int)DAT_UnitsState::instance.units[_otherUnitID].x
                    - (int)DAT_UnitsState::instance.units[unitID].x;
                _yDifference = (int)DAT_UnitsState::instance.units[_otherUnitID].y
                    - (int)DAT_UnitsState::instance.units[unitID].y;
                if (_distance < _xDifference * _xDifference + _yDifference * _yDifference) {
                    _actionID = 0x1e;
                } else {
                    _actionID = 0x19;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, _actionID);
                /*
                  The import left this guard with an empty body. The original jumps to the
                  common epilogue (`cmp dword ptr [esp + 0x18], 0x4a; jnz 0x521e48`), so
                  only a horse archer reaches the two plays below.
                 */
                if (_ptrptrCurrentSelectionID != Map::Units::UT_A_HARCHER) {
                    return;
                }
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xea;
                } else if ((int)_ptrCurrentSelectionID < 5) {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xeb;
                } else {
                    _otherY = (int)DAT_UnitsState::instance.units[_otherUnitID].y;
                    _otherX = (int)DAT_UnitsState::instance.units[_otherUnitID].x;
                    sfxOffsetInArray = 0xec;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    _otherX, _otherY, sfxOffsetInArray);
                /*
                  A second play, of 0x59, with the coordinates read again (0x521c0b,
                  0x521c12) - which is what the decompiler turned into an assignment of
                  0x59 to one of the coordinate locals - and then `ret 8`.
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)DAT_UnitsState::instance.units[_otherUnitID].y, 0x59);
                return;
            case Map::Units::UT_E_KNIGHT:
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherX = 0x56;
                LAB_00521c6f:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                        (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
                } else {
                    if ((_ptrCurrentSelectionID == (TribesState*)0x2)
                        || (_ptrCurrentSelectionID == (TribesState*)0x3)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                            (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x57);
                    }
                    if (3 < (int)_ptrCurrentSelectionID_2) {
                        _otherX = 0x58;
                        goto LAB_00521c6f;
                    }
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x59);
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0xfa;
                break;
            default:
                UVar2 = DAT_UnitsState::instance.units[unitID].unitType;
                /*
                  The two speeches are exclusive. Ghidra's disassembly of the table arm at
                  0x521df7 is a `jz` chain over the five target types into the 0x11 block,
                  with the 0x15 block inline and its own `ret 8`; the decompilation played
                  0x15 conditionally and then 0x11 unconditionally.
                 */
                if (UVar2 != Map::Units::UT_E_KNIGHT && UVar2 != Map::Units::UT_E_SWORD
                    && UVar2 != Map::Units::UT_E_MACE && UVar2 != Map::Units::UT_E_PIKE
                    && UVar2 != Map::Units::UT_LORD) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                        (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x11);
                return;
            case Map::Units::UT_E_SWORD:
                if (_ptrCurrentSelectionID == (TribesState*)0x1) {
                    _otherX = 0xad;
                } else if (_ptrCurrentSelectionID == (TribesState*)0x2) {
                    _otherX = 0xae;
                } else {
                    if ((int)_ptrCurrentSelectionID < 3)
                        goto LAB_00521d1b;
                    _otherX = 0xaf;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
            LAB_00521d1b:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x14);
                return;
            case Map::Units::UT_E_SPEAR:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, 0x15);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0x14;
                break;
            case Map::Units::UT_E_PIKE:
            case Map::Units::UT_E_MACE:
            case Map::Units::UT_E_MONK:
                UVar2 = DAT_UnitsState::instance.units[unitID].unitType;
                if (UVar2 == Map::Units::UT_E_KNIGHT || UVar2 == Map::Units::UT_E_SWORD
                    || UVar2 == Map::Units::UT_LORD) {
                    _otherX = 0x11;
                } else {
                    _otherX = 0x15;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeech, DAT_SFXState::ptr)(
                    (Map::Units::UnitType)_ptrptrCurrentSelectionID, _otherX);
                if (sVar1 < 0xf) {
                    return;
                }
                _otherX = 0x14;
                break;
            case Map::Units::UT_A_SWORDSMAN:
                if (sVar1 < 0xf) {
                    return;
                }
                /*
                  The table arm at 0x521dc8 ends in `ret 8`. Without the return this fell
                  out of the switch into the shared play below with `_otherX` never
                  assigned on this path.
                 */
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                    (int)(DAT_UnitsState::instance.units[_otherUnitID].y), 0x14);
                return;
            case Map::Units::UT_E_ENGINEER:
                return;
            }
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                (int)DAT_UnitsState::instance.units[_otherUnitID].x,
                (int)(DAT_UnitsState::instance.units[_otherUnitID].y), _otherX);
        }

    }
}
}
