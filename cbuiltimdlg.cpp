#include "cbuiltimdlg.h"
#include <QGridLayout>
#include <QPrinter>
#include <QPrintDialog>
#include <QPageSetupDialog>  // Include the missing header
#include <QThread>           // For QThread::msleep
#include <QtWidgets>

CBuiltimDlg::CBuiltimDlg(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *gridLayout = new QGridLayout;
    displayTextEdit = new QTextEdit(QStringLiteral("Qt的標準通用對話盒"));
    colorPushBtn = new QPushButton(QStringLiteral("背景顏色盒"));
    errorPushBtn = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn = new QPushButton(QStringLiteral("列印對話盒"));
    testPushBtn = new QPushButton(QStringLiteral("文字顏色盒"));
    gridLayout-> addWidget(colorPushBtn, 0, 0, 1, 1);
    gridLayout-> addWidget(errorPushBtn, 0, 1, 1, 1);
    gridLayout-> addWidget(filePushBtn, 0, 2, 1, 1);
    gridLayout-> addWidget(fontPushBtn, 1, 0, 1, 1);
    gridLayout-> addWidget(inputPushBtn, 1, 1, 1, 1);
    gridLayout-> addWidget(pagePushBtn, 1, 2, 1, 1);
    gridLayout-> addWidget(progressPushBtn, 2, 0, 1, 1);
    gridLayout-> addWidget(printPushBtn, 2, 1, 1, 1);
    gridLayout-> addWidget(testPushBtn, 2, 2, 1, 1);
    gridLayout-> addWidget(displayTextEdit, 3, 0, 3, 3);
    setLayout(gridLayout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(400, 300);
    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(filePushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(fontPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(inputPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(pagePushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(progressPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(printPushBtn, SIGNAL(clicked()), this, SLOT(doPushBth()));
    connect(testPushBtn, SIGNAL(clicked()), this, SLOT(dotextcolor()));
}

CBuiltimDlg::~CBuiltimDlg() {}
void CBuiltimDlg::dotextcolor()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == testPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color = QColorDialog::getColor(palette.color(QPalette::ToolTipBase), this, tr("設定文字顏色"));
        if (color.isValid())
        {
            palette.setColor(QPalette::Text, color);
            displayTextEdit->setPalette(palette);
        }
    }
}

void CBuiltimDlg::doPushBth()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    if (btn == colorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor& color = QColorDialog::getColor(palette.color(QPalette::Base), this, tr("設定背景顏色"));
        if (color.isValid())
        {
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
        }
    }

    if (btn == filePushBtn) {
        QString fileName = QFileDialog::getOpenFileName(this, tr("開啟檔案"), ".", tr("任何檔案(*.*);;文字檔(*.txt);;XML檔(*.xml)"));
        displayTextEdit->setText(fileName);
    }
    if (btn == errorPushBtn)
    {
        QErrorMessage box(this);
        box.setWindowTitle(tr("錯誤訊息盒"));
        box.showMessage(tr("錯誤訊息盒實例xx :"));
        box.exec();
        box.showMessage(tr("錯誤訊息盒實例yy :"));
        box.exec();
        box.showMessage(tr("錯誤訊息盒實例zz :"));
        box.exec();
    }
    if (btn == fontPushBtn) {
        bool ok;
        QFont font = QFontDialog::getFont(&ok, displayTextEdit->font(), this);
        if (ok) {
            displayTextEdit->setFont(font);
        }
    }
    if (btn == inputPushBtn) {
        bool ok;
        QString text = QInputDialog::getText(this, tr("輸入對話盒"), tr("請輸入內容："), QLineEdit::Normal, "", &ok);
        if (ok && !text.isEmpty()) {
            displayTextEdit->setText(text);
        }
    }
    if (btn == pagePushBtn) {
        QPageSetupDialog pageDialog(this);
        pageDialog.exec();
    }
    if (btn == progressPushBtn) {
        QProgressDialog progress(tr("正在複製檔案..."), tr("取消"), 0, 10000, this);
        progress.setWindowTitle(tr("進度對話盒"));
        progress.show();
        for (int i = 0; i < 10000; i++) {
            progress.setValue(i);
            qApp->processEvents();
            if(progress.wasCanceled())
                break;
            qDebug() << i;
        }
        QThread::msleep(100);  // Replace _sleep with QThread::msleep
    }
    if (btn == printPushBtn) {
        QPrinter printer;
        QPrintDialog printDialog(&printer, this);
        if (printDialog.exec() == QDialog::Accepted) {
            return;
        }
    }
}
