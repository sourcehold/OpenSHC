#include "../Rendering.func.hpp"

#include "OpenSHC/Audio/MSS/SoundSystem.func.hpp"
#include "OpenSHC/Rendering/Bink/BinkControlClass.func.hpp"
#include "OpenSHC/UI/Credits.func.hpp"
#include "OpenSHC/UI/Rendering.func.hpp"
#include "OpenSHC/Audio/MSS/enums/SHC_SoundStream.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/DAT_00eb0e40.hpp"
#include "OpenSHC/Globals/DAT_00eb1234.hpp"
#include "OpenSHC/Globals/DAT_00eb9af4.hpp"
#include "OpenSHC/Globals/DAT_00ed2bd8.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00eb9b68.hpp"
#include "OpenSHC/Globals/DAT_ARRAY_00ec0348.hpp"
#include "OpenSHC/Globals/DAT_BinkControlState.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_MouseState.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedX.hpp"
#include "OpenSHC/Globals/DAT_RenderRelatedY.hpp"
#include "OpenSHC/Globals/DAT_SoundSystemState.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkCount.hpp"
#include "OpenSHC/Globals/DAT_UnknownBinkIndex.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/DWORD_00eb9ac4.hpp"
#include "OpenSHC/Globals/FLOAT_00eb0e2c.hpp"
#include "OpenSHC/Globals/FLOAT_Between1And5.hpp"
#include "OpenSHC/Globals/INT_00eb0e30.hpp"
#include "OpenSHC/Globals/INT_00ec083c.hpp"
#include "OpenSHC/Globals/INT_00ed27a4.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/INT_00ec0828.hpp"

