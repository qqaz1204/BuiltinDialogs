#ifndef CBUILTIMDLG_H
#define CBUILTIMDLG_H

#include <QDialog>
#include <QtWidgets>
#include <QPushButton>
#include <QTextEdit>

class CBuiltimDlg : public QDialog
{
    Q_OBJECT

public:
    CBuiltimDlg(QWidget *parent = nullptr);
    ~CBuiltimDlg();
private:
    QTextEdit *displayTextEdit;
    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;
    QPushButton *testPushBtn;
private slots:
    void doPushBth();
    void dotextcolor();
};
#endif // CBUILTIMDLG_H
