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