namespace OpenSHC {

using Audio::MSS::enums::SHC_SoundStream;
using WindowsHelper::Enums::BOOLEnum;

// FUNCTION: STRONGHOLDCRUSADER 0x004E0A50
void Rendering::ProcessCreditsScriptCommands()
{
    int iVar1;
    SHC_SoundStream sndStreamIndex;
    int pFVar2;
    BOOLEnum BVar3;
    int* piVar4;
    CreditsRelatedStructure* pCVar4;
    CreditsRelatedStructure2* pCVar5;
    int* piVar7;
    int* piVar6;
    int iVar8;
    int iVar9;
    int iVar10;
    bool bVar11;
    if ((DAT_GameCore::instance.menuViewToSwitchTo == DAT_GameCore::instance.currentMenuViewType)
        && (iVar9 = DAT_UnknownBinkIndex::instance, -1 < DAT_UnknownBinkIndex::instance)) {
        while (iVar9 < DAT_UnknownBinkCount::instance) {
            iVar10 = iVar9;
            switch (DAT_ARRAY_00eb9b68::instance[iVar9].commandType) {
            case 1:
                if (FLOAT_Between1And5::instance + (float)INT_00ec083c::instance
                    <= (float)(int)DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                    INT_00ec083c::instance = (int)(FLOAT_Between1And5::instance + (float)INT_00ec083c::instance);
                    return;
                }
                INT_00ec083c::instance = 0;
                break;
            case 2:
                iVar8 = 0;
                piVar7 = &DAT_ARRAY_00ec0348::instance[0].xSpace;
            LAB_004e0b60:
                if (((CreditsRelatedStructure*)(piVar7 + -1))->isValid != 1
                    || *piVar7 != DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)
                    goto LAB_004e0b74;
                iVar1 = DAT_ARRAY_00ec0348::instance[iVar8].fadeMode;
            LAB_004e0b8e:
                if (!iVar1) {
                    DAT_UnknownBinkIndex::instance = iVar9 + 1;
                    iVar10 = DAT_UnknownBinkIndex::instance;
                }
                goto LAB_004e0b98;
            case 3:
                iVar8 = 0;
                piVar7 = &DAT_ARRAY_00ec0348::instance[0].xSpace;
                do {
                    if (((CreditsRelatedStructure*)(piVar7 + -1))->isValid == 2
                        && *piVar7 == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                        iVar1 = DAT_ARRAY_00ec0348::instance[iVar8].fadeMode;
                        goto LAB_004e0b8e;
                    }
                    piVar7 = piVar7 + 0xd;
                    iVar8 = iVar8 + 1;
                } while ((int)piVar7 < (int)&DAT_00ec082c::instance);
            LAB_004e0b98:
                bVar11 = iVar8 == 0x18;
                goto LAB_004e0b9b;
            case 4:
                BVar3 = MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::isSampleOrStreamPlaying,
                    DAT_SoundSystemState::ptr)((SHC_SoundStream)DAT_ARRAY_00eb9b68::instance[iVar9].soundStream);
                bVar11 = BVar3 == FALSE;
                iVar10 = DAT_UnknownBinkIndex::instance;
            LAB_004e0b9b:
                if (bVar11)
                    break;
                goto LAB_004e10ba;
            case 5:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(1,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field17_0x38)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].height)), 0,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field13_0x28)));
                break;
            case 6:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(1,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field17_0x38)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].height)), 1,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field13_0x28)));
                break;
            case 7:
                piVar7 = &DAT_ARRAY_00ec0348::instance[0].xSpace;
                do {
                    if (((CreditsRelatedStructure*)(piVar7 + -1))->isValid == 1
                        && *piVar7 == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                        ((CreditsRelatedStructure*)(piVar7 - 1))->blendStrength = 1.0f;
                        ((CreditsRelatedStructure*)(piVar7 - 1))->fadeMode = 2;
                    }
                    piVar7 = piVar7 + 0xd;
                } while ((int)piVar7 < (int)&DAT_00ec082c::instance);
                break;
            case 8:
                pCVar4 = DAT_ARRAY_00ec0348::instance;
                do {
                    if ((pCVar4->isValid == 1) && (pCVar4->xSpace == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)) {
                        pCVar4->isValid = 0;
                    }
                    pCVar4 = pCVar4 + 1;
                } while ((int)pCVar4 < (int)&INT_00ec0828::instance);
                break;
            case 9:
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::endSoundStream, DAT_SoundSystemState::ptr)(
                    (Audio::MSS::enums::SHC_SoundStream)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream));
                iVar10 = DAT_UnknownBinkIndex::instance;
                break;
            case 10:
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(
                    DAT_ARRAY_00eb9b68::instance[iVar9].soundStream);
                iVar10 = DAT_UnknownBinkIndex::instance;
                break;
            case 0xb:
                pCVar4 = DAT_ARRAY_00ec0348::instance;
                do {
                    if ((pCVar4->isValid == 2) && (pCVar4->xSpace == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)) {
                        pCVar4->isValid = 0;
                    }
                    pCVar4 = pCVar4 + 1;
                } while ((int)pCVar4 < (int)&INT_00ec0828::instance);
                break;
            case 0xc:
                MACRO_CALL_MEMBER(Rendering::Bink::BinkControlClass_Func::playBINK, DAT_BinkControlState::ptr)(
                    DAT_ARRAY_00eb9b68::instance[iVar9].binkObjIndex,
                    (char*)&DAT_ARRAY_00eb9b68::instance[iVar9].binkFileName,
                    (DWORD)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].flagLoopCount)), 0,
                    DAT_ARRAY_00eb9b68::instance[iVar9].x + DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth,
                    DAT_ARRAY_00eb9b68::instance[iVar9].y + DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight,
                    (DWORD)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field13_0x28)));
                iVar10 = DAT_UnknownBinkIndex::instance;
                break;
            case 0xd:
                sndStreamIndex = (SHC_SoundStream)DAT_ARRAY_00eb9b68::instance[iVar9].binkObjIndex;
                DAT_SoundSystemState::instance.streamFileVolumeNextUnk_0x48[sndStreamIndex]
                    = DAT_ARRAY_00eb9b68::instance[iVar9].volume;
                MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::playSoundStreamUnk, DAT_SoundSystemState::ptr)(
                    sndStreamIndex, (char*)&DAT_ARRAY_00eb9b68::instance[iVar9].binkFileName,
                    DAT_ARRAY_00eb9b68::instance[iVar9].flagLoopCount);
                iVar10 = DAT_UnknownBinkIndex::instance;
                break;
            case 0xe:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_2)(2,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field6_0x18)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field16_0x34)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)), 0,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field15_0x30)));
                break;
            case 0xf:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_2)(2,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field6_0x18)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field16_0x34)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)), 1,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field15_0x30)));
                break;
            case 0x10:
                piVar7 = &DAT_ARRAY_00ec0348::instance[0].xSpace;
                do {
                    if (((CreditsRelatedStructure*)(piVar7 + -1))->isValid == 2
                        && *piVar7 == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                        ((CreditsRelatedStructure*)(piVar7 - 1))->blendStrength = 1.0f;
                        ((CreditsRelatedStructure*)(piVar7 - 1))->fadeMode = 2;
                    }
                    piVar7 = piVar7 + 0xd;
                } while ((int)piVar7 < (int)&DAT_00ec082c::instance);
                break;
            case 0x11:
                INT_00ed27a4::instance = DAT_ARRAY_00eb9b68::instance[iVar9].soundStream;
                if (INT_00ed27a4::instance == Audio::MSS::enums::SND_STR_SFX_1Unk) {
                    DAT_00eb9af4::instance = DAT_ARRAY_00eb9b68::instance[iVar9].x;
                }
                break;
            case 0x12:
                DAT_00eb0e40::instance = 1;
                FLOAT_00eb0e2c::instance = 0.0;
                break;
            case 0x13:
                DAT_00eb0e40::instance = 2;
                FLOAT_00eb0e2c::instance = 31.0;
                break;
            case 0x14:
                pFVar2 = (int)DAT_00eb0e40::instance;
                goto joined_r0x004e1060;
            case 0x15:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoArrayAt_ec0348_3)(3,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].height)), 0,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field13_0x28)));
                break;
            case 0x16:
                if (!DAT_MouseState::instance.draggingStopped) {
                    return;
                }
                piVar4 = &DAT_ARRAY_00ec0348::instance[0].x;
                do {
                    if (((CreditsRelatedStructure*)(piVar4 - 2))->isValid == 3) {
                        if (((CreditsRelatedStructure*)(piVar4 - 2))->xSpace <= DAT_MouseState::instance.screenSpaceX
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                            && DAT_MouseState::instance.screenSpaceX
                                    - DAT_WindowAndDirectDraw::instance.mainMenuBorderWidth
                                < ((CreditsRelatedStructure*)(piVar4 - 2))->y
                                    + ((CreditsRelatedStructure*)(piVar4 - 2))->xSpace) {
                            if (((CreditsRelatedStructure*)(piVar4 - 2))->x <= DAT_MouseState::instance.screenSpaceY
                                        - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                                && DAT_MouseState::instance.screenSpaceY
                                        - DAT_WindowAndDirectDraw::instance.mainMenuBorderHeight
                                    < ((CreditsRelatedStructure*)(piVar4 - 2))->width
                                        + ((CreditsRelatedStructure*)(piVar4 - 2))->x)
                                break;
                        }
                    }
                    piVar4 = piVar4 + 0xd;
                    if (0xec082f < (int)piVar4) {
                        return;
                    }
                } while (true);
            case 0x17:
                pCVar4 = DAT_ARRAY_00ec0348::instance;
                do {
                    if (pCVar4->isValid == 3) {
                        pCVar4->isValid = 0;
                    }
                    pCVar4 = pCVar4 + 1;
                } while ((int)pCVar4 < (int)&INT_00ec0828::instance);
                break;
            case 0x18:
                pFVar2 = (int)DAT_BinkControlState::instance.binkObjPtrArray[0];
            joined_r0x004e1060:
                if (pFVar2 != 0) {
                    return;
                }
                break;
            case 0x19:
                if ((INT_00ed27a4::instance != 2)
                    && (DAT_BinkControlState::instance.binkObjPtrArray[0] != (HBINK)0x0)) {
                    MACRO_CALL_MEMBER(
                        Rendering::Bink::BinkControlClass_Func::stopBinkPlayback, DAT_BinkControlState::ptr)(0);
                    iVar10 = DAT_UnknownBinkIndex::instance;
                }
                pCVar4 = DAT_ARRAY_00ec0348::instance;
                do {
                    if (pCVar4->isValid) {
                        pCVar4->isValid = 0;
                    }
                    pCVar4 = pCVar4 + 1;
                } while ((int)pCVar4 < (int)&INT_00ec0828::instance);
                break;
            case 0x1a:
                DAT_00ed2bd8::instance = 1;
            default:
            switchD_004e0abf_caseD_1d:
                break;
            case 0x1b:
                MACRO_CALL(UI::Rendering_Func::DisplayFullScreenTextPage)(
                    DAT_ARRAY_00eb9b68::instance[iVar9].soundStream);
                DWORD_00eb9ac4::instance = 1;
                iVar10 = DAT_UnknownBinkIndex::instance;
                break;
            case 0x1c:
                DWORD_00eb9ac4::instance = 0;
                DAT_00ed2bd8::instance = 0;
                goto switchD_004e0abf_caseD_1d;
            case 0x20:
                DAT_00ed2bd8::instance = 2;
                goto switchD_004e0abf_caseD_1d;
            case 0x24:
                DAT_00eb0e40::instance = 3;
                FLOAT_00eb0e2c::instance = 0.0;
                goto LAB_004e0f3c;
            case 0x25:
                DAT_00eb0e40::instance = 4;
                FLOAT_00eb0e2c::instance = 31.0;
            LAB_004e0f3c:
                DAT_RenderRelatedX::instance = DAT_ARRAY_00eb9b68::instance[iVar9].x;
                DAT_RenderRelatedY::instance = DAT_ARRAY_00eb9b68::instance[iVar9].y;
                DAT_00eb1234::instance = DAT_ARRAY_00eb9b68::instance[iVar9].width;
                INT_00eb0e30::instance = DAT_ARRAY_00eb9b68::instance[iVar9].height;
                break;
            case 0x27:
                if (DAT_SoundSystemState::instance.sec_Section1055_0x3274
                    != DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setSomeSoundTime, DAT_SoundSystemState::ptr)();
                    MACRO_CALL_MEMBER(Audio::MSS::SoundSystem_Func::setupVolumeAndSoundID, DAT_SoundSystemState::ptr)(
                        (DE::SHCDE::eMusicIDs)(DAT_ARRAY_00eb9b68::instance[DAT_UnknownBinkIndex::instance]
                                .soundStream));
                    iVar10 = DAT_UnknownBinkIndex::instance;
                }
                break;
            case 0x28:
                iVar10 = iVar9 + -1;
                if (0 < iVar10) {
                    pCVar5 = DAT_ARRAY_00eb9b68::instance + iVar10;
                    do {
                        if (pCVar5->commandType == 0x1f)
                            break;
                        iVar10 = iVar10 + -1;
                        pCVar5 = pCVar5 + -1;
                    } while (0 < iVar10);
                }
                break;
            case 0x29:
                MACRO_CALL(UI::Credits_Func::InsertElementIntoAnArrayAt_ec0348)(4,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].soundStream)), 0,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].x)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].y)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].width)),
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].height)), 0,
                    (undefined4)((int)(DAT_ARRAY_00eb9b68::instance[iVar9].field13_0x28)));
                break;
            case 0x2a:
                piVar6 = &DAT_ARRAY_00ec0348::instance[0].xSpace;
                do {
                    if (((CreditsRelatedStructure*)(piVar6 - 1))->isValid == 4
                        && ((CreditsRelatedStructure*)(piVar6 - 1))->xSpace
                            == DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                        ((CreditsRelatedStructure*)(piVar6 - 1))->blendStrength = 1.0f;
                        ((CreditsRelatedStructure*)(piVar6 - 1))->fadeMode = 2;
                    }
                    piVar6 = piVar6 + 0xd;
                } while ((int)piVar6 < (int)&DAT_00ec082c::instance);
                break;
            case 0x2b:
                DAT_00eb0e40::instance = 5;
                FLOAT_00eb0e2c::instance = 31.0;
                break;
            case 0x2c:
                if (FLOAT_Between1And5::instance + (float)INT_00ec083c::instance
                    <= (float)(int)DAT_ARRAY_00eb9b68::instance[iVar9].soundStream) {
                    if (!DAT_MouseState::instance.draggingStopped) {
                        INT_00ec083c::instance = (int)(FLOAT_Between1And5::instance + (float)INT_00ec083c::instance);
                        return;
                    }
                    INT_00ec083c::instance = 0;
                } else {
                    INT_00ec083c::instance = 0;
                }
            }
            iVar10 = iVar10 + 1;
            DAT_UnknownBinkIndex::instance = iVar10;
        LAB_004e10ba:
            if (iVar10 == iVar9) {
                return;
            }
            iVar9 = iVar10;
            if (iVar10 < 0) {
                return;
            }
        }
    }
    return;
LAB_004e0b74:
    piVar7 = piVar7 + 0xd;
    iVar8 = iVar8 + 1;
    if (0xec082b < (int)piVar7)
        goto LAB_004e0b98;
    goto LAB_004e0b60;
}

}
