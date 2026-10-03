#include "../DisplayElements.func.hpp"

#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/UI/Enums/BuildingsAndStatusMenuTabType.hpp"
#include "OpenSHC/UI/Enums/DisplayElementPositionModifier.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"

#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_PointerToDisplayElementStackTop.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_ViewportRenderState.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::UI::Enums::BuildingsAndStatusMenuTabType;
    using OpenSHC::UI::Enums::DisplayElementPositionModifier;
    using OpenSHC::UI::Enums::MenuViewType;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004AF700
    void DisplayElements::RenderDisplayElementsUnk()
    {
        DWORD _currentTime;
        DisplayElementPositionModifierInt _positionModifier;
        int _yPos;
        int _xPos;
        DisplayElementPositionModifierInt _xPosModifier;
        DisplayElement* _displayElementPtr;
        _currentTime = timeGetTime();
        for (_displayElementPtr = DAT_PointerToDisplayElementStackTop::instance;
            _displayElementPtr != (DisplayElement*)0x0;
            _displayElementPtr = _displayElementPtr->nextDisplayElement_0x20) {
            if (_displayElementPtr->elementStateUnk_0xc != 0) {
                _xPos
                    = _displayElementPtr->x_0x0 + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetX;
                _yPos
                    = _displayElementPtr->y_0x4 + DAT_ViewportRenderState::instance.viewportState.currentCameraOffsetY;
                _positionModifier = _displayElementPtr->positionModifier_0x1c
                    & (OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y | OpenSHC::UI::Enums::DEPM_RESOLUTION_Y);
                switch (_positionModifier) {
                case OpenSHC::UI::Enums::DEPM_RESOLUTION_Y:
                    break;
                case OpenSHC::UI::Enums::DEPM_TOWARDS_MID_Y: {
                    _yPos = _yPos + -600 + DAT_WindowAndDirectDraw::instance.resolutionY;
                    if (((DAT_GameCore::instance.currentMenuViewType == OpenSHC::UI::Enums::MVT_BUILD_MENU)
                            || (DAT_GameCore::instance.currentMenuViewType
                                == OpenSHC::UI::Enums::MVT_MAP_EDITOR_LANDSCAPING))
                        && ((DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SIEGETOWER
                            || (DAT_GameCore::instance.activeMenuTab.tabType
                                == OpenSHC::UI::Enums::BASMTT_SIEGETENT_SHIELD)))) {
                        _yPos = _yPos + 0x80;
                    }
                    if (DAT_GameCore::instance.currentMenuViewType
                        == OpenSHC::UI::Enums::MVT_BUILDING_AND_STATUS_MENU) {
                        _yPos = _yPos + -0x14;
                    }
                    break;
                }
                default:
                    _yPos = _yPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight;
                }
                _xPosModifier = _displayElementPtr->positionModifier_0x1c
                    & (OpenSHC::UI::Enums::DEPM_TOWARDS_MID_X | OpenSHC::UI::Enums::DEPM_RESOLUTION_X);
                if (_xPosModifier != OpenSHC::UI::Enums::DEPM_RESOLUTION_X) {
                    if (_xPosModifier == OpenSHC::UI::Enums::DEPM_TOWARDS_MID_X) {
                        _xPos = _xPos + -800 + DAT_WindowAndDirectDraw::instance.resolutionX;
                    } else {
                        _xPos = _xPos + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth;
                    }
                }
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                (*_displayElementPtr->renderFunction_0x18)(_xPos, _yPos, _displayElementPtr->elementStateUnk_0xc);
                DAT_TextManagerObject::instance.textSurfaceTarget = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if ((-1 < _displayElementPtr->displayDuration_0x14)
                    && (_displayElementPtr->displayDuration_0x14
                        < (int)(_currentTime - _displayElementPtr->activationTime_0x10))) {
                    _displayElementPtr->elementStateUnk_0xc = 0;
                }
            }
        }
    }

}
}
