#include "../Rendering.func.hpp"

#include "OpenSHC/OS.func.hpp"
#include "OpenSHC/Text/TextManager.func.hpp"
#include "OpenSHC/UI/GreatestLord.func.hpp"
#include "OpenSHC/UI/Rendering/PencilRenderCore.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/DE/SHCDE/eTextSections.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"
#include "OpenSHC/Rendering/ScreenResolutionEnum.hpp"
#include "OpenSHC/Text/TextAlignment.hpp"
#include "OpenSHC/WindowsHelper/Enums/BOOLEnum.hpp"

#include "OpenSHC/Globals/COL_WHITE.hpp"
#include "OpenSHC/Globals/DAT_00eb9af8.hpp"
#include "OpenSHC/Globals/DAT_00ec082c.hpp"
#include "OpenSHC/Globals/DAT_00ed3118.hpp"
#include "OpenSHC/Globals/DAT_BlendingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_FinalResultsOrderByColumn.hpp"
#include "OpenSHC/Globals/DAT_GameCore.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_MenuHandlerState.hpp"
#include "OpenSHC/Globals/DAT_MissionDefinedData.hpp"
#include "OpenSHC/Globals/DAT_PencilRenderCore.hpp"
#include "OpenSHC/Globals/DAT_RenderingDefinedData.hpp"
#include "OpenSHC/Globals/DAT_TextManagerObject.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/Globals/INT_00eb0e44.hpp"
#include "OpenSHC/Globals/MSVC_SecurityCookie.hpp"

namespace OpenSHC {
namespace UI {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::DE::SHCDE::eTextSections;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Rendering::ScreenResolutionEnum;
    using OpenSHC::Rendering::Enums::RenderTarget;
    using OpenSHC::Text::TextAlignment;
    using OpenSHC::WindowsHelper::Enums::BOOLEnum;

