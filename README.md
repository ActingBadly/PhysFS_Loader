# PhysFS_Loader

A Simple wrapper for PhysFS to load and access the contents of .zip's and other package files easily.

## Install

### Manual

Grab PhysFS from https://github.com/icculus/physfs.git and include it in your project, then simply download and add ABI_PhysFS_Loader.h to your project.

### AUTOMATED INSTALL (CMAKE)

# Copy and paste the following and add it to your CMakeLists.txt file.

FetchContent_Declare(
  physfs
  GIT_REPOSITORY https://github.com/icculus/physfs.git
  GIT_TAG main
)
FetchContent_MakeAvailable(physfs)

# If you have PhysFS_Loader cloned locally, set "" to that location. Otherwise, leave it blank, cmake will grab it from it's git automaticlly.
set(PhysFS_Loader_LOCAL_PATH "" CACHE PATH "CACHE_PhysFS_Loader" FORCE)

if(PhysFS_Loader_LOCAL_PATH)
  FetchContent_Declare(
    PhysFS_Loader
    SOURCE_DIR ${PhysFS_Loader_LOCAL_PATH}
  )
else()
  FetchContent_Declare(
    PhysFS_Loader
    GIT_REPOSITORY https://github.com/ActingBadly/PhysFS_Loader.git
    GIT_TAG        main
  )
endif()
FetchContent_MakeAvailable(PhysFS_Loader)

target_link_libraries(PhysFS_Loader)

### USAGE

