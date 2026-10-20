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
          fixme: this function is a chain of tail calls in the original and the
          decompilation of it is wrong in two places. The UT_E_SWORD arm reaches
          `iVar5 = 0xad` unconditionally, so for a two-unit selection it plays 0xae, then
          0xaf, then 0xad where the original plays 0xae alone and returns; the original has
          three separate blocks, each with its own `ret`, and a selection below three units
          that is neither one nor two plays nothing. `if (param_1 < 3) {}` is that case.
          Every `param_1 = <id>;` in front of a playUnitSpeechEffect call is MSVC writing
          the argument into the incoming parameter slot for a tail call, not a real
          assignment, and the siege arm's five arms each return rather than falling into
          the shared block at the end.

          Rebuilding it from those branches was tried and reverted: writing the arms out
          separately costs 32 points of raw match (46.5% -> 14.5%) because the original
          shares the play calls through its tail calls, while the normalized match rises
          (34.4% -> 40.8%). It needs the sharing reproduced, not just the arms corrected.
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x005217E0
        void TribesState::playUnitSelectionSound(int param_1)
        {
            short* psVar1;
            short* psVar2;
            int iVar3;
            UnitType UVar4;
            int iVar5;
            int sfxOffsetInArray;
            iVar3 = MACRO_CALL_MEMBER(Map::Units::UnitsState_Func::selectionContainsCombatUnit, DAT_UnitsState::ptr)(1);
            UVar4
                = MACRO_CALL_MEMBER(Map::Units::TribesState_Func::getMajoritySelectedUnitType, this)(param_1, &param_1);
            iVar5 = param_1;
            switch (UVar4) {
            case Map::Units::UT_E_SWORD:
                if (param_1 != 1) {
                    if (param_1 == 2) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0xae);
                    }
                    if (param_1 < 3) {}
                    iVar5 = 0xaf;
                LAB_0052188b:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x, (int)(DAT_UnitsState::instance.units[iVar3].y),
                        iVar5);
                }
                iVar5 = 0xad;
                goto LAB_00521827;
            case Map::Units::UT_E_KNIGHT:
                if (param_1 == 1) {
                    iVar5 = 0x56;
                LAB_005218ec:
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                        (int)DAT_UnitsState::instance.units[iVar3].x, (int)(DAT_UnitsState::instance.units[iVar3].y),
                        iVar5);
                } else {
                    if ((param_1 == 2) || (param_1 == 3)) {
                        MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                            (int)DAT_UnitsState::instance.units[iVar3].x,
                            (int)(DAT_UnitsState::instance.units[iVar3].y), 0x57);
                    }
                    if (3 < iVar5) {
                        iVar5 = 0x58;
                        goto LAB_005218ec;
                    }
                }
                iVar5 = 0x59;
            LAB_00521827:
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)DAT_UnitsState::instance.units[iVar3].x, (int)(DAT_UnitsState::instance.units[iVar3].y),
                    iVar5);
                return;
            case Map::Units::UT_E_ENGINEER:
                if ((DAT_UnitsState::instance.units[iVar3].unitType == Map::Units::UT_E_ENGINEER)
                    && (DAT_UnitsState::instance.units[iVar3].resourceToDeposit != 0)) {
                    param_1 = 0x24;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0x24);
                }
                break;
            case Map::Units::UT_S_CATAPULT:
            case Map::Units::UT_S_TOWER:
            case Map::Units::UT_S_BATTERINGRAM:
                iVar5 = MACRO_CALL_MEMBER(
                    Map::Units::UnitsState_Func::getRemainingRequiredEngineers, DAT_UnitsState::ptr)(iVar3);
                if (iVar5 <= 0) {
                    iVar5 = 0x68;
                    goto LAB_0052188b;
                }
                if ((DAT_UnitsState::instance.units[iVar3]
                            .digTileX__OR__countCurrentlyManningEnginers__OR__forCowsRandomBelow300
                        == 0)
                    || (3 < iVar5)) {
                    param_1 = 0xe;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xe);
                }
                if (iVar5 == 1) {
                    param_1 = 0xb;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xb);
                }
                if (iVar5 == 2) {
                    param_1 = 0xc;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xc);
                }
                if (iVar5 == 3) {
                    param_1 = 0xd;
                    MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playUnitSpeechEffect, DAT_SFXState::ptr)(0xd);
                }
                break;
            case Map::Units::UT_A_HARCHER:
                psVar1 = &DAT_UnitsState::instance.units[iVar3].y;
                psVar2 = &DAT_UnitsState::instance.units[iVar3].x;
                if (param_1 == 1) {
                    iVar3 = (int)*psVar1;
                    iVar5 = (int)*psVar2;
                    sfxOffsetInArray = 0xea;
                } else if (param_1 < 5) {
                    iVar3 = (int)*psVar1;
                    iVar5 = (int)*psVar2;
                    sfxOffsetInArray = 0xeb;
                } else {
                    iVar3 = (int)*psVar1;
                    iVar5 = (int)*psVar2;
                    sfxOffsetInArray = 0xec;
                }
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    iVar5, iVar3, sfxOffsetInArray);
                MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playSFXAtLocationFullVolume, DAT_SFXState::ptr)(
                    (int)*psVar2, (int)(*psVar1), 0x59);
            }
        }

    }
}
}
