/****************************************************************************
**
** EPFText text render engine for the EPF Text format.
** Part of the LEAF EPF renderer.
** http://leaf.dreamlogics.com/
**
** Copyright (C) 2014 DreamLogics
** Copyright (C) 2014 Stefan Ladage <sladage@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#ifndef EPFTEXTWIDGET_H
#define EPFTEXTWIDGET_H

#include <QWidget>
#include "document.h"

class EPFTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EPFTextWidget(QWidget *parent = 0);

    void load(QByteArray &data, QOPS::Propsheet sheet);

signals:

public slots:

protected:

    virtual void paintEvent(QPaintEvent *ev);
    virtual void resizeEvent(QResizeEvent *ev);

private:

    EPFText::Document m_doc;
    bool m_bLoaded;
};

#endif // EPFTEXTWIDGET_H
