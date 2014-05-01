#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "paragraph.h"
#include <QRectF>
#include <qopslib.h>

#define EPFT_OK 0
#define EPFT_PARSE_ERROR 1

class QPainter;

namespace EPFText
{

class DocumentPrivate;

class Document
{
public:
    Document();
    Document(const Document &d);
    ~Document();

    int fromData(QByteArray &data) const;

    QString toPlainText() const;
    QByteArray toData() const;

    void setStyleInfo(QOPS::Propsheet &propsheet, QString ns) const;

    void format() const;
    void setSize(QSize &size) const;
    void setWidth(int width) const;
    QSize documentSize() const;

    int paragraphCount() const;
    Paragraph paragraph(int index) const;
    void addParagraph(Paragraph p) const;
    void insertParagraph(Paragraph p, int pos) const;
    void removeParagraph(int index) const;

    void render(QPainter *p, QRect area = QRect()) const;

    virtual Document& operator=(const Document &ref);

private:

    DocumentPrivate *m_p;

};

}

#endif // DOCUMENT_H
