#include "../TutorialBox.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/FontSizeClass.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Colors/ColorsEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/string-literals.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_MissionAestheticsDefinedData.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/INT_00df5564.hpp"
#include "OpenSHC/Globals/INT_00df5644.hpp"
#include "OpenSHC/Globals/INT_00df5648.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00df5598.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        // FUNCTION: STRONGHOLDCRUSADER 0x004BCBA0
        void TutorialBox::MenuModalRenderFunction_TutorialBox(int x, int y, int width, int height)
        {
            if (DAT_TutorialCurrentStep::instance >= 32) {
                return;
            }
            int const textX = x + 16;
            int const textWidth = width - 32;
            int const tutorialTextOffset = INT_ARRAY_00df5598::instance[DAT_TutorialCurrentStep::instance];
            int blendStrength = 0;
            if (DAT_00df5540::instance != 0) {
                blendStrength = DAT_00df5544::instance;
            }
            // The frame is drawn in 24 pixel tiles, rounded up to whole tiles
            int const boxWidth = ((width - 1) / 24 + 1) * 24;
            int const boxHeight = ((height - 1) / 24 + 1) * 24;
            for (int offsetY = 0; offsetY < boxHeight; offsetY += 24) {
                // Icons 1-3 are the top row's left, inner and right tiles, 7-9 a middle row's and 13-15 the bottom's
                int rowBaseIcon;
                if (offsetY == 0) {
                    rowBaseIcon = 1;
                } else if (offsetY == boxHeight - 24) {
                    rowBaseIcon = 13;
                } else {
                    rowBaseIcon = 7;
                }
                for (int offsetX = 0; offsetX < boxWidth; offsetX += 24) {
                    int iconIndex = rowBaseIcon;
                    if (offsetX != 0) {
                        if (offsetX == boxWidth - 24) {
                            iconIndex = rowBaseIcon + 2;
                        } else if (rowBaseIcon == 7) {
                            // The plain inner tile has its own call (the original pushes 8 and 11 as constants)
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 8,
                                offsetX + x, offsetY + y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 11,
                                blendStrength);
                            continue;
                        } else {
                            iconIndex = rowBaseIcon + 1;
                        }
                    }
                    // Each tile's alpha mask is three icons on
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iconIndex,
                        offsetX + x, offsetY + y, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iconIndex + 3,
                        blendStrength);
                }
            }
            // Speaks the button hint once when it comes up, the two recordings taking turns
            if (INT_00df5564::instance && !INT_00df5648::instance) {
                ++INT_00df5644::instance;
                if (INT_00df5644::instance > 1) {
                    INT_00df5644::instance = 0;
                }
                if (!MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1)
                    && !MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                        DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2)) {
                    char speechFileName[32];
                    // "%s%s", "fx\\speech\\"
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(speechFileName, s__s_s_005aa800, s_fx_speech__005a64cc,
                        DAT_MissionAestheticsDefinedData::instance.field_0x41e4[INT_00df5644::instance + 34][0]);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                        DAT_SoundSystemState::ptr)(speechFileName);
                }
            }
            INT_00df5648::instance = INT_00df5564::instance;
            // >> 1 for the centre, as the original has no rounding fix (/ 2: quick_diff 0.9764 -> 0.8745)
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL, tutorialTextOffset),
                (width >> 1) + x, y + 15, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_CCFAFF, 18, FALSE,
                blendStrength);
            int bodyY = y + 38;
            if (!INT_00df5564::instance) {
                // The text's offset is worked out before the call (in the call: quick_diff 0.9764 -> 0.9291)
                int const bodyTextOffset = DAT_00df5558::instance + 1 + tutorialTextOffset;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                        DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL, bodyTextOffset),
                    textX, bodyY, textWidth, OpenSHC::Rendering::Colors::COL_C2F0EB, 19, blendStrength);
                bodyY += DAT_TextManagerObject::instance.field_0x4;
            }
            // A second test, not an else (else: quick_diff 0.9764 -> 0.9261)
            if (INT_00df5564::instance) {
                // Read for measuring and again in each arm (in the calls: quick_diff 0.9764 -> 0.9333)
                int const measuredText = INT_00df5644::instance + 3;
                // "That's not a valid option at this time." or "You can't do that at this point in the tutorial.":
                // wrapped when taller than 35 pixels (more than one line), centred on one line otherwise
                if (MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                        &DAT_TextManagerObject::instance.fontSizeClassArray[18])(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, measuredText),
                        0, 0, textWidth, 0, 0, 1)
                    > 35) {
                    int const hintText = INT_00df5644::instance + 3;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, hintText),
                        textX, bodyY, textWidth, OpenSHC::Rendering::Colors::COL_0000FF, 18, blendStrength);
                } else {
                    int const hintText = INT_00df5644::instance + 3;
                    // fixme: the original passes the blend as keepOffsetX here, and 0 as the blend
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                            DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, hintText),
                        (width >> 1) + x, bodyY, OpenSHC::Text::TTA_CENTER, OpenSHC::Rendering::Colors::COL_0000FF, 18,
                        blendStrength, 0);
                }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTutorialFloatForUIElement)(DAT_TutorialCurrentStep::instance);
        }

    }
}
}
