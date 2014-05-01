/****************************************************************************
**
** EPFText text render engine for the EPF Text format.
** Part of the LEAF EPF renderer.
** http://leaf.dreamlogics.com/
**
** Copyright (C) 2014 DreamLogics
** Copyright (C) 2014 Stefan Ladage <sladage@gmail.com>
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published
** by the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "epftextwidget.h"
#include <QFile>
#include <QFileDialog>
#include "opsinformationprovider.h"
#include "qopslib.h"
#include <QDebug>

class infoprovider : public QOPS::InformationProvider
{
public:
    infoprovider()
    {

    }

    virtual QString sysVarForObject(QString varname, QString id, QString ns)
    {
        return QString();
    }

    virtual QString valueForProp(QString prop, QString value, int index, QStringList rules)
    {
        return value.replace("\"","");
    }

    virtual QByteArray importPropsheet(QString filename)
    {
        return QByteArray();
    }

    virtual QOPS::ValueType valueTypeForProp(QString prop, QString value, int index, QStringList rules)
    {
        return QOPS::vtString;
    }
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_pIP = new infoprovider();

    m_pTW = new EPFTextWidget(this);
    ui->verticalLayout->addWidget(m_pTW);
    m_pTW->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_pIP;
    delete m_pTW;
}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"Open epf text.",QString(),"EPFText (*.xml)");

    if (file.isNull())
        return;

    QFile sf(file.left(file.size()-3)+"ops");
    QFile f(file);

    if (!f.open(QIODevice::ReadOnly))
        return;

    if (!sf.open(QIODevice::ReadOnly))
        return;

    QByteArray data,sdata;

    data = f.readAll();
    f.close();

    sdata = sf.readAll();
    sf.close();

    QOPS::PropsheetReader reader;
    QOPS::Propsheet sheet = reader.fromUtf8String(sdata);

    if (reader.getError() != QOPS_NO_ERR)
    {
        qDebug() << reader.getErrorMsg();
        return;
    }

    m_pTW->load(data,sheet);
}
