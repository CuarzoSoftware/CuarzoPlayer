#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2016 Tadej Novak <tadej@tano.si>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Automatically run moc, uic and/or rcc, if required
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)
# Verbose makefile
SET(CMAKE_VERBOSE_MAKEFILE ON)

# Detect debug build
IF(CMAKE_BUILD_TYPE MATCHES Debug)
    SET(LE d) # For Qt

    IF(MINGW OR MSVC)
        OPTION(DEBUG_SUFFIX "Debug library suffix" ON)
    ELSE()
        OPTION(DEBUG_SUFFIX "Debug library suffix" OFF)
    ENDIF()
    MESSAGE("VLC-Qt: Debug library suffix ${DEBUG_SUFFIX}")
    IF(DEBUG_SUFFIX)
        SET(LS d) # For VLC-Qt
    ENDIF()
ENDIF()

# C++11 support
IF (NOT MSVC)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ENDIF()

# Show all warnings
IF(NOT MSVC)
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra")
ENDIF()

# Make final release build smaller
IF(CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")
    SET(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} -s")
ENDIF()

# Statically link with libgcc
IF(MINGW)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
    SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static-libgcc -static-libstdc++")
ENDIF()

IF(MSVC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nologo -Zc:wchar_t")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nologo -Zc:wchar_t -w34100 -w34189")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NOLOGO /DYNAMICBASE /NXCOMPAT")
ENDIF()

# Support OS X 10.6 or later (64-bit only)
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    OPTION(HOMEBREW "Build using Homebrew provided Qt" OFF)
    MESSAGE("VLC-Qt: Build using Homebrew provided Qt: ${HOMEBREW}")

    IF(HOMEBREW)
        SET(CMAKE_MACOSX_RPATH OFF)
    ELSE()
        SET(CMAKE_MACOSX_RPATH ON)
        SET(CMAKE_INSTALL_RPATH "@loader_path/../lib")
        SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
    ENDIF()
    SET(CMAKE_OSX_ARCHITECTURES x86_64)
ENDIF()
