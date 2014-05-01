#ifndef EPFTEXTWIDGET_H
#define EPFTEXTWIDGET_H

#include <QWidget>
#include "document.h"

class EPFTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EPFTextWidget(QWidget *parent = 0);

    void load(QByteArray &data, QOPS::Propsheet sheet);

signals:

public slots:

protected:

    virtual void paintEvent(QPaintEvent *ev);
    virtual void resizeEvent(QResizeEvent *ev);

private:

    EPFText::Document m_doc;
    bool m_bLoaded;
};

#endif // EPFTEXTWIDGET_H
