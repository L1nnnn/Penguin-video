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
#include "penguinplaydialog.h"

PenguinPlayDialog::PenguinPlayDialog(QWidget *parent) : DDialog(parent)
{
    initUI();
}

void PenguinPlayDialog::initUI()
{
     m_playWidget=new DFrame(this);
     m_playWidget->setMinimumSize(800,600);
     m_slider=new DSlider(Qt::Horizontal,this);
     insertContent(0,m_playWidget,Qt::AlignTop);
     insertContent(1,m_slider,Qt::AlignTop);
}
