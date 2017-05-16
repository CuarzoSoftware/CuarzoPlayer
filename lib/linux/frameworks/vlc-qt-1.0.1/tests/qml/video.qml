/****************************************************************************
* VLC-Qt - Qt and libvlc connector library
* Copyright (C) 2013 Tadej Novak <tadej@tano.si>
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published
* by the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

import QtQuick 2.0
import VLCQt 1.0

Rectangle {
    width: 640
    height: 480
    color: "black"

    VlcVideoPlayer {
        id: vidwidget
        anchors.fill: parent
        url: "http://videos.hd-trailers.net/e23ab4b8-a737-46dd-a0e4-259ba36056b6_YsfXbEghC5XywlmkKiYrF0D1oWcPYHA94aPeKmTuUKJJVJBpH4AFbPzcNWMhAJHuRnKZAAatvKg-_8_0.mp4"
        //url: "http://download.blender.org/peach/bigbuckbunny_movies/BigBuckBunny_640x360.m4v"
    }
}
