#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2015 Tadej Novak <tadej@tano.si>
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
# OS X Extra #
##############
# Set the OS X Bundle specific CMake variables which will be used to populate the plist for
# the application bundle
SET(MACOSX_BUNDLE_COPYRIGHT "2015 ${PROJECT_AUTHOR}")
SET(MACOSX_BUNDLE_ICON_FILE "${VLCQT_TEST}.icns")
SET(MACOSX_BUNDLE_GUI_IDENTIFIER "si.tano.${PROJECT_NAME}")

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/platform/osx/Info.plist.in
    ${CMAKE_BINARY_DIR}/platform/osx/Info.plist
)

IF(${BUILD_TESTS})
    ADD_CUSTOM_TARGET(dmg
        "${QT_BIN_DIR}/macdeployqt" "${CMAKE_INSTALL_PREFIX}/bin/${VLCQT_TEST}.app" -dmg)
ENDIF()

FILE(GLOB Vlc_Libs ${LIBVLC_LIB_DIR}/*.dylib)
FILE(GLOB Vlc_Plugins ${LIBVLC_PLUGINS_DIR}/*.dylib)
