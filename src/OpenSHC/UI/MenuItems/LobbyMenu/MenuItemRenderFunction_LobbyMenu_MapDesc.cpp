#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/COL_VERY_SOFT_YELLOW.hpp"
#include "OpenSHC/Globals/DAT_00b960f4.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004285F0
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapDesc(int buttonID, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            int const x = DAT_ButtonX::instance;
            int const y = DAT_ButtonY::instance;
            // the box, its outline and the scroll bar's column. The edges are declared right, left, top, bottom: in the
            // order bottom, top, left, right, their registers differ from the original's
            {
                int const right = DAT_ButtonW::instance + x + 101;
                int const left = x - 110;
                int const top = y + 3;
                int const bottom = DAT_ButtonH::instance + y + 122;
                // written the long way round, as the original computes them (for the texts it is the strength itself)
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    left, top, right - 20, bottom, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 16 / 32 + 32);
                // the lines only once the menu is fully blended in: the outline, then the column and its two squares
                if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, top - 1, right + 1, top - 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, bottom + 1, right + 1, bottom + 1, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        left - 1, top, left - 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right + 1, top, right + 1, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right - 20, top, right - 20, bottom, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right - 20, top + 20, right, top + 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawLine, DAT_PencilRenderCore::ptr)(
                        right - 20, bottom - 20, right, bottom - 20, COL_VERY_SOFT_YELLOW::instance.shortValue);
                }
            }
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber == 0
                || DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                return;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRange,
                DAT_TextureRenderCoreObject::ptr)(y + 7, DAT_ButtonH::instance + y + 121);
            // the host shows the selected map, a guest the map the host chose. The lookup and the title are written in
            // both arms, and the title's x at each use: written once, or x - 100 in a local, the match is lost
            if (DAT_GameSynchronyState::instance.isHost) {
                // the lookup's second result, which is not used. Declared in each arm: at function scope its address
                // stays live to the end and the last call is no longer a tail jump; with a value it gets a store
                int descriptionGroup;
                // the file name and the title are locals: written into the calls that use them, the match is lost
                char* const fileName
                    = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                        DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                            .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                + DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected]);
                char* const title
                    = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(fileName, &descriptionGroup);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    title, x - 100, y - DAT_00b960f4::instance - 8, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            } else {
                int descriptionGroup;
                char* const title = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(
                    DAT_GameSynchronyState::instance.mapName, &descriptionGroup);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    title, x - 100, y - DAT_00b960f4::instance - 8, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 19, FALSE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            }
            // "-"
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                s___005a2280, x - 94, y - DAT_00b960f4::instance - 8, OpenSHC::Text::TTA_LEFT,
                OpenSHC::Rendering::Colors::COL_C2F0EB, 19, TRUE,
                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            // "Unbalanced" (412) or "Balanced" (411)
            if (DAT_GameCore::instance.savedMapBalance != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 412, x - 88, y - DAT_00b960f4::instance - 8,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, TRUE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextFromTextGroup, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM, 411, x - 88, y - DAT_00b960f4::instance - 8,
                    OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, TRUE,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            }
            // the description: the map's own text, or one from the string table
            if (!DAT_GameCore::instance.mapDescUseStringTable) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    DAT_GameCore::instance.mapDescription, x - 100, y - DAT_00b960f4::instance + 11,
                    DAT_ButtonW::instance + 170, OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                    DAT_TextureRenderCoreObject::ptr)();
                return;
            }
            if (DAT_GameCore::instance.mapDescUseStringTableIndex != 0) {
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineTextUnk, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MAP_NAMES, DAT_GameCore::instance.mapDescUseStringTableIndex, x - 100,
                    y - DAT_00b960f4::instance + 11, DAT_ButtonW::instance + 170,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 19,
                    (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            }
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::TextureRenderCore_Func::setScreenMenuSurfaceHeightRangeToResolution,
                DAT_TextureRenderCoreObject::ptr)();
        }

    }
}
}
