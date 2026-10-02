#include "../IntroLogos.func.hpp"

#include "OpenSHC/Game/GameCore.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/UI/Enums/MenuViewType.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_BLACK.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_IntroBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_IntroStep.hpp"
#include "OpenSHC/Globals/DAT_IntroTimestamp.hpp"
#include "OpenSHC/Globals/DAT_IntroTransitionStep.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuViews {

        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::UI::Enums::MenuViewType;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004247A0
        void IntroLogos::MenuView_IntroLogos_DoEveryFrame()
        {
            char* _textAddress;
            DWORD _currentTime;
            int _yParam;
            int _introStepDuration;
            TextAlignment alignment;
            int _blendStrength;
            BGR24 _color;
            int _fontSIze;
            BOOLEnum _keepOffsetX;
            MenuViewType _menuID;
            int _xPos;
            if (DAT_IntroStep::instance < 2) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::drawGfxOnFlaggedSurface,
                    DAT_TextureRenderCoreObject::ptr)(0,
                    (DAT_WindowAndDirectDraw::instance.resolutionX
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].width)
                        / 2,
                    (DAT_WindowAndDirectDraw::instance.resolutionY
                        - DAT_TextureRenderCoreObject::instance.loadedGfxArray[0].height)
                        / 2);
            } else {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawColorBox,
                    DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                    DAT_WindowAndDirectDraw::instance.resolutionY, (ushort)((int)(COL_BLACK::instance.shortValue)));
                _blendStrength = 0;
                _keepOffsetX = FALSE;
                _fontSIze = 0x10;
                _color = 0xffffff;
                alignment = OpenSHC::Text::TTA_CENTER;
                _yParam = DAT_WindowAndDirectDraw::instance.resolutionY / 2 + -0x1e;
                _xPos = DAT_WindowAndDirectDraw::instance.resolutionX / 2;
                /*
                  added by script: "Gameplay may change during online play"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_GAMEPLAY_ONLINE, 0), _xPos, _yParam, alignment, _color, _fontSIze, _keepOffsetX, _blendStrength);
            }
            _currentTime = timeGetTime();
            if (DAT_IntroTransitionStep::instance == 0) {
                DAT_IntroBlendStrength::instance = (int)(_currentTime - DAT_IntroTimestamp::instance) / 0x14;
                if (DAT_IntroBlendStrength::instance < 0x20)
                    goto LAB_0042496a;
                DAT_IntroBlendStrength::instance = 0x20;
                DAT_IntroTransitionStep::instance = 1;
                DAT_IntroTimestamp::instance = timeGetTime();
            } else if (DAT_IntroTransitionStep::instance == 1) {
                _introStepDuration = 0x9c4;
                if (DAT_IntroStep::instance == 1) {
                    /*
                      Duration of second logo.
                     */
                    _introStepDuration = 6000;
                }
                if (_introStepDuration < (int)(_currentTime - DAT_IntroTimestamp::instance)) {
                    DAT_IntroTransitionStep::instance = 2;
                    DAT_IntroTimestamp::instance = timeGetTime();
                }
            } else if ((DAT_IntroTransitionStep::instance == 2)
                && (DAT_IntroBlendStrength::instance = 0x20 - (int)(_currentTime - DAT_IntroTimestamp::instance) / 0x14,
                    DAT_IntroBlendStrength::instance < 1)) {
                if (DAT_IntroStep::instance == 0) {
                    DAT_IntroTransitionStep::instance = DAT_IntroStep::instance;
                    DAT_IntroBlendStrength::instance = DAT_IntroStep::instance;
                    DAT_IntroStep::instance = 1;
                    _menuID = OpenSHC::UI::Enums::MVT_INTRO_LOGOS;
                } else if (DAT_IntroStep::instance == 1) {
                    DAT_IntroTransitionStep::instance = 0;
                    DAT_IntroBlendStrength::instance = 0;
                    DAT_IntroStep::instance = 2;
                    _menuID = OpenSHC::UI::Enums::MVT_INTRO_LOGOS;
                } else {
                    _menuID = OpenSHC::UI::Enums::MVT_INTRO_VIDEO;
                }
                MACRO_CALL_MEMBER(OpenSHC::Game::GameCore_Func::switchToMenuView, DAT_GameCore::ptr)(_menuID, 0);
            }
            if (0x1f < DAT_IntroBlendStrength::instance) {
                return;
            }
        LAB_0042496a:
            timeGetTime();
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(0, 0, DAT_WindowAndDirectDraw::instance.resolutionX,
                DAT_WindowAndDirectDraw::instance.resolutionY, (int)((int)(DAT_IntroBlendStrength::instance)));
            return;
        }

    }
}
}
