cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(soundbuzzer LANGUAGES MikroC)
else()
    project(soundbuzzer LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    legacy_cmake_path()
endif()

set(PROJECT_TYPE "legacy" CACHE STRING "" FORCE)

add_executable(soundbuzzer main.c)

############################ soundbuzzer GENERATED CODE START ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(soundbuzzer PUBLIC MikroC.Core)
find_package(MikroC.System REQUIRED)
target_link_libraries(soundbuzzer PUBLIC MikroC.System)
find_package(MikroC.Sound REQUIRED)
target_link_libraries(soundbuzzer PUBLIC MikroC.Sound)
find_package(MikroC.Button REQUIRED)
target_link_libraries(soundbuzzer PUBLIC MikroC.Button)
############################ soundbuzzer GENERATED CODE END ###########################
find_package(MikroC.Core REQUIRED)
target_link_libraries(soundbuzzer
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(soundbuzzer
        PUBLIC
            MikroC.System
    )
endif()

if(COMPILER_REVISION)
    if(${COMPILER_REVISION} VERSION_GREATER_EQUAL "1.0")
        if(${TOOLCHAIN_LANGUAGE} STREQUAL "GNU")
            if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/.meproject)
                fetch_startup_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject startupName)
                if(startupName)
                    add_startup_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${startupName})
                endif()
                fetch_linker_name(${CMAKE_CURRENT_SOURCE_DIR}/.meproject linkerName)
                if(linkerName)
                    add_ld_all_targets(. ${CMAKE_CURRENT_SOURCE_DIR} ${linkerName})
                endif()
            endif()
        endif()
    endif()
endif()
