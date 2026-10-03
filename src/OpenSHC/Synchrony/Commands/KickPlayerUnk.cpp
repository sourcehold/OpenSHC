#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony/Actions.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/MenuItems/General.func.hpp"
#include "OpenSHC/Audio/mss/SoundFlagsAndLoopCount.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"

#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Audio::MSS::SoundFlagsAndLoopCount;
    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Game::GameMode;
    using OpenSHC::IO::FileResourceType;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00484F30
    void Commands::KickPlayerUnk()
    {
        char* filename;
        SoundFlagsAndLoopCount flagsAndLoopCount;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        DAT_GameSynchronyState::instance.DAT_CommandSize = 4;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&DAT_GameSynchronyState::instance.DAT_GameCommandParam0, 4,
                OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS, OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if (DAT_GameSynchronyState::instance.DAT_GameCommandParam0
                == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                    OpenSHC::IO::FRT_GFX_SPEECH, "insult1.wav");
                flagsAndLoopCount = -536870911;
                filename = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::getFileNameOfCurrentActiveResource, DAT_ResourceManager::ptr)();
                MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playSoundOnStream3Unk,
                    DAT_SoundSystemState::ptr)(filename, flagsAndLoopCount);
                DAT_GameSynchronyState::instance.kickedAtTime = timeGetTime();
                DAT_GameSynchronyState::instance.currentGameMode = OpenSHC::Game::GM_MULTIPLAYER_END_OF_GAME;
                DAT_MenuTextInputState::instance.DAT_MenuOptionsActionParameter = 7;
                MACRO_CALL(
                    OpenSHC::UI::MenuItems::General_Func::MenuItemActionHandler_General_LaunchOrQuitMultiplayerGameUnk)(
                    0x16);
                MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(
                    DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
            }
            if (DAT_GameSynchronyState::instance.currentAIArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                != 0) {
                DAT_GameSynchronyState::instance.currentAIArray[DAT_GameSynchronyState::instance.DAT_GameCommandParam0]
                    = 0;
            }
            MACRO_CALL(OpenSHC::Synchrony::Actions_Func::RemovePositionOfPlayer)(
                DAT_GameSynchronyState::instance.DAT_GameCommandParam0);
        }
    }

}
}
