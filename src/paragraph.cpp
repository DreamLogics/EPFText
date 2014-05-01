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
#include "paragraph.h"
#include "paragraphprivate.h"
#include "textnodeprivate.h"

using namespace EPFText;

Paragraph::Paragraph()
{
    m_p = new ParagraphPrivate();
}

Paragraph::Paragraph(const Paragraph &ref)
{
    m_p = ref.m_p;
    m_p->iRefCount++;
}

Paragraph::~Paragraph()
{
    if (--m_p->iRefCount <= 0)
        delete m_p;
}

Paragraph Paragraph::copy() const
{
    Paragraph p;
    p.m_p->sPstyle = m_p->sPstyle;

    for (int i=0;i<textNodeCount();i++)
        p.addTextNode(textNode(i).copy());

    return p;
}

int Paragraph::textNodeCount() const
{
    return m_p->nodes.size();
}
TextNode Paragraph::textNode(int index) const
{
    if (index < 0 || index >= m_p->nodes.size())
        return TextNode();

    return m_p->nodes[index];
}
void Paragraph::addTextNode(TextNode node) const
{
    m_p->nodes.append(node);
    node.m_p->pParagraph = m_p;
    node.m_p->setStyle();
}
void Paragraph::insertTextNode(TextNode node, int pos) const
{
    m_p->nodes.insert(pos,node);
    node.m_p->pParagraph = m_p;
    node.m_p->setStyle();
}

void Paragraph::removeTextNode(int index) const
{
    if (index < 0 || index >= m_p->nodes.size())
        return;

    m_p->nodes[index].m_p->pParagraph = 0;
    m_p->nodes.removeAt(index);
}

QString Paragraph::plainText() const
{
    QString str;
    for (int i=0;i<m_p->nodes.size();i++)
        str += m_p->nodes[i].text();
    return str;
}
int Paragraph::widthForRange(int start, int len) const
{
    int pos,sz,spos,ln;
    int width = 0;

    pos = 0;

    for (int i=0;i<m_p->nodes.size();i++)
    {
        TextNode node = m_p->nodes[i];
        sz = node.text().size();
        if (start > pos+sz)
        {
            pos += sz;
            continue;
        }

        spos = start - pos;

        if (spos + len > sz)
        {
            len = spos + len - sz;
            ln = sz - spos;
        }
        else
            ln = len;

        width += node.widthForRange(spos,ln);

        if (len == ln)
            break;
        else
            start = pos + sz;

        pos += sz;
    }

    return width;
}
int Paragraph::heightForRange(int start, int len) const
{
    int h=0;
    for (int i=0;i<m_p->nodes.size();i++)
    {
        TextNode node = m_p->nodes[i];
        if (node.height() > h)
            h = node.height();
    }
    return h;
}

Paragraph& Paragraph::operator=(const Paragraph &ref)
{
    if (--m_p->iRefCount <= 0)
        delete m_p;
    m_p = ref.m_p;
    m_p->iRefCount++;
    return *this;
}

/*
 * Private Impl.
 */

ParagraphPrivate::ParagraphPrivate() : iRefCount(1), pDocument(0)
{

}
