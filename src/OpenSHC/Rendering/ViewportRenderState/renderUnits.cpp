#include "OpenSHC/Rendering/ViewportRenderState.func.hpp"
#include "OpenSHC/UI/Rendering/TextureRenderCore.func.hpp"
#include "OpenSHC/DE/SHCDE/eGM.hpp"
#include "OpenSHC/Game/GameMode.hpp"
#include "OpenSHC/IO/Graphics/GmID.hpp"
#include "OpenSHC/Map/Units/States/UnitState.hpp"
#include "OpenSHC/Map/Units/States/UnitStateShort.hpp"
#include "OpenSHC/Map/Units/UnitType.hpp"
#include "OpenSHC/Map/Units/UnitTypeShort.hpp"

#include "OpenSHC/Globals/COL_MAGENTA.hpp"
#include "OpenSHC/Globals/DAT_CurrentlyRenderedSpriteID.hpp"
#include "OpenSHC/Globals/DAT_GMImageSizes.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/GMTotalPicturesProcessed.hpp"

namespace OpenSHC {
namespace Rendering {

    using OpenSHC::DE::SHCDE::eGM;
    using OpenSHC::Game::GameMode;
    using OpenSHC::IO::Graphics::GmID;
    using OpenSHC::Map::Units::UnitType;
    using OpenSHC::Map::Units::UnitTypeShort;
    using OpenSHC::Map::Units::States::UnitState;
    using OpenSHC::Map::Units::States::UnitStateShort;

