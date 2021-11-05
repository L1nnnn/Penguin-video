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
#include "penguinwindow.h"
#include "penguinplaydialog.h"

#include <DFileDialog>

#include <QVBoxLayout>

PenguinWindow::PenguinWindow(QWidget *parent):DMainWindow (parent),m_play(new PenguinPlay)
{
   initUI();
   initConnect();
}

PenguinWindow::~PenguinWindow()
{
    if(m_play){
        delete  m_play;
        m_play=nullptr;
    }
}

void PenguinWindow::initUI()
{
   QVBoxLayout *mainLayout=new QVBoxLayout;
   m_filechooseBtn=new DPushButton("file choose");
   mainLayout->addWidget(m_filechooseBtn,Qt::AlignCenter);
   auto widget=new QWidget;
   setCentralWidget(widget);
   widget->setLayout(mainLayout);
}

void PenguinWindow::initConnect()
{
    QObject::connect(m_filechooseBtn,&DPushButton::clicked,this,[&]{
        QString fileName = DFileDialog::getSaveFileName(
                               this);
        this->playVideo(fileName);
    });


}

void PenguinWindow::playVideo(const QString &fileLoc)
{
    PenguinPlayDialog *dialog=new PenguinPlayDialog (this);
    dialog->show();
    WId windowId=dialog->window()->winId();
    m_play->setWindowId(windowId);
    m_play->setFileLoc(fileLoc);
    if(m_play->startPlay()){
       qCritical()<<"paly failed";
    }
}
