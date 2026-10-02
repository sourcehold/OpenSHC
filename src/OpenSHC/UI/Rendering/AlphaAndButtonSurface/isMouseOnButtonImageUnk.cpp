#include "../AlphaAndButtonSurface.func.hpp"

#include "OpenSHC/IO/LowLevelMemory.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_GMImageHeaders.hpp"
#include "OpenSHC/Globals/DAT_LowLevelMemory.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004630D0
        BOOLEnum AlphaAndButtonSurface::isMouseOnButtonImageUnk()
        {
            ushort* dst;
            int iVar1;
            int iVar2;
            int iVar3;
            iVar1 = DAT_CurrentButtonPictureInGm::instance;
            dst = this->surfacePtr;
            if (-1 < DAT_CurrentButtonPictureInGm::instance) {
                iVar3 = GMTotalPicturesProcessed::instance[DAT_UIButtonDefinedData::instance
                        .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                        .gmId_0x0];
                iVar2
                    = (int)DAT_GMImageHeaders::instance.imh[DAT_CurrentButtonPictureInGm::instance + iVar3 + -1].width;
                this->currentImageWidth = iVar2;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                    DAT_GMImageHeaders::instance.imh[iVar1 + iVar3 + -1].height * iVar2 * 2,
                    (ushort)((int)(COL_MAGENTA::instance.shortValue)), (void*)((int)(dst)));
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                    = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    (int)((int)((OpenSHC::DE::SHCDE::eGM)DAT_CurrentButtonPictureInGm::instance)), 0, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return (
                    uint)(dst[((DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance) * this->currentImageWidth
                                  - DAT_ButtonX::instance)
                              + DAT_MouseState::instance.screenSpaceX]
                    != COL_MAGENTA::instance.shortValue);
            }
            DAT_CurrentButtonPictureInGm::instance = -DAT_CurrentButtonPictureInGm::instance;
            iVar1 = (GMTotalPicturesProcessed::instance[DAT_UIButtonDefinedData::instance
                             .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                             .alphaGmIdUnk_0xc]
                        + -1 + DAT_CurrentButtonPictureInGm::instance)
                * 0x10;
            iVar3 = (int)*(short*)((int)DAT_GMImageHeaders::ptr + iVar1);
            this->currentImageWidth = iVar3;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                *(short*)((int)DAT_GMImageHeaders::ptr + iVar1 + 2) * iVar3 * 2,
                (ushort)((int)(COL_MAGENTA::instance.shortValue)), (void*)((int)(this->surfacePtr)));
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                      .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                      .alphaGmIdUnk_0xc,
                (int)((int)(DAT_CurrentButtonPictureInGm::instance)), 0, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            if ((dst[this->currentImageWidth * (DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance)
                     + (DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance)]
                    != COL_MAGENTA::instance.shortValue)
                && (0x1e < ((byte)dst[this->currentImageWidth
                                    * (DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance)
                                + (DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance)]
                        & 0x1f))) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