    // FUNCTION: STRONGHOLDCRUSADER 0x004E7810
    void ViewportRenderState::renderUnits()
    {
        ushort savedPixelColor;
        short graphicSize;
        UnitTypeShort unitType;
        UnitStateShort unitState;
        int overlayX;
        uint animationTick;
        int overlayY;
        int maskImageID;
        int overlayImageID;
        int _drawX;
        int _drawY;
        int _imageID;
        uint _blendStrength;
        int _unitID;
        int _gmID;
        int _renderBatchSize;
        int _alpha;

        int renderCount5 = this->unitRender5;
        int renderCount4 = this->unitRender4;
        int renderCount3 = this->unitRender3;
        int renderCount2 = this->unitRender2;
        int renderCount1 = this->unitRender1;
        this->unitBatchedRenderCounterUntil6 = this->unitBatchedRenderCounterUntil6 + 1;
        _drawX = 0;
        _drawY = 0;
        _renderBatchSize = 0;
        _unitID = 0;
        _imageID = 0;
        _blendStrength = 0;
        _gmID = 0;
        if (5 < this->unitBatchedRenderCounterUntil6) {
            this->unitBatchedRenderCounterUntil6 = 1;
        }
        if (this->unitBatchedRenderCounterUntil6 == 1) {
            this->unitRender1 = 0;
            _renderBatchSize = renderCount1;
        } else if (this->unitBatchedRenderCounterUntil6 == 2) {
            this->unitRender2 = 0;
            _renderBatchSize = renderCount2;
        } else if (this->unitBatchedRenderCounterUntil6 == 3) {
            this->unitRender3 = 0;
            _renderBatchSize = renderCount3;
        } else if (this->unitBatchedRenderCounterUntil6 == 4) {
            this->unitRender4 = 0;
            _renderBatchSize = renderCount4;
        } else if (this->unitBatchedRenderCounterUntil6 == 5) {
            this->unitRender5 = 0;
            _renderBatchSize = renderCount5;
        }
        if (0 < _renderBatchSize) {
            for (int _batchedUnitID = 0; _batchedUnitID < _renderBatchSize; _batchedUnitID++) {
                switch (this->unitBatchedRenderCounterUntil6) {
                case 1:
                    _unitID = this->unitBatch1[_batchedUnitID].unitIDOrStatus;
                    DAT_RenderedUnitOwner::instance = this->unitBatch1[_batchedUnitID].ownerColor;
                    DAT_CurrentlyRenderedSpriteID::instance = this->unitBatch1[_batchedUnitID].spriteID;
                    _imageID = this->unitBatch1[_batchedUnitID].imageID;
                    _drawY = this->unitBatch1[_batchedUnitID].drawY;
                    _drawX = this->unitBatch1[_batchedUnitID].drawX;
                    _blendStrength = this->unitBatch1[_batchedUnitID].blendStrength;
                    _gmID = this->unitBatch1[_batchedUnitID].gmID;
                    break;
                case 2:
                    _unitID = this->unitBatch2[_batchedUnitID].unitIDOrStatus;
                    DAT_RenderedUnitOwner::instance = this->unitBatch2[_batchedUnitID].ownerColor;
                    DAT_CurrentlyRenderedSpriteID::instance = this->unitBatch2[_batchedUnitID].spriteID;
                    _imageID = this->unitBatch2[_batchedUnitID].imageID;
                    _drawY = this->unitBatch2[_batchedUnitID].drawY;
                    _drawX = this->unitBatch2[_batchedUnitID].drawX;
                    _blendStrength = this->unitBatch2[_batchedUnitID].blendStrength;
                    _gmID = this->unitBatch2[_batchedUnitID].gmID;
                    break;
                case 3:
                    _unitID = this->unitBatch3[_batchedUnitID].unitIDOrStatus;
                    DAT_RenderedUnitOwner::instance = this->unitBatch3[_batchedUnitID].ownerColor;
                    DAT_CurrentlyRenderedSpriteID::instance = this->unitBatch3[_batchedUnitID].spriteID;
                    _imageID = this->unitBatch3[_batchedUnitID].imageID;
                    _drawY = this->unitBatch3[_batchedUnitID].drawY;
                    _drawX = this->unitBatch3[_batchedUnitID].drawX;
                    _blendStrength = this->unitBatch3[_batchedUnitID].blendStrength;
                    _gmID = this->unitBatch3[_batchedUnitID].gmID;
                    break;
                case 4:
                    _unitID = this->unitBatch4[_batchedUnitID].unitIDOrStatus;
                    DAT_RenderedUnitOwner::instance = this->unitBatch4[_batchedUnitID].ownerColor;
                    DAT_CurrentlyRenderedSpriteID::instance = this->unitBatch4[_batchedUnitID].spriteID;
                    _imageID = this->unitBatch4[_batchedUnitID].imageID;
                    _drawY = this->unitBatch4[_batchedUnitID].drawY;
                    _drawX = this->unitBatch4[_batchedUnitID].drawX;
                    _blendStrength = this->unitBatch4[_batchedUnitID].blendStrength;
                    _gmID = this->unitBatch4[_batchedUnitID].gmID;
                    break;
                case 5:
                    _unitID = this->unitBatch5[_batchedUnitID].unitIDOrStatus;
                    DAT_RenderedUnitOwner::instance = this->unitBatch5[_batchedUnitID].ownerColor;
                    DAT_CurrentlyRenderedSpriteID::instance = this->unitBatch5[_batchedUnitID].spriteID;
                    _imageID = this->unitBatch5[_batchedUnitID].imageID;
                    _drawY = this->unitBatch5[_batchedUnitID].drawY;
                    _drawX = this->unitBatch5[_batchedUnitID].drawX;
                    _blendStrength = this->unitBatch5[_batchedUnitID].blendStrength;
                    _gmID = this->unitBatch5[_batchedUnitID].gmID;
                }
                if (_unitID == -1) {
                    if ((int)_blendStrength < 0) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance, _imageID,
                            _drawX, _drawY, (GmID)((int)(DAT_CurrentlyRenderedSpriteID::instance)), (int)((int)(_gmID)),
                            (int)((int)(-1 - _blendStrength)));
                    } else if (_blendStrength == 0) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                            (eGM)DAT_CurrentlyRenderedSpriteID::instance, _imageID, _drawX, _drawY);
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance, _imageID,
                            _drawX, _drawY, (int)((int)(_blendStrength)));
                    }
                } else if (_unitID == 0) {
                    if ((_blendStrength & 4) != 0) {
                        DAT_RenderedUnitOwner::instance = ~-(uint)((_blendStrength & 0x10) != 0)
                            & DAT_GameSynchronyState::instance.currentPlayerSlotID;
                        DAT_CurrentlyRenderedSpriteID::instance = _gmID;
                    }
                    if ((_blendStrength & 0x20) == 0) {
                        if ((_blendStrength & 0xffff0000) == 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)((eGM)_gmID, _imageID, _drawX, _drawY);
                        } else {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                DAT_TextureRenderCoreObject::ptr)(
                                (GmID)_gmID, _imageID, _drawX, _drawY, (int)((int)(_blendStrength >> 0x10)));
                        }
                    } else {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)((GmID)_gmID, _imageID, _drawX, _drawY,
                            (GmID)((int)(_gmID)), ((int)_blendStrength >> 0x10) + _imageID, 0);
                    }
                } else {
                    savedPixelColor = *this->viewportState.ptrColor;
                    *this->viewportState.ptrColor = COL_MAGENTA::instance.shortValue;
                    _alpha = (int)(char)DAT_UnitsState::instance.units[_unitID].disappearFadeAlphaCountdown;
                    if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                        if (((DAT_GameState::instance.mapAndTime
                                     .playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                                 != DAT_GameState::instance.mapAndTime
                                     .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID])
                                && (120 < DAT_UnitsState::instance.units[_unitID].assassinsMicroDistanceToEnemyUnk))
                            && ((DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                                || (DAT_UnitsState::instance.units[_unitID].idleCounterUnk < 2400)))) {
                            _alpha = 0x20 - (0x20 - _alpha) / 2;
                        }
                        overlayX = DAT_UnitsState::instance.units[_unitID].imageID2;
                        if (overlayX != 0) {
                            overlayY = (0x20 - _alpha) / 3;
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                                DAT_TextureRenderCoreObject::ptr)(_drawX, _drawY, _imageID,
                                (int)((int)(_blendStrength)),
                                (byte*)((
                                    int)((DAT_GMImageSizes::instance[GMTotalPicturesProcessed::instance[(
                                                                         int)DAT_CurrentlyRenderedSpriteID::instance]
                                              + overlayX + 0x1c51f]
                                    + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                (0x10 - overlayY) * 2);
                            graphicSize = DAT_UnitsState::instance.units[_unitID].drawYOffset;
                            if (graphicSize != 0) {
                                MACRO_CALL_MEMBER(
                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                                    DAT_TextureRenderCoreObject::ptr)(_drawX, _drawY, _imageID,
                                    (int)((int)(_blendStrength)),
                                    (byte*)((int)((
                                        DAT_GMImageSizes::instance[GMTotalPicturesProcessed::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                            + (int)graphicSize + 0x1c51f]
                                        + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))),
                                    0x20 - overlayY);
                            }
                        }
                    }
                    if (_alpha == 0) {
                        if (DAT_UnitsState::instance.units[_unitID].graphicSize == 4) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::Rendering::ViewportRenderState_Func::renderAssassinClimbingOverlay, this)(
                                _unitID);
                        }
                        graphicSize = DAT_UnitsState::instance.units[_unitID].field59_0x86;
                        if (graphicSize < 0) {
                            overlayX = 0;
                        } else {
                            overlayX = (int)graphicSize;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                            DAT_TextureRenderCoreObject::ptr)(
                            _drawX, graphicSize + _drawY, _imageID, _blendStrength - overlayX, (byte*)_gmID);
                        graphicSize = DAT_UnitsState::instance.units[_unitID].graphicSize;
                        if ((graphicSize != 4) && (1 < graphicSize)) {
                            DAT_RenderedUnitOwner::instance
                                = (uint)DAT_UnitsState::instance.units[_unitID].displayColorPlayerID;
                            DAT_CurrentlyRenderedSpriteID::instance
                                = (int)DAT_UnitsState::instance.units[_unitID].gmIDUnk;
                            overlayX = DAT_UnitsState::instance.units[_unitID].imageIDUnk;
                            if (0 < overlayX) {
                                graphicSize = DAT_UnitsState::instance.units[_unitID].field60_0x88;
                                if (graphicSize < 0) {
                                    overlayY = 0;
                                } else {
                                    overlayY = (int)graphicSize;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                    DAT_TextureRenderCoreObject::ptr)(_drawX, graphicSize + _drawY, _imageID,
                                    _blendStrength - overlayY,
                                    (byte*)((int)((
                                        DAT_GMImageSizes::instance[GMTotalPicturesProcessed::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                            + overlayX + 0x1c51f]
                                        + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                            }
                        }
                        if (2 < DAT_UnitsState::instance.units[_unitID].graphicSize) {
                            overlayX = DAT_UnitsState::instance.units[_unitID].imageID2;
                            if (0 < overlayX) {
                                graphicSize = DAT_UnitsState::instance.units[_unitID].drawYOffset;
                                if (graphicSize < 0) {
                                    overlayY = 0;
                                } else {
                                    overlayY = (int)graphicSize;
                                }
                                MACRO_CALL_MEMBER(
                                    OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                    DAT_TextureRenderCoreObject::ptr)(_drawX, graphicSize + _drawY, _imageID,
                                    _blendStrength - overlayY,
                                    (byte*)((int)((
                                        DAT_GMImageSizes::instance[GMTotalPicturesProcessed::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                            + overlayX + 0x1c51f]
                                        + (int)DAT_TextureRenderCoreObject::instance.gmProcessedImageData))));
                            }
                            if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                                unitType = DAT_UnitsState::instance.units[_unitID].unitType;
                                overlayX = _drawX;
                                overlayY = _drawY;
                                if ((unitType == OpenSHC::Map::Units::UT_S_TOWER)
                                    && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                                    switch (DAT_UnitsState::instance.units[_unitID]
                                            .facingDirectionMapOrientationCorrected) {
                                    case 0:
                                        overlayX = _drawX + 0x22;
                                        break;
                                    case 1:
                                        overlayX = _drawX + 0x2f;
                                        overlayY = _drawY + -0xc;
                                        break;
                                    case 2:
                                        overlayX = _drawX + 0x4b;
                                        overlayY = _drawY + -0x13;
                                        break;
                                    case 3:
                                        overlayX = _drawX + 0x65;
                                        overlayY = _drawY + -10;
                                        break;
                                    case 4:
                                        overlayX = _drawX + 0x70;
                                        overlayY = _drawY + 2;
                                        break;
                                    case 5:
                                        overlayX = _drawX + 100;
                                        overlayY = _drawY + 0x14;
                                        break;
                                    case 6:
                                        overlayX = _drawX + 0x46;
                                        overlayY = _drawY + 0x13;
                                        break;
                                    case 7:
                                        overlayX = _drawX + 0x2c;
                                        overlayY = _drawY + 0x17;
                                    }
                                } else if ((unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                    && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                                    switch (DAT_UnitsState::instance.units[_unitID]
                                            .facingDirectionMapOrientationCorrected) {
                                    case 0:
                                    case 1:
                                        overlayX = _drawX + 0x2c;
                                        overlayY = _drawY + -0x14;
                                        break;
                                    case 2:
                                        overlayX = _drawX + 0x31;
                                        overlayY = _drawY + -0x11;
                                        break;
                                    case 3:
                                        overlayX = _drawX + 0x29;
                                        overlayY = _drawY + -0xf;
                                        break;
                                    case 4:
                                        overlayX = _drawX + 0x22;
                                        overlayY = _drawY + -0x11;
                                        break;
                                    case 5:
                                    case 6:
                                        overlayX = _drawX + 0x20;
                                        overlayY = _drawY + -0x14;
                                        break;
                                    case 7:
                                        overlayX = _drawX + 0x28;
                                        overlayY = _drawY + -0x17;
                                    }
                                }
                                DAT_RenderedUnitOwner::instance = (uint)DAT_UnitsState::instance.units[_unitID].owner;
                                DAT_CurrentlyRenderedSpriteID::instance = 0xbd;
                                animationTick = DAT_UnitsState::instance.units[_unitID].fixedRng
                                        + DAT_GameState::instance.mapAndTime.totalGameTicksUnk
                                    & 0x8000003f;
                                if ((int)animationTick < 0) {
                                    animationTick = (animationTick - 1 | 0xffffffc0) + 1;
                                }
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL,
                                    (int)((int)(animationTick / 2 + 1)), overlayX, overlayY);
                            }
                        }
                        if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                            *this->viewportState.ptrColor = savedPixelColor;
                        } else {
                            this->viewportState.mouseRayUnitID = _unitID;
                            this->viewportState.mouseRayBuildingID = 0;
                        }
                    } else {
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                            DAT_TextureRenderCoreObject::ptr)(
                            _drawX, _drawY, _imageID, (int)((int)(_blendStrength)), (byte*)_gmID, _alpha);
                        if (*this->viewportState.ptrColor == COL_MAGENTA::instance.shortValue) {
                            *this->viewportState.ptrColor = savedPixelColor;
                        } else {
                            this->viewportState.mouseRayUnitID = _unitID;
                            this->viewportState.mouseRayBuildingID = 0;
                        }
                    }
                    if (0 < _unitID) {
                        if ((DAT_UnitsState::instance.units[_unitID].isSelected != 0)
                            && (DAT_UnitsState::instance.units[_unitID].usingTeleport == 0)) {
                            if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                                savedPixelColor = DAT_UnitsState::instance.units[_unitID].maxHealthRatingLord;
                                overlayX = (int)DAT_UnitsState::instance.units[_unitID].someDrawYOffset;
                                if (savedPixelColor == 0) {
                                    overlayX = overlayX + -6 + _drawY;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].healthbar + 0x11;
                                } else {
                                    overlayX = overlayX + -8 + _drawY;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].healthbar + 0xe4
                                        + savedPixelColor * 0xb;
                                }
                            } else {
                                overlayX = DAT_GameState::instance
                                               .playerDataArray[DAT_UnitsState::instance.units[_unitID].owner]
                                               .fearFactorLevel;
                                if (overlayX == 0) {
                                    overlayX = DAT_UnitsState::instance.units[_unitID].someDrawYOffset + -6;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].healthbar + 0x11;
                                } else {
                                    if (overlayX < 1) {
                                        overlayY = overlayX * -0xb + 0xad;
                                    } else {
                                        overlayY = overlayX * 0xb + 0x76;
                                    }
                                    overlayX = DAT_UnitsState::instance.units[_unitID].someDrawYOffset + -8;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].healthbar + overlayY;
                                }
                                overlayX = overlayX + _drawY;
                            }
                            maskImageID = (_imageID + -0x16) / 2 + _drawX;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_FLOATS, overlayY, maskImageID, overlayX);
                            if (((DAT_UnitsState::instance.units[_unitID].unitType
                                     == OpenSHC::Map::Units::UT_A_ASSASSIN)
                                    && (DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                                        == DAT_GameState::instance.mapAndTime
                                            .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]))
                                && ((DAT_UnitsState::instance.units[_unitID].assassinsMicroDistanceToEnemyUnk < 160
                                    || ((unitState = DAT_UnitsState::instance.units[_unitID].state.generic,
                                        unitState == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                                            || (unitState == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL)))))) {
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2,
                                    (int)((int)(447)), maskImageID + 2,
                                    DAT_UnitsState::instance.units[_unitID].someDrawYOffset + -0x1b + _drawY, 0x10);
                            }
                        }
                        savedPixelColor = DAT_UnitsState::instance.units[_unitID].field46_0x6e;
                        if (savedPixelColor != 0) {
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                (int)((int)(savedPixelColor + 0xd4)),
                                (int)((int)(DAT_UnitsState::instance.units[_unitID].drawX)),
                                (int)((int)(DAT_UnitsState::instance.units[_unitID].drawY + -0x36
                                    + DAT_UnitsState::instance.units[_unitID].someDrawYOffset)),
                                OpenSHC::IO::Graphics::GID_FLOATS_NEW, (int)((int)(savedPixelColor + 0xdc)), 0);
                            DAT_UnitsState::instance.units[_unitID].field46_0x6e = 0;
                        }
                        savedPixelColor = DAT_UnitsState::instance.units[_unitID].field45_0x6c;
                        if (savedPixelColor != 0) {
                            overlayY = 0;
                            overlayX = 0;
                            if (savedPixelColor == 1) {
                                maskImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0x30;
                                overlayX = DAT_UnitsState::instance.units[_unitID].drawY + -0x46
                                    + (int)DAT_UnitsState::instance.units[_unitID].someDrawYOffset;
                                overlayY = DAT_UnitsState::instance.units[_unitID].field22_0x2a + -0x35
                                    + (int)DAT_UnitsState::instance.units[_unitID].drawX;
                                overlayImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0x20;
                                MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                    DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                    overlayImageID, overlayY, overlayX, OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                    maskImageID, 0);
                            } else {
                                if (savedPixelColor == 2) {
                                    switch (DAT_UnitsState::instance.units[_unitID].unitType) {
                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                        overlayY = 0x29;
                                        overlayX = 0x3a;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                        overlayY = 0x4f;
                                        overlayX = 0x38;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                        overlayY = 0x2b;
                                        overlayX = 0x23;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                        overlayY = 0x24;
                                        overlayX = 0x3d;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                        overlayY = -3;
                                        overlayX = 0x3c;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                        overlayY = 0x13;
                                        overlayX = 0x24;
                                    }
                                    maskImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0x84;
                                    overlayX = ((int)DAT_UnitsState::instance.units[_unitID].drawY
                                                   + (int)DAT_UnitsState::instance.units[_unitID].someDrawYOffset)
                                        - overlayX;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].drawX + overlayY;
                                    overlayImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0x74;
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                        overlayImageID, overlayY, overlayX, OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                        maskImageID, 0);
                                }
                                if (savedPixelColor == 3) {
                                    switch (DAT_UnitsState::instance.units[_unitID].unitType) {
                                    case OpenSHC::Map::Units::UT_S_CATAPULT:
                                        overlayY = 0x29;
                                        overlayX = 0x3a;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_TREBUCHET:
                                    case OpenSHC::Map::Units::UT_S_TOWER:
                                        overlayY = 0x4f;
                                        overlayX = 0x38;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_MANGONEL:
                                        overlayY = 0x2b;
                                        overlayX = 0x23;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                                        overlayY = 0x24;
                                        overlayX = 0x3d;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_SHIELD:
                                        overlayY = -3;
                                        overlayX = 0x3c;
                                        break;
                                    case OpenSHC::Map::Units::UT_S_BALLISTA:
                                    case OpenSHC::Map::Units::UT_S_FBALLISTA:
                                        overlayY = 0x13;
                                        overlayX = 0x24;
                                    }
                                    maskImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0xa4;
                                    overlayX = ((int)DAT_UnitsState::instance.units[_unitID].drawY
                                                   + (int)DAT_UnitsState::instance.units[_unitID].someDrawYOffset)
                                        - overlayX;
                                    overlayY = DAT_UnitsState::instance.units[_unitID].drawX + overlayY;
                                    overlayImageID = DAT_TileMapState::instance.field161_0x5549c0 + 0x94;
                                    MACRO_CALL_MEMBER(
                                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                        overlayImageID, overlayY, overlayX, OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                                        maskImageID, 0);
                                }
                            }
                            DAT_UnitsState::instance.units[_unitID].field45_0x6c = 0;
                        }
                    }
                }
            }
        }
    }

}
}
