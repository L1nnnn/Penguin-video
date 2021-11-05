/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     linxun <linxun@uniontech.com>
*
* Maintainer: linxun <linxun@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "penguinplay.h"
#include <gst/video/videooverlay.h>

#include <QDebug>
PenguinPlay::PenguinPlay(QObject *parent) : QObject(parent)
{
    gst_init(nullptr,nullptr);
}

PenguinPlay::~PenguinPlay()
{
    denit();
}

void PenguinPlay::setFileLoc(const QString &fileLoc)
{
    m_fileLoc=fileLoc;
}

bool PenguinPlay::startPlay()
{
    if (!createPipe())
        return false;

    int state = -1;
    int pending = -1;
    GetGstState(&state,&pending);
    if (state == GST_STATE_PLAYING) {
        return true;
    } else if (state == GST_STATE_PAUSED) {
        gst_element_set_state(m_pipeLine, GST_STATE_PLAYING);
        return true;
    }
    if (gst_element_set_state(m_pipeLine, GST_STATE_PLAYING) == GST_STATE_CHANGE_FAILURE) {
        qCritical() << "start error";
        return false;
    }
    return true;
}

void PenguinPlay::stopPlay()
{
    if (m_pipeLine) {
        setStateToNull();
    }
}

void PenguinPlay::setWindowId(const WId &windowId)
{
     m_windowId=windowId;
}

void PenguinPlay::GetGstState(int *state, int *pending)
{
    *state=GST_STATE_NULL;
    *pending=GST_STATE_NULL;
    if (m_pipeLine == nullptr)
        return;
    gst_element_get_state(m_pipeLine, reinterpret_cast<GstState *>(state),
                          reinterpret_cast<GstState *>(pending), 0);
}

bool PenguinPlay::createPipe()
{
     CustomData data;
     m_pipeLine=gst_pipeline_new("penguinpipe");
     data.src=gst_element_factory_make("filesrc","penguinsrc");
     if (!data.src) {
       qCritical()<< "Failed to create element of type 'filesrc'\n";
       return false;
     }
     if(!m_fileLoc.isEmpty())
         g_object_set(reinterpret_cast<gpointer>(data.src),"location",m_fileLoc.toLatin1().data(),nullptr);
     data.demuxer=gst_element_factory_make("qtdemux", "demuxer");
     if (!data.demuxer) {
       qCritical()<< "Failed to create element of type 'demuxer'\n";
       return false;
     }
     data.vdecoder=gst_element_factory_make("avdec_h264", "decorder");
     if (!data.vdecoder) {
       qCritical()<< "Failed to create element of type 'vdecoder'\n";
       return false;
     }
     data.vsink=gst_element_factory_make("ximagesink", "sink");
     if (!data.vsink) {
       qCritical()<< "Failed to create element of type 'vsink'\n";
       return false;
     }
     gst_bin_add_many(reinterpret_cast<GstBin*>(m_pipeLine),data.src,data.demuxer,data.vdecoder,data.vsink,nullptr);
    if(!gst_element_link (data.src,data.demuxer)){
        qCritical()<< "Failed to create element of type 'demuxer'\n";
        return false;
    }
     if(!gst_element_link_many(data.vdecoder,data.vsink,nullptr)){
         qCritical()<< "Failed to create element of type 'link'\n";
         return false;
     }

     gst_video_overlay_set_window_handle (reinterpret_cast<GstVideoOverlay*>(data.vsink), m_windowId);
     return true;
}

void PenguinPlay::denit()
{
     stopPlay();
     gst_object_unref(m_pipeLine);
     gst_deinit();
}

void PenguinPlay::setStateToNull()
{
    GstState cur_state = GST_STATE_NULL, pending = GST_STATE_NULL;
    gst_element_get_state(m_pipeLine, &cur_state, &pending, 0);
    if (cur_state == GST_STATE_NULL) {
        if (pending != GST_STATE_VOID_PENDING) {
            gst_element_set_state(m_pipeLine, GST_STATE_NULL);
        }
        return;
    }
    gst_element_set_state(m_pipeLine, GST_STATE_READY);
    gst_element_get_state(m_pipeLine, nullptr, nullptr, static_cast<GstClockTime>(-1));
    gst_element_set_state(m_pipeLine, GST_STATE_NULL);
}
