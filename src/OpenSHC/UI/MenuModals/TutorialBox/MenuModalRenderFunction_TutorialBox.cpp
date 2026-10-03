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
#include "OpenSHC/Rendering/Colors/BGR24.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00df5540.hpp"
#include "OpenSHC/Globals/DAT_00df5544.hpp"
#include "OpenSHC/Globals/DAT_00df5558.hpp"
#include "OpenSHC/Globals/DAT_00df5564.hpp"
#include "OpenSHC/Globals/DAT_00df5644.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TutorialCurrentStep.hpp"
#include "OpenSHC/Globals/INT_00df5648.hpp"
#include "OpenSHC/Globals/INT_ARRAY_00df5598.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {
    namespace MenuModals {

        using OpenSHC::Audio::MSS::enums::SHC_SoundStream;
        using OpenSHC::DE::SHCDE::eTextSections;
        using OpenSHC::IO::Graphics::GmID;
        using OpenSHC::Rendering::Colors::BGR24;
        using OpenSHC::Text::TextAlignment;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        /*
          decompilerscript: committed: 2025-01-30 21:57:43.216000
         */
        // FUNCTION: STRONGHOLDCRUSADER 0x004BCBA0
        void TutorialBox::MenuModalRenderFunction_TutorialBox(int x, int y, int width, int height)
        {
            BOOLEnum BVar1;
            char* pcVar2;
            int iVar3;
            BOOLEnum keepOffsetX;
            int iVar4;
            int iVar5;
            TextAlignment TVar6;
            int iVar7;
            BGR24 BVar8;
            int iVar9;
            uint uVar10;
            BOOLEnum keepOffsetX_00;
            int iVar11;
            int iVar12;
            int iVar13;
            int local_3c;
            int local_38;
            int local_34;
            int local_30;
            int local_2c;
            int local_28;
            char local_24[32];
            uint local_4;
            local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_3c;
            if (0x1f < DAT_TutorialCurrentStep::instance)
                goto LAB_004bceab;
            local_28 = INT_ARRAY_00df5598::instance[DAT_TutorialCurrentStep::instance];
            local_38 = x + 0x10;
            local_34 = width + -0x20;
            keepOffsetX = FALSE;
            if (DAT_00df5540::instance != 0) {
                keepOffsetX = DAT_00df5544::instance;
            }
            iVar3 = ((height + -1) / 0x18 + 1) * 0x18;
            iVar13 = ((width + -1) / 0x18 + 1) * 0x18;
            local_30 = 0;
            local_3c = iVar13;
            local_2c = iVar3;
            if (0 < iVar3) {
                do {
                    if (local_30 == 0) {
                        iVar5 = 1;
                    } else {
                        iVar5 = (-(uint)(local_30 != iVar3 + -0x18) & 0xfffffffa) + 0xd;
                    }
                    iVar4 = 0;
                    if (0 < iVar13) {
                        iVar9 = local_30 + y;
                        do {
                            iVar3 = iVar5;
                            if (iVar4 == 0) {
                            LAB_004bcca6:
                                iVar13 = iVar3 + 3;
                            } else {
                                if (iVar4 == iVar13 + -0x18) {
                                    iVar3 = iVar5 + 2;
                                    goto LAB_004bcca6;
                                }
                                if (iVar5 != 7) {
                                    iVar3 = iVar5 + 1;
                                    goto LAB_004bcca6;
                                }
                                iVar13 = 0xb;
                                iVar3 = 8;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar3,
                                iVar4 + x, iVar9, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, iVar13,
                                (int)((int)(keepOffsetX)));
                            iVar4 = iVar4 + 0x18;
                            iVar3 = local_2c;
                            iVar13 = local_3c;
                        } while (iVar4 < local_3c);
                    }
                    local_30 = local_30 + 0x18;
                } while (local_30 < iVar3);
            }
            iVar3 = local_28;
            if ((DAT_00df5564::instance != 0) && (INT_00df5648::instance == 0)) {
                DAT_00df5644::instance = DAT_00df5644::instance + 1;
                if (1 < DAT_00df5644::instance) {
                    DAT_00df5644::instance = 0;
                }
                BVar1 = MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                    DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_1);
                if ((BVar1 == FALSE)
                    && (BVar1 = MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                            DAT_SoundSystemState::ptr)(OpenSHC::Audio::MSS::enums::SND_STR_SPEECH_2),
                        BVar1 == FALSE)) {
                    MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                        local_24, "%s%s", "fx\\speech\\", DAT_00df5644::instance * 0x60 + 0xb3e4d0);
                    MACRO_CALL_MEMBER(OpenSHC::Audio::MSS::SoundSystem_Func::playAmbientStreamWithLoop,
                        DAT_SoundSystemState::ptr)(local_24);
                }
            }
            keepOffsetX_00 = FALSE;
            iVar9 = 0x12;
            BVar8 = 0xccfaff;
            TVar6 = OpenSHC::Text::TTA_CENTER;
            iVar13 = y + 0xf;
            iVar4 = (width >> 1) + x;
            INT_00df5648::instance = DAT_00df5564::instance;
            iVar5 = iVar4;
            BVar1 = keepOffsetX;
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_TUTORIAL, iVar3),
                iVar5, iVar13, TVar6, BVar8, iVar9, keepOffsetX_00, (int)((int)(BVar1)));
            iVar13 = local_34;
            iVar5 = y + 0x26;
            if (DAT_00df5564::instance == 0) {
                iVar11 = 0x13;
                uVar10 = 0xc2f0eb;
                iVar9 = local_38;
                iVar7 = iVar5;
                iVar12 = local_34;
                BVar1 = keepOffsetX;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TUTORIAL, DAT_00df5558::instance + 1 + iVar3),
                    iVar9, iVar7, iVar12, uVar10, iVar11, (int)((int)(BVar1)));
                iVar5 = iVar5 + DAT_TextManagerObject::instance.field1_0x4;
                if (DAT_00df5564::instance != 0)
                    goto LAB_004bce14;
            } else {
            LAB_004bce14:
                iVar11 = 1;
                iVar12 = 0;
                BVar8 = 0;
                iVar7 = 0;
                iVar9 = 0;
                iVar3 = iVar13;
                iVar3 = MACRO_CALL_MEMBER(OpenSHC::Text::FontSizeClass_Func::renderMultilineTextUnk,
                    &DAT_TextManagerObject::instance.fontSizeClassArray[0x12])(
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                        OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                    iVar9, iVar7, iVar3, BVar8, iVar12, iVar11);
                if (iVar3 < 0x24) {
                    iVar13 = 0;
                    iVar3 = 0x12;
                    BVar8 = 0xff;
                    TVar6 = OpenSHC::Text::TTA_CENTER;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                        iVar4, iVar5, TVar6, BVar8, iVar3, keepOffsetX, iVar13);
                } else {
                    iVar4 = 0x12;
                    uVar10 = 0xff;
                    iVar3 = local_38;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderMultilineText5Unk, DAT_TextManagerObject::ptr)(
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                            OpenSHC::DE::SHCDE::TEXT_TUTORIAL_BUTTONS, DAT_00df5644::instance + 3),
                        iVar3, iVar5, iVar13, uVar10, iVar4, (int)((int)(keepOffsetX)));
                }
            }
            MACRO_CALL(OpenSHC::UI::Rendering_Func::RenderTutorialFloatForUIElement)(DAT_TutorialCurrentStep::instance);
        LAB_004bceab:;
        }

    }
}
}
