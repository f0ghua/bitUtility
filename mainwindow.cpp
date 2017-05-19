#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbHex_clicked()
{
    QString output;

    if (ui->leHex->text().isEmpty())
        return;

    bool ok;
    qint64 hexVal = ui->leHex->text().toLongLong(&ok, 16);
    if (!ok) return;

    int maxBits = (sizeof(hexVal)*8);

    output += QStringLiteral("Enabled Bits(0x%x):");
    for(int bit = maxBits-1; bit >= 0; --bit)
    {
        if(hexVal & (1LL << bit))
            output += QString(" %1").arg(bit);
    }

    ui->pteOutput->document()->setPlainText(output);
}

void MainWindow::on_pbBits_clicked()
{
    QString output;
    qint64 hexVal = 0;
    QString input = ui->leBits->text().simplified().replace(" ", "");
    QByteArray ba = input.toLatin1();

    for (int i = 0; i < ba.size(); ++i) {
        qDebug() << QObject::tr("ba[%1] = %2").arg(i).arg(ba.at(i));
        hexVal |= (1LL << (ba.at(i) - '0'));
    }
    output = "0x";
    output += QString::number(hexVal, 16).toUpper();
    ui->pteOutput->document()->setPlainText(output);
}
