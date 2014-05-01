#include "document.h"
#include "documentprivate.h"
#include "paragraphprivate.h"
#include "textnodeprivate.h"
#include <QPainter>
#include "pugixml.hpp"
#include <QDebug>

using namespace EPFText;

Document::Document()
{
    m_p = new DocumentPrivate();
}

Document::Document(const Document &d)
{
    m_p = d.m_p;
    m_p->iRefcount++;
}

Document::~Document()
{
    if (--m_p->iRefcount <= 0)
        delete m_p;
}

int Document::fromData(QByteArray &data) const
{
    pugi::xml_document xml;
    pugi::xml_parse_result r = xml.load_buffer(data.constData(),data.size());

    if (!r)
        return EPFT_PARSE_ERROR;

    /*QByteArray styledata;

    //get stylesheet
    for (pugi::xml_node style = xml.child("epft").child("style"); style; style = style.next_sibling("style"))
    {
        if (QString(style.attribute("type").as_string()) == "text/ops")
        {

        }
    }*/

    pugi::xml_node content = xml.child("epft").child("content");

    for (pugi::xml_node p = content.child("p"); p; p = p.next_sibling("p"))
    {
        Paragraph pp;
        pp.m_p->sPstyle = p.attribute("pstyle").as_string("");
        addParagraph(pp);
        for (pugi::xml_node t = p.child("t");t;t = t.next_sibling("t"))
        {
            TextNode tt;
            QString cstyle = t.attribute("cstyle").as_string("");
            if (cstyle != "")
                tt.m_p->cstyles = cstyle.split(QRegExp(" +"),QString::SkipEmptyParts);
            tt.m_p->sText = t.child_value();
            pp.addTextNode(tt);
        }
    }

    return EPFT_OK;
}

QString Document::toPlainText() const
{
    QString str;

    for (int i=0;i<m_p->paragraphs.size();i++)
    {
        if (i>0)
            str+="\n\n";
        str += m_p->paragraphs[i].plainText();
    }
    return str;
}

QByteArray Document::toData() const
{
    QString xml = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                  "<epft version=\"1.0\">\n"
                  "\t<content>\n";

    for (int i=0;i<paragraphCount();i++)
    {
        Paragraph p = paragraph(i);
        if (p.m_p->sPstyle != "")
            xml += "\t\t<p pstyle=\"" + p.m_p->sPstyle + "\">\n";
        else
            xml += "\t\t<p>\n";

        for (int n=0;n<p.m_p->nodes.size();n++)
        {
            TextNode node = p.textNode(n);
            if (node.m_p->cstyles.size() > 0)
            {
                xml += "\t\t\t<t cstyle=\"";
                for (int t=0;node.m_p->cstyles.size();t++)
                {
                    if (t>0)
                        xml += " ";
                    xml += node.m_p->cstyles[t];
                }
                xml += "\">";
            }
            else
                xml += "\t\t\t<t>";
            xml += node.text() + "</t>\n";
        }
        xml += "\t\t</p>\n";
    }
    xml += "\t</content>\n<epft>";

    return xml.toUtf8();
}

void Document::setStyleInfo(QOPS::Propsheet &propsheet, QString ns) const
{
    m_p->stylesheet = propsheet;
    m_p->sPropsheetNS = ns;
}

