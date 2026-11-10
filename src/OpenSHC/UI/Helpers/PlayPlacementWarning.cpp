#include "../Helpers.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_SFXState.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004380E0
    void Helpers::PlayPlacementWarning(BuildingFailReasonEnum reason)
    {
        switch (reason) {
        case Map::Buildings::BFRE_NOT_ADJ_STOCKPILE:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToStockpile);
            return;
        case Map::Buildings::BFRE_NOT_ADJ_ARMORY:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToArmory);
            return;
        case Map::Buildings::BFRE_NOT_IRON_ORE:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_IronMineMustBeBuiltOnIronOre);
            return;
        case Map::Buildings::BFRE_NOT_OIL_MARSH:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_PitchrigMustBeBuiltOnOilInTheMarsh);
            return;
        case Map::Buildings::BFRE_NOT_ADJ_GRANARY:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                SFX_NeedsToBePlacedAdjacentToGranary);
            return;
        case Map::Buildings::BFRE_MISSING2:
            // "placement_warning21.wav"
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning21_wav_005a2650);
            return;
        case Map::Buildings::BFRE_MISSING4:
            // "placement_warning19.wav"
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning19_wav_005a2638);
            return;
        case Map::Buildings::BFRE_MUST_BE_PLACED_ON_OASES:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_FarmsMustBePlacedOnOases);
            return;
        case Map::Buildings::BFRE_MISSING5:
            // "placement_warning20.wav"
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(
                s_placement_warning20_wav_005a2608);
            return;
        default:
            MACRO_CALL_MEMBER(Audio::SFX::SFXState_Func::playWAVSFX, DAT_SFXState::ptr)(SFX_CantPlaceThatThereMyLord);
        }
    }

}
}
