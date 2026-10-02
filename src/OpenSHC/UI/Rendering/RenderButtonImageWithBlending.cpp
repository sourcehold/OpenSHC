#include "../Rendering.func.hpp"

#include "OpenSHC/UI/Rendering/ButtonGmData.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"

#include "OpenSHC/Globals/DAT_ButtonBlendStrength.hpp"
#include "OpenSHC/Globals/DAT_ButtonCurrentlyInteracting.hpp"
#include "OpenSHC/Globals/DAT_ButtonX.hpp"
#include "OpenSHC/Globals/DAT_ButtonY.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonGmDataIndex.hpp"
#include "OpenSHC/Globals/DAT_CurrentButtonPictureInGm.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_UIButtonDefinedData.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::IO::Graphics::GmID;

    // FUNCTION: STRONGHOLDCRUSADER 0x004641A0
    void Rendering::RenderButtonImageWithBlending()
    {
        ButtonGmData* pBVar1;
        int imageID;
        int iVar2;
        int iVar3;
        int iVar4;
        if (DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance].alphaGmIdUnk_0xc
            != ((GmID)0)) {
            if (DAT_ButtonBlendStrength::instance != 0x20) {
                pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
                iVar3 = DAT_ButtonX::instance;
                iVar4 = DAT_ButtonY::instance;
                iVar2 = DAT_ButtonBlendStrength::instance;
                imageID = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
                    DAT_ButtonCurrentlyInteracting::instance);
                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                    DAT_TextureRenderCoreObject::ptr)(
                    (OpenSHC::IO::Graphics::GmID)pBVar1->gmId_0x0, imageID, iVar3, iVar4, iVar2);
            }
            DAT_CurrentButtonPictureInGm::instance
                = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                      .pictureInGm_0x4;
        }
        pBVar1 = DAT_UIButtonDefinedData::instance.ButtonGmDataArray + DAT_CurrentButtonGmDataIndex::instance;
        iVar3 = DAT_ButtonX::instance;
        iVar4 = DAT_ButtonY::instance;
        iVar2 = MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::ButtonGmData_Func::getPictureNumberInGm, pBVar1)(
            DAT_ButtonCurrentlyInteracting::instance);
        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
            (OpenSHC::DE::SHCDE::eGM)pBVar1->gmId_0x0, iVar2, iVar3, iVar4);
        DAT_CurrentButtonPictureInGm::instance
            = DAT_UIButtonDefinedData::instance.ButtonGmDataArray[DAT_CurrentButtonGmDataIndex::instance]
                  .pictureInGm_0x4;
    }

}
}
