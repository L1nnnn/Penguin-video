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
#ifndef PENGUINPLAYDIALOG_H
#define PENGUINPLAYDIALOG_H

#include <DDialog>
#include <DSlider>
#include <DFrame>

DWIDGET_USE_NAMESPACE
class PenguinPlayDialog : public DDialog
{
    Q_OBJECT
public:
    explicit PenguinPlayDialog(QWidget *parent = nullptr);

signals:

public slots:

private:
    void initUI();
private:
    DFrame *m_playWidget{nullptr};
    DSlider *m_slider{nullptr};
};

#endif // PENGUINPLAYDIALOG_H