    /*
      WARNING: Enum "DPSEND_EnumInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "DPERRInt": Some values do not have unique names
     */
    /*
      WARNING: Enum "MappersEnum": Some values do not have unique names
     */
    /*
      decompilerscript: committed: 2025-01-30 21:57:43.216000
     */
    // FUNCTION: STRONGHOLDCRUSADER 0x004D5810
    void Rendering::RenderGreatestLordScreen()
    {
        char (*text)[90];
        short sVar1;
        eTextSections offsetIndex;
        int iVar2;
        int iVar3;
        int iVar4;
        char* pcVar5;
        char* pcVar6;
        int* piVar7;
        int iVar8;
        uint uVar9;
        int iVar10;
        int _renderPlayer;
        TextAlignment TVar11;
        BGR24 BVar12;
        BOOLEnum BVar13;
        int blendStrength;
        int local_3d0;
        int local_3cc;
        int local_3c8;
        int local_3c4;
        int _highestRankingInDomain[10];
        int aiStack_398[9];
        int local_374[8];
        int aiStack_354[9];
        int aiStack_330[9];
        int local_30c[9];
        int aiStack_2e8[9];
        int aiStack_2c4[9];
        int aiStack_2a0[9];
        int aiStack_27c[9];
        int aiStack_258[9];
        int aiStack_234[9];
        int aiStack_210[9];
        int aiStack_1ec[18];
        int aiStack_1a4[9];
        int aiStack_180[9];
        int aiStack_15c[9];
        int aiStack_138[9];
        int aiStack_114[9];
        int aiStack_f0[9];
        char local_cc[100];
        char local_68[100];
        uint local_4;
        local_4 = MSVC_SecurityCookie::instance ^ (uint)&local_3d0;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            local_3c4 = DAT_MenuHandlerState::instance.x + 10;
            local_3cc = 0x3a;
        } else {
            local_3c4 = DAT_MenuHandlerState::instance.x + -0x66;
            local_3cc = 0x20a;
        }
        local_3d0 = DAT_MenuHandlerState::instance.y;
        iVar2 = 1;
        piVar7 = DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[1] + 2;
        _highestRankingInDomain[1] = 0;
        _highestRankingInDomain[2] = 0;
        _highestRankingInDomain[3] = 0;
        _highestRankingInDomain[4] = 0;
        _highestRankingInDomain[5] = 0;
        _highestRankingInDomain[6] = 0;
        _highestRankingInDomain[7] = 0;
        _highestRankingInDomain[8] = 0;
        do {
            iVar8 = 0;
            if (iVar2 != 1) {
                iVar8 = piVar7[-1];
            }
            if (iVar2 != 2) {
                iVar8 = iVar8 + *piVar7;
            }
            if (iVar2 != 3) {
                iVar8 = iVar8 + piVar7[1];
            }
            if (iVar2 != 4) {
                iVar8 = iVar8 + piVar7[2];
            }
            if (iVar2 != 5) {
                iVar8 = iVar8 + piVar7[3];
            }
            if (iVar2 != 6) {
                iVar8 = iVar8 + piVar7[4];
            }
            if (iVar2 != 7) {
                iVar8 = iVar8 + piVar7[5];
            }
            if (iVar2 != 8) {
                iVar8 = iVar8 + piVar7[6];
            }
            aiStack_354[iVar2] = iVar8;
            iVar8 = 0;
            if (iVar2 != 0) {
                iVar8 = DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[0][iVar2];
            }
            if (iVar2 != 1) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[1][iVar2];
            }
            if (iVar2 != 2) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[2][iVar2];
            }
            if (iVar2 != 3) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[3][iVar2];
            }
            if (iVar2 != 4) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[4][iVar2];
            }
            if (iVar2 != 5) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalKillMatrix[5][iVar2];
            }
            if (iVar2 != 6) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[iVar2 + -0x1b];
            }
            if (iVar2 != 7) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[iVar2 + -0x12];
            }
            if (iVar2 != 8) {
                iVar8 = iVar8 + DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[iVar2 + -9];
            }
            aiStack_330[iVar2] = iVar8;
            piVar7 = piVar7 + 9;
            iVar2 = iVar2 + 1;
        } while ((int)piVar7 < 0x1a27210);
        iVar2 = 1;
        aiStack_398[0] = 0;
        aiStack_398[1] = 0;
        aiStack_398[2] = 0;
        aiStack_398[3] = 0;
        aiStack_398[4] = 0;
        aiStack_398[5] = 0;
        aiStack_398[6] = 0;
        aiStack_398[7] = 0;
        do {
            _highestRankingInDomain[iVar2 + 0x12] = iVar2;
            piVar7 = local_30c + iVar2;
            iVar8 = 0x10;
            do {
                *piVar7 = iVar2;
                piVar7 = piVar7 + 9;
                iVar8 = iVar8 + -1;
            } while (iVar8 != 0);
            iVar2 = iVar2 + 1;
        } while (iVar2 < 9);
        local_3c8 = 8;
        do {
            iVar2 = 1;
            if (1 < local_3c8) {
                do {
                    iVar8 = _highestRankingInDomain[iVar2 + 0x12];
                    iVar3 = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(iVar8);
                    iVar10 = _highestRankingInDomain[iVar2 + 0x13];
                    iVar4 = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(iVar10);
                    if ((iVar3 < iVar4)
                        || ((iVar3 == iVar4
                            && ((iVar3 = DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[iVar10],
                                iVar4 = DAT_GameSynchronyState::instance.finalResults.finalTimeAlive[iVar8],
                                iVar4 < iVar3
                                    || ((iVar4 == iVar3
                                        && (DAT_GameState::instance.mapAndTime.playerIsAlive[iVar8]
                                            < DAT_GameState::instance.mapAndTime.playerIsAlive[iVar10])))))))) {
                        _highestRankingInDomain[iVar2 + 0x12] = iVar10;
                        _highestRankingInDomain[iVar2 + 0x13] = iVar8;
                    }
                    iVar8 = local_30c[iVar2];
                    if (aiStack_354[iVar8] < aiStack_354[local_30c[iVar2 + 1]]) {
                        local_30c[iVar2] = local_30c[iVar2 + 1];
                        local_30c[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_1a4[iVar2];
                    if (aiStack_330[aiStack_1a4[iVar2 + 1]] < aiStack_330[iVar8]) {
                        aiStack_1a4[iVar2] = aiStack_1a4[iVar2 + 1];
                        aiStack_1a4[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_2e8[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[aiStack_2e8[iVar2 + 1]]) {
                        aiStack_2e8[iVar2] = aiStack_2e8[iVar2 + 1];
                        aiStack_2e8[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_2c4[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[aiStack_2c4[iVar2 + 1]]) {
                        aiStack_2c4[iVar2] = aiStack_2c4[iVar2 + 1];
                        aiStack_2c4[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_2a0[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalGold[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalGold[aiStack_2a0[iVar2 + 1]]) {
                        aiStack_2a0[iVar2] = aiStack_2a0[iVar2 + 1];
                        aiStack_2a0[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_27c[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[aiStack_27c[iVar2 + 1]]) {
                        aiStack_27c[iVar2] = aiStack_27c[iVar2 + 1];
                        aiStack_27c[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_258[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[aiStack_258[iVar2 + 1]]) {
                        aiStack_258[iVar2] = aiStack_258[iVar2 + 1];
                        aiStack_258[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_234[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[aiStack_234[iVar2 + 1]]) {
                        aiStack_234[iVar2] = aiStack_234[iVar2 + 1];
                        aiStack_234[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_210[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalIronProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalIronProduced[aiStack_210[iVar2 + 1]]) {
                        aiStack_210[iVar2] = aiStack_210[iVar2 + 1];
                        aiStack_210[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_1ec[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[aiStack_1ec[iVar2 + 1]]) {
                        aiStack_1ec[iVar2] = aiStack_1ec[iVar2 + 1];
                        aiStack_1ec[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_180[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[aiStack_180[iVar2 + 1]]) {
                        aiStack_180[iVar2] = aiStack_180[iVar2 + 1];
                        aiStack_180[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_15c[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[aiStack_15c[iVar2 + 1]]
                        < DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[iVar8]) {
                        aiStack_15c[iVar2] = aiStack_15c[iVar2 + 1];
                        aiStack_15c[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_138[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[aiStack_138[iVar2 + 1]]) {
                        aiStack_138[iVar2] = aiStack_138[iVar2 + 1];
                        aiStack_138[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_114[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[aiStack_114[iVar2 + 1]]) {
                        aiStack_114[iVar2] = aiStack_114[iVar2 + 1];
                        aiStack_114[iVar2 + 1] = iVar8;
                    }
                    iVar8 = aiStack_f0[iVar2];
                    if (DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[iVar8]
                        < DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[aiStack_f0[iVar2 + 1]]) {
                        aiStack_f0[iVar2] = aiStack_f0[iVar2 + 1];
                        aiStack_f0[iVar2 + 1] = iVar8;
                    }
                    iVar2 = iVar2 + 1;
                } while (iVar2 < local_3c8);
            }
            local_3c8 = local_3c8 + -1;
        } while (0 < local_3c8);
        _highestRankingInDomain[local_374[0]] = _highestRankingInDomain[local_374[0]] + 3;
        if ((10 < aiStack_354[local_30c[1]]) && (aiStack_354[local_30c[2]] * 2 < aiStack_354[local_30c[1]])) {
            _highestRankingInDomain[local_30c[1]] = _highestRankingInDomain[local_30c[1]] + 3;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[aiStack_2e8[1]];
        if ((2 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[aiStack_2e8[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_2e8[1]] = _highestRankingInDomain[aiStack_2e8[1]] + 2;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[aiStack_2c4[1]];
        if ((0x32 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[aiStack_2c4[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_2c4[1]] = _highestRankingInDomain[aiStack_2c4[1]] + 2;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalGold[aiStack_2a0[1]];
        if ((100 < iVar2) && (DAT_GameSynchronyState::instance.finalResults.finalGold[aiStack_2a0[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_2a0[1]] = _highestRankingInDomain[aiStack_2a0[1]] + 3;
        }
        sVar1 = DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[aiStack_27c[1]];
        if ((0x18 < sVar1)
            && (DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[aiStack_27c[2]] * 2 < (int)sVar1)) {
            _highestRankingInDomain[local_30c[1]] = _highestRankingInDomain[local_30c[1]] + 1;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[aiStack_258[1]];
        if ((100 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[aiStack_258[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_258[1]] = _highestRankingInDomain[aiStack_258[1]] + 1;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[aiStack_234[1]];
        if ((0x32 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[aiStack_234[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_234[1]] = _highestRankingInDomain[aiStack_234[1]] + 1;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalIronProduced[aiStack_210[1]];
        if ((10 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalIronProduced[aiStack_210[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_210[1]] = _highestRankingInDomain[aiStack_210[1]] + 1;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[aiStack_1ec[1]];
        if ((0x14 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[aiStack_1ec[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_1ec[1]] = _highestRankingInDomain[aiStack_1ec[1]] + 1;
        }
        iVar2 = DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[aiStack_180[1]];
        if ((0x14 < iVar2)
            && (DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[aiStack_180[2]] * 2 < iVar2)) {
            _highestRankingInDomain[aiStack_180[1]] = _highestRankingInDomain[aiStack_180[1]] + 1;
        }
        uVar9 = 0;
        if (DAT_GameSynchronyState::instance.finalResults.active[1] != 0) {
            uVar9 = 8;
        }
        _renderPlayer = 1;
        do {
            _highestRankingInDomain[_renderPlayer + 9] = _highestRankingInDomain[_renderPlayer] / 3;
            if (5 < _highestRankingInDomain[_renderPlayer] / 3) {
                _highestRankingInDomain[_renderPlayer + 9] = 5;
            }
            if ((uVar9 < 4) && (_highestRankingInDomain[_renderPlayer + 9] == 5)) {
                _highestRankingInDomain[_renderPlayer + 9] = 4;
            }
            _renderPlayer = _renderPlayer + 1;
        } while (_renderPlayer < 9);
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
        if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x, DAT_MenuHandlerState::instance.y,
                DAT_MenuHandlerState::instance.x + 800, DAT_MenuHandlerState::instance.y + 600, 0x10);
            /*
              added by script: "Greatest Lord"
             */
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner,
                DAT_PencilRenderCore::ptr)(0xe1, 1, DAT_MenuHandlerState::instance.x + 0x28, local_3d0, 0x2d0, 0x2d0);
        } else {
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBlendedBlackBox,
                DAT_PencilRenderCore::ptr)(DAT_MenuHandlerState::instance.x + -0x70,
                DAT_MenuHandlerState::instance.y + -0x54, DAT_MenuHandlerState::instance.x + 0x390,
                DAT_MenuHandlerState::instance.y + 0x2ac, 0x10);
            iVar2 = local_3d0;
            /*
              added by script: "Greatest Lord"
             */
            MACRO_CALL_MEMBER(
                OpenSHC::UI::Rendering::PencilRenderCore_Func::drawHeaderTextBanner, DAT_PencilRenderCore::ptr)(
                0xe1, 1, DAT_MenuHandlerState::instance.x + -0x68, local_3d0 + -0x1e, 0x3f0, 0);
            local_3d0 = iVar2 + 0x14;
        }
        iVar2 = local_3d0 + 0xac;
        DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
        local_3c8 = 0;
        local_3d0 = local_3d0 + 0xbe;
        do {
            iVar8 = local_3c4;
            switch (DAT_FinalResultsOrderByColumn::instance) {
            case 0:
                _renderPlayer = *(int*)((int)_highestRankingInDomain + local_3c8 + 0x4c);
                break;
            case 1:
                _renderPlayer = *(int*)((int)local_30c + local_3c8 + 4);
                break;
            case 2:
                _renderPlayer = *(int*)((int)aiStack_2e8 + local_3c8 + 4);
                break;
            case 3:
                _renderPlayer = *(int*)((int)aiStack_1a4 + local_3c8 + 4);
                break;
            case 4:
                _renderPlayer = *(int*)((int)aiStack_2a0 + local_3c8 + 4);
                break;
            case 5:
                _renderPlayer = *(int*)((int)aiStack_2c4 + local_3c8 + 4);
                break;
            case 6:
                _renderPlayer = *(int*)((int)aiStack_258 + local_3c8 + 4);
                break;
            case 7:
                _renderPlayer = *(int*)((int)aiStack_234 + local_3c8 + 4);
                break;
            case 8:
                _renderPlayer = *(int*)((int)aiStack_210 + local_3c8 + 4);
                break;
            case 9:
                _renderPlayer = *(int*)((int)aiStack_1ec + local_3c8 + 4);
                break;
            case 10:
                _renderPlayer = *(int*)((int)aiStack_27c + local_3c8 + 4);
                break;
            case 0xb:
                _renderPlayer = *(int*)((int)aiStack_180 + local_3c8 + 4);
                break;
            case 0xc:
                _renderPlayer = *(int*)((int)aiStack_15c + local_3c8 + 4);
                break;
            case 0xd:
                _renderPlayer = *(int*)((int)aiStack_138 + local_3c8 + 4);
                break;
            case 0xe:
                _renderPlayer = *(int*)((int)aiStack_114 + local_3c8 + 4);
                break;
            case 0xf:
                _renderPlayer = *(int*)((int)aiStack_f0 + local_3c8 + 4);
            }
            if (DAT_GameSynchronyState::instance.finalResults.active[_renderPlayer] != 0) {
                text = DAT_GameSynchronyState::instance.finalResults.names + _renderPlayer;
                DAT_TextManagerObject::instance.field12_0x30 = 1;
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderMultilineText6Unk, DAT_TextManagerObject::ptr)(
                    *text, local_3c4, local_3d0, 0x104,
                    (uint)((int)(DAT_RenderingDefinedData::instance
                            .ColorArray[DAT_BlendingDefinedData::instance.PlayerSlotUnitColor[_renderPlayer]])),
                    0, 0x12, 0);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::computeTextWidth, DAT_TextManagerObject::ptr)(
                    *text, 0x12);
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                if (DAT_GameState::instance.mapAndTime.playerIsAlive[_renderPlayer] != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0x8b, iVar8, iVar2 + -2);
                    iVar8 = iVar8 + 0x16;
                }
                if (0 < _highestRankingInDomain[_renderPlayer + 9]) {
                    iVar10 = _highestRankingInDomain[_renderPlayer + 9];
                    do {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0x8b, iVar8, iVar2 + -2);
                        iVar8 = iVar8 + 0x16;
                        iVar10 = iVar10 + -1;
                    } while (iVar10 != 0);
                }
                iVar10 = 0;
                if ('\0' < (char)DAT_GameSynchronyState::instance.finalResults.finalKilledLords[_renderPlayer]) {
                    do {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS3, 0x8a, iVar8, iVar2 + -5);
                        iVar10 = iVar10 + 1;
                        iVar8 = iVar8 + 0x16;
                    } while (
                        iVar10 < (char)DAT_GameSynchronyState::instance.finalResults.finalKilledLords[_renderPlayer]);
                }
                if (DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[_renderPlayer] != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        "(", iVar8 + 8, iVar2, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        OpenSHC::DE::SHCDE::GM_INTERFACE_ICONS2, 0x299, iVar8 + 0xe, iVar2 + -5);
                    blendStrength = 0;
                    BVar13 = FALSE;
                    iVar4 = 0x13;
                    BVar12 = 0xc2f0eb;
                    TVar11 = OpenSHC::Text::TTA_LEFT;
                    iVar10 = iVar8 + 0x1c;
                    iVar3 = iVar2;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_MONTHS, (int)(( int)(DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[_renderPlayer] % 0xc))), iVar10, iVar3, TVar11, BVar12, iVar4, BVar13, blendStrength);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalDateOfDeathInMonths[_renderPlayer] / 0xc,
                        iVar8 + 0x20, iVar2, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, TRUE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                        ")", iVar8 + 0x20, iVar2, OpenSHC::Text::TTA_LEFT, 0xc2f0eb, 0x13, TRUE, 0);
                }
                iVar10 = local_3c4;
                iVar8 = local_3d0;
                DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                if ((DAT_00ec082c::instance == 0) || (DAT_00ec082c::instance == 2)) {
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(aiStack_354[_renderPlayer], local_3c4 + 0x117, local_3d0,
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderNumberToScreen2,
                        DAT_TextManagerObject::ptr)(aiStack_330[_renderPlayer], iVar10 + 0x151, iVar8,
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalGold[_renderPlayer], iVar10 + 0x18b, iVar8,
                        OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalFoodProduced[_renderPlayer], iVar10 + 0x1c5,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalWoodProduced[_renderPlayer], iVar10 + 0x1ff,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalStoneProduced[_renderPlayer], iVar10 + 0x239,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalIronProduced[_renderPlayer], iVar10 + 0x273,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalPitchProduced[_renderPlayer], iVar10 + 0x2ad,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalWeaponsProduced[_renderPlayer],
                        iVar10 + 0x2e7, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                }
                if ((DAT_00ec082c::instance == 1) || (DAT_00ec082c::instance == 2)) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        (int)DAT_GameSynchronyState::instance.finalResults.finalMaxPopulation[_renderPlayer],
                        local_3cc + 0x117 + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_SCREEN_MENU;
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3,
                        (int)((
                            int)(((char)DAT_GameSynchronyState::instance.finalResults.finalMaxGoodThings[_renderPlayer]
                                         * 6
                                     - (char)
                                         DAT_GameSynchronyState::instance.finalResults.finalMaxBadThings[_renderPlayer])
                            + 0x8c)),
                        local_3cc + 0x14a + iVar10, iVar8, OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_3, 0xb0, 0);
                    DAT_TextureRenderCoreObject::instance.drawBufferChoiceValue
                        = OpenSHC::Rendering::Enums::RT_MAP_GAME;
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalBuildingsBurned[_renderPlayer],
                        local_3cc + 0x18b + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalBuidingsDestroyed[_renderPlayer],
                        local_3cc + 0x1c5 + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    if (DAT_00ec082c::instance == 1) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[_renderPlayer],
                            local_3cc + 0x1ff + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[_renderPlayer],
                            local_3cc + 0x239 + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                        MACRO_CALL_MEMBER(
                            OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                            DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[_renderPlayer],
                            local_3cc + 0x273 + iVar10, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    }
                }
                if (DAT_00ec082c::instance == 3) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalTroopsProduced[_renderPlayer],
                        iVar10 + 0x1ff, iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalGoodsRecieved[_renderPlayer], iVar10 + 0x239,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                    MACRO_CALL_MEMBER(
                        OpenSHC::Text::TextManager_Func::renderNumberToScreen2, DAT_TextManagerObject::ptr)(
                        DAT_GameSynchronyState::instance.finalResults.finalGoodsSent[_renderPlayer], iVar10 + 0x273,
                        iVar8, OpenSHC::Text::TTA_CENTER, 0xc2f0eb, 0x12, FALSE, 0);
                }
                local_3d0 = iVar8 + 0x2d;
                iVar2 = iVar2 + 0x2d;
            }
            local_3c8 = local_3c8 + 4;
        } while (local_3c8 < 0x20);
        if ((char)INT_00eb0e44::instance == '\0') {
            if ((DAT_00eb9af8::instance == 0) && (DAT_GameSynchronyState::instance.finalResults.yearStart != 0)) {
                iVar8 = DAT_GameSynchronyState::instance.finalResults.yearEnd;
                pcVar5 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameSynchronyState::instance.finalResults.monthEnd);
                iVar2 = DAT_GameSynchronyState::instance.finalResults.yearStart;
                pcVar6 = MACRO_CALL_MEMBER(
                    OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(
                    OpenSHC::DE::SHCDE::TEXT_MONTHS, DAT_GameSynchronyState::instance.finalResults.monthStart);
                MACRO_CALL(OpenSHC::OS_Func::_sprintf)((char*)local_30c, "%s %d - %s %d", pcVar6, iVar2, pcVar5, iVar8);
                iVar2 = DAT_MissionDefinedData::instance.field23_0x7d4[DAT_00eb9af8::instance][1];
                offsetIndex = (OpenSHC::DE::SHCDE::eTextSections)(DAT_MissionDefinedData::instance
                        .field23_0x7d4[DAT_00eb9af8::instance][0]);
                iVar10 = 0;
                BVar13 = FALSE;
                iVar8 = 0x11;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_CENTER;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    iVar3 = DAT_MenuHandlerState::instance.y + 0x221;
                    iVar4 = DAT_MenuHandlerState::instance.x + 0x1c9;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(offsetIndex, iVar2), iVar4, iVar3, TVar11, BVar12, iVar8, BVar13, iVar10);
                    iVar8 = 0;
                    BVar13 = FALSE;
                    iVar2 = 0x12;
                    BVar12 = 0xccfaff;
                    TVar11 = OpenSHC::Text::TTA_CENTER;
                    iVar10 = DAT_MenuHandlerState::instance.y + 0x23f;
                    iVar3 = DAT_MenuHandlerState::instance.x + 0x1c9;
                    piVar7 = local_30c;
                } else {
                    iVar3 = DAT_MenuHandlerState::instance.y + 0x25a;
                    iVar4 = DAT_MenuHandlerState::instance.x + 0x19c;
                    MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(offsetIndex, iVar2), iVar4, iVar3, TVar11, BVar12, iVar8, BVar13, iVar10);
                    iVar8 = 0;
                    BVar13 = FALSE;
                    iVar2 = 0x12;
                    BVar12 = 0xccfaff;
                    TVar11 = OpenSHC::Text::TTA_CENTER;
                    iVar10 = DAT_MenuHandlerState::instance.y + 0x278;
                    iVar3 = DAT_MenuHandlerState::instance.x + 0x19c;
                    piVar7 = local_30c;
                }
            } else {
                iVar8 = 0;
                BVar13 = FALSE;
                iVar2 = 0x11;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_CENTER;
                if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                    iVar10 = DAT_MenuHandlerState::instance.y + 0x230;
                    iVar3 = DAT_MenuHandlerState::instance.x + 0x1c9;
                } else {
                    iVar10 = DAT_MenuHandlerState::instance.y + 0x269;
                    iVar3 = DAT_MenuHandlerState::instance.x + 0x19c;
                }
                piVar7 = (int*)MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset,
                    DAT_TextManagerObject::ptr)((OpenSHC::DE::SHCDE::eTextSections)(DAT_MissionDefinedData::instance
                                                        .field23_0x7d4[DAT_00eb9af8::instance][0]),
                    (int)((int)((OpenSHC::DE::SHCDE::eTextSections)
                            DAT_MissionDefinedData::instance.field23_0x7d4[DAT_00eb9af8::instance][1])));
            }
            MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                (char*)piVar7, iVar3, iVar10, TVar11, BVar12, iVar2, BVar13, iVar8);
        }
        DAT_00eb9af8::instance = DAT_FinalResultsOrderByColumn::instance;
        if ((char)INT_00eb0e44::instance != '\0') {
            iVar2 = MACRO_CALL(OpenSHC::UI::GreatestLord_Func::ComputeSkMasterScore)(
                DAT_GameSynchronyState::instance.currentPlayerSlotID);
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(local_68, " : %d        ", iVar2);
            MACRO_CALL(OpenSHC::OS_Func::_sprintf)(
                local_cc, " :   -M%d-%d.sav", DAT_GameCore::instance.extremeTrailProgress + 1, DAT_00ed3118::instance);
            iVar8 = 0;
            BVar13 = FALSE;
            iVar2 = 0x12;
            BVar12 = 0xccfaff;
            TVar11 = OpenSHC::Text::TTA_LEFT;
            if (DAT_WindowAndDirectDraw::instance.currentGameResolution == OpenSHC::Rendering::SRE_800x600) {
                iVar10 = DAT_MenuHandlerState::instance.y + 0x229;
                iVar3 = DAT_MenuHandlerState::instance.x + 0x32;
                /*
                  added by script: "Extreme Score"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1b), iVar3, iVar10, TVar11, BVar12, iVar2, BVar13, iVar8);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_68, DAT_MenuHandlerState::instance.x + 0x32, DAT_MenuHandlerState::instance.y + 0x229,
                    OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                iVar3 = 0;
                BVar13 = TRUE;
                iVar10 = 0x12;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar2 = DAT_MenuHandlerState::instance.y + 0x229;
                iVar8 = DAT_MenuHandlerState::instance.x + 0x32;
                /*
                  added by script: "Save File"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1c), iVar8, iVar2, TVar11, BVar12, iVar10, BVar13, iVar3);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_cc, DAT_MenuHandlerState::instance.x + 0x32, DAT_MenuHandlerState::instance.y + 0x229,
                    OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                iVar4 = 0;
                BVar13 = FALSE;
                iVar3 = 0x12;
                iVar2 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x32 + DAT_MenuHandlerState::instance.x;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar10 = DAT_MenuHandlerState::instance.y + 0x23f;
                iVar8 = DAT_MenuHandlerState::instance.x + 0x32;
                /*
                  added by script: "To submit this score, visit"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1d), iVar8, iVar10, TVar11, BVar12, iVar3, BVar13, iVar4);
                iVar8 = DAT_MenuHandlerState::instance.y + 0x23f;
                iVar4 = 0;
                BVar13 = TRUE;
                iVar3 = 0x12;
                BVar12 = 0xffffff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar10 = DAT_MenuHandlerState::instance.x + 0x38;
                /*
                  added by script: "www.fireflyworlds.com"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1e), iVar10, iVar8, TVar11, BVar12, iVar3, BVar13, iVar4);
                iVar8 = DAT_TextManagerObject::instance.currentXOffset_0x0 + 0x38 + DAT_MenuHandlerState::instance.x;
                if (iVar2 < iVar8) {
                    iVar2 = iVar8;
                }
                iVar8 = DAT_MenuHandlerState::instance.y + 0x253;
                iVar10 = DAT_MenuHandlerState::instance.y + 0x222;
                iVar3 = DAT_MenuHandlerState::instance.x + 0x1e;
            } else {
                iVar10 = DAT_MenuHandlerState::instance.y + 0x262;
                iVar3 = DAT_MenuHandlerState::instance.x + -0x2a;
                /*
                  added by script: "Extreme Score"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1b), iVar3, iVar10, TVar11, BVar12, iVar2, BVar13, iVar8);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_68, DAT_MenuHandlerState::instance.x + -0x2a, DAT_MenuHandlerState::instance.y + 0x262,
                    OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                iVar3 = 0;
                BVar13 = TRUE;
                iVar10 = 0x12;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar2 = DAT_MenuHandlerState::instance.y + 0x262;
                iVar8 = DAT_MenuHandlerState::instance.x + -0x2a;
                /*
                  added by script: "Save File"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1c), iVar8, iVar2, TVar11, BVar12, iVar10, BVar13, iVar3);
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(
                    local_cc, DAT_MenuHandlerState::instance.x + -0x2a, DAT_MenuHandlerState::instance.y + 0x262,
                    OpenSHC::Text::TTA_LEFT, 0xccfaff, 0x12, TRUE, 0);
                iVar4 = 0;
                BVar13 = FALSE;
                iVar3 = 0x12;
                iVar2 = DAT_TextManagerObject::instance.currentXOffset_0x0 + -0x2a + DAT_MenuHandlerState::instance.x;
                BVar12 = 0xccfaff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar10 = DAT_MenuHandlerState::instance.y + 0x278;
                iVar8 = DAT_MenuHandlerState::instance.x + -0x2a;
                /*
                  added by script: "To submit this score, visit"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1d), iVar8, iVar10, TVar11, BVar12, iVar3, BVar13, iVar4);
                iVar8 = DAT_MenuHandlerState::instance.y + 0x278;
                iVar4 = 0;
                BVar13 = TRUE;
                iVar3 = 0x12;
                BVar12 = 0xffffff;
                TVar11 = OpenSHC::Text::TTA_LEFT;
                iVar10 = DAT_MenuHandlerState::instance.x + -0x24;
                /*
                  added by script: "www.fireflyworlds.com"
                 */
                MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::renderTextToScreen, DAT_TextManagerObject::ptr)(MACRO_CALL_MEMBER(OpenSHC::Text::TextManager_Func::getTextStringInGroupAtOffset, DAT_TextManagerObject::ptr)(OpenSHC::DE::SHCDE::TEXT_SKIRMISH_CHOOSE2, 0x1e), iVar10, iVar8, TVar11, BVar12, iVar3, BVar13, iVar4);
                iVar8 = DAT_TextManagerObject::instance.currentXOffset_0x0 + -0x24 + DAT_MenuHandlerState::instance.x;
                if (iVar2 < iVar8) {
                    iVar2 = iVar8;
                }
                iVar8 = DAT_MenuHandlerState::instance.y + 0x28c;
                iVar10 = DAT_MenuHandlerState::instance.y + 0x25b;
                iVar3 = DAT_MenuHandlerState::instance.x + -0x3e;
            }
            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::PencilRenderCore_Func::drawBorderBox, DAT_PencilRenderCore::ptr)(
                iVar3, iVar10, iVar2 + 0x14, iVar8, (ushort)((int)(COL_WHITE::instance.shortValue)));
        };
        return;
    }

}
}
