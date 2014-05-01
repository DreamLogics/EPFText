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
#ifndef TEXTNODE_H
#define TEXTNODE_H

#include <QString>
#include <QSize>
#include <QColor>
#include <QFont>

namespace EPFText
{

class TextNodePrivate;

class TextNode
{
public:
    TextNode();
    TextNode(const TextNode &ref);
    ~TextNode();

    int width() const;
    int widthForRange(int start, int len) const;
    QSize sizeForString(QString str) const;
    int height() const;

    TextNode copy() const;

    QString text() const;
    QFont font() const;
    QColor color() const;

    void setLetterSpacing(double spacing) const;
    void setWordSpacing(double spacing) const;

    virtual TextNode& operator=(const TextNode &ref);

private:

    TextNodePrivate *m_p;
    friend class Paragraph;
    friend class Document;
};

}

#endif // TEXTNODE_H
