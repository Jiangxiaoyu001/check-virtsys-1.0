#ifndef CHECK_VIRTSYS_DETAILEDWINDOW_H
#define CHECK_VIRTSYS_DETAILEDWINDOW_H

#include <QLabel>
#include <QDialog>
#include <QWidget>
#include <QObject>
#include <QMouseEvent>
#include <QListWidget>
#include <QListWidgetItem>
#include <QPushButton>
#include <iostream>

#include <QTreeWidget>
#include <QTreeView>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QStandardItemModel>
//class _listStyle_;
class  CHECK_VIRTSYS_MANAGER ;

class CHECK_VIRTSYS_DETAILEDWINDOW:public QWidget
{
public:
    CHECK_VIRTSYS_DETAILEDWINDOW(QWidget * parent=nullptr);
    ~CHECK_VIRTSYS_DETAILEDWINDOW();
    void check_virtsys_detailWinInit();
private:
    QHBoxLayout *m_vBoxLay;
    QPlainTextEdit * plEdit;
    /*sub class _listWid_ */
    class _listWid_:public QListWidget{
    public:
        _listWid_(QWidget * parent=nullptr);
        ~_listWid_();
        void check_virtsys_detailWinInit();
    protected:
        /* over load mouse-Event*/
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseDoubleClickEvent(QMouseEvent *event);
    private:
        QLabel *m_label;
        QDialog * dialog;
        QListWidget * m_listWidget;
        QListWidgetItem * m_listWinItem;
        QPushButton * btn;
        QHBoxLayout * vbLayout;
        void check_virtsys_updataDetailWid(int);
    public slots:
           void _check_virtsys_updataDetailWid_(int);
    }* m_lswid;

   /* sub class _listStyle_*/
    class _listStyle_:public QObject{

    public:
        _listStyle_( QWidget * parent=nullptr);
        ~_listStyle_();
        QListWidget * listWid;
        QPoint m_mousePoint;
        QListWidgetItem * m_lisItem;
        void check_virtsys_loadQss();
        void check_virtsys_setMousePoint( QPoint &);
        QPoint check_virtsys_mousePonit();
        QSize check_virtsys_listWidSize();
        CHECK_VIRTSYS_MANAGER *virManager;
        void check_virtsys_listWidCreate(_listWid_ *);
        void check_virtsys_listWidDestroy();
    }static *m_ls;

    /* sub class */
    class _treeWid_:public QTreeView{
    public:
        _treeWid_(QWidget * parent =nullptr);
        ~_treeWid_();
        void check_virtsys_setXml(QString xml){
            this->xmlInfo.clear();
            this->xmlInfo=xml;
        }
        QString & check_virtsys_getXml(){
            return this->xmlInfo;
        }
        void check_virtsys_updataTreeView();
    private:
        QString xmlInfo;
        QHBoxLayout * m_hBoxLay;
        QTreeView *  _m_treeView_;
        QStandardItemModel * model;

        void check_virtsys_treeViewInit();
    } static *m_treeWid;

signals:

private slots:
};

#endif // CHECK_VIRTSYS_DETAILEDWINDOW_H
