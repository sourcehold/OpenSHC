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
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::WindowsHelper::Enums::BOOLEnum;

        // FUNCTION: STRONGHOLDCRUSADER 0x004630D0
        BOOLEnum AlphaAndButtonSurface::isMouseOnButtonImageUnk()
        {
            ushort* const surface = this->surfacePtr;
            if (DAT_CurrentButtonPictureInGm::instance >= 0) {
                int const imageIndex = GMFirstPictureIndex::instance[DAT_UIButtonDefinedData::instance
                                               .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                               .gmId_0x0]
                    + DAT_CurrentButtonPictureInGm::instance - 1;
                int const width = DAT_GMImageHeaders::instance.imh[imageIndex].width;
                this->currentImageWidth = width;
                MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                    DAT_GMImageHeaders::instance.imh[imageIndex].height * width * 2,
                    (ushort)COL_MAGENTA::instance.shortValue, surface);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                    = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                          .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                          .gmId_0x0,
                    DAT_CurrentButtonPictureInGm::instance, 0, 0);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                return surface[(DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance) * this->currentImageWidth
                           - DAT_ButtonX::instance + DAT_MouseState::instance.screenSpaceX]
                    != (ushort)COL_MAGENTA::instance.shortValue;
            }
            // A negative picture number means the alpha image of the button.
            DAT_CurrentButtonPictureInGm::instance = -DAT_CurrentButtonPictureInGm::instance;
            int const imageIndex = GMFirstPictureIndex::instance[DAT_UIButtonDefinedData::instance
                                           .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                           .alphaGmIdUnk_0xc]
                + DAT_CurrentButtonPictureInGm::instance - 1;
            int const width = DAT_GMImageHeaders::instance.imh[imageIndex].width;
            this->currentImageWidth = width;
            MACRO_CALL_MEMBER(OpenSHC::IO::LowLevelMemory_Func::fillMemory_ShortValue, DAT_LowLevelMemory::ptr)(
                DAT_GMImageHeaders::instance.imh[imageIndex].height * width * 2,
                (ushort)COL_MAGENTA::instance.shortValue, this->surfacePtr);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                = OpenSHC::Rendering::Enums::RT_BUTTON_AND_ALPHA;
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                DAT_TextureRenderCoreObject::ptr)((OpenSHC::DE::SHCDE::eGM)DAT_UIButtonDefinedData::instance
                                                      .ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                                                      .alphaGmIdUnk_0xc,
                DAT_CurrentButtonPictureInGm::instance, 0, 0);
            DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
            ushort const pixel
                = surface[this->currentImageWidth * (DAT_MouseState::instance.screenSpaceY - DAT_ButtonY::instance)
                    + (DAT_MouseState::instance.screenSpaceX - DAT_ButtonX::instance)];
            if (pixel != (ushort)COL_MAGENTA::instance.shortValue && (char)(pixel & 0x1f) >= 31) {
                return TRUE;
            }
            return FALSE;
        }

    }
}
}
