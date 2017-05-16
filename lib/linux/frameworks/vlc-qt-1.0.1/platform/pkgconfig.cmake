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
# Configuration #
#################

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/platform/pkgconfig/lib${VLCQT_CORE_NAME}.pc.in"
    "${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_CORE_NAME}.pc"
    @ONLY
)

CONFIGURE_FILE(
    "${CMAKE_SOURCE_DIR}/platform/pkgconfig/lib${VLCQT_WIDGETS_NAME}.pc.in"
    "${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_WIDGETS_NAME}.pc"
    @ONLY
)

IF(QT_VERSION MATCHES 5)
    CONFIGURE_FILE(
        "${CMAKE_SOURCE_DIR}/platform/pkgconfig/lib${VLCQT_QML_NAME}.pc.in"
        "${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_QML_NAME}.pc"
        @ONLY
    )
ENDIF()


################
# Installation #
################
INSTALL(FILES ${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_CORE_NAME}.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig)
INSTALL(FILES ${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_WIDGETS_NAME}.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig)
IF(QT_VERSION MATCHES 5)
    INSTALL(FILES ${CMAKE_BINARY_DIR}/platform/pkgconfig/lib${VLCQT_QML_NAME}.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig)
ENDIF()
