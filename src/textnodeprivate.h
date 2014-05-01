#ifndef TEXTNODEPRIVATE_H
#define TEXTNODEPRIVATE_H

#include <QString>
#include <QFont>
#include <QStringList>
#include <QColor>

namespace EPFText
{

class ParagraphPrivate;

class TextNodePrivate
{
public:
    TextNodePrivate();

private:

    void setStyle();

    int iRefCount;

    QString sText;
    QFont font;
    QStringList cstyles;
    QColor color;

    ParagraphPrivate *pParagraph;

    friend class TextNode;
    friend class Document;
    friend class Paragraph;
};

}

#endif // TEXTNODEPRIVATE_H
