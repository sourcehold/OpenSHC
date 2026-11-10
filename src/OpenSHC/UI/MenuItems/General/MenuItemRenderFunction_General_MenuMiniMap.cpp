#include "../General.func.hpp"

#include "OpenSHC/UI/Helpers.func.hpp"
#include "OpenSHC/UI/MinimapViewState.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_ButtonBackgroundBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MinimapViewState.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/INT_00b95950.hpp"
#include "OpenSHC/Globals/INT_00b95960.hpp"
#include "OpenSHC/Globals/INT_00b95f6c.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x00428150
        void General::MenuItemRenderFunction_General_MenuMiniMap(int unused, ...)
        {
            if (MACRO_CALL(OpenSHC::UI::Helpers_Func::AModalDialogIsActiveButIsNotQuitting)()) {
                return;
            }
            int const buttonX = DAT_ButtonX::instance;
            int const buttonY = DAT_ButtonY::instance;
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderedBoxWithCustomBlendedBackground,
                DAT_PencilRenderCore::ptr)(
                buttonX - 108, buttonY - 108, 216, 216, DAT_ButtonBackgroundBlendStrength::instance);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if (DAT_GameSynchronyState::instance.DAT_MapSelectionTotalNumber == 0
                || DAT_GameSynchronyState::instance.DAT_MapSelectionRelativeSelected == -1) {
                return;
            }
            if (DAT_ButtonBackgroundBlendStrength::instance == 0) {
                MACRO_CALL_MEMBER(OpenSHC::UI::MinimapViewState_Func::renderMinimapPreview, DAT_MinimapViewState::ptr)(
                    buttonX - 100, buttonY - 100);
                for (int position = 0; position < countof(DAT_GameCore::instance.keepPositions); ++position) {
                    int const keepX = DAT_GameCore::instance.keepPositions[position].x;
                    if (keepX < 0) {
                        continue;
                    }
                    char const player = DAT_GameSynchronyState::instance.playerPositionsArray[position];
                    if (player == INT_00b95960::instance) {
                        continue;
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    // -10 marks a free position
                    if (player == -10) {
                        if (INT_00b95950::instance == position) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 211,
                                keepX - 103 + buttonX,
                                DAT_GameCore::instance.keepPositions[position].y - 107 + buttonY);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 220,
                                keepX - 103 + buttonX,
                                DAT_GameCore::instance.keepPositions[position].y - 107 + buttonY);
                        }
                    } else {
                        if (DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player + 1] > 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                                DAT_GameSynchronyState::instance.DAT_PlayerGroupArray[player + 1] * 2 + 492,
                                keepX - 96 + buttonX, DAT_GameCore::instance.keepPositions[position].y - 100 + buttonY,
                                12);
                        }
                        // the keep x and the player are read again below: the locals instead lose the match
                        if (INT_00b95f6c::instance != 0) {
                            int const drawX = DAT_GameCore::instance.keepPositions[position].x - 113 + buttonX;
                            int const playerIndex = DAT_GameSynchronyState::instance.playerPositionsArray[position];
                            int const drawY = DAT_GameCore::instance.keepPositions[position].y - 116 + buttonY;
                            if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[playerIndex + 1] != -1) {
                                // Render Player portrait
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, playerIndex + 719, drawX, drawY);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    DAT_GameSynchronyState::instance.playerPositionsArray[position] + 20, drawX + 2,
                                    drawY + 2);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                    DAT_PencilRenderCore::ptr)(
                                    drawX, drawY, drawX + 35, drawY + 35, COL_BLACK::instance.shortValue);
                            } else if (DAT_GameSynchronyState::instance.currentAIArray[playerIndex + 1] != 0) {
                                // Render AI portrait
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, playerIndex + 719, drawX, drawY);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                    DAT_GameSynchronyState::instance.currentAIArray
                                            [DAT_GameSynchronyState::instance.playerPositionsArray[position] + 1]
                                        + 700,
                                    drawX, drawY);
                            }
                        } else if (INT_00b95950::instance == position) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3,
                                DAT_GameSynchronyState::instance.playerPositionsArray[position] + 212,
                                DAT_GameCore::instance.keepPositions[position].x - 103 + buttonX,
                                DAT_GameCore::instance.keepPositions[position].y - 107 + buttonY);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                DAT_GameSynchronyState::instance.playerPositionsArray[position] + 470,
                                DAT_GameCore::instance.keepPositions[position].x - 103 + buttonX,
                                DAT_GameCore::instance.keepPositions[position].y - 107 + buttonY);
                        }
                    }
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                }
                if (INT_00b95960::instance >= 0) {
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                        INT_00b95960::instance + 470, DAT_MouseState::instance.screenSpaceX - 5,
                        DAT_MouseState::instance.screenSpaceY - 7);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    if (!DAT_MouseState::instance.leftClickState && !DAT_MouseState::instance.draggingStopped) {
                        INT_00b95960::instance = -1;
                    }
                }
            }
            INT_00b95950::instance = -1;
        }

    }
}
}
