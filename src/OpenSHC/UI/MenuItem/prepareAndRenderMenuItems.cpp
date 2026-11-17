#include "../MenuItem.func.hpp"

#include "OpenSHC/UI/Enums/MenuItemRenderFunctionType.hpp"
#include "OpenSHC/UI/Enums/MenuItemType.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonH.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonW.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {

    // FUNCTION: STRONGHOLDCRUSADER 0x004F49D0
    void MenuItem::prepareAndRenderMenuItems()
    {
        if (this->iconDeactivatedUnk_0x36 != 0) {
            return;
        }
        if (this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_GM_DATA_IMAGE) {
            int const image = GMFirstPictureIndex::instance[DAT_UIButtonDefinedData::instance
                                      .ButtonGmDataArray[this->firstItemTypeData.gmDataIndex]
                                      .gmId_0x0]
                + DAT_UIButtonDefinedData::instance.ButtonGmDataArray[this->firstItemTypeData.gmDataIndex]
                      .pictureInGm_0x4
                - 1;
            this->itemWidth = DAT_GMImageHeaders::instance.imh[image].width;
            this->itemHeight = DAT_GMImageHeaders::instance.imh[image].height;
        }
        DAT_ButtonX::instance = this->menuPointer->xPosition - this->menuPointer->currentBuildMenuButtonShiftUnk_0x14
            + this->position.position.x;
        DAT_ButtonY::instance = this->menuPointer->yPosition + this->position.position.y;
        DAT_ButtonW::instance = this->itemWidth;
        DAT_ButtonH::instance = this->itemHeight;
        // the low 23 bits are the index (the same mask as MIT_MENU_ITEM_TYPE_ID_PARTUnk)
        int const gmDataIndexMask = 0x7fffff;
        DAT_CurrentButtonGmDataIndex::instance = this->firstItemTypeData.gmDataIndex & gmDataIndexMask;
        DAT_ButtonCurrentlyInteracting::instance = this->clicked | this->hovering;
        DAT_ButtonBlendStrength::instance = 0;
        DAT_ButtonUnknownZero::instance = this->unknownZero;
        if (DAT_GameCore::instance.hasMenuRenderedUnk) {
            DAT_ButtonCurrentlyInteracting::instance = FALSE;
        }
        int const shift = this->menuPointer->currentBuildMenuButtonShiftUnk_0x14;
        if (shift != 0) {
            // while the build menu slides, items outside its area aren't drawn, and none are around the halfway point
            if (this->position.position.x - shift < (int)DAT_MenuHandlerState::instance.const017) {
                return;
            }
            if (this->position.position.x - shift + this->itemWidth > (int)DAT_MenuHandlerState::instance.const516) {
                return;
            }
            int const progress = DAT_MenuHandlerState::instance.buildMenuTransitionProgress_0x38;
            if (progress > 45 && progress < 55) {
                return;
            }
            if (progress < 50) {
                DAT_ButtonBlendStrength::instance = progress * 32 / 45;
            } else {
                DAT_ButtonBlendStrength::instance = (100 - progress) * 32 / 45;
            }
        }
        if (this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_SLIDER_OR_SCROLLBAR) {
            if (this->menuPointer->one) {
                // 1: set-up: range and position
                (*this->menuItemActionHandler.slider)(this->callbackParameter.parameter, 1,
                    &this->secondItemTypeData.scrollbarOrSliderState.minValue,
                    &this->secondItemTypeData.scrollbarOrSliderState.maxValue,
                    &this->secondItemTypeData.scrollbarOrSliderState.currentValue);
                this->secondItemTypeData.scrollbarOrSliderState.dragTiming = -1000;
                if (this->secondItemTypeData.scrollbarOrSliderState.currentValue
                    < this->secondItemTypeData.scrollbarOrSliderState.minValue) {
                    this->secondItemTypeData.scrollbarOrSliderState.currentValue
                        = this->secondItemTypeData.scrollbarOrSliderState.minValue;
                }
                if (this->secondItemTypeData.scrollbarOrSliderState.currentValue
                    > this->secondItemTypeData.scrollbarOrSliderState.maxValue) {
                    this->secondItemTypeData.scrollbarOrSliderState.currentValue
                        = this->secondItemTypeData.scrollbarOrSliderState.maxValue;
                }
            }
            // declared here, before thumbPos and thumbLength: at its first use it loses the match
            BOOLEnum isDragged = FALSE;
            int thumbPos = 0;
            int length = this->itemWidth;
            if ((this->menuItemType & OpenSHC::UI::Enums::MIT_MENU_ITEM_TYPE_ID_PARTUnk)
                == OpenSHC::UI::Enums::MIT_SCROLLBARUnk) {
                length = this->itemHeight;
            }
            int thumbLength = length;
            // the range is written out at each use: a local loses the match
            if ((this->secondItemTypeData.scrollbarOrSliderState.maxValue
                    - this->secondItemTypeData.scrollbarOrSliderState.minValue)
                > 0) {
                thumbLength = length
                    / ((this->secondItemTypeData.scrollbarOrSliderState.maxValue
                           - this->secondItemTypeData.scrollbarOrSliderState.minValue)
                        + 1);
                if (thumbLength <= this->firstItemTypeData.itemsToSkip) {
                    thumbLength = this->firstItemTypeData.itemsToSkip;
                }
                thumbPos = (this->secondItemTypeData.scrollbarOrSliderState.currentValue
                               - this->secondItemTypeData.scrollbarOrSliderState.minValue)
                    * (length - thumbLength)
                    / (this->secondItemTypeData.scrollbarOrSliderState.maxValue
                        - this->secondItemTypeData.scrollbarOrSliderState.minValue);
            }
            if (this->secondItemTypeData.scrollbarOrSliderState.dragTiming > -1000) {
                isDragged = TRUE;
            }
            (*this->menuItemRenderFunction.slider)(this->callbackParameter.parameter, thumbPos,
                this->secondItemTypeData.scrollbarOrSliderState.currentValue, thumbLength, isDragged);
        } else if (this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_SIMPLE_RENDERUnk) {
            (*this->menuItemRenderFunction.simple)(this->callbackParameter.parameter);
        } else if (this->menuItemRenderFunctionType == OpenSHC::UI::Enums::MIRFT_GM_DATA_IMAGE) {
            (*this->menuItemRenderFunction.gmDataImage)(this->callbackParameter.parameter);
            this->secondItemTypeData.buttonState.currentButtonPictureInGm_0xc = DAT_CurrentButtonPictureInGm::instance;
        }
        if (this->menuPointer->hoveredItem == this
            && DAT_ButtonCurrentlyInteracting::instance != (this->clicked | this->hovering)) {
            this->menuPointer->zero = 0;
        }
        this->unknownZero = DAT_ButtonUnknownZero::instance;
    }

}
}
