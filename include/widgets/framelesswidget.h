#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QFrame>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QScreen>

/*
*Description: mouse location point
*@Value:0: edge null
*/
enum {
    EDGENULL = 0,
    TOPLEFT,
    TOPRIGHT,
    BOTTOMRIGHT,
    BOTTOMLEFT,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
};




class FramelessWidget : public QFrame //QMainWindow
{
    Q_OBJECT
public:
    explicit FramelessWidget(QWidget *parent = nullptr);
    virtual ~FramelessWidget();
protected:
//    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;
    virtual bool eventFilter(QObject *obj, QEvent *event) override;
    /* code test */

    bool mouse_down, /* 0:release, 1:pressed*/
         zoom,       /* 0:null, 1:drag */
         move;       /* 0:null, 1:move*/

    QRect m_windowRectBeforeStretch;

    bool maxBtnPress;
    int edgeHeight,
        edgeValue,
        is_on_edge;

    QPoint last_point,
           current_point;

    QWidget *widget;
    QPushButton * minBtn,
                * maxBtn,
                * closeBtn,
                * generalBtn;

    QGridLayout *Glayout  ;
    QHBoxLayout *Hlayout ;
    QVBoxLayout *Vlayout ;
    void  createLayout();
    void  frameWidgetInit();
    void loadQss();
	/* screen resolution */
	QRect currScreenRes();
	std::list<QScreen *> allScreenResolution();
 
    void customBtnAbility();
    void MenuIconHandler(QHBoxLayout *Hlayout);

    virtual void switchPage();

    void paintEvent(QPaintEvent *) override;
    void  mouseEdgeRect(QPoint p);
    void  updateCursor();                            /*update cursor shape*/
    void  mouseIsOnEdge(QPoint point, QRect rect);   /* mouse hover edge */
    void  resizeWidget(QPoint p);                    /* resize widget */
    void  widgetEventHandler(QEvent *e);             /* deal widget event */
    void  mouseHoverEventHandler(QHoverEvent *e);    /* mouse hoverEvent handle */
    void  mouseMoveEventHandler(QMouseEvent *e);     /* mouse move handle */
    void  mousePressEventHandler(QMouseEvent *e);    /* mouse pressEvent handle */
    void  mouseReleaseEventHandler(QMouseEvent *e);  /* mouse releaseEvent handle */
signals:
public:
    void setCentralWidget(QWidget *widget);
};

#endif // FRAMELESSWIDGET_H
