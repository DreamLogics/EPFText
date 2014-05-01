#ifndef DOCUMENTPRIVATE_H
#define DOCUMENTPRIVATE_H

#include <QList>
#include "paragraph.h"
#include <qopslib.h>
#include <QSize>

namespace EPFText
{

class DocumentPrivate
{
public:
    DocumentPrivate();

private:

    QList<Paragraph> paragraphs;
    QList<Paragraph> paragraphs_formatted;

    QOPS::Propsheet stylesheet;
    QString sPropsheetNS;

    QSize rect;
    QSize docrect;

    int iRefcount;

    friend class Document;
    friend class ParagraphPrivate;
    friend class TextNodePrivate;
};

}

#endif // DOCUMENTPRIVATE_H
