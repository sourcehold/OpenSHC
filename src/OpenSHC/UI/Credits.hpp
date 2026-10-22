/**
  THIS FILE IS AUTO GENERATED
  Communicate changes to the dev team (e.g. via a Pull Request).
  Changes get lost otherwise.

  path: 'OpenSHC/UI/Credits.hpp'
*/

#pragma once

#include "OpenSHC/Audio/MSS/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStreamInt.hpp"
namespace OpenSHC {
namespace UI {
    namespace Credits {

        using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::Audio::MSS::enums::SHC_SoundStreamInt;

        void __cdecl SetActiveCreditsSequenceIndex(undefined4 param_1);

        void __cdecl StopCreditsPlaybackAndSounds();

        void __cdecl EndCreditsSegmentAndAdvanceToNext();

        void __cdecl ResetCredits();

        void __cdecl AppendCreditsSoundEntry(SHC_SoundStreamInt param_1, int param_2);

        void __cdecl AppendCreditsCommand(int param_1);

        void __cdecl AppendCreditsListTerminator();

        void __cdecl AppendCreditsPauseCommand();

        void __cdecl AppendCreditsSegmentEndCommand();

        void __cdecl AppendCreditsClearImageCommand();

        void __cdecl AppendCreditsImageTransitionCommand(
            int param_1, int param_2, int param_3, int param_4, int param_5);

        void __cdecl AppendCreditsImageEndCommand(int param_1, int param_2);

        void __cdecl AppendCreditsShowImageCommand(int param_1, int param_2, int param_3, int param_4, int param_5,
            int param_6, undefined4 param_7, int param_8);

        void __cdecl AppendCreditsBinkVideoCommand(
            undefined4 param_1, char* param_2, int param_3, int param_4, int param_5, SoundFlagsAndLoopCount param_6);

        void __cdecl AppendCreditsFixedImageCommand(int param_1, int param_2, int param_3);

        void __cdecl AppendCreditsBinkVideoWithAudioCommand(char* param_1, int param_2, int param_3, int param_4);

        void __cdecl AppendCreditsSoundStreamCommand(int param_1, SHC_SoundStream param_2);

        void __cdecl AppendCreditsTextCommand(
            int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);

        void __cdecl AppendCreditsTextEndCommand(int param_1, int param_2);

        void __cdecl InsertElementIntoAnArrayAt_ec0348(int state, int xSpace, int param_3, int ySpace, int someX,
            int someY, int param_7, int param_8, int param_9);

        void __cdecl InsertElementIntoArrayAt_ec0348_3(
            int param_1, int param_2, int param_3, int param_4, int param_5, int param_6, int param_7, int param_8);

        void __cdecl InsertElementIntoArrayAt_ec0348_2(int param_1, int xSpace, int param_3, int param_4, int ySpace,
            int someX, int param_7, int someY, int param_9);

        void __cdecl RenderScrollingCreditsTextFrame(float param_1);

    } // namespace Credits
} // namespace UI
} // namespace OpenSHC
