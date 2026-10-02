#include "../MenuItem.func.hpp"

#include "OpenSHC/Audio/SFX/SFXState.func.hpp"
#include "OpenSHC/Input/MouseState.func.hpp"
#include "OpenSHC/UI/Rendering/AlphaAndButtonSurface.func.hpp"
#include "OpenSHC/Audio/SFX/SoundEffectID.hpp"
#include "OpenSHC/Rendering/Enums/GmDataIndex.hpp"
#include "OpenSHC/UI/Enums/MenuItemRenderFunctionType.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/AlphaAndButtonSurfaceObj.hpp"
#include "OpenSHC/Globals/BOOL_CurrentMenuClickState.hpp"
#include "OpenSHC/Globals/DAT_00ed31d0.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MenuModalComposition1.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_SFXState.hpp"
#include "OpenSHC/Globals/DAT_ScrollingHandler.hpp"
#include "OpenSHC/Globals/DAT_StopHandlingMenuItems.hpp"
#include "OpenSHC/Globals/DAT_UIDragDropDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Audio::SFX::SoundEffectID;
    using OpenSHC::Rendering::Enums::GmDataIndex;
    using OpenSHC::UI::Enums::MenuItemRenderFunctionType;
    using OpenSHC::UI::Enums::MenuItemType;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    // FUNCTION: STRONGHOLDCRUSADER 0x004F4290
    int MenuItem::handleMenuElementsCallbacks()
    {
        int* piVar1;
        int* piVar2;
        MenuItemSecondItemTypeData* pMVar3;
        Menu* pMVar4;
        DWORD DVar5;
        BOOLEnum BVar6;
        int iVar7;
        int iVar8;
        int yPos;
        int xPos;
        int iVar9;
        MenuItemTypeInt MVar10;
        int heigth;
        int iStack_1c;
        int iStack_18;
        int iStack_14;
        int iStack_10;
        int iStack_c;
        MenuItemTypeInt local_8;
        int iStack_4;
        MVar10 = this->menuItemType & OpenSHC::UI::Enums::MIT_MENU_ITEM_TYPE_ID_PARTUnk;
        if ((this->iconDeactivatedUnk_0x36 == 0) && (this->unknownZero == 0)) {
            this->hovering = 0;
            local_8 = MVar10;
            if (MVar10 != ((MenuItemType)0)) {
                if ((MVar10 == ((MenuItemType)1)) && (DAT_ScrollingHandler::instance.isScrolling_0x0 != FALSE)) {
                    (*(this->menuItemActionHandler).simple)((this->callbackParameter).parameter);
                    return 0;
                }
                if ((this->clicked != 0)
                    && (DVar5 = timeGetTime(),
                        this->menuPointer->thousand
                            < (int)(DVar5 - (this->secondItemTypeData).buttonState.clickTimestamp_0x4))) {
                    this->clicked = 0;
                }
                if ((MVar10 == OpenSHC::UI::Enums::MIT_SLIDERUnk) || (MVar10 == OpenSHC::UI::Enums::MIT_SCROLLBARUnk)) {
                    if (this->menuPointer->one == 0) {
                        iVar8 = (this->secondItemTypeData).buttonState.someTimestamp_1_0x0;
                        pMVar3 = &this->secondItemTypeData;
                        piVar1 = &(this->secondItemTypeData).buttonState.countTo100;
                        if ((this->secondItemTypeData).buttonState.countTo100 < iVar8) {
                            *piVar1 = iVar8;
                        }
                        iVar8 = (this->secondItemTypeData).buttonState.clickTimestamp_0x4;
                        piVar2 = &(this->secondItemTypeData).buttonState.clickTimestamp_0x4;
                        if (iVar8 < *piVar1) {
                            *piVar1 = iVar8;
                        }
                        (*(this->menuItemActionHandler).slider)(
                            (this->callbackParameter).parameter, 4, (int*)pMVar3, piVar2, piVar1);
                        if (DAT_MouseState::instance.scrollEventData == 7) {
                            (*(this->menuItemActionHandler).slider)(
                                (this->callbackParameter).parameter, 6, (int*)pMVar3, piVar2, piVar1);
                        } else if (DAT_MouseState::instance.scrollEventData == 8) {
                            (*(this->menuItemActionHandler).slider)(
                                (this->callbackParameter).parameter, 5, (int*)pMVar3, piVar2, piVar1);
                        }
                        iStack_c = (pMVar3->buttonState).someTimestamp_1_0x0;
                        if (*piVar2 < iStack_c) {
                            *piVar2 = iStack_c;
                        }
                        if (*piVar1 < iStack_c) {
                            *piVar1 = iStack_c;
                        }
                        iVar8 = *piVar2;
                        if (iVar8 < *piVar1) {
                            *piVar1 = iVar8;
                        }
                        if ((DAT_MouseState::instance.leftClickStart == 0)
                            && (DAT_MouseState::instance.leftClickState == FALSE)) {
                            (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc = -1000;
                            return 0;
                        }
                        iVar9 = this->itemWidth;
                        iStack_1c = 0;
                        iStack_10 = 0;
                        iStack_14 = DAT_MouseState::instance.screenSpaceX;
                        iStack_4 = this->menuPointer->xPosition + (this->position).position.x;
                        iStack_18 = iStack_4;
                        if (local_8 == OpenSHC::UI::Enums::MIT_SCROLLBARUnk) {
                            iStack_18 = this->menuPointer->yPosition + (this->position).position.y;
                            iVar9 = this->itemHeight;
                            iStack_14 = DAT_MouseState::instance.screenSpaceY;
                        }
                        iVar8 = iVar8 - iStack_c;
                        iVar7 = iVar9;
                        if (0 < iVar8) {
                            iVar7 = iVar9 / (iVar8 + 1);
                            if (iVar7 <= (this->firstItemTypeData).itemsToSkip) {
                                iVar7 = (this->firstItemTypeData).itemsToSkip;
                            }
                            iStack_1c = ((*piVar1 - iStack_c) * (iVar9 - iVar7)) / iVar8;
                        }
                        BVar6 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox,
                            DAT_MouseState::ptr)(iStack_4, this->menuPointer->yPosition + (this->position).position.y,
                            this->itemWidth, this->itemHeight);
                        if (BVar6 != FALSE) {
                            this->hovering = 1;
                        }
                        pMVar4 = this->menuPointer;
                        if (local_8 == OpenSHC::UI::Enums::MIT_SLIDERUnk) {
                            yPos = pMVar4->yPosition + (this->position).position.y;
                            xPos = pMVar4->xPosition + (this->position).position.x + iStack_1c;
                            iVar8 = iVar7;
                            heigth = this->itemHeight;
                        } else {
                            iVar8 = this->itemWidth;
                            yPos = pMVar4->yPosition + (this->position).position.y + iStack_1c;
                            xPos = pMVar4->xPosition + (this->position).position.x;
                            heigth = iVar7;
                        }
                        BVar6 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox,
                            DAT_MouseState::ptr)(xPos, yPos, iVar8, heigth);
                        if (BVar6 != FALSE) {
                            iStack_10 = 1;
                        }
                        if (DAT_MouseState::instance.leftClickStart == 0) {
                            if ((DAT_MouseState::instance.leftClickState != FALSE)
                                && (-1000 < (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc)) {
                                iVar8 = (pMVar3->buttonState).someTimestamp_1_0x0;
                                iStack_4 = *piVar2 - iVar8;
                                if (0 < iStack_4) {
                                    *piVar1
                                        = ((((((iVar9 - iVar7) / iStack_4) / 2
                                                 - (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc)
                                                - iStack_18)
                                               + iStack_14)
                                              * iStack_4)
                                            / (iVar9 - iVar7)
                                        + iVar8;
                                    if (*piVar2 < iVar8) {
                                        *piVar2 = iVar8;
                                    }
                                    if (*piVar1 < iVar8) {
                                        *piVar1 = iVar8;
                                    }
                                    if (*piVar2 < *piVar1) {
                                        *piVar1 = *piVar2;
                                    }
                                    (*(this->menuItemActionHandler).slider)(
                                        (this->callbackParameter).parameter, 3, (int*)pMVar3, piVar2, piVar1);
                                    iVar8 = (pMVar3->buttonState).someTimestamp_1_0x0;
                                    if (*piVar2 < iVar8) {
                                        *piVar2 = iVar8;
                                    }
                                    if (*piVar1 < iVar8) {
                                        *piVar1 = iVar8;
                                    }
                                    if (*piVar2 < *piVar1) {
                                        *piVar1 = *piVar2;
                                    }
                                }
                            }
                        } else if (this->hovering != 0) {
                            if (iStack_10 == 0) {
                                if (iStack_14 < iStack_18 + iStack_1c) {
                                    iStack_10 = ((*piVar2 - (pMVar3->buttonState).someTimestamp_1_0x0) * iVar7)
                                        / (iVar9 - iVar7);
                                    if (iStack_10 == 0) {
                                        iStack_10 = 1;
                                    }
                                    (*(this->menuItemActionHandler).slider)(
                                        (this->callbackParameter).parameter, 7, (int*)pMVar3, piVar2, &iStack_10);
                                    *piVar1 = *piVar1 - iStack_10;
                                    if (*piVar1 < (pMVar3->buttonState).someTimestamp_1_0x0) {
                                        *piVar1 = (pMVar3->buttonState).someTimestamp_1_0x0;
                                    }
                                    (*(this->menuItemActionHandler).slider)(
                                        (this->callbackParameter).parameter, 2, (int*)pMVar3, piVar2, piVar1);
                                } else {
                                    iStack_10 = ((*piVar2 - (pMVar3->buttonState).someTimestamp_1_0x0) * iVar7)
                                        / (iVar9 - iVar7);
                                    if (iStack_10 == 0) {
                                        iStack_10 = 1;
                                    }
                                    (*(this->menuItemActionHandler).slider)(
                                        (this->callbackParameter).parameter, 7, (int*)pMVar3, piVar2, &iStack_10);
                                    *piVar1 = *piVar1 + iStack_10;
                                    if (*piVar2 < *piVar1) {
                                        *piVar1 = *piVar2;
                                    }
                                    (*(this->menuItemActionHandler).slider)(
                                        (this->callbackParameter).parameter, 2, (int*)pMVar3, piVar2, piVar1);
                                }
                            } else {
                                (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc
                                    = (iStack_14 - iStack_18) - iStack_1c;
                                if (*piVar1 < (pMVar3->buttonState).someTimestamp_1_0x0) {
                                    *piVar1 = (pMVar3->buttonState).someTimestamp_1_0x0;
                                }
                                if (*piVar2 < *piVar1) {
                                    *piVar1 = *piVar2;
                                }
                                (*(this->menuItemActionHandler).slider)(
                                    (this->callbackParameter).parameter, 3, (int*)pMVar3, piVar2, piVar1);
                            }
                            iVar8 = (pMVar3->buttonState).someTimestamp_1_0x0;
                            if (*piVar2 < iVar8) {
                                *piVar2 = iVar8;
                            }
                            if (*piVar1 < iVar8) {
                                *piVar1 = iVar8;
                            }
                            if (*piVar2 < *piVar1) {
                                *piVar1 = *piVar2;
                                return 0;
                            }
                        }
                    } else {
                        piVar1 = &(this->secondItemTypeData).buttonState.countTo100;
                        piVar2 = &(this->secondItemTypeData).buttonState.clickTimestamp_0x4;
                        (*(this->menuItemActionHandler).slider)(
                            (this->callbackParameter).parameter, 1, (int*)&this->secondItemTypeData, piVar2, piVar1);
                        iVar8 = (this->secondItemTypeData).buttonState.someTimestamp_1_0x0;
                        (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc = -1000;
                        if (*piVar2 < iVar8) {
                            *piVar2 = iVar8;
                        }
                        if (*piVar1 < iVar8) {
                            *piVar1 = iVar8;
                        }
                        if (*piVar2 < *piVar1) {
                            *piVar1 = *piVar2;
                            return 0;
                        }
                    }
                } else {
                    DAT_StopHandlingMenuItems::instance = 1;
                    BVar6 = MACRO_CALL_MEMBER(OpenSHC::Input::MouseState_Func::isMouseInsideBox, DAT_MouseState::ptr)(
                        this->menuPointer->xPosition + (this->position).position.x,
                        this->menuPointer->yPosition + (this->position).position.y, this->itemWidth, this->itemHeight);
                    if (BVar6 != FALSE) {
                        DAT_MenuHandlerState::instance.field18_0x3c = 1;
                        DAT_ButtonX::instance = this->menuPointer->xPosition + (this->position).position.x;
                        DAT_ButtonY::instance = this->menuPointer->yPosition + (this->position).position.y;
                        BOOL_CurrentMenuClickState::instance = (BOOLEnum)this->clicked;
                        if ((this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_GM_DATA_IMAGE)
                            && (((this->firstItemTypeData).gmDataIndex
                                    & OpenSHC::Rendering::Enums::GDI_USE_PIXEL_MOUSE_HIT_CHECKUnk)
                                != OpenSHC::Rendering::Enums::GDI_NONE_0)) {
                            DAT_CurrentButtonGmDataIndex::instance = (this->firstItemTypeData).gmDataIndex & 0x7fffff;
                            DAT_ButtonCurrentlyInteracting::instance
                                = (BOOLEnum)(short)(this->hovering | this->clicked);
                            DAT_CurrentButtonPictureInGm::instance
                                = (this->secondItemTypeData).buttonState.currentButtonPictureInGm_0xc;
                            BVar6 = MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::AlphaAndButtonSurface_Func::isMouseOnButtonImageUnk,
                                AlphaAndButtonSurfaceObj::ptr)();
                            if (BVar6 == FALSE) {
                                return 0;
                            }
                        }
                        if (((*(int*)&this->textMessageLookupIndex) != -1)
                            && (DAT_MenuModalComposition1::instance.mbr_0x78 == 0)) {
                            this->menuPointer->hoveredItem = this;
                        }
                        pMVar4 = this->menuPointer;
                        if ((pMVar4->someMenuItemPtr_0x3c != this) && (pMVar4->field16_0x40 == 0)) {
                            iVar8 = (int)(this->textMessageLookupIndex).field1_0x2;
                            if (iVar8 == 1) {
                                pMVar4->someMenuItemPtr_0x3c = this;
                                MACRO_CALL_MEMBER(OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk,
                                    DAT_SFXState::ptr)(((SoundEffectID)0x88));
                                this->menuPointer->field16_0x40 = 1;
                            } else if (iVar8 - 2U < 6) {
                                pMVar4->someMenuItemPtr_0x3c = this;
                                MACRO_CALL_MEMBER(
                                    OpenSHC::Audio::SFX::SFXState_Func::setUpSFXToPlayUnk, DAT_SFXState::ptr)(
                                    (OpenSHC::Audio::SFX::SoundEffectID)(this->textMessageLookupIndex.field1_0x2
                                        + (OpenSHC::Audio::SFX::SEID_SIEGE_EQUIPMENT_DESTROYED
                                            | OpenSHC::Audio::SFX::SEID_QUARRY_STONE_LIFT_01)));
                                this->menuPointer->field16_0x40 = 1;
                            }
                        }
                        this->hovering = 1;
                        if (MVar10 == OpenSHC::UI::Enums::MIT_TEXT_OR_STATE_OR_PLAYER_DEPENDENTUnk) {
                            if (DAT_MouseState::instance.rightClickStart != 0) {
                            LAB_004f444b:
                                DVar5 = timeGetTime();
                                (this->secondItemTypeData).buttonState.clickTimestamp_0x4 = DVar5;
                                (this->secondItemTypeData).buttonState.someTimestamp_1_0x0 = DVar5;
                                this->clicked = 1;
                                BOOL_CurrentMenuClickState::instance = TRUE;
                                (*(this->menuItemActionHandler).simple)((this->callbackParameter).parameter);
                                (this->secondItemTypeData).buttonState.countTo100 = 0;
                                this->clicked = (undefined2)BOOL_CurrentMenuClickState::instance;
                                return (int)(DAT_StopHandlingMenuItems::instance);
                            }
                        } else {
                            if (DAT_MouseState::instance.leftClickStart != 0)
                                goto LAB_004f444b;
                            if ((DAT_MouseState::instance.leftClickState == FALSE) || (MVar10 != ((MenuItemType)2))) {
                                if ((DAT_MouseState::instance.draggingStopped != FALSE)
                                    && (MVar10 == ((MenuItemType)10))) {
                                    DVar5 = timeGetTime();
                                    (this->secondItemTypeData).buttonState.clickTimestamp_0x4 = DVar5;
                                    (this->secondItemTypeData).buttonState.someTimestamp_1_0x0 = DVar5;
                                    this->clicked = 1;
                                    BOOL_CurrentMenuClickState::instance = TRUE;
                                    (*(this->menuItemActionHandler).simple)((this->callbackParameter).parameter);
                                    (this->secondItemTypeData).buttonState.countTo100 = 0;
                                    this->clicked = (undefined2)BOOL_CurrentMenuClickState::instance;
                                    DAT_StopHandlingMenuItems::instance = 0;
                                    return 0;
                                }
                                if (this->menuItemRenderFunctionType == ((MenuItemRenderFunctionType)2)) {
                                    if (DAT_MouseState::instance.scrollEventData == 7) {
                                        iVar8 = 2;
                                    } else {
                                        if (DAT_MouseState::instance.scrollEventData != 8) {
                                            return 0;
                                        }
                                        iVar8 = 1;
                                    }
                                    DVar5 = timeGetTime();
                                    (this->secondItemTypeData).buttonState.clickTimestamp_0x4 = DVar5;
                                    (this->secondItemTypeData).buttonState.someTimestamp_1_0x0 = DVar5;
                                    this->clicked = 1;
                                    BOOL_CurrentMenuClickState::instance = TRUE;
                                    if (DAT_MouseState::instance.midClickState == FALSE) {
                                        iVar9 = 10;
                                        do {
                                            (*(this->menuItemActionHandler).simple)(iVar8);
                                            iVar9 = iVar9 + -1;
                                        } while (iVar9 != 0);
                                    } else {
                                        iVar9 = 100;
                                        do {
                                            (*(this->menuItemActionHandler).simple)(iVar8);
                                            iVar9 = iVar9 + -1;
                                        } while (iVar9 != 0);
                                    }
                                    (this->secondItemTypeData).buttonState.countTo100 = 0;
                                    this->clicked = (undefined2)BOOL_CurrentMenuClickState::instance;
                                    return (int)(DAT_StopHandlingMenuItems::instance);
                                }
                            } else {
                                DVar5 = timeGetTime();
                                (this->secondItemTypeData).buttonState.clickTimestamp_0x4 = DVar5;
                                iVar8 = (this->secondItemTypeData).buttonState.someTimestamp_1_0x0;
                                this->clicked = 1;
                                BOOL_CurrentMenuClickState::instance = TRUE;
                                if (0x27 < (int)(DVar5 - iVar8)) {
                                    piVar1 = &(this->secondItemTypeData).buttonState.countTo100;
                                    *piVar1 = *piVar1 + 1;
                                    (this->secondItemTypeData).buttonState.someTimestamp_1_0x0
                                        = (this->secondItemTypeData).buttonState.clickTimestamp_0x4;
                                    if (99 < (this->secondItemTypeData).buttonState.countTo100) {
                                        (this->secondItemTypeData).buttonState.countTo100 = 99;
                                    }
                                    DAT_00ed31d0::instance = (this->secondItemTypeData).buttonState.countTo100;
                                    if (DAT_UIDragDropDefinedData::instance
                                            .UI_DragTicks[(this->secondItemTypeData).buttonState.countTo100]
                                        != 0) {
                                        (*(this->menuItemActionHandler).simple)((this->callbackParameter).parameter);
                                        this->clicked = (undefined2)BOOL_CurrentMenuClickState::instance;
                                        (this->secondItemTypeData).buttonState.countTo100 = DAT_00ed31d0::instance;
                                        return (int)(DAT_StopHandlingMenuItems::instance);
                                    }
                                }
                            }
                        }
                    }
                }
                return 0;
            }
            (*(this->menuItemActionHandler).simple)((this->callbackParameter).parameter);
        }
        return 0;
    }

}
}
