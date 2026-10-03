#include "../../Synchrony.func.hpp"
#include "../Commands.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Util/WideCharMultiByteState.func.hpp"
#include "OpenSHC/Commands/GameCommandParameterLocation.hpp"
#include "OpenSHC/Commands/GameCommandParameterReadWrite.hpp"
#include "OpenSHC/Commands/GameCommandScheduling.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_WideCharMultiByteState.hpp"

namespace OpenSHC {
namespace Synchrony {

    using OpenSHC::Commands::GameCommandParameterLocation;
    using OpenSHC::Commands::GameCommandParameterReadWrite;
    using OpenSHC::Commands::GameCommandScheduling;
    using OpenSHC::Game::GameMode;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x00483290
    void Commands::CommandChangeMapSelection()
    {
        int mapIndex;
        char* lpMultiByteStr;
        int numberOfSymbols;
        int _selectionIndex;
        WCHAR _mapName[1002];
        DAT_GameSynchronyState::instance.DAT_CommandSize = 0x7d4;
        DAT_GameSynchronyState::instance.DAT_GameCommandArray[DAT_GameSynchronyState::instance.DAT_CurrentGameCommandID]
            .time = 0;
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_SCHEDULE_AND_SEND) {
            _selectionIndex = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_selectionIndex, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            if (_selectionIndex < 0) {
                mapIndex = 0;
            } else {
                mapIndex = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[_selectionIndex + -1];
            }
            numberOfSymbols = 1000;
            lpMultiByteStr = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                DAT_ResourceManager::ptr)(mapIndex);
            MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::multiByteToWideCharWithSize,
                DAT_WideCharMultiByteState::ptr)(_mapName, (LPCSTR)((int)(lpMultiByteStr)), numberOfSymbols);
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(_mapName, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_SERIALIZE_INTO_PARAM_1);
            DAT_GameSynchronyState::instance.DAT_CommandActionPlan = OpenSHC::Commands::GCS_EXECUTE;
            ;
            return;
        }
        if (DAT_GameSynchronyState::instance.DAT_CommandActionPlan == OpenSHC::Commands::GCS_EXECUTE) {
            MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                DAT_GameSynchronyState::ptr)(&_selectionIndex, 4, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
            if ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER)
                || (DAT_GameCore::instance.isSkirmishTrail != TRUE)) {
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::serializeOrDeserializeCommandParameter,
                    DAT_GameSynchronyState::ptr)(_mapName, 2000, OpenSHC::Commands::GCPL_FIXED_COMMAND_DATA_ADDRESS,
                    OpenSHC::Commands::GCPRW_DESERIALIZE_FROM_PARAM1);
                MACRO_CALL_MEMBER(OpenSHC::Util::WideCharMultiByteState_Func::wideCharToMultiByteWithSize,
                    DAT_WideCharMultiByteState::ptr)(
                    DAT_GameSynchronyState::instance.mapName, (LPWSTR)((int)(_mapName)), 1000);
            }
            if (_selectionIndex < 0) {
                DAT_GameSynchronyState::instance.mapName[0] = '\0';
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::DisplayMapDescriptionAndAllocatePlayersToSlots)();
            DAT_GameSynchronyState::instance.skirmishRelated1 = -1;
        };
    }

}
}
