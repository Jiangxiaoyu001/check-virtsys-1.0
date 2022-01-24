#include <QApplication>
#include <QDebug>
#include <checkVirsys/mainwindow.h>
//MainWindow * w=nullptr;
//class baseWindowManager:public QApplication{
//    //Q_OBJECT
//public:
//    baseWindowManager(int &argc,char ** argv);
////    virtual bool notify(QObject *, QEvent *) override;
//    virtual bool eventFilter(QObject *obj, QEvent *event) override;
//};

//baseWindowManager::baseWindowManager(int &argc, char **argv):QApplication(argc,argv)
//{

//}

//bool baseWindowManager::eventFilter(QObject * obj, QEvent * e)
//{
//    if(::w&&obj){
//    switch (e->type()) {
//    case QEvent::MouseMove:
//    case QEvent::MouseButtonPress:
//    case QEvent::MouseButtonRelease:
//    case QEvent::HoverMove:
//    case QEvent::HoverEnter:
////        qDebug()<<"obj:"<<obj<<"event->type:"<<e->type();
//        w->widgetEventHandler(e);
//        return true;
//        break;
//    default:
////        return QApplication::notify(obj,e);
//        return QApplication::eventFilter(obj,e);
//    }
//    }
////    return QApplication::notify(obj,e);
//    return QApplication::eventFilter(obj,e);
//}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    baseWindowManager a(argc, argv);
//    Check_Virtsys_Window * w=new Check_Virtsys_Window;
    MainWindow * w = MainWindow::getInface();
    w->installEventFilter(w);
    w->show();
    return a.exec();
}




