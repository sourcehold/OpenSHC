#include "../Allies.func.hpp"

#include "OpenSHC/Synchrony/GameSynchronyState.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_00df42b0.hpp"
#include "OpenSHC/Globals/DAT_00df51f0.hpp"
#include "OpenSHC/Globals/DAT_00df51f4.hpp"
#include "OpenSHC/Globals/DAT_AlliesCount.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_LastTeamMemberIndex.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SomeTeamMemberPlayerIDArray.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        // FUNCTION: STRONGHOLDCRUSADER 0x004AC7A0
        void Allies::MenuItemRenderFunction_Allies_Main(int button, ...)
        {
            if (button == 100) {
                return;
            }
            // without allies every item but -1 is off
            if (DAT_AlliesCount::instance < 1 && button != -1) {
                DAT_ButtonUnknownZero::instance = TRUE;
                DAT_ButtonCurrentlyInteracting::instance = FALSE;
                return;
            }
            if (button == 110 || button == 111) {
                // 110 and 111: the selected ally's button, shown while it needs help or has asked you to attack
                int const player = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
                if ((DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .requestStateUnk
                            == 1
                        && DAT_GameSynchronyState::instance.currentPlayerFullIDArray[DAT_GameState::instance
                                   .playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                   .playerID_askerUnk]
                            != -1
                        && DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                                .playerID_askerUnk
                            == player)
                    || DAT_GameState::instance.playerDataArray[player].isNotNervousByEnemyTroopValue) {
                    DAT_ButtonUnknownZero::instance = FALSE;
                    MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
                    return;
                }
                DAT_ButtonUnknownZero::instance = TRUE;
                return;
            }
            // 200: the help line; 20 to 22 choose its text
            if (button == 200) {
                if (DAT_00df51f4::instance == 0) {
                    return;
                }
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, DAT_00df51f0::instance, DAT_ButtonX::instance,
                    DAT_ButtonY::instance, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 18,
                    FALSE);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                return;
            }
            DAT_ButtonUnknownZero::instance = FALSE;
            if (button >= 0 && button <= 19) {
                // up to 6: the portrait of the ally at button - 1
                if (button <= 6) {
                    if (button == 1) {
                        DAT_00df51f4::instance = 0;
                    }
                    // button becomes the index, then the ally's player ID (a variable of its own loses the match)
                    button--;
                    if (button >= DAT_AlliesCount::instance) {
                        return;
                    }
                    int const index = button;
                    button = DAT_SomeTeamMemberPlayerIDArray::instance[index];
                    int ai = 0;
                    if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray[button] == -1) {
                        ai = DAT_GameSynchronyState::instance.currentAIArray[button];
                    }
                    // the selected ally's portrait is drawn plain, the others blended
                    // a call in each arm (one call with the picture's number in a local loses the match)
                    if (index == DAT_LastTeamMemberIndex::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, button + 546,
                            DAT_ButtonX::instance, DAT_ButtonY::instance);
                        if (ai == 0) {
                            if (DAT_GameCore::instance.lordIcons[button] == 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 539,
                                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                            } else if (DAT_GameCore::instance.lordIcons[button] == 1) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 540,
                                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                            } else if (DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[button + 19] > 0) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 541,
                                    DAT_ButtonX::instance, DAT_ButtonY::instance);
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFace,
                                    DAT_TextureRenderCoreObject::ptr)(
                                    button + 19, DAT_ButtonX::instance + 4, DAT_ButtonY::instance + 4);
                            }
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, ai + 522,
                                DAT_ButtonX::instance, DAT_ButtonY::instance);
                        }
                    } else if (ai == 0) {
                        if (DAT_GameCore::instance.lordIcons[button] == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 539,
                                DAT_ButtonX::instance, DAT_ButtonY::instance, 12);
                        } else if (DAT_GameCore::instance.lordIcons[button] == 1) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 540,
                                DAT_ButtonX::instance, DAT_ButtonY::instance, 12);
                        } else if (DAT_TextureRenderCoreObject::instance.bitmapFaceSizes[button + 19] > 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 541,
                                DAT_ButtonX::instance, DAT_ButtonY::instance, 12);
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::TextureRenderCore_Func::drawBitmapFaceWithBlendUnk,
                                DAT_TextureRenderCoreObject::ptr)(
                                button + 19, DAT_ButtonX::instance + 4, DAT_ButtonY::instance + 4, 12);
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, ai + 522,
                            DAT_ButtonX::instance, DAT_ButtonY::instance, 12);
                    }
                    if (index == DAT_LastTeamMemberIndex::instance) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 514,
                            DAT_ButtonX::instance - 6, DAT_ButtonY::instance - 6,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 513, 0);
                    }
                    // the signs: resource, help, orders; the blend by if (a conditional expression loses the match)
                    int blend = 0;
                    if (index != DAT_LastTeamMemberIndex::instance) {
                        blend = 8;
                    }
                    int resource
                        = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                              .goodsRequestTypeByPlayer[button];
                    if (resource == OpenSHC::Game::Resources::RT_PITCH) {
                        resource = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                    }
                    // counted from wood on, in a statement of its own (inside the test the match is lost)
                    resource -= OpenSHC::Game::Resources::RT_WOOD;
                    if (resource >= 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            resource + 580, DAT_ButtonX::instance + 60, DAT_ButtonY::instance - 12,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, blend);
                    }
                    if (DAT_GameState::instance.playerDataArray[button].isNotNervousByEnemyTroopValue) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                            DAT_00df42b0::instance + 578, DAT_ButtonX::instance + 60, DAT_ButtonY::instance + 60,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, blend);
                    }
                    if (DAT_GameState::instance.playerDataArray[button].requestStateUnk == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 576,
                            DAT_ButtonX::instance - 15, DAT_ButtonY::instance + 57,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 577, blend);
                    }
                    if (DAT_GameState::instance.playerDataArray[button].requestStateUnk == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 604,
                            DAT_ButtonX::instance - 15, DAT_ButtonY::instance + 57,
                            OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 605, blend);
                    }
                    return;
                }
                if (button != 10) {
                    return;
                }
                // 10: the panel; its frame tile by tile, then the selected ally's state in it
                int const buttonX = DAT_ButtonX::instance;
                int const buttonY = DAT_ButtonY::instance;
                for (int rowY = 0; rowY < DAT_ButtonH::instance; rowY += 24) {
                    // no first value (7 as its first value loses the match)
                    int row;
                    if (rowY == 0) {
                        row = 1;
                    } else if (rowY == DAT_ButtonH::instance - 24) {
                        row = 13;
                    } else {
                        row = 7;
                    }
                    for (int columnX = 0; columnX < 648; columnX += 24) {
                        int picture = row;
                        if (columnX != 0) {
                            if (columnX == 624) {
                                picture = row + 2;
                            } else if (row == 7) {
                                continue;
                            } else {
                                picture = row + 1;
                            }
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, picture,
                            columnX + buttonX, buttonY + rowY, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                            picture + 3, 0);
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    buttonX + 24, buttonY + 24, buttonX + 623, DAT_ButtonH::instance + buttonY - 25, 20);
                // button takes the ally's player ID here too, as above
                button = DAT_SomeTeamMemberPlayerIDArray::instance[DAT_LastTeamMemberIndex::instance];
                // its full ID read once (read twice, the match is lost)
                int const fullID = DAT_GameSynchronyState::instance.currentPlayerFullIDArray[button];
                if (fullID == -1
                    && !MACRO_CALL_MEMBER(
                        OpenSHC::Synchrony::GameSynchronyState_Func::isAIPlayer, DAT_GameSynchronyState::ptr)(button)) {
                    return;
                }
                // the player's name, or the AI lord's
                int y = DAT_ButtonY::instance + 24;
                int const x = DAT_ButtonX::instance + 24;
                if (fullID != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderInGameText, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.DAT_PlayerNames[button], x, y, OpenSHC::Text::TTA_LEFT,
                        DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[button]],
                        0, 17, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_XPLAY_WAITING_ROOM,
                        DAT_GameSynchronyState::instance.aiVariationArray[button] + 103
                            + DAT_GameSynchronyState::instance.currentAIArray[button] * 8,
                        x, y, OpenSHC::Text::TTA_LEFT,
                        DAT_RenderingDefinedData::instance
                            .ColorTable1[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[button]],
                        0, 17, FALSE);
                }
                // the resource it asks for: "Requests", the amount, the resource's picture and its name
                int resource
                    = DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                          .goodsRequestTypeByPlayer[button];
                if (resource == OpenSHC::Game::Resources::RT_PITCH) {
                    resource = OpenSHC::Game::Resources::RT_PARTIALPITCH;
                }
                resource -= OpenSHC::Game::Resources::RT_WOOD;
                y += 32;
                // tested this way round (the other way, the match is lost)
                if (resource < 0) {
                    // "No Goods Requested"
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 1, x, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 12, x, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderLeftAlignedNumberToScreen, DAT_TextManagerObject::ptr)(
                        DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                            .goodsRequestAmountByPlayer[button],
                        x + 5, y, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, resource + 580,
                        DAT_TextManagerObject::instance.currentXOffset_0x0 + x + 10, y - 8,
                        OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 603, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_GOODS, resource + OpenSHC::Game::Resources::RT_WOOD, x + 45, y,
                        OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                }
                // its orders: "No Orders", or "Orders:", "Attack" or "Defend", and the target: "You" or a picture
                y += 32;
                if (DAT_GameState::instance.playerDataArray[button].requestStateUnk == 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 2, x, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 16, x, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                    if (DAT_GameState::instance.playerDataArray[button].requestStateUnk == 1) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, x + 5, y, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                    }
                    if (DAT_GameState::instance.playerDataArray[button].requestStateUnk == 2) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 17, x + 5, y, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                    } else if (DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk
                        == DAT_GameSynchronyState::instance.currentPlayerSlotID) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_ALLIES, 18, x + 10, y, OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 18, TRUE);
                    } else {
                        // a face in a frame, or an AI lord's picture; x before y (the other order loses the match)
                        int const iconX = DAT_TextManagerObject::instance.currentXOffset_0x0 + x + 10;
                        int const iconY = y - 12;
                        // the picture in each arm (called once before the test, the match is lost)
                        if (DAT_GameSynchronyState::instance.currentPlayerFullIDArray
                                [DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk]
                            != -1) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk + 718, iconX,
                                iconY);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                                DAT_TextureRenderCoreObject::ptr)(
                                DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk + 19,
                                iconX + 2, iconY + 2);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox,
                                DAT_PencilRenderCore::ptr)(
                                iconX, iconY, iconX + 35, iconY + 35, COL_BLACK::instance.shortValue);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk + 718, iconX,
                                iconY);
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                                DAT_GameSynchronyState::instance.currentAIArray
                                        [DAT_GameState::instance.playerDataArray[button].requestedAttackTargetUnk]
                                    + 700,
                                iconX, iconY);
                        }
                    }
                }
                // "Help Needed!"
                y += 32;
                if (DAT_GameState::instance.playerDataArray[button].isNotNervousByEnemyTroopValue) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_ALLIES, 4, x, y, OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                }
                // this ally's request that you attack: "Attack" and the target's picture
                int const own = DAT_GameSynchronyState::instance.currentPlayerSlotID;
                if (DAT_GameState::instance.playerDataArray[own].requestStateUnk != 1) {
                    return;
                }
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameState::instance.playerDataArray[own].playerID_askerUnk]
                    == -1) {
                    return;
                }
                if (DAT_GameState::instance.playerDataArray[own].playerID_askerUnk != button) {
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderText2, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_ALLIES, 10, x, y, OpenSHC::Text::TTA_LEFT,
                    OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE);
                // new variables (changing x and y loses the match)
                int const iconX = DAT_TextManagerObject::instance.currentXOffset_0x0 + x + 10;
                int const iconY = y - 5;
                // the picture in each arm, as above
                if (DAT_GameSynchronyState::instance
                        .currentPlayerFullIDArray[DAT_GameState::instance.playerDataArray[own].requestedAttackTargetUnk]
                    != -1) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                        DAT_GameState::instance.playerDataArray[own].requestedAttackTargetUnk + 718, iconX, iconY);
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderFacesSmallUnk,
                        DAT_TextureRenderCoreObject::ptr)(
                        DAT_GameState::instance.playerDataArray[own].requestedAttackTargetUnk + 19, iconX + 2,
                        iconY + 2);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                        iconX, iconY, iconX + 35, iconY + 35, COL_BLACK::instance.shortValue);
                    return;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    DAT_GameState::instance.playerDataArray[own].requestedAttackTargetUnk + 718, iconX, iconY);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2,
                    DAT_GameSynchronyState::instance
                            .currentAIArray[DAT_GameState::instance.playerDataArray[own].requestedAttackTargetUnk]
                        + 700,
                    iconX, iconY);
                return;
            }
            // above 19, and -1: a plain button (moved before the portraits, the match is lost)
            MACRO_CALL(
                OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
            if (!DAT_ButtonCurrentlyInteracting::instance) {
                return;
            }
            if (button == 20) {
                DAT_00df51f4::instance = 1;
                // "Set Orders"
                DAT_00df51f0::instance = 5;
            } else if (button == 21) {
                DAT_00df51f4::instance = 1;
                // "Send Goods"
                DAT_00df51f0::instance = 6;
            } else if (button == 22) {
                DAT_00df51f4::instance = 1;
                // "Request Goods"
                DAT_00df51f0::instance = 7;
            }
        }

    }
}
}
