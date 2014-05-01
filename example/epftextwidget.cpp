#include "epftextwidget.h"
#include <QPainter>
#include "qopslib.h"

EPFTextWidget::EPFTextWidget(QWidget *parent) :
    QWidget(parent), m_bLoaded(false)
{
}

void EPFTextWidget::load(QByteArray &data, QOPS::Propsheet sheet)
{
    m_doc.setStyleInfo(sheet,QString());

    if (m_doc.fromData(data) != EPFT_OK)
        return;

    m_bLoaded = true;
    m_doc.setWidth(width());
    m_doc.format();
    update();
}

void EPFTextWidget::paintEvent(QPaintEvent *ev)
{
    QPainter p;

    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing,true);

    p.fillRect(0,0,width(),height(),QColor(220,220,220));

    if (m_bLoaded)
        m_doc.render(&p);


    p.end();
}

void EPFTextWidget::resizeEvent(QResizeEvent *ev)
{
    if (!m_bLoaded)
        return;
    m_doc.setWidth(width());
    m_doc.format();
}
