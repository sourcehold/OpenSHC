

#include "ucp3.h"
#include <string>

inline FILE* ucp_getFilePointer(const std::string& path, const std::string &mode, std::string &errorMsg) {
	FILE* result = ucp_getFilePointer(path.c_str(), mode.c_str());
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline int ucp_getFileDescriptor(const std::string& path, const int mode, const int perm, std::string& errorMsg) {
	int result = ucp_getFileDescriptor(path.c_str(), mode, perm);
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline void ucp_log(const ucp_NamedVerbosity logLevel, const std::string& logMessage) {
	return ucp_log(logLevel, logMessage.c_str());
}

inline FILE* ucp_getFilePointerForFileInExtension(const std::string& extensionName, const std::string& path, const  std::string& mode, std::string& errorMsg) {
	FILE* result = ucp_getFilePointerForFileInExtension(extensionName.c_str(), path.c_str(), mode.c_str());
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline int ucp_getFileDescriptorForFileInExtension(const std::string& extensionName, const std::string& path, const int mode, std::string& errorMsg) {
	int result = ucp_getFileDescriptorForFileInExtension(extensionName.c_str(), path.c_str(), mode);
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline void* ucp_getProcAddressFromLibraryInModule(const std::string& moduleName, const std::string& library, const std::string& name, std::string& errorMsg) {
	void* result = ucp_getProcAddressFromLibraryInModule(moduleName.c_str(), library.c_str(), name.c_str());
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline int ucp_getFileSize(const std::string& filename, std::string& errorMsg) {
	int result = ucp_getFileSize(filename.c_str());
	errorMsg = ucp_lastErrorMessage();

	return result;
}
inline int ucp_getFileContents(const std::string& filename, void* buffer, const int size, std::string& errorMsg) {
	int result = ucp_getFileContents(filename.c_str(), buffer, size);
	errorMsg = ucp_lastErrorMessage();

	return result;
}

inline int ucp_getFileSizeForFileInExtension(const std::string& extensionName, const std::string& path, std::string& errorMsg) {
	int result = ucp_getFileSizeForFileInExtension(extensionName.c_str(), path.c_str());
	errorMsg = ucp_lastErrorMessage();

	return result;
}
inline int ucp_getFileContentsForFileInExtension(const std::string& extensionName, const std::string& path, void* buffer, const int size, std::string& errorMsg) {
	int result = ucp_getFileContentsForFileInExtension(extensionName.c_str(), path.c_str(), buffer, size);
	errorMsg = ucp_lastErrorMessage();

	return result;
}