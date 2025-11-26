
#include "ucp3.h"

#include <sstream>

// TODO?: When in doubt regarding the transition to full exe: Add other logging system.

#ifdef OPEN_SHC_DLL

static void createRelativeJump(int from, int to)
{
    const int instructionLength = 5;
    const int relativeOffset = to - (from + instructionLength);

    DWORD oldProtection;
    if (!VirtualProtect((void*)from, instructionLength, PAGE_EXECUTE_READWRITE, &oldProtection)) {
        std::ostringstream oss;
        oss << "Error while trying to remove memory protection to create relative jump from '" << from << "' to '" << to
            << "': " << GetLastError();
        ucp_log(Verbosity_FATAL, oss.str().c_str());
    }

    // create relative jmp
    *((char*)from) = (char)0xe9;
    *((int*)(from + 1)) = relativeOffset;

    DWORD dummyProtection;
    if (!VirtualProtect((void*)from, instructionLength, oldProtection, &dummyProtection)) {
        std::ostringstream oss;
        oss << "Error while trying to re-enable memory protection after creating relative jump from '" << from
            << "' to '" << to << "': " << GetLastError();
        ucp_log(Verbosity_FATAL, oss.str().c_str());
    }
}

#endif

void StructResolver::initialize(
    bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName)
{
    if (initialized) {
#ifdef OPEN_SHC_EXE
        abort(); // crash silently; if we switch to exe, we should already be sure to never trigger this
#endif

#ifdef OPEN_SHC_DLL
        std::ostringstream oss;
        oss << "Abort execution, since address '" << gameAddress << "' was resolved more then once.";
        ucp_log(Verbosity_FATAL, oss.str().c_str());
#endif
        return;
    }
    initialized = true;

#ifdef OPEN_SHC_DLL
    if (ucp_logLevel() < Verbosity_1) {
        return;
    }
    std::ostringstream oss;
    if (isImplemented) {
        oss << "Implemented '" << (void*)gameAddress << "' at address '" << funcPtr << "' as a '" << funcName;
    } else {
        oss << "Use '" << (void*)gameAddress << "' as a '" << funcName;
    }
    ucp_log(Verbosity_1, oss.str().c_str());
#endif
}

void FunctionResolver::initialize(
    bool& initialized, bool isImplemented, int gameAddress, const void* funcPtr, const char* funcName)
{
    if (initialized) {
#ifdef OPEN_SHC_EXE
        abort(); // crash silently; if we switch to exe, we should already be sure to never trigger this
#endif

#ifdef OPEN_SHC_DLL
        std::ostringstream oss;
        oss << "Abort execution, since address '" << gameAddress << "' was resolved more then once.";
        ucp_log(Verbosity_FATAL, oss.str().c_str());
#endif
        return;
    }
    initialized = true;

#ifdef OPEN_SHC_DLL
    if (isImplemented) {
        createRelativeJump(gameAddress, (int)funcPtr);
    }

    if (ucp_logLevel() < Verbosity_1) {
        return;
    }
    std::ostringstream oss;
    if (isImplemented) {
        oss << "Implemented '" << (void*)gameAddress << "' at address '" << funcPtr << "' as '" << funcName;
    } else {
        oss << "Use '" << (void*)gameAddress << "' as '" << funcName;
    }
    ucp_log(Verbosity_1, oss.str().c_str());
#endif
}
