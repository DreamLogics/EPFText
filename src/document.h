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
#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "paragraph.h"
#include <QRectF>
#include <QOPSLib/qopslib.h>

#define EPFT_OK 0
#define EPFT_PARSE_ERROR 1

class QPainter;

namespace EPFText
{

class DocumentPrivate;

class Document
{
public:
    Document();
    Document(const Document &d);
    ~Document();

    int fromData(QByteArray &data) const;

    QString toPlainText() const;
    QByteArray toData() const;

    void setStyleInfo(QOPS::Propsheet &propsheet, QString ns) const;

    void format() const;
    void setSize(QSize &size) const;
    void setWidth(int width) const;
    QSize documentSize() const;

    int paragraphCount() const;
    Paragraph paragraph(int index) const;
    void addParagraph(Paragraph p) const;
    void insertParagraph(Paragraph p, int pos) const;
    void removeParagraph(int index) const;

    void render(QPainter *p, QRect area = QRect()) const;

    virtual Document& operator=(const Document &ref);

private:

    DocumentPrivate *m_p;

};

}

#endif // DOCUMENT_H
