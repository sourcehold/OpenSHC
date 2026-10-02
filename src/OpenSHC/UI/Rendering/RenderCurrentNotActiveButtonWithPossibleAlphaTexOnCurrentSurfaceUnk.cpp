#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonUnknownZero.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004640D0
    void Rendering::RenderCurrentNotActiveButtonWithPossibleAlphaTexOnCurrentSurfaceUnk()
    {
        ButtonGmData* buttonGmData;
        int iVar1;
        int iVar2;
        int iVar3;
        iVar3 = DAT_CurrentButtonGmDataIndex::instance;
        iVar2 = 0;
        if (DAT_ButtonUnknownZero::instance != 0) {
            iVar2 = 2;
        }
        buttonGmData = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
        iVar1 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, buttonGmData)(FALSE);
        if (DAT_ButtonCurrentlyInteracting::instance != FALSE) {
            iVar1 = iVar1 + 1;
        }
        if (DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar3].alphaGmIdUnk_0xc != ((GmID)0)) {
            if (DAT_ButtonBlendStrength::instance != 0x20) {
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)((OpenSHC::IO::Graphics::GmID)buttonGmData->gmId_0x0,
                    iVar1 + iVar2, (int)((int)(DAT_ButtonX::instance)), (int)((int)(DAT_ButtonY::instance)),
                    (int)((int)(DAT_ButtonBlendStrength::instance)));
                iVar3 = DAT_CurrentButtonGmDataIndex::instance;
            }
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[iVar3].pictureInGm_0x4 + iVar2;
        }
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            (OpenSHC::DE::SHCDE::eGM)buttonGmData->gmId_0x0, iVar1 + iVar2, (int)((int)(DAT_ButtonX::instance)),
            (int)((int)(DAT_ButtonY::instance)));
        DAT_CurrentButtonPictureInGm::instance
            = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                  .pictureInGm_0x4
            + iVar2;
    }

}
}
