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
#include "epftextwidget.h"
#include <QPainter>
#include "qopslib.h"

EPFTextWidget::EPFTextWidget(QWidget *parent) :
    QWidget(parent), m_bLoaded(false)
{
}

void EPFTextWidget::load(QByteArray &data, QOPS::Propsheet sheet)
{
    m_doc.setStyleInfo(sheet,QString());

    if (m_doc.fromData(data) != EPFT_OK)
        return;

    m_bLoaded = true;
    m_doc.setWidth(width());
    m_doc.format();
    update();
}

void EPFTextWidget::paintEvent(QPaintEvent *ev)
{
    QPainter p;

    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing,true);

    p.fillRect(0,0,width(),height(),QColor(220,220,220));

    if (m_bLoaded)
        m_doc.render(&p);


    p.end();
}

void EPFTextWidget::resizeEvent(QResizeEvent *ev)
{
    if (!m_bLoaded)
        return;
    m_doc.setWidth(width());
    m_doc.format();
}
