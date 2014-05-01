#ifndef PARAGRAPHPRIVATE_H
#define PARAGRAPHPRIVATE_H

#include <QList>
#include "textnode.h"

namespace EPFText
{

class DocumentPrivate;

class ParagraphPrivate
{
public:
    ParagraphPrivate();

private:

    int iRefCount;

    QList<TextNode> nodes;
    QList<QList<int> > lines;
    DocumentPrivate *pDocument;

    QString sPstyle;

    friend class Paragraph;
    friend class TextNodePrivate;
    friend class Document;
};

}

#endif // PARAGRAPHPRIVATE_H
