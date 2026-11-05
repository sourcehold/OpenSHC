#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00492C90
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableContent(int row, ...)
        {
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                row == DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex, row, 0);
            if (DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + row
                >= DAT_MenuTextInputState::instance.fileListEntryCount) {
                return;
            }
            int const mapIndex
                = DAT_MenuTextInputState::instance
                      .DAT_ArrayOfMapIndices[DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset
                          + row];
            // the file's DOS time stamp: day, month, two-digit year, hour, minute
            // the game reads it here, before the calls below
            int const fileTime = DAT_ResourceManager::instance.mapFileTimes[mapIndex];
            uint color;
            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                && DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER
                && DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices2[mapIndex - 1] == 0) {
                // outside solitary and skirmish, a file with flag 0 is greyed out (SaveLoadMap_Buttons won't load it)
                color = OpenSHC::Rendering::Colors::COL_7F7F7F;
            } else if (row == DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionIndex
                || DAT_ButtonCurrentlyInteracting::instance) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
            }
            // the game reads the position and the name before it sets field_0x30
            int const textY = DAT_ButtonY::instance + 3;
            int const textX = DAT_ButtonX::instance + 8;
            char* const mapName
                = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(mapIndex);
            DAT_TextManagerObject::instance.field_0x30 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                mapName, textX, textY, 195, color, 18, 0);
            char dateText[32];
            // "%02d/%02d/%02d %02d:%02d"
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(dateText, s__02d_02d_02d__02d_02d_005a229c, (fileTime >> 16) & 31,
                (fileTime >> 21) & 15, (fileTime >> 25) - 20, (fileTime >> 11) & 31, (fileTime >> 5) & 63);
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(dateText,
                DAT_ButtonX::instance + 208, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT, color, 18, FALSE, 0);
        }

    }
}
}
