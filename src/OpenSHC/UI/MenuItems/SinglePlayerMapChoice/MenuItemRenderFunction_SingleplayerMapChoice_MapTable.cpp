#include "../SinglePlayerMapChoice.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MapMissionType.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042D9A0
        void SinglePlayerMapChoice::MenuItemRenderFunction_SingleplayerMapChoice_MapTable(int row, ...)
        {
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                DAT_PencilRenderCore::ptr)(row == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected,
                row, DAT_ButtonBackgroundBlendStrength::instance);
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row
                < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                uint color;
                if (row == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected) {
                    color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                } else {
                    color = OpenSHC::Rendering::Colors::COL_C2F0EB;
                    if (DAT_ButtonCurrentlyInteracting::instance) {
                        color = OpenSHC::Rendering::Colors::COL_CCFAFF;
                    }
                }
                int nameWidth;
                if (DAT_MapMissionType::instance == 2) {
                    nameWidth = 230;
                } else {
                    nameWidth = 370;
                }
                int textShift;
                if (DAT_MapMissionType::instance != 0) {
                    textShift = 5;
                    if (DAT_MenuTextInputState::instance.arrayOfMapEndInt2[DAT_MenuTextInputState::instance
                                .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                    + row]]
                        == 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 727,
                            DAT_ButtonX::instance + 6, DAT_ButtonY::instance + 3,
                            DAT_ButtonBackgroundBlendStrength::instance);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 124,
                            DAT_ButtonX::instance + 1, DAT_ButtonY::instance + 4,
                            DAT_ButtonBackgroundBlendStrength::instance);
                    }
                } else {
                    textShift = -16;
                }
                char* const loadedName = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex, DAT_ResourceManager::ptr)(
                    DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]);
                int descriptionGroup;
                char* const mapName
                    = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(loadedName, &descriptionGroup);
                // the fades go through locals as in the original: inlining them loses the match
                int const nameFade = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                DAT_TextManagerObject::instance.field_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    mapName, DAT_ButtonX::instance + 24 + textShift, DAT_ButtonY::instance + 3, nameWidth, color, 18,
                    nameFade / 32 + 32);
                // fixme: the original reads the load-game list's scroll offset here, not DAT_MapSelectionScrollOffset
                // the file's DOS time stamp: day, month, two-digit year, hour, minute
                int const fileTime
                    = DAT_ResourceManager::instance.mapFileTimes[DAT_MenuTextInputState::instance.DAT_ArrayOfMapIndices
                            [DAT_MenuTextInputState::instance.menuLoadGameRelativeSelectionOffset + row]];
                // "%02d/%02d/%02d %02d:%02d"
                char dateText[32];
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)(dateText, s__02d_02d_02d__02d_02d_005a229c,
                    (fileTime >> 16) & 31, (fileTime >> 21) & 15, (fileTime >> 25) - 20, (fileTime >> 11) & 31,
                    (fileTime >> 5) & 63);
                int const dateFade = (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    dateText, DAT_ButtonX::instance + 308, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT, color,
                    18, FALSE, dateFade / 32 + 32);
            }
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        }

    }
}
}
