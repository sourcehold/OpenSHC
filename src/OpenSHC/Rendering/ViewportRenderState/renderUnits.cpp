#include "../ViewportRenderState.func.hpp"

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
#include "OpenSHC/Globals/DAT_GMImageOffsets.hpp"
#include "OpenSHC/Globals/DAT_GameState.hpp"
#include "OpenSHC/Globals/DAT_GameSynchronyState.hpp"
#include "OpenSHC/Globals/DAT_RenderedUnitOwner.hpp"
#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_TileMapState.hpp"
#include "OpenSHC/Globals/DAT_UnitsState.hpp"
#include "OpenSHC/Globals/GMFirstPictureIndex.hpp"

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
        short graphicSize;
        UnitTypeShort unitType;
        int overlayX;
        int overlayY;

        this->unitBatchedRenderCounterUntil6 = this->unitBatchedRenderCounterUntil6 + 1;
        int _drawX = 0;
        int _drawY = 0;
        int _renderBatchSize = 0;
        int _unitID = 0;
        int _imageID = 0;
        int _blendStrength = 0;
        int _gmID = 0;
        if (5 < this->unitBatchedRenderCounterUntil6) {
            this->unitBatchedRenderCounterUntil6 = 1;
        }
        if (this->unitBatchedRenderCounterUntil6 == 1) {
            _renderBatchSize = this->unitRender1;
            this->unitRender1 = 0;
        } else if (this->unitBatchedRenderCounterUntil6 == 2) {
            _renderBatchSize = this->unitRender2;
            this->unitRender2 = 0;
        } else if (this->unitBatchedRenderCounterUntil6 == 3) {
            _renderBatchSize = this->unitRender3;
            this->unitRender3 = 0;
        } else if (this->unitBatchedRenderCounterUntil6 == 4) {
            _renderBatchSize = this->unitRender4;
            this->unitRender4 = 0;
        } else if (this->unitBatchedRenderCounterUntil6 == 5) {
            _renderBatchSize = this->unitRender5;
            this->unitRender5 = 0;
        }
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
                if (_blendStrength < 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)((GmID)DAT_CurrentlyRenderedSpriteID::instance, _imageID,
                        _drawX, _drawY, (GmID)(DAT_CurrentlyRenderedSpriteID::instance), _gmID, -1 - _blendStrength);
                } else if (_blendStrength == 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM, DAT_TextureRenderCoreObject::ptr)(
                        (eGM)DAT_CurrentlyRenderedSpriteID::instance, _imageID, _drawX, _drawY);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)(
                        (GmID)DAT_CurrentlyRenderedSpriteID::instance, _imageID, _drawX, _drawY, _blendStrength);
                }
            } else if (_unitID != 0) {
                ushort savedPixelColor = *this->viewportState.ptrColor;
                *this->viewportState.ptrColor = COL_MAGENTA::instance.ushortValue;
                int _alpha = (int)(char)DAT_UnitsState::instance.units[_unitID].disappearFadeAlphaCountdown;
                if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN) {
                    if (DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                            != DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        && 120 < DAT_UnitsState::instance.units[_unitID].assassinsMicroDistanceToEnemyUnk
                        && (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY
                            || (DAT_UnitsState::instance.units[_unitID].idleCounterUnk <= 2400))) {
                        _alpha = 32 - (32 - _alpha) / 2;
                    }
                    overlayX = DAT_UnitsState::instance.units[_unitID].imageID2;
                    if (overlayX != 0) {
                        overlayY = (32 - _alpha) / 3;
                        MACRO_CALL_MEMBER(
                            OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                            DAT_TextureRenderCoreObject::ptr)(_drawX, _drawY, _imageID, _blendStrength,
                            DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                + DAT_GMImageOffsets::instance[GMFirstPictureIndex::instance[(
                                                                   int)DAT_CurrentlyRenderedSpriteID::instance]
                                    + overlayX - 1],
                            (16 - overlayY) * 2);
                        graphicSize = DAT_UnitsState::instance.units[_unitID].drawYOffset;
                        if (graphicSize != 0) {
                            MACRO_CALL_MEMBER(
                                OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                                DAT_TextureRenderCoreObject::ptr)(_drawX, _drawY, _imageID, _blendStrength,
                                DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                    + DAT_GMImageOffsets::instance[GMFirstPictureIndex::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                        + graphicSize - 1],
                                32 - overlayY);
                        }
                    }
                }
                if (_alpha != 0) {
                    MACRO_CALL_MEMBER(
                        OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationWithBlendingUnk,
                        DAT_TextureRenderCoreObject::ptr)(
                        _drawX, _drawY, _imageID, _blendStrength, (byte*)_gmID, _alpha);
                    if (*this->viewportState.ptrColor != COL_MAGENTA::instance.ushortValue) {
                        this->viewportState.mouseRayUnitID = _unitID;
                        this->viewportState.mouseRayBuildingID = 0;
                    } else {
                        *this->viewportState.ptrColor = savedPixelColor;
                    }
                } else {
                    if (DAT_UnitsState::instance.units[_unitID].graphicSize == 4) {
                        MACRO_CALL_MEMBER(
                            OpenSHC::Rendering::ViewportRenderState_Func::renderAssassinClimbingOverlay, this)(_unitID);
                    }
                    graphicSize = DAT_UnitsState::instance.units[_unitID].field_0x86;
                    if (graphicSize < 0) {
                        overlayX = 0;
                    } else {
                        overlayX = graphicSize;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                        DAT_TextureRenderCoreObject::ptr)(
                        _drawX, graphicSize + _drawY, _imageID, _blendStrength - overlayX, (byte*)_gmID);
                    graphicSize = DAT_UnitsState::instance.units[_unitID].graphicSize;
                    if (graphicSize != 4 && graphicSize >= 2) {
                        DAT_RenderedUnitOwner::instance
                            = (uint)DAT_UnitsState::instance.units[_unitID].displayColorPlayerID;
                        DAT_CurrentlyRenderedSpriteID::instance = DAT_UnitsState::instance.units[_unitID].gmIDUnk;
                        overlayX = DAT_UnitsState::instance.units[_unitID].imageIDUnk;
                        if (0 < overlayX) {
                            graphicSize = DAT_UnitsState::instance.units[_unitID].field_0x88;
                            if (graphicSize < 0) {
                                overlayY = 0;
                            } else {
                                overlayY = graphicSize;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                DAT_TextureRenderCoreObject::ptr)(_drawX, graphicSize + _drawY, _imageID,
                                _blendStrength - overlayY,
                                DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                    + DAT_GMImageOffsets::instance[GMFirstPictureIndex::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                        + overlayX - 1]);
                        }
                    }
                    if (DAT_UnitsState::instance.units[_unitID].graphicSize >= 3) {
                        overlayX = DAT_UnitsState::instance.units[_unitID].imageID2;
                        if (0 < overlayX) {
                            graphicSize = DAT_UnitsState::instance.units[_unitID].drawYOffset;
                            if (graphicSize < 0) {
                                overlayY = 0;
                            } else {
                                overlayY = graphicSize;
                            }
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderUnitAnimationUnk,
                                DAT_TextureRenderCoreObject::ptr)(_drawX, graphicSize + _drawY, _imageID,
                                _blendStrength - overlayY,
                                DAT_TextureRenderCoreObject::instance.gmProcessedImageData
                                    + DAT_GMImageOffsets::instance[GMFirstPictureIndex::instance[(
                                                                       int)DAT_CurrentlyRenderedSpriteID::instance]
                                        + overlayX - 1]);
                        }
                        if (DAT_GameSynchronyState::instance.currentGameMode != OpenSHC::Game::GM_SOLITARY) {
                            unitType = DAT_UnitsState::instance.units[_unitID].unitType;
                            overlayX = _drawX;
                            overlayY = _drawY;
                            if ((unitType == OpenSHC::Map::Units::UT_S_TOWER)
                                && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                                switch (
                                    DAT_UnitsState::instance.units[_unitID].facingDirectionMapOrientationCorrected) {
                                case 0:
                                    overlayX = _drawX + 34;
                                    break;
                                case 1:
                                    overlayX = _drawX + 47;
                                    overlayY = _drawY - 12;
                                    break;
                                case 2:
                                    overlayX = _drawX + 75;
                                    overlayY = _drawY - 19;
                                    break;
                                case 3:
                                    overlayX = _drawX + 101;
                                    overlayY = _drawY - 10;
                                    break;
                                case 4:
                                    overlayX = _drawX + 112;
                                    overlayY = _drawY + 2;
                                    break;
                                case 5:
                                    overlayX = _drawX + 100;
                                    overlayY = _drawY + 20;
                                    break;
                                case 6:
                                    overlayX = _drawX + 70;
                                    overlayY = _drawY + 19;
                                    break;
                                case 7:
                                    overlayX = _drawX + 44;
                                    overlayY = _drawY + 23;
                                }
                            } else if ((unitType == OpenSHC::Map::Units::UT_S_BATTERINGRAM)
                                && (DAT_UnitsState::instance.units[_unitID].dying == 0)) {
                                switch (
                                    DAT_UnitsState::instance.units[_unitID].facingDirectionMapOrientationCorrected) {
                                case 0:
                                case 1:
                                    overlayX = _drawX + 44;
                                    overlayY = _drawY - 20;
                                    break;
                                case 2:
                                    overlayX = _drawX + 49;
                                    overlayY = _drawY - 17;
                                    break;
                                case 3:
                                    overlayX = _drawX + 41;
                                    overlayY = _drawY - 15;
                                    break;
                                case 4:
                                    overlayX = _drawX + 34;
                                    overlayY = _drawY - 17;
                                    break;
                                case 5:
                                case 6:
                                    overlayX = _drawX + 32;
                                    overlayY = _drawY - 20;
                                    break;
                                case 7:
                                    overlayX = _drawX + 40;
                                    overlayY = _drawY - 23;
                                }
                            }
                            DAT_RenderedUnitOwner::instance = (uint)DAT_UnitsState::instance.units[_unitID].owner;
                            DAT_CurrentlyRenderedSpriteID::instance = 189;
                            int const animationTick = (DAT_UnitsState::instance.units[_unitID].fixedRng
                                                          + DAT_GameState::instance.mapAndTime.totalGameTicksUnk)
                                % 64;
                            MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                                DAT_TextureRenderCoreObject::ptr)(
                                OpenSHC::DE::SHCDE::GM_ANIM_FLAG_SMALL, animationTick / 2 + 1, overlayX, overlayY);
                        }
                    }
                    if (*this->viewportState.ptrColor != COL_MAGENTA::instance.ushortValue) {
                        this->viewportState.mouseRayUnitID = _unitID;
                        this->viewportState.mouseRayBuildingID = 0;
                    } else {
                        *this->viewportState.ptrColor = savedPixelColor;
                    }
                }
            } else {
                if ((_blendStrength & 4) != 0) {
                    DAT_RenderedUnitOwner::instance
                        = (_blendStrength & 0x10) != 0 ? 0 : DAT_GameSynchronyState::instance.currentPlayerSlotID;
                    DAT_CurrentlyRenderedSpriteID::instance = _gmID;
                }
                if ((_blendStrength & 0x20) != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(
                        (GmID)_gmID, _imageID, _drawX, _drawY, (GmID)_gmID, (_blendStrength >> 16) + _imageID, 0);
                } else if ((_blendStrength & 0xffff0000) != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                        DAT_TextureRenderCoreObject::ptr)((GmID)_gmID, _imageID, _drawX, _drawY, _blendStrength >> 16);
                } else {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)((eGM)_gmID, _imageID, _drawX, _drawY);
                }
            }
            if (0 < _unitID) {
                if (DAT_UnitsState::instance.units[_unitID].isSelected != 0
                    && DAT_UnitsState::instance.units[_unitID].usingTeleport == 0) {
                    int const barX = (_imageID - 22) / 2 + _drawX;
                    int barY;
                    int barImage;
                    if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_LORD) {
                        short const lordRating = DAT_UnitsState::instance.units[_unitID].maxHealthRatingLord;
                        barY = DAT_UnitsState::instance.units[_unitID].someDrawYOffset;
                        if (lordRating == 0) {
                            barY = barY - 6 + _drawY;
                            barImage = DAT_UnitsState::instance.units[_unitID].healthbar + 17;
                        } else {
                            barY = barY - 8 + _drawY;
                            barImage = DAT_UnitsState::instance.units[_unitID].healthbar + 228 + lordRating * 11;
                        }
                    } else {
                        int const fearFactor
                            = DAT_GameState::instance.playerDataArray[DAT_UnitsState::instance.units[_unitID].owner]
                                  .fearFactorLevel;
                        if (fearFactor != 0) {
                            int fearImage;
                            if (fearFactor > 0) {
                                fearImage = fearFactor * 11 + 118;
                            } else {
                                fearImage = 173 - fearFactor * 11;
                            }
                            barY = DAT_UnitsState::instance.units[_unitID].someDrawYOffset - 8;
                            barImage = DAT_UnitsState::instance.units[_unitID].healthbar + fearImage;
                        } else {
                            barY = DAT_UnitsState::instance.units[_unitID].someDrawYOffset - 6;
                            barImage = DAT_UnitsState::instance.units[_unitID].healthbar + 17;
                        }
                        barY = barY + _drawY;
                    }
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGM,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::DE::SHCDE::GM_FLOATS, barImage, barX, barY);
                    if (DAT_UnitsState::instance.units[_unitID].unitType == OpenSHC::Map::Units::UT_A_ASSASSIN
                        && DAT_GameState::instance.mapAndTime.playerTeams[DAT_UnitsState::instance.units[_unitID].owner]
                            == DAT_GameState::instance.mapAndTime
                                .playerTeams[DAT_GameSynchronyState::instance.currentPlayerSlotID]
                        && (DAT_UnitsState::instance.units[_unitID].assassinsMicroDistanceToEnemyUnk <= 160
                            || DAT_UnitsState::instance.units[_unitID].state.generic
                                == OpenSHC::Map::Units::States::US_MELEE_ATTACK
                            || DAT_UnitsState::instance.units[_unitID].state.generic
                                == OpenSHC::Map::Units::States::US_MELEE_ATTACK_WALL)) {
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithBlending,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_INTERFACE_ICONS_2, 447,
                            barX + 2, DAT_UnitsState::instance.units[_unitID].someDrawYOffset - 27 + _drawY, 16);
                    }
                }
                short const floaterImage = DAT_UnitsState::instance.units[_unitID].field_0x6e;
                if (floaterImage != 0) {
                    MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                        DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW, floaterImage + 212,
                        DAT_UnitsState::instance.units[_unitID].drawX,
                        DAT_UnitsState::instance.units[_unitID].drawY - 54
                            + DAT_UnitsState::instance.units[_unitID].someDrawYOffset,
                        OpenSHC::IO::Graphics::GID_FLOATS_NEW, floaterImage + 220, 0);
                    DAT_UnitsState::instance.units[_unitID].field_0x6e = 0;
                }
                short const siegeOverlay = DAT_UnitsState::instance.units[_unitID].field_0x6c;
                if (siegeOverlay != 0) {
                    int offsetX = 0;
                    int offsetY = 0;
                    switch (siegeOverlay) {
                    case 1:
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 32,
                            DAT_UnitsState::instance.units[_unitID].field_0x2a - 53
                                + DAT_UnitsState::instance.units[_unitID].drawX,
                            DAT_UnitsState::instance.units[_unitID].drawY - 70
                                + DAT_UnitsState::instance.units[_unitID].someDrawYOffset,
                            OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 48, 0);
                        break;
                    case 2:
                        switch (DAT_UnitsState::instance.units[_unitID].unitType) {
                        case OpenSHC::Map::Units::UT_S_CATAPULT:
                            offsetX = 41;
                            offsetY = 58;
                            break;
                        case OpenSHC::Map::Units::UT_S_TREBUCHET:
                        case OpenSHC::Map::Units::UT_S_TOWER:
                            offsetX = 79;
                            offsetY = 56;
                            break;
                        case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            offsetX = 36;
                            offsetY = 61;
                            break;
                        case OpenSHC::Map::Units::UT_S_SHIELD:
                            offsetX = -3;
                            offsetY = 60;
                            break;
                        case OpenSHC::Map::Units::UT_S_MANGONEL:
                            offsetX = 43;
                            offsetY = 35;
                            break;
                        case OpenSHC::Map::Units::UT_S_BALLISTA:
                        case OpenSHC::Map::Units::UT_S_FBALLISTA:
                            offsetX = 19;
                            offsetY = 36;
                            break;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 116,
                            DAT_UnitsState::instance.units[_unitID].drawX + offsetX,
                            (DAT_UnitsState::instance.units[_unitID].drawY
                                + DAT_UnitsState::instance.units[_unitID].someDrawYOffset)
                                - offsetY,
                            OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 132, 0);
                        break;
                    case 3:
                        switch (DAT_UnitsState::instance.units[_unitID].unitType) {
                        case OpenSHC::Map::Units::UT_S_CATAPULT:
                            offsetX = 41;
                            offsetY = 58;
                            break;
                        case OpenSHC::Map::Units::UT_S_TREBUCHET:
                        case OpenSHC::Map::Units::UT_S_TOWER:
                            offsetX = 79;
                            offsetY = 56;
                            break;
                        case OpenSHC::Map::Units::UT_S_BATTERINGRAM:
                            offsetX = 36;
                            offsetY = 61;
                            break;
                        case OpenSHC::Map::Units::UT_S_SHIELD:
                            offsetX = -3;
                            offsetY = 60;
                            break;
                        case OpenSHC::Map::Units::UT_S_MANGONEL:
                            offsetX = 43;
                            offsetY = 35;
                            break;
                        case OpenSHC::Map::Units::UT_S_BALLISTA:
                        case OpenSHC::Map::Units::UT_S_FBALLISTA:
                            offsetX = 19;
                            offsetY = 36;
                            break;
                        }
                        MACRO_CALL_MEMBER(OpenSHC::UI::Rendering::TextureRenderCore_Func::renderGMWithAlphaMask,
                            DAT_TextureRenderCoreObject::ptr)(OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 148,
                            DAT_UnitsState::instance.units[_unitID].drawX + offsetX,
                            (DAT_UnitsState::instance.units[_unitID].drawY
                                + DAT_UnitsState::instance.units[_unitID].someDrawYOffset)
                                - offsetY,
                            OpenSHC::IO::Graphics::GID_FLOATS_NEW,
                            DAT_TileMapState::instance.cursorOverlayAnimationFrame + 164, 0);
                        break;
                    }
                    DAT_UnitsState::instance.units[_unitID].field_0x6c = 0;
                }
            }
        }
    }

}
}
