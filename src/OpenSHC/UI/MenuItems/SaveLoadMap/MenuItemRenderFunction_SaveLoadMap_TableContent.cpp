#include "../SaveLoadMap.func.hpp"

#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::Game::GameMode;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
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
        // FUNCTION: STRONGHOLDCRUSADER 0x00492C90
        void SaveLoadMap::MenuItemRenderFunction_SaveLoadMap_TableContent(int param_1, ...)
        {
            int mapIndex;
            dword dVar1;
            char* text;
            int yPos;
            int xPos;
            uint color;
            char local_24[32];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)local_24;
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground, DAT_PencilRenderCore::ptr)(
                (uint)(param_1 == DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex), param_1, 0);
            if (DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1
                < DAT_MenuTextInputState::instance.field32_0x74) {
                mapIndex
                    = DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                          [DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionOffset + param_1 + -1];
                dVar1 = DAT_ResourceManager::instance.mapFileTimes[mapIndex];
                if (((DAT_GameSynchronyState::instance.currentGameMode == OpenSHC::Game::GM_SOLITARY)
                        || (DAT_GameSynchronyState::instance.currentGameMode
                            == OpenSHC::Game::GM_SKIRMISH_SINGLE_PLAYER))
                    || (DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices[mapIndex + 499] != 0)) {
                    if ((param_1 == DAT_MenuTextInputState::instance.DAT_MenuLoadGameRelativeSelectionIndex)
                        || (color = 0xc2f0eb, DAT_ButtonCurrentlyInteracting::instance != FALSE)) {
                        color = 0xccfaff;
                    }
                } else {
                    color = 0x7f7f7f;
                }
                yPos = DAT_ButtonY::instance + 3;
                xPos = DAT_ButtonX::instance + 8;
                text = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(mapIndex);
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    text, xPos, yPos, 0xc3, color, 0x12, 0);
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_24, "%02d/%02d/%02d %02d:%02d", (int)dVar1 >> 0x10 & 0x1f,
                    (int)dVar1 >> 0x15 & 0xf, ((int)dVar1 >> 0x19) + -0x14, (int)dVar1 >> 0xb & 0x1f,
                    (int)dVar1 >> 5 & 0x3f);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_24, (int)((int)(DAT_ButtonX::instance + 0xd0)), (int)((int)(DAT_ButtonY::instance + 3)),
                    OpenSHC::Text::TTA_LEFT, (BGR24)((int)(color)), 0x12, FALSE, 0);
            };
        }

    }
}
}
