#pragma once
#include <physfs.h>

inline bool ABI_PhysFS_Load_Package(const char* zipPath, const char* mountPoint = "/", bool appendToPath = true) {
    if (!PHYSFS_isInit()) {
        if (!PHYSFS_init(nullptr)) {
            return false;
        }
    }
    return PHYSFS_mount(zipPath, mountPoint, appendToPath) != 0;
}

inline bool ABI_PhysFS_Check_Package_Loaded(const char* zipPath) {
    char **mounts = PHYSFS_getSearchPath();
    if (!mounts) return false;
    bool found = false;
    for (char **p = mounts; *p != nullptr; ++p) {
        const char *a = zipPath, *b = *p;
        while (*a && (*a == *b)) { ++a; ++b; }
        if (*a == *b) {
            found = true;
            break;
        }
    }
    PHYSFS_freeList(mounts);
    return found;
}

inline bool ABI_PhysFS_Check_File_Exists(const char* filePath) {
    if (!PHYSFS_isInit()) return false;
    return PHYSFS_exists(filePath) != 0;
}

inline void* ABI_PhysFS_Get_File_Contents(const char* filePath, PHYSFS_sint64* outSize = nullptr) {
    if (outSize) *outSize = 0;
    PHYSFS_File* file = PHYSFS_openRead(filePath);
    if (!file) return nullptr;
    PHYSFS_sint64 size = PHYSFS_fileLength(file);
    if (size <= 0) {
        PHYSFS_close(file);
        return nullptr;
    }
    void* buffer = PHYSFS_getAllocator()->Malloc(static_cast<PHYSFS_sint64>(size));
    if (!buffer) {
        PHYSFS_close(file);
        return nullptr;
    }
    PHYSFS_sint64 readBytes = PHYSFS_readBytes(file, buffer, size);
    PHYSFS_close(file);
    if (readBytes != size) {
        PHYSFS_getAllocator()->Free(buffer);
        return nullptr;
    }
    if (outSize) *outSize = size;
    return buffer;
}