#include "../AlliesSendAndRequestGoods.func.hpp"

#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Game/Resources/ResourceType.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RequestedGoodsByWhoArray.hpp"
#include "OpenSHC/Globals/DAT_SentOrRequestedGoodsAmount.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuItems {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004AD920
        void AlliesSendAndRequestGoods::MenuItemRenderFunction_AlliesSendAndRequestGoods_Main(int actionParam, ...)
        {
            int iVar1;
            int iVar2;
            int iVar3;
            int iVar4;
            eTextSections offsetIndex;
            BOOLEnum keepOffsetX;
            // first render resource type in condensed form
            if (actionParam < 20) {
                int _xOffset = 0;
                if (actionParam == 6 || actionParam == 11 || actionParam == 20) {
                    _xOffset = 8;
                }
                // skip unusable resources
                if (4 <= actionParam) {
                    ++actionParam;
                }
                if (6 <= actionParam) {
                    ++actionParam;
                }
                if (actionParam == 14) {
                    actionParam = 23;
                }
                int _gmID = actionParam * 2 + 617;
                if (DAT_ButtonCurrentlyInteracting::instance) {
                    _gmID = actionParam * 2 + 618;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, _gmID,
                    DAT_ButtonX::instance + _xOffset, (int)(DAT_ButtonY::instance));
                if (actionParam == 7) {
                    actionParam = 6;
                }
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[actionParam + 1],
                    (int)(DAT_ButtonX::instance + 21), (int)(DAT_ButtonY::instance + 40), OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 19, FALSE, 0);
            } else if (actionParam == 21) {
                if (!DAT_ButtonCurrentlyInteracting::instance) {
                    iVar1 = 645;
                } else {
                    iVar1 = 646;
                }
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1,
                    (int)(DAT_ButtonX::instance), (int)(DAT_ButtonY::instance));
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                    DAT_GameState::instance.playerDataArray[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        .currentResources[OpenSHC::Game::Resources::RT_GOLD],
                    (int)(DAT_ButtonX::instance + 21), (int)(DAT_ButtonY::instance + 20), OpenSHC::Text::TTA_CENTER,
                    OpenSHC::Rendering::Colors::COL_C2F0EB, 0, 19, FALSE, 0);
                return;
            }
            iVar1 = DAT_ButtonX::instance;
            int iVar5 = DAT_ButtonY::instance;
            // then draw the rest
            if (actionParam == 40) {
                // everything below belongs to actionParam == 40 only
                if (0 < (int)DAT_ButtonH::instance) {
                    for (int iVar2 = 0; iVar2 < (int)DAT_ButtonH::instance; iVar2 = iVar2 + 24) {
                        if (iVar2 == 0) {
                            iVar3 = 1;
                        } else {
                            if (iVar2 == DAT_ButtonH::instance - 24) {
                                iVar3 = 13;
                            } else {
                                iVar3 = 7;
                            }
                        }
                        iVar4 = 0;
                        do {
                            int imageID = iVar3;
                            if (iVar4 == 0) {
                            LAB_004adacf:
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID, iVar4 + iVar1, iVar2 + iVar5, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                                    imageID + 3, 0);
                            } else {
                                if (iVar4 == 528) {
                                    imageID = iVar3 + 2;
                                    goto LAB_004adacf;
                                }
                                if (iVar3 != 7) {
                                    imageID = iVar3 + 1;
                                    goto LAB_004adacf;
                                }
                                return;
                            }
                            iVar4 += 24;
                        } while (iVar4 < 552);
                    }
                }
                MACRO_CALL_MEMBER(
                    OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox, DAT_PencilRenderCore::ptr)(
                    iVar1 + 24, iVar5 + 24, iVar1 + 527, DAT_ButtonH::instance - 25 + iVar5, 20);
                if (DAT_RequestedGoodsByWhoArray::instance[0] == 6) {
                    iVar1 = 7;
                LAB_004adb48:
                    if (DAT_SentOrRequestedGoodsAmount::instance != 0) {
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(
                            DAT_SentOrRequestedGoodsAmount::instance, (int)(DAT_ButtonX::instance + 36),
                            (int)(DAT_ButtonY::instance + 36), OpenSHC::Text::TTA_LEFT,
                            OpenSHC::Rendering::Colors::COL_CCFAFF, 0, 17, FALSE, 0);
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 * 2 + 618,
                            (int)(DAT_TextManagerObject::instance.currentXOffset_0x0 + 46 + DAT_ButtonX::instance),
                            (int)(DAT_ButtonY::instance + 24));
                        keepOffsetX = TRUE;
                        iVar1 = DAT_ButtonX::instance + 96;
                        iVar5 = DAT_RequestedGoodsByWhoArray::instance[0] + 1;
                        offsetIndex = OpenSHC::DE::SHCDE::TEXT_GOODS;
                        goto LAB_004adbc8;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, iVar1 * 2 + 618,
                        (int)(DAT_ButtonX::instance + 36), (int)(DAT_ButtonY::instance + 24));
                    iVar1 = DAT_ButtonX::instance + 84;
                    iVar5 = 14;
                } else {
                    iVar1 = DAT_RequestedGoodsByWhoArray::instance[0];
                    if (0 < DAT_RequestedGoodsByWhoArray::instance[0])
                        goto LAB_004adb48;
                    iVar1 = DAT_ButtonX::instance + 36;
                    iVar5 = 13;
                }
                keepOffsetX = FALSE;
                offsetIndex = OpenSHC::DE::SHCDE::TEXT_ALLIES;
            LAB_004adbc8:
                iVar2 = DAT_ButtonY::instance + 36;
                iVar4 = 0;
                iVar3 = 17;
                // added by script: "Choose Goods"
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(offsetIndex, iVar5),
                    iVar1, iVar2, OpenSHC::Text::TTA_LEFT, OpenSHC::Rendering::Colors::COL_CCFAFF, iVar3, keepOffsetX,
                    iVar4);
                return;
            }
            if (100 <= actionParam) {
                MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderButtonImageWithBlending)();
                return;
            }
            // the original ends this bound with `jl`, so 0x32 is inside it; written as
            // `50 <` the `actionParam == 0x32` test below could never be true
            if (50 <= actionParam) {
                MACRO_CALL(
                    OpenSHC::UI::Rendering_Func::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk)();
                if (actionParam == 50) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(10,
                        (int)(DAT_ButtonX::instance + 18), (int)(DAT_ButtonY::instance + 16), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                    return;
                }
                if (actionParam == 51) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(25,
                        (int)(DAT_ButtonX::instance + 15), (int)(DAT_ButtonY::instance + 16), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                    return;
                }
                if (actionParam == 52) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(100,
                        (int)(DAT_ButtonX::instance + 12), (int)(DAT_ButtonY::instance + 16), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                    return;
                }
                if (actionParam == 53) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(5,
                        (int)(DAT_ButtonX::instance + 21), (int)(DAT_ButtonY::instance + 16), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                    return;
                }
                if (actionParam == 54) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumber2, DAT_TextManagerObject::ptr)(500,
                        (int)(DAT_ButtonX::instance + 11), (int)(DAT_ButtonY::instance + 16), OpenSHC::Text::TTA_LEFT,
                        OpenSHC::Rendering::Colors::COL_B8EEFB, 0, 17, FALSE, 0);
                    return;
                }
            }
        }

    }
}
}
