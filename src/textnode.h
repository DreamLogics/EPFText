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
