#include "../LobbyMenu.func.hpp"

#include "OpenSHC/Global.func.hpp"
#include "OpenSHC/IO/ResourceManager.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuModalType.hpp"

#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MenuTextInputState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_ResourceManager.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x0042B4C0
        void LobbyMenu::MenuItemRenderFunction_LobbyMenu_MapSelectTable(int row, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            // set for the host while the round table or an AI lord select is open; a guest stores TRUE, then FALSE
            bool const aiSetupOpen
                = DAT_MenuModalComposition1::instance.activeModalDialogID == OpenSHC::UI::Enums::MMT_ROUNDTABLE
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_BASIC_AI_LORD_SELECT
                || DAT_MenuModalComposition1::instance.activeModalDialogID
                    == OpenSHC::UI::Enums::MMT_EXTENDED_AI_LORD_SELECT;
            if (aiSetupOpen) {
                DAT_ButtonUnknownZero::instance = TRUE;
            }
            if (!aiSetupOpen || !DAT_GameSynchronyState::instance.isHost) {
                DAT_ButtonUnknownZero::instance = FALSE;
            }
            // for a guest, -1 marks another map than the host's and 1 the host's map
            int hostMap = 0;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            if (!DAT_GameSynchronyState::instance.isHost) {
                hostMap = -1;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row
                        < DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber
                    && MACRO_CALL(OpenSHC::OS_Func::__stricmp)(
                           MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                               DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                                   .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset
                                       + row]),
                           DAT_GameSynchronyState::instance.mapName)
                        == 0) {
                    hostMap = 1;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                        DAT_PencilRenderCore::ptr)(TRUE, row, DAT_ButtonBackgroundBlendStrength::instance);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                        DAT_PencilRenderCore::ptr)(FALSE, row, DAT_ButtonBackgroundBlendStrength::instance);
                }
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawTableCellBackground,
                    DAT_PencilRenderCore::ptr)(row == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected,
                    row, DAT_ButtonBackgroundBlendStrength::instance);
            }
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row
                >= DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber) {
                return;
            }
            int iconsWidth = 0;
            uint color;
            if (DAT_GameSynchronyState::instance.unknownMapRelatedReceivedDataArray[DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]]
                <= 0) {
                color = OpenSHC::Rendering::Colors::COL_7F7F7F;
            } else if ((row == DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected
                           || DAT_ButtonCurrentlyInteracting::instance || hostMap == 1)
                && hostMap >= 0) {
                color = OpenSHC::Rendering::Colors::COL_CCFAFF;
            } else {
                color = OpenSHC::Rendering::Colors::COL_C2F0EB;
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                DAT_GameSynchronyState::instance.mapPlayerCountArray[DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]],
                DAT_ButtonX::instance + 8, DAT_ButtonY::instance + 3, OpenSHC::Text::TTA_LEFT, color, 18, FALSE,
                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
            if (DAT_GameSynchronyState::instance.mapBalanceArray[DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]]
                != 0) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 210,
                    DAT_ButtonX::instance + 24, DAT_ButtonY::instance + 5, DAT_ButtonBackgroundBlendStrength::instance);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                iconsWidth = 20;
            }
            int descriptionGroup;
            if (DAT_GameSynchronyState::instance.mapU4Int0_2Array[DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]]
                != 0) {
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 394,
                    DAT_ButtonX::instance + 24 + iconsWidth, DAT_ButtonY::instance + 5,
                    DAT_ButtonBackgroundBlendStrength::instance);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                // the file name first: as an argument, &descriptionGroup would be pushed before the call
                char* const fileName = MACRO_CALL_MEMBER(
                    OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex, DAT_ResourceManager::ptr)(
                    DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]);
                char* const name
                    = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(fileName, &descriptionGroup);
                DAT_TextManagerObject::instance.field_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    name, DAT_ButtonX::instance + 44 + iconsWidth, DAT_ButtonY::instance + 3, 150 - iconsWidth, color,
                    18, (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
                return;
            }
            char* const fileName
                = MACRO_CALL_MEMBER(OpenSHC::IO::ResourceManager_Func::mapNames_getLoadedMapNameForIndex,
                    DAT_ResourceManager::ptr)(DAT_MenuTextInputState::instance
                        .DAT_ArrayOfMapIndices[DAT_GameSynchronyState::instance.DAT_MapSelectionScrollOffset + row]);
            char* const name
                = MACRO_CALL(OpenSHC::Global_Func::GetStringBasedOnHardcodedMaps)(fileName, &descriptionGroup);
            DAT_TextManagerObject::instance.field_0x30 = 1;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                name, DAT_ButtonX::instance + 24 + iconsWidth, DAT_ButtonY::instance + 3, 170 - iconsWidth, color, 18,
                (DAT_ButtonBackgroundBlendStrength::instance - 32) * 32 / 32 + 32);
        }

    }
}
}
