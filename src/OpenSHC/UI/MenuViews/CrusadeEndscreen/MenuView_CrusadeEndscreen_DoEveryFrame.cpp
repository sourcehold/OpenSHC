#include "../CrusadeEndscreen.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/DE/SHCDE/eMusicIDs.hpp"

#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/INT_00ed27b8.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eMusicIDs;

        /*
          WARNING: Enum "eMusicIDs": Some values do not have unique names
         */
        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004E1F50
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_DoEveryFrame()
        {
            int iVar1;
            iVar1 = MACRO_CALL(OpenSHC::UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1 != 0) {
                MACRO_CALL(OpenSHC::Rendering_Func::ProcessCreditsScriptCommands)();
                if ((0x3a < DAT_UnknownBinkIndex::instance) && (INT_00ed27b8::instance == 0)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID,
                        DAT_SoundSystemState::ptr)(OpenSHC::DE::SHCDE::MUSIC_GERMAN_EGG);
                    INT_00ed27b8::instance = 1;
                }
                MACRO_CALL(OpenSHC::Rendering_Func::RenderActiveCreditsElements)();
            }
        }

    }
}
}
