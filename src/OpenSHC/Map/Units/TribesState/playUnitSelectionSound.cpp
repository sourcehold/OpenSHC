#include "../../../Map.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Map/Units/TribesState.func.hpp"
#include "OpenSHC/Map/Units/UnitsState.func.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"

namespace OpenSHC {
namespace Map {
    namespace Units {

        using Map::Units::UnitType;

        /*
          Rebuilt from Ghidra's disassembly of 0x5217e0 rather than its decompilation: the
          jump table at 0x521a48 has six arms and the byte table at 0x521a60 maps
          unitType - 0x1b onto them. The speech calls in the engineer and siege arms are
          tail calls (`mov [esp + 4], <id>` then `jmp`), which is what the decompiler
          printed as an assignment to `param_1` in front of each one.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005217E0
        void TribesState::playUnitSelectionSound(int param_1)
        {
            int const iVar3
                = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            UnitType const UVar4
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(param_1, &param_1);
            /*
              Arm order and the case labels both come from the dispatch at 0x521a48: six
              dword entries and a 48-entry byte index table at 0x521a60, indexed by
              `unitType - 0x1b`. Three of the labels the import had were wrong.

              0x1b and 0x1c - swordsman and knight - share one arm, 0x521819. The
              0x56/0x59 arm at 0x5218aa belongs to 0x1d, the ladderman, not the knight.
              The siege arm at 0x521983 covers 0x29, 0x3a and 0x3b - mangonel, tower and
              battering ram - so the first of the three is UT_S_MANGONEL, not
              UT_S_CATAPULT (0x27), which falls to the default and plays nothing.

              The last one is odd rather than wrong: the arm at 0x521a11 is reached only
              by 0x1f, the miner, yet its body compares the unit's own type against 0x1e,
              the engineer (`cmp word ptr [esi + 0x13885da], 0x1e`). The majority type
              that selects the arm and the type of the unit the sound plays on are two
              different units, so this is reachable; but labelling it UT_E_ENGINEER, as
              the import did, gave the speech to engineers and nothing to miners.

              Physical order by address is 0x521819, the default `ret 4` at 0x521876,
              then 0x5218aa, 0x521915, 0x521983, 0x521a11 - so the archer arm sits
              between the ladderman and the siege engines.
             */
            switch (UVar4) {
            case Map::Units::UT_E_SWORD:
            case Map::Units::UT_E_KNIGHT:
                /*
                  Three separate blocks at 0x521819, each with its own `ret 4`, and a
                  selection below three that is neither one nor two plays nothing.
                 */
                if (param_1 == 1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x,
                        (int)(DAT_UnitsState::instance.units[iVar3].y), 0xad);
                    return;
                }
                if (param_1 == 2) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x,
                        (int)(DAT_UnitsState::instance.units[iVar3].y), 0xae);
                    return;
                }
                if (param_1 < 3) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[iVar3].x,
                    (int)(DAT_UnitsState::instance.units[iVar3].y), 0xaf);
                return;
            case Map::Units::UT_E_LADDER: {
                /*
                  The arm at 0x5218aa: one shared play of the size-dependent effect, then
                  0x59. A selection of two or three gets 0x57 as well, and one of four or
                  more gets 0x58 instead of 0x56.
                 */
                /*
                  The play is written out in each arm with its constant. The original
                  pushes them directly - `cmp edi, 1; jne 0x4; push 0x56; jmp 0x35` for
                  the first and `push 0x58` for the four-or-more case - and shares the
                  coordinate pushes and the call after them, which is MSVC tail-merging
                  two call sites. An `_sfx` local and one shared call makes it
                  materialise the value into a register first instead.
                 */
                if (param_1 == 1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x,
                        (int)(DAT_UnitsState::instance.units[iVar3].y), 0x56);
                } else {
                    if (param_1 == 2 || param_1 == 3) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0x57);
                    }
                    /*
                      This one stays, against the asm. The original has `cmp edi, 4;
                      jl 0x24`, jumping away for a smaller selection, so `push 0x58` is
                      its fall-through and the lone 0x59 play sits in the far block -
                      ours is the other way round. Rewriting it as
                      `if (param_1 >= 4) { _sfx = 0x58; } else { ...; return; }` measures
                      62.1% -> 56.0%. Retried after the play was written out in each arm,
                      in case the surrounding blocks had changed enough to matter: still a
                      loss, 65.4% -> 60.2%. Second and third losses for the inverted-arm
                      fix after giveTribeMoveInstruction, and all of them are in functions
                      whose remaining gap is dominated by where the shared epilogue lands.

                      What is left here is how far MSVC tail-merges. The original shares
                      one coordinate-read-and-call block between the 0x56 and 0x58 arms,
                      duplicating only the `push`, and its 0x59 plays jump back to a second
                      shared block. Ours pushes the constants per arm correctly but keeps
                      its own copy of the coordinate reads, which is the two extra reads of
                      units[].x and units[].y the diff shows (orig 4 and 5, ours 6 and 7).
                     */
                    if (param_1 < 4) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0x59);
                        return;
                    }
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x,
                        (int)(DAT_UnitsState::instance.units[iVar3].y), 0x58);
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[iVar3].x,
                    (int)(DAT_UnitsState::instance.units[iVar3].y), 0x59);
                return;
            }
            case Map::Units::UT_A_HARCHER: {
                /*
                  The arm at 0x521915 keeps a pointer to each coordinate (`lea edi, [esi +
                  0x1388612]`, `lea esi, [esi + 0x1388610]`) and reads through them four
                  times rather than re-indexing the unit.
                 */
                short* const _unitY = &DAT_UnitsState::instance.units[iVar3].y;
                short* const _unitX = &DAT_UnitsState::instance.units[iVar3].x;
                int sfxOffsetInArray;
                if (param_1 == 1) {
                    sfxOffsetInArray = 0xea;
                } else if (param_1 <= 4) {
                    sfxOffsetInArray = 0xeb;
                } else {
                    sfxOffsetInArray = 0xec;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)*_unitX, (int)(*_unitY), sfxOffsetInArray);
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)*_unitX, (int)(*_unitY), 0x59);
            }
            case Map::Units::UT_S_MANGONEL:
            case Map::Units::UT_S_TOWER:
            case Map::Units::UT_S_BATTERINGRAM: {
                int const _requiredEngineers = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getRemainingRequiredEngineers, DAT_UnitsState::ptr)(iVar3);
                if (_requiredEngineers <= 0) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x,
                        (int)(DAT_UnitsState::instance.units[iVar3].y), 0x68);
                    return;
                }
                if (DAT_UnitsState::instance.units[iVar3]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        == 0
                    || 3 < _requiredEngineers) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xe);
                    return;
                }
                if (_requiredEngineers == 1) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xb);
                    return;
                }
                if (_requiredEngineers == 2) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xc);
                    return;
                }
                /*
                  The last arm at 0x5219d9 tests for three and returns without a speech
                  otherwise, which the earlier count tests already make unreachable.
                 */
                if (_requiredEngineers == 3) {
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xd);
                }
                return;
            }
            case Map::Units::UT_MINER:
                if (DAT_UnitsState::instance.units[iVar3].unitType != Map::Units::UT_E_ENGINEER) {
                    return;
                }
                if (DAT_UnitsState::instance.units[iVar3].resourceToDeposit == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0x24);
                return;
            }
        }

    }
}
}
