/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;

        void __cdecl SetActiveCreditsSequenceIndex(undefined4 param_1);

        void __cdecl StopCreditsPlaybackAndSounds();

        void __cdecl EndCreditsSegmentAndAdvanceToNext();

        void __cdecl ResetCredits();

        void __cdecl AppendCreditsSoundEntry(undefined4 param_1, undefined4 param_2);

        void __cdecl AppendCreditsCommand(int param_1);

        void __cdecl AppendCreditsListTerminator();

        void __cdecl AppendCreditsPauseCommand();

        void __cdecl AppendCreditsSegmentEndCommand();

        void __cdecl AppendCreditsClearImageCommand();

        void __cdecl AppendCreditsImageTransitionCommand(
            int param_1, int param_2, undefined4 param_3, undefined4 param_4, undefined4 param_5);

        void __cdecl AppendCreditsImageEndCommand(int param_1, int param_2);

        void __cdecl AppendCreditsShowImageCommand(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        void __cdecl AppendCreditsBinkVideoCommand(undefined4 param_1, char* param_2, undefined4 param_3,
            undefined4 param_4, undefined4 param_5, undefined4 param_6);

        void __cdecl AppendCreditsFixedImageCommand(int param_1, undefined4 param_2, undefined4 param_3);

        void __cdecl AppendCreditsBinkVideoWithAudioCommand(
            char* param_1, undefined4 param_2, int param_3, undefined4 param_4);

        void __cdecl AppendCreditsSoundStreamCommand(int param_1, SHC_SoundStream param_2);

        void __cdecl AppendCreditsTextCommand(int param_1, int param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        void __cdecl AppendCreditsTextEndCommand(int param_1, int param_2);

        void __cdecl InsertElementIntoAnArrayAt_ec0348(int state, undefined4 xSpace, undefined4 param_3,
            undefined4 ySpace, undefined4 someX, undefined4 someY, undefined4 param_7, int param_8, undefined4 param_9);

        void __cdecl InsertElementIntoArrayAt_ec0348_3(int param_1, undefined4 param_2, undefined4 param_3,
            undefined4 param_4, undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8);

        void __cdecl InsertElementIntoArrayAt_ec0348_2(int param_1, undefined4 xSpace, undefined4 param_3,
            undefined4 param_4, undefined4 ySpace, undefined4 someX, int param_7, undefined4 someY, undefined4 param_9);

        void __cdecl RenderScrollingCreditsTextFrame(float param_1);

    } // namespace Credits
} // namespace UI
} // namespace OpenSHC
