#include "textnode.h"
#include "textnodeprivate.h"
#include <QFontMetrics>
#include "paragraphprivate.h"
#include "documentprivate.h"

using namespace EPFText;

TextNode::TextNode()
{
    m_p = new TextNodePrivate();
}

TextNode::TextNode(const TextNode &ref)
{
    m_p = ref.m_p;
    m_p->iRefCount++;
}

TextNode::~TextNode()
{
    if (--m_p->iRefCount <= 0)
        delete m_p;
}

int TextNode::width() const
{
    return sizeForString(m_p->sText).width();
}
int TextNode::widthForRange(int start, int len) const
{
    QSize s = sizeForString(m_p->sText.mid(start,len));
    return s.width();
}
QSize TextNode::sizeForString(QString str) const
{
    QFontMetrics fm(m_p->font);
    return fm.size(Qt::TextSingleLine,str);
}

TextNode TextNode::copy() const
{
    TextNode t;
    t.m_p->color = m_p->color;
    t.m_p->cstyles = m_p->cstyles;
    t.m_p->font = m_p->font;
    t.m_p->sText = m_p->sText;
    return t;
}

int TextNode::height() const
{
    return sizeForString(m_p->sText).height();
}

QString TextNode::text() const
{
    return m_p->sText;
}

TextNode& TextNode::operator=(const TextNode &ref)
{
    if (--m_p->iRefCount <= 0)
        delete m_p;
    m_p = ref.m_p;
    m_p->iRefCount++;
    return *this;
}

QFont TextNode::font() const
{
    return m_p->font;
}

QColor TextNode::color() const
{
    return m_p->color;
}

void TextNode::setLetterSpacing(double spacing) const
{
    m_p->font.setLetterSpacing(QFont::AbsoluteSpacing,spacing);
}
void TextNode::setWordSpacing(double spacing) const
{
    m_p->font.setWordSpacing(spacing);
}

/*
 * Private Impl.
 */

TextNodePrivate::TextNodePrivate() : iRefCount(1), pParagraph(0)
{

}

void TextNodePrivate::setStyle()
{
    if (!pParagraph)
        return;
    if (!pParagraph->pDocument)
        return;
    QString ns = pParagraph->pDocument->sPropsheetNS;
    if (ns != "")
        ns += "::";
    else
        ns = QString();
    QOPS::Table style = pParagraph->pDocument->stylesheet.objectPropertyTable(pParagraph->sPstyle,ns+"pstyles").copy();
    //TODO: if style empty, merge from first found (for info provider)
    for (int i=0;i<cstyles.size();i++)
        style.merge(pParagraph->pDocument->stylesheet.objectPropertyTable(cstyles[i],ns+"cstyles"),true,true);

    font.setFamily(style.property("font-family").toString());
    font.setPixelSize(style.property("font-size").toInt());

    if (style.property("font-weight").toString() == "bold")
        font.setBold(true);
    else
        font.setBold(false);

    if (style.property("font-style").toString() == "italic")
        font.setItalic(true);
    else
        font.setItalic(false);

    if (!style.property("color").isNull())
        color = style.property("color").toColor();
    else
        color = QColor(0,0,0);

    if (style.property("text-decoration").toString() == "underline")
        font.setUnderline(true);
    else
        font.setUnderline(false);

    //TODO set other font stuff
}
