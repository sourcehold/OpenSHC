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

        using DE::SHCDE::eMusicIDs;

        // FUNCTION: STRONGHOLDCRUSADER 0x004E1F50
        void CrusadeEndscreen::MenuView_CrusadeEndscreen_DoEveryFrame()
        {
            int iVar1 = MACRO_CALL(UI::Helpers_Func::TicksSinceCounterStart)();
            if (iVar1) {
                MACRO_CALL(Rendering_Func::ProcessCreditsScriptCommands)();
                if ((0x3a < DAT_UnknownBinkIndex::instance) && (!INT_00ed27b8::instance)) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                        DE::SHCDE::MUSIC_GERMAN_EGG);
                    INT_00ed27b8::instance = 1;
                }
                MACRO_CALL(Rendering_Func::RenderActiveCreditsElements)();
            }
        }

    }
}
}
