cmake_minimum_required(VERSION 3.19)

if (${TOOLCHAIN_LANGUAGE} MATCHES "MikroC")
    project(Lab_6_interfacing-on-board-Buzzer LANGUAGES MikroC)
else()
    project(Lab_6_interfacing-on-board-Buzzer LANGUAGES C ASM)
endif()

include(mikroeUtils)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    legacy_cmake_path()
endif()

set(PROJECT_TYPE "mikrosdk" CACHE STRING "" FORCE)

add_executable(Lab_6_interfacing-on-board-Buzzer main.c)
############################ Lab_6_interfacing-on-board-Buzzer GENERATED CODE START ###########################
############################ Lab_6_interfacing-on-board-Buzzer GENERATED CODE END ###########################

find_package(MikroC.Core REQUIRED)
target_link_libraries(Lab_6_interfacing-on-board-Buzzer
    PUBLIC
        MikroC.Core
)

if (${MIKROSDK_TYPE} STREQUAL "legacy")
    find_package(MikroC.System REQUIRED)
    target_link_libraries(Lab_6_interfacing-on-board-Buzzer
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
