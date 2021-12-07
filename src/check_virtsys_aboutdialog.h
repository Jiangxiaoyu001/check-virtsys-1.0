#ifndef CHECK_VIRTSYS_ABOUTDIALOG_H
#define CHECK_VIRTSYS_ABOUTDIALOG_H

#include <QLabel>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QMouseEvent>
#include <QPlainTextEdit>
class CHECK_VIRTSYS_MANAGER;
class CHECK_VIRTSYS_ABOUTDIALOG:public QWidget
{
public:
    CHECK_VIRTSYS_ABOUTDIALOG(QWidget * parent=nullptr);
    ~CHECK_VIRTSYS_ABOUTDIALOG();
    QDialog * & check_virtsys_getAboutDialog();
    void check_virtsys_showAboutDialog();
    void check_virtsys_aboutDialogInit();
protected:
    QDialog * dialog;
    QLabel * m_label;
    CHECK_VIRTSYS_MANAGER * virManager;
//    void mousePressEvent(QMouseEvent *event)override{
//        qDebug()<<"----dialog mousePressEvent--------"<<endl;
//        event->accept();
//    }
};

#endif // CHECK_VIRTSYS_ABOUTDIALOG_H
