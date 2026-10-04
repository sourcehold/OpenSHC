#include "../TextureRenderCore.func.hpp"

#include "OpenSHC/IO/Graphics/TgxToken.hpp"
#include "OpenSHC/Rendering/Enums/RenderTarget.hpp"

#include "OpenSHC/Globals/DAT_TextureRenderCoreObject.hpp"
#include "OpenSHC/Globals/DAT_WindowAndDirectDraw.hpp"
#include "OpenSHC/IO/Graphics/TgxTokenByte.hpp"

namespace OpenSHC {
namespace UI {
    namespace Rendering {

        using OpenSHC::IO::Graphics::TgxToken;
        using OpenSHC::Rendering::Enums::RenderTarget;
        using OpenSHC::IO::Graphics::TgxTokenByte;

        // FUNCTION: STRONGHOLDCRUSADER 0x00454A60
        void TextureRenderCore::drawTgxOnFlaggedSurface(
            int xPos, int yPos, int gfxWidth, int gfxHeight, ushort* tgxSourcePtr)
        {
            undefined2 uVar1;
            LONG LVar2;
            LONG LVar3;
            TgxTokenByte _tgxToken;
            int iVar4;
            uint uVar5;
            TgxTokenByte _tgxToken2;
            int iVar6;
            TgxTokenByte* pTVar7;
            ushort* _renderPtr;
            int _byteWidth;
            int _xRenderPos;
            LVar3 = DAT_TextureRenderCoreObject::instance.renderingRect_16c854.right;
            LVar2 = DAT_TextureRenderCoreObject::instance.renderingRect_16c854.left;
            if (DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8 == OpenSHC::Rendering::Enums::RT_SCREEN_MENU) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_screenMenu;
                /*
                  Could be "jump"-line needed to skip to start of next horizontal line.   --TheRedDaemon
                 */
                gfxWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine + gfxWidth * -2;
                _byteWidth = DAT_WindowAndDirectDraw::instance.byteSizeOfOneHorizontalLine;
            } else if (DAT_TextureRenderCoreObject::instance.currentRenderSurfaceIdentifierUnk_0x8 == OpenSHC::Rendering::Enums::RT_MAP_GAME) {
                DAT_TextureRenderCoreObject::instance.currentRenderSurface = DAT_WindowAndDirectDraw::instance.surfacePointer_mapGame;
                gfxWidth = (0xfd8 - gfxWidth) * 2;
                _byteWidth = 0x1fb0;
            }
            if ((gfxHeight + yPos <= DAT_TextureRenderCoreObject::instance.renderingRect_16c854.bottom)
                || (gfxHeight = DAT_TextureRenderCoreObject::instance.renderingRect_16c854.bottom - yPos, 0 < gfxHeight)) {
                if (yPos < DAT_TextureRenderCoreObject::instance.renderingRect_16c854.top) {
                    iVar6 = DAT_TextureRenderCoreObject::instance.renderingRect_16c854.top - yPos;
                    if (gfxHeight <= iVar6) {}
                    gfxHeight = gfxHeight - iVar6;
                    do {
                        while (true) {
                            while (true) {
                                do {
                                    pTVar7 = (TgxTokenByte*)tgxSourcePtr;
                                    _tgxToken2 = *pTVar7 & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                                    tgxSourcePtr = (ushort*)(pTVar7 + 1);
                                } while (_tgxToken2 == OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS);
                                if (_tgxToken2 != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                                    break;
                                tgxSourcePtr = (ushort*)((int)tgxSourcePtr + ((*pTVar7 & 0xffffff1f) + 1) * 2);
                            }
                            if (_tgxToken2 != OpenSHC::IO::Graphics::TT_REPEATING_PIXELS)
                                break;
                            tgxSourcePtr = (ushort*)(pTVar7 + 3);
                        }
                        iVar6 = iVar6 + -1;
                        yPos = DAT_TextureRenderCoreObject::instance.renderingRect_16c854.top;
                    } while (0 < iVar6);
                }
                _renderPtr = (ushort*)((int)DAT_TextureRenderCoreObject::instance.currentRenderSurface + yPos * _byteWidth + xPos * 2);
                _xRenderPos = xPos;
            LAB_00454b69:
                do {
                    while (true) {
                        while (true) {
                            _tgxToken = *(TgxTokenByte*)tgxSourcePtr & OpenSHC::IO::Graphics::TT_TGX_PIXEL_HEADER;
                            uVar5 = *(TgxTokenByte*)tgxSourcePtr & 0xffffff1f;
                            pTVar7 = (TgxTokenByte*)((int)tgxSourcePtr + 1);
                            if (_tgxToken != OpenSHC::IO::Graphics::TT_TRANSPARENT_PIXELS)
                                break;
                            _xRenderPos = _xRenderPos + uVar5 + 1;
                            _renderPtr = _renderPtr + uVar5 + 1;
                            tgxSourcePtr = (ushort*)pTVar7;
                        }
                        if (_tgxToken != OpenSHC::IO::Graphics::TT_STREAM_OF_PIXELS)
                            break;
                        iVar6 = uVar5 + 1;
                        if (_xRenderPos < LVar3) {
                            tgxSourcePtr = (ushort*)pTVar7;
                            if (_xRenderPos < LVar2) {
                                if (iVar6 + _xRenderPos <= LVar2)
                                    goto LAB_00454c2d;
                                iVar4 = LVar2 - _xRenderPos;
                                iVar6 = iVar6 - iVar4;
                                _xRenderPos = _xRenderPos + iVar4;
                                tgxSourcePtr = (ushort*)(pTVar7 + iVar4 * 2);
                                _renderPtr = _renderPtr + iVar4;
                            }
                            if (iVar6 + _xRenderPos < LVar3) {
                                do {
                                    *_renderPtr = *tgxSourcePtr;
                                    tgxSourcePtr = (ushort*)((int)tgxSourcePtr + 2);
                                    _renderPtr = _renderPtr + 1;
                                    _xRenderPos = _xRenderPos + 1;
                                    iVar6 = iVar6 + -1;
                                } while (iVar6 != 0);
                            } else {
                                iVar4 = (iVar6 + _xRenderPos) - LVar3;
                                iVar6 = iVar6 - iVar4;
                                do {
                                    *_renderPtr = *tgxSourcePtr;
                                    tgxSourcePtr = (ushort*)((int)tgxSourcePtr + 2);
                                    _renderPtr = _renderPtr + 1;
                                    _xRenderPos = _xRenderPos + 1;
                                    iVar6 = iVar6 + -1;
                                } while (iVar6 != 0);
                                _xRenderPos = _xRenderPos + iVar4;
                                _renderPtr = _renderPtr + iVar4;
                                tgxSourcePtr = (ushort*)((int)tgxSourcePtr + iVar4 * 2);
                            }
                        } else {
                        LAB_00454c2d:
                            _xRenderPos = _xRenderPos + iVar6;
                            _renderPtr = _renderPtr + iVar6;
                            tgxSourcePtr = (ushort*)(pTVar7 + iVar6 * 2);
                        }
                    }
                    if (_tgxToken == OpenSHC::IO::Graphics::TT_REPEATING_PIXELS) {
                        iVar6 = uVar5 + 1;
                        if (_xRenderPos < LVar3) {
                            if (_xRenderPos < LVar2) {
                                if (iVar6 + _xRenderPos <= LVar2)
                                    goto LAB_00454bb5;
                                iVar4 = LVar2 - _xRenderPos;
                                iVar6 = iVar6 - iVar4;
                                _xRenderPos = _xRenderPos + iVar4;
                                _renderPtr = _renderPtr + iVar4;
                            }
                            if (iVar6 + _xRenderPos < LVar3) {
                                uVar1 = *(undefined2*)pTVar7;
                                do {
                                    *_renderPtr = uVar1;
                                    _renderPtr = _renderPtr + 1;
                                    _xRenderPos = _xRenderPos + 1;
                                    iVar6 = iVar6 + -1;
                                } while (iVar6 != 0);
                                tgxSourcePtr = (ushort*)((int)tgxSourcePtr + 3);
                            } else {
                                iVar4 = (iVar6 + _xRenderPos) - LVar3;
                                iVar6 = iVar6 - iVar4;
                                uVar1 = *(undefined2*)pTVar7;
                                do {
                                    *_renderPtr = uVar1;
                                    _renderPtr = _renderPtr + 1;
                                    _xRenderPos = _xRenderPos + 1;
                                    iVar6 = iVar6 + -1;
                                } while (iVar6 != 0);
                                _xRenderPos = _xRenderPos + iVar4;
                                _renderPtr = _renderPtr + iVar4;
                                tgxSourcePtr = (ushort*)((int)tgxSourcePtr + 3);
                            }
                        } else {
                        LAB_00454bb5:
                            _xRenderPos = _xRenderPos + iVar6;
                            _renderPtr = _renderPtr + iVar6;
                            tgxSourcePtr = (ushort*)((int)tgxSourcePtr + 3);
                        }
                        goto LAB_00454b69;
                    }
                    _renderPtr = (ushort*)((int)_renderPtr + gfxWidth);
                    gfxHeight = gfxHeight + -1;
                    _xRenderPos = xPos;
                    tgxSourcePtr = (ushort*)pTVar7;
                } while (0 < gfxHeight);
            }
        }

    }
}
}
