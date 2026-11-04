// disable deprecation warnings for strcpy and strcat
#pragma warning(disable : 4996)

#include "../Rendering.func.hpp"

#include "OpenSHC/IO/FilePackager.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Synchrony.func.hpp"
#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/Commands/GameCommandType.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/FileResourceType.hpp"
#include "OpenSHC/string-macros.hpp"

#include "OpenSHC/Globals/DAT_00b95b74.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/FilePackagerObj.hpp"
#include "OpenSHC/Globals/INT_00b95958.hpp"
#include "OpenSHC/Globals/INT_00b95ab8.hpp"
#include "OpenSHC/Globals/INT_00b960b0.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004410D0
    void Rendering::DisplayMapDescriptionAndAllocatePlayersToSlots()
    {
        if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                >= 0
            || (!DAT_GameSynchronyState::instance.isHost && strlen(DAT_GameSynchronyState::instance.mapName) != 0)) {
            char mapFileName[1008];
            strcpy(mapFileName, DAT_GameSynchronyState::instance.mapName);
            // ".map"
            strcat(mapFileName, S__MAP_005A2294);
            MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::resolveResourceFileName, DAT_ResourceManager::ptr)(
                OpenSHC::IO::FRT_MAPS, mapFileName);
            MACRO_CALL_MEMBER(OpenSHC::IO::FilePackager_Func::readMapHeader, FilePackagerObj::ptr)(TRUE);
            INT_00b95958::instance = 1;
            DAT_00b95b74::instance = 0;
            DAT_00b960f4::instance = -19;
            if (DAT_GameCore::instance.mapDescUseStringTable == 0) {
                DAT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                    DAT_GameCore::instance.mapDescription, 0, 0, 345, 0, 0, 1);
            } else if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
                DAT_00b95b74::instance = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[19])(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.mapDescUseStringTableIndex),
                    0, 0, 345, 0, 0, 1);
            }
            if (DAT_GameSynchronyState::instance.isHost
                && (INT_00b960b0::instance
                        != DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                            + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                    || INT_00b95ab8::instance != 0)) {
                INT_00b960b0::instance = DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                    + DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset;
                memset(DAT_GameSynchronyState::instance.playerPositionsArray, -10,
                    sizeof(DAT_GameSynchronyState::instance.playerPositionsArray));
                for (int playerID = 1; playerID < 9; ++playerID) {
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerID] != -1
                        || DAT_GameSynchronyState::instance.currentAIArray[playerID] != 0) {
                        MACRO_CALL(OpenSHC::Synchrony_Func::PutPlayerIntoRandomSlot)(playerID);
                    }
                }
                MACRO_CALL_MEMBER(OpenSHC::Synchrony::GameSynchronyState_Func::queueCommand,
                    DAT_GameSynchronyState::ptr)(OpenSHC::Commands::GCT_HOST_ANNOUNCE_TEAMS_AND_POSITIONS);
            }
        }
        INT_00b95ab8::instance = 0;
    }

}
}
