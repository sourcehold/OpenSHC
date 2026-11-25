#include "../ResourceManager.func.hpp"

#include "OpenSHC/Globals/DAT_CurrentResourceCoreName.hpp"

namespace OpenSHC {
namespace IO {

    // FUNCTION: STRONGHOLDCRUSADER 0x00471D30
    char* ResourceManager::getCurrentResourceCoreNameUnk()
    {
        char const* _resourceName = MACRO_CALL_MEMBER(ResourceManager_Func::getFileNameOfCurrentActiveResource, this)();
        int basenameEnd = strlen(_resourceName);
        DAT_CurrentResourceCoreName::instance[0] = '\0';

        for (int basenameStart = basenameEnd - 1; basenameStart >= 0; --basenameStart) {
            if (_resourceName[basenameStart] == '.') {
                basenameEnd = basenameStart;
            }
            if (_resourceName[basenameStart] == '\\') {
                int basenameLength = 0;
                for (int i = basenameStart + 1; i < basenameEnd; ++i) {
                    DAT_CurrentResourceCoreName::instance[basenameLength++] = _resourceName[i];
                }
                DAT_CurrentResourceCoreName::instance[basenameLength] = '\0';
                break;
            }
        }
        return DAT_CurrentResourceCoreName::instance;
    }

} // namespace IO
} // namespace OpenSHC