void Document::format() const
{
    QString ns = m_p->sPropsheetNS;
    int w;
    int h=0;

    if (ns != "")
        ns += "::";
    m_p->paragraphs_formatted.clear();
    for (int i=0;i<paragraphCount();i++)
    {
        w=0;
        Paragraph p = paragraph(i);
        Paragraph np = p.copy();
        m_p->paragraphs_formatted.append(np);
        //theun magic hier
        //QOPS::Table pstyle = m_p->stylesheet.objectPropertyTable(p.m_p->sPstyle,ns+"pstyle");
        //pstyle.property("first-line-indent").toInt();
        QList<int> line;
        for (int n=0;n<np.textNodeCount();n++)
        {
            if (w + np.textNode(n).width() > m_p->rect.width())
            {
                //break text node
                TextNode tnode = np.textNode(n);
                QString str = tnode.text();

                int f,lf;
                lf = 0;
                int off = 0;
                while (true)
                {
                    f=str.indexOf(" ",off);
                    if (f == -1 && lf == 0)
                        break;
                    else if (f == -1)
                        f = str.size();

                    if (tnode.widthForRange(0,f) + w > m_p->rect.width())
                    {
                        if (lf == 0)
                            break;
                        TextNode pnode = tnode.copy();
                        pnode.m_p->sText = str.mid(lf).replace(QRegExp("^ +"),"");
                        np.insertTextNode(pnode,n+1);
                        tnode.m_p->sText = str.left(lf);
                        break;
                    }

                    if (f == str.size())
                        break;

                    lf = f;
                    off = f+1;
                }

                if (lf == 0)
                {
                    //could not break, break on letter if this was the first node on the line
                    int tw;
                    if (line.size() == 0)
                    {
                        for (tw=1;(tw <= str.size() && tnode.widthForRange(0,tw) + w <= m_p->rect.width());tw++);
                        TextNode pnode = tnode.copy();
                        pnode.m_p->sText = str.mid(tw).replace(QRegExp("^ +"),"");
                        np.insertTextNode(pnode,n+1);
                        tnode.m_p->sText = str.left(tw);
                        line.append(n);
                    }
                    else
                    {
                        //move to next line
                        n--;
                    }
                    w=0;
                    np.m_p->lines.append(line);
                    line.clear();
                }
                else
                {
                    w=0;
                    line.append(n);
                    np.m_p->lines.append(line);
                    line.clear();
                }

            }
            else
            {
                w += np.textNode(n).width();
                line.append(n);
            }

        }
        //
        np.m_p->lines.append(line);
    }

    m_p->docrect = m_p->rect;
    if (m_p->docrect.height() == 0)
    {
        for (int i=0;i<m_p->paragraphs_formatted.size();i++)
        {
            Paragraph p = m_p->paragraphs_formatted[i];
            //y = space before, p[i-1] space after
            for (int n=0;n<p.m_p->lines.size();n++) //go trough all text lines
            {
                int lineheight = 0;
                for (int t=0;t<p.m_p->lines[n].size();t++) //go trough all textnodes in line
                {
                    TextNode tn = p.textNode(p.m_p->lines[n][t]);

                    if (lineheight < tn.height())
                        lineheight = tn.height();
                }
                h += lineheight;
            }
        }
        m_p->docrect.setHeight(h);
    }
}

void Document::setSize(QSize &size) const
{
    m_p->rect = size;
}
void Document::setWidth(int width) const
{
    m_p->rect.setWidth(width);
}

QSize Document::documentSize() const
{
    return m_p->docrect;
}

int Document::paragraphCount() const
{
    return m_p->paragraphs.size();
}
Paragraph Document::paragraph(int index) const
{
    if (index < 0 || index >= m_p->paragraphs.size())
        return Paragraph();

    return m_p->paragraphs[index];
}
void Document::addParagraph(Paragraph p) const
{
    m_p->paragraphs.append(p);
    p.m_p->pDocument = m_p;
    for (int i=0;i<p.textNodeCount();i++)
        p.textNode(i).m_p->setStyle();
}
void Document::insertParagraph(Paragraph p, int pos) const
{
    m_p->paragraphs.insert(pos, p);
    p.m_p->pDocument = m_p;
    for (int i=0;i<p.textNodeCount();i++)
        p.textNode(i).m_p->setStyle();
}
void Document::removeParagraph(int index) const
{
    if (index < 0 || index >= m_p->paragraphs.size())
        return;

    m_p->paragraphs[index].m_p->pDocument = 0;
    m_p->paragraphs.removeAt(index);
}

void Document::render(QPainter *painter, QRect area) const
{
    int x = 0;
    int y = 0;
    int lineheight = 0;



    for (int i=0;i<m_p->paragraphs_formatted.size();i++) //go trough all formatted paragraphs
    {
        Paragraph p = m_p->paragraphs_formatted[i];
        //y = space before, p[i-1] space after
        for (int n=0;n<p.m_p->lines.size();n++) //go trough all text lines
        {
            lineheight = 0;
            x = 0;
            //x = line indent, first-line indent;
            for (int t=0;t<p.m_p->lines[n].size();t++) //go trough all textnodes in line
            {
                TextNode tn = p.textNode(p.m_p->lines[n][t]);

                if (lineheight < tn.height())
                    lineheight = tn.height();
            }
            y += lineheight; //+ spacing...
            for (int t=0;t<p.m_p->lines[n].size();t++) //go trough all textnodes in line
            {
                TextNode tn = p.textNode(p.m_p->lines[n][t]);
                painter->setFont(tn.font());
                painter->setPen(tn.color());
                painter->drawText(x,y,tn.text());

                x += tn.width();
            }
        }
    }
}

Document& Document::operator=(const Document &ref)
{
    if (--m_p->iRefcount <= 0)
        delete m_p;
    m_p = ref.m_p;
    m_p->iRefcount++;
    return *this;
}

/*
 * Private Impl.
 */

DocumentPrivate::DocumentPrivate() : iRefcount(1)
{

}
