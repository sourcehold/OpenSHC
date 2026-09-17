/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits.func.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/UI/Credits.hpp"
namespace OpenSHC {
namespace UI {
    namespace Credits_Func {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1), false, Address::SHC_3BB0A8C1_0x004D9270,
            &OpenSHC::UI::Credits::SetActiveCreditsSequenceIndex)
        SetActiveCreditsSequenceIndex;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA180,
            &OpenSHC::UI::Credits::StopCreditsPlaybackAndSounds)
        StopCreditsPlaybackAndSounds;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA200,
            &OpenSHC::UI::Credits::EndCreditsSegmentAndAdvanceToNext)
        EndCreditsSegmentAndAdvanceToNext;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA300, &OpenSHC::UI::Credits::ResetCredits)
        ResetCredits;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, undefined4 param_2), false,
            Address::SHC_3BB0A8C1_0x004DA7A0, &OpenSHC::UI::Credits::AppendCreditsSoundEntry)
        AppendCreditsSoundEntry;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1), false, Address::SHC_3BB0A8C1_0x004DA7E0,
            &OpenSHC::UI::Credits::AppendCreditsCommand)
        AppendCreditsCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA810,
            &OpenSHC::UI::Credits::AppendCreditsListTerminator)
        AppendCreditsListTerminator;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA840, &OpenSHC::UI::Credits::AppendCreditsPauseCommand)
        AppendCreditsPauseCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA870,
            &OpenSHC::UI::Credits::AppendCreditsSegmentEndCommand)
        AppendCreditsSegmentEndCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(), false, Address::SHC_3BB0A8C1_0x004DA8A0,
            &OpenSHC::UI::Credits::AppendCreditsClearImageCommand)
        AppendCreditsClearImageCommand;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5), false,
            Address::SHC_3BB0A8C1_0x004DA8D0, &OpenSHC::UI::Credits::AppendCreditsImageTransitionCommand)
        AppendCreditsImageTransitionCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004DA9A0,
            &OpenSHC::UI::Credits::AppendCreditsImageEndCommand)
        AppendCreditsImageEndCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
                                    undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
            false, Address::SHC_3BB0A8C1_0x004DA9F0, &OpenSHC::UI::Credits::AppendCreditsShowImageCommand)
        AppendCreditsShowImageCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(undefined4 param_1, char* param_2, undefined4 param_3,
                                    undefined4 param_4, undefined4 param_5, undefined4 param_6),
            false, Address::SHC_3BB0A8C1_0x004DAA80, &OpenSHC::UI::Credits::AppendCreditsBinkVideoCommand)
        AppendCreditsBinkVideoCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 param_2, undefined4 param_3), false,
            Address::SHC_3BB0A8C1_0x004DAB00, &OpenSHC::UI::Credits::AppendCreditsFixedImageCommand)
        AppendCreditsFixedImageCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(char* param_1, undefined4 param_2, int param_3, undefined4 param_4),
            false, Address::SHC_3BB0A8C1_0x004DAB80, &OpenSHC::UI::Credits::AppendCreditsBinkVideoWithAudioCommand)
        AppendCreditsBinkVideoWithAudioCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, SHC_SoundStream param_2), false,
            Address::SHC_3BB0A8C1_0x004DABF0, &OpenSHC::UI::Credits::AppendCreditsSoundStreamCommand)
        AppendCreditsSoundStreamCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
                                    undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
            false, Address::SHC_3BB0A8C1_0x004DAC30, &OpenSHC::UI::Credits::AppendCreditsTextCommand)
        AppendCreditsTextCommand;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, int param_2), false, Address::SHC_3BB0A8C1_0x004DACF0,
            &OpenSHC::UI::Credits::AppendCreditsTextEndCommand)
        AppendCreditsTextEndCommand;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int state, undefined4 xSpace, undefined4 param_3, undefined4 ySpace, undefined4 someX,
                undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9),
            false, Address::SHC_3BB0A8C1_0x004DAD40, &OpenSHC::UI::Credits::InsertElementIntoAnArrayAt_ec0348)
        InsertElementIntoAnArrayAt_ec0348;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(int param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
                                    undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8),
            false, Address::SHC_3BB0A8C1_0x004DAE00, &OpenSHC::UI::Credits::InsertElementIntoArrayAt_ec0348_3)
        InsertElementIntoArrayAt_ec0348_3;

        MACRO_FUNCTION_RESOLVER(
            void(__cdecl*)(int param_1, undefined4 xSpace, undefined4 param_3, undefined4 param_4, undefined4 ySpace,
                undefined4 someX, int param_7, undefined4 someY, undefined4 param_9),
            false, Address::SHC_3BB0A8C1_0x004DAE90, &OpenSHC::UI::Credits::InsertElementIntoArrayAt_ec0348_2)
        InsertElementIntoArrayAt_ec0348_2;

        MACRO_FUNCTION_RESOLVER(void(__cdecl*)(float param_1), false, Address::SHC_3BB0A8C1_0x004DB390,
            &OpenSHC::UI::Credits::RenderScrollingCreditsTextFrame)
        RenderScrollingCreditsTextFrame;

    } // namespace Credits_Func
} // namespace UI
} // namespace OpenSHC
