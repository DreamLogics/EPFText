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
#ifndef PARAGRAPH_H
#define PARAGRAPH_H

#include "textnode.h"
#include <QString>

namespace EPFText
{

class ParagraphPrivate;

class Paragraph
{
public:
    Paragraph();
    Paragraph(const Paragraph &ref);
    ~Paragraph();

    int textNodeCount() const;
    TextNode textNode(int index) const;
    void addTextNode(TextNode node) const;
    void insertTextNode(TextNode node, int pos) const;
    void removeTextNode(int index) const;

    int lineCount() const;
    QList<int> textLine() const;

    int lineIndent() const;
    int firstLineIndent() const;
    int lineHeight() const;

    Paragraph copy() const;

    QString plainText() const;
    int widthForRange(int start, int len) const;
    int heightForRange(int start, int len) const;

    virtual Paragraph& operator=(const Paragraph &ref);

private:

    ParagraphPrivate* m_p;
    friend class Document;
};

}

#endif // PARAGRAPH_H
