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

#include <DApplication>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>

#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("Penguin-video");
    a.setApplicationVersion("1.0");
    a.setProductIcon(QIcon(":/icons/youtube.svg"));
    a.setProductName("Penguin Video");
    a.setApplicationDescription("This is a video player.");

    PenguinWindow w;
    w.titlebar()->setIcon(QIcon(":/icons/youtube.svg"));
    // 设置标题，宽度不够会隐藏标题文字
    w.setMinimumSize(QSize(1000, 1000));
    w.show();
    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
