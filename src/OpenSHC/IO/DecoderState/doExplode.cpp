#include "../DecoderState.func.hpp"

#include "OpenSHC/IO/DecoderBuffer.func.hpp"
#include "OpenSHC/OS.func.hpp"

#include "pklib.h"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x004725A0
    BOOLEnum DecoderState::doExplode(
        int* hash, undefined* src, unsigned int sizeCompressed, undefined* dst, unsigned int sizeUncompressed)
    {
        BOOLEnum _status = TRUE;
        HGLOBAL hMem = GlobalAlloc(GHND, sizeof(TCmpStruct));
        if (!hMem) {
            return FALSE;
        }
        TCmpStruct* _work_buf = (TCmpStruct*)GlobalLock(hMem);
        if (!_work_buf) {
            GlobalFree(hMem);
            return FALSE;
        }
        Helpers::BufferHelper _param;
        MACRO_CALL(OS_Func::_memset)(&_param, 0, sizeof(Helpers::BufferHelper));
        _param.buffer1.data = src;
        _param.buffer1.size = sizeCompressed;
        _param.imploding1orexploding2 = 2;
        _param.hash = 0xffffffff;
        _param.buffer2.data = dst;
        _param.buffer2.size = sizeUncompressed;
        unsigned int const _pkware_status = explode(MACRO_CALL(DecoderBuffer_Func::ReadBufferAndComputeHash),
            MACRO_CALL(DecoderBuffer_Func::WriteBufferAndComputeHash), (char*)_work_buf, &_param);
        if (_pkware_status == CMP_NO_ERROR && _param.underflow == FALSE) {
            _param.hash = ~_param.hash;
            *hash = _param.hash;
        } else {
            _status = CMP_NO_ERROR;
        }
        GlobalUnlock(hMem);
        GlobalFree(hMem);
        return _status;
    }

}
}
