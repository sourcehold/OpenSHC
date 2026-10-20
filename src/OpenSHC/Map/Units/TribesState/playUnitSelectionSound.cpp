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
            switch (UVar4) {
            case Map::Units::UT_E_SWORD:
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
            case Map::Units::UT_E_KNIGHT: {
                /*
                  The arm at 0x5218aa: one shared play of the size-dependent effect, then
                  0x59. A selection of two or three gets 0x57 as well, and one of four or
                  more gets 0x58 instead of 0x56.
                 */
                int _sfx;
                if (param_1 == 1) {
                    _sfx = 0x56;
                } else {
                    if (param_1 == 2 || param_1 == 3) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0x57);
                    }
                    if (param_1 < 4) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0x59);
                        return;
                    }
                    _sfx = 0x58;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[iVar3].x,
                    (int)(DAT_UnitsState::instance.units[iVar3].y), _sfx);
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[iVar3].x,
                    (int)(DAT_UnitsState::instance.units[iVar3].y), 0x59);
                return;
            }
            case Map::Units::UT_E_ENGINEER:
                if (DAT_UnitsState::instance.units[iVar3].unitType != Map::Units::UT_E_ENGINEER) {
                    return;
                }
                if (DAT_UnitsState::instance.units[iVar3].resourceToDeposit == 0) {
                    return;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0x24);
                return;
            case Map::Units::UT_S_CATAPULT:
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
            }
        }

    }
}
}
