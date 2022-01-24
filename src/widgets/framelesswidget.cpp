#include <QDebug>
#include <QEvent>
#include <QHoverEvent>
#include <iostream>
#include <QPainter>
#include <QGuiApplication>
#include <QGraphicsDropShadowEffect>
#include <widgets/framelesswidget.h>

FramelessWidget::FramelessWidget(QWidget *parent) :
    QFrame(parent),
    mouse_down(0),
    zoom(false),
    move(false),
    maxBtnPress(false),
    edgeHeight(100),
    edgeValue(8),
    is_on_edge(0),
    minBtn(nullptr),
    maxBtn(nullptr),
    closeBtn(nullptr),
    generalBtn(nullptr)
{
    frameWidgetInit();
    createLayout();
    loadQss();
    customBtnAbility();
	allScreenResolution();
}

FramelessWidget::~FramelessWidget()
{

}

QRect FramelessWidget::currScreenRes()
{
	QScreen * screen = QGuiApplication::primaryScreen();
	QRect screenRec=screen->availableGeometry() ;
	/* primary screen resolution  */
	qDebug()<<screenRec.width ()<<screenRec.height ();
	return screenRec;

}

std::list<QScreen *> FramelessWidget::allScreenResolution()
{
    QList<QScreen *> listSce = QGuiApplication::screens();

    std::list<QScreen *> list_screens(0,0);
    for(auto &listScrResolution:listSce){
        qDebug()<<"scrGeometry:"<<listScrResolution->geometry();
        list_screens.push_back(listScrResolution);
    }
	/* erase list  */
    for(QList<QScreen *>::iterator itr=listSce.begin();itr != listSce.end(); itr++){
        listSce.erase(itr);
    }
	/* Now ,TODO:*/

    return list_screens.size() != 0 ? list_screens:list_screens;
}




void FramelessWidget::createLayout()
{
    QPalette m_pal;
    m_pal.setColor(QPalette::Background,QColor(100,100,105));
    this->setPalette(m_pal);
    this->setAutoFillBackground(true);

    QPushButton * minBtn=new QPushButton(this);
    QPushButton * maxBtn=new QPushButton(this);
    QPushButton * closeBtn=new QPushButton(this);
    this->minBtn = minBtn;
    this->maxBtn = maxBtn;
    this->closeBtn = closeBtn;
    minBtn->setObjectName("MinBtn");
    maxBtn->setObjectName("MaxBtn");
    closeBtn->setObjectName("CloseBtn");

    Glayout  = new QGridLayout();
    Hlayout = new QHBoxLayout();
    Vlayout = new QVBoxLayout();

    MenuIconHandler(Hlayout);
//    layout->setHorizontalSpacing(100);
//    layout->setColumnMinimumWidth(0,100);
    Hlayout->addStretch();
    Hlayout->addWidget(minBtn);
    /* Hlayout->addSpacing(20); */
    Hlayout->addWidget(maxBtn);
    /* Hlayout->addSpacing(20); */
    Hlayout->addWidget(closeBtn);
    Hlayout->addSpacing(10);
    Hlayout->setContentsMargins(0,0,0,0);
    Glayout->setVerticalSpacing(1);
    Glayout->addLayout(Hlayout,0,0);
    Glayout->addLayout(Vlayout,1,0);
    setLayout(Glayout);

 }

void FramelessWidget::frameWidgetInit()
{
    //resize(800,800);
    setAttribute(Qt::WA_Hover,true);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint);
//    setAttribute(Qt::WA_TranslucentBackground);
    setFrameShape(QFrame::StyledPanel);
}

void FramelessWidget::loadQss()
{
    //:/frameLessWidget.qss /usr/share/qss/frameLessWidget.qss
	QRect rec=currScreenRes();
	//std::string str;
	QString str("");
	if(rec.width() > 1920)
		str.append(":/resources/frameLessWidget_4k.qss");
    	//QFile m_file(":/resources/frameLessWidget_4k.qss");
	else
		str.append(":/resources/frameLessWidget.qss");
		//QFile m_file(":/resources/frameLessWidget.qss");
    QFile m_file(str);
	m_file.open(QFile::ReadOnly);
    QString m_styleSheet=QLatin1String(m_file.readAll());
    this->setStyleSheet(m_styleSheet);
}

void FramelessWidget::customBtnAbility()
{
    connect(closeBtn,&QPushButton::clicked,this,[&](){close();});
    connect(minBtn,&QPushButton::clicked,this,[&](){showMinimized();});
    connect(maxBtn,&QPushButton::clicked,this,
        [&](){
        if(!maxBtnPress){
            showFullScreen();
            maxBtnPress = true;
        }else{
            showNormal();
            maxBtnPress = false;
        };});
    connect(generalBtn,&QPushButton::clicked,this,[=](){switchPage();});
}

void FramelessWidget::MenuIconHandler(QHBoxLayout *Hlayout)
{
    generalBtn = new QPushButton(this);
    generalBtn->setCheckable(true);
    generalBtn->setObjectName("generalBtn");
    Hlayout->addWidget(generalBtn);

}

void FramelessWidget::switchPage()
{
    QPushButton * btn =qobject_cast<QPushButton *>(sender());
    if(btn == generalBtn){
        generalBtn->setChecked(true);
    }
}

void FramelessWidget::paintEvent(QPaintEvent * e)
{
    QPainter painter(this);
    QRect b_rect =this->rect();
//    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(100,100,105));

//    painter.setRenderHint(QPainter::Antialiasing);
    b_rect.setWidth(b_rect.width()+1);
    b_rect.setHeight(b_rect.height()+1);
    painter.fillRect(0,0,width(),64,Qt::NoBrush);
    painter.drawRoundedRect(b_rect,13,13);
//    this->setMask(QRegion(0,0,width(),64));
    return QWidget::paintEvent(e);
}


void FramelessWidget::setCentralWidget(QWidget *widget)
{

     widget->setParent(this);
     Vlayout->addWidget(widget);
//     this->layout()->addWidget(widget);
     this->layout()->setContentsMargins(3,0,1,0);
     widget->layout()->setContentsMargins(QMargins()); //QMargins()
//     resize(widget->size());
//     adjustSize();
}







bool FramelessWidget::eventFilter(QObject *obj, QEvent *event)
{
    QWidget * widget = static_cast<QWidget *>(obj);
    if(widget == this){
    switch (event->type()){
    case QEvent::MouseMove:
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::HoverMove:
//    case QEvent::HoverEnter:
//        qDebug()<<"event->type:=========>>"<<event->type();
        widgetEventHandler(event);
        return true;
    default:
        return QObject::eventFilter(obj,event);
    }
  }
    return QObject::eventFilter(obj,event);
}





void FramelessWidget::mouseEdgeRect(QPoint p)
{
    const int width = this->width();
    const int height = this->height();
    QRect topLeft(0,0,edgeValue,edgeValue);
    QRect topRight(width - edgeValue,0,edgeValue,edgeValue);
    QRect bottomLeft(0,height - edgeValue,edgeValue,edgeValue);
    QRect bottomRight(width - edgeValue,height - edgeValue,edgeValue,edgeValue);
    QRect top(edgeValue,0,width-edgeValue*2,edgeValue);
    QRect bottom(edgeValue,height-edgeValue,width-edgeValue*2,edgeValue);
    QRect left(0,edgeValue,edgeValue,height-edgeValue*2);
    QRect right(width - edgeValue,edgeValue,edgeValue,height-edgeValue*2);
    if(topLeft.contains(p))
        is_on_edge = TOPLEFT;
    else if(topRight.contains(p))
        is_on_edge = TOPRIGHT;
    else if(bottomLeft.contains(p))
        is_on_edge = BOTTOMLEFT;
    else if(bottomRight.contains(p))
        is_on_edge = BOTTOMRIGHT;
    else if(top.contains(p))
        is_on_edge = TOP;
    else if(bottom.contains(p))
        is_on_edge = BOTTOM;
    else if(left.contains(p))
        is_on_edge = LEFT;
    else if(right.contains(p))
        is_on_edge = RIGHT;
    else
        is_on_edge = EDGENULL;
      zoom = is_on_edge == EDGENULL ? 0 : 1;
}

void FramelessWidget::updateCursor()
{
    switch (is_on_edge) {
    case TOPLEFT:
    case BOTTOMRIGHT:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case TOPRIGHT:
    case BOTTOMLEFT:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case TOP:
    case BOTTOM:
        setCursor(Qt::SizeVerCursor);
        break;
    case LEFT:
    case RIGHT:
        setCursor(Qt::SizeHorCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void FramelessWidget::resizeWidget(QPoint p)
{
    QPoint temp_point(0,0);
    QRect windowRect = m_windowRectBeforeStretch;
    const int min_width = this->minimumWidth();
    const int min_height = this->minimumHeight();
    QRect frame = this->frameGeometry();
    switch (is_on_edge) { /* change window shape accord to mouse point */
    case TOPLEFT:
        temp_point = frame.topLeft();
        if(frame.bottomRight().x() - p.x() > min_width){temp_point.setX(p.x());}
        else{temp_point.setX(frame.bottomRight().x() - min_width);}
        if(frame.bottomRight().y() - p.y() > min_height){temp_point.setY(p.y());}
        else{temp_point.setY(frame.bottomRight().y() - min_height);}
        frame.setRight(windowRect.right());
        frame.setBottom(windowRect.bottom());
        frame.setTop(temp_point.y());
        frame.setLeft(temp_point.x());
//        frame.setTopLeft(temp_point);
        break;
    case TOPRIGHT:
        temp_point = frame.topRight();
        if(p.x() - frame.bottomLeft().x() > min_width ){temp_point.setX(p.x());}
        else{temp_point.setX(frame.bottomLeft().x()+min_width);}
        if(frame.bottomLeft().y() - p.y() > min_height){
            temp_point.setY(p.y());
        }else{temp_point.setY(frame.bottomLeft().y() - p.y());}
        frame.setTopRight(temp_point);
        break;
    case BOTTOMLEFT:
        temp_point = frame.bottomLeft();
        if(frame.topRight().x() - p.x() > min_width){
            temp_point.setX(p.x());
        }else{
            temp_point.setX(frame.topRight().x()- min_width);
        }if(p.y() - frame.topRight().y() > min_height){
            temp_point.setY(p.y());
        }else{
            temp_point.setY(frame.topRight().y() + min_height);
        }
//        frame.setBottomLeft(temp_point);
        frame.setTop(windowRect.top());
        frame.setLeft(temp_point.x());
        frame.setRight(windowRect.right());
        frame.setBottom(temp_point.y());
        break;
    case BOTTOMRIGHT:
        temp_point = frame.bottomRight();
        if(p.x() - frame.topLeft().x() > min_width){
            temp_point.setX(p.x());
        }else{
            temp_point.setX(frame.topLeft().x() + min_width);
        }if(p.y() - frame.topLeft().y() > min_height){
            temp_point.setY(p.y());
        }else{
            temp_point.setY(frame.topLeft().y() + min_height);
        }
        frame.setBottomRight(temp_point);
        break;
    case TOP:
        temp_point = frame.bottomRight();
        if(temp_point.y() - p.y() > min_height){
            temp_point.setY(p.y());
        }else{
            temp_point.setY(frame.bottomLeft().y() - min_height);
        }
//        frame.setTopRight(temp_point);
        frame.setTop(temp_point.y());
        frame.setLeft(windowRect.x());
        frame.setRight(windowRect.right());
        frame.setBottom(windowRect.bottom());
        break;
    case BOTTOM:
        temp_point = frame.topRight();
        if( p.y() - temp_point.y() > min_height){
            temp_point.setY(p.y());
        }else{
            temp_point.setY(temp_point.y() + min_height);
        }
        frame.setBottomRight(temp_point);
        break;
    case LEFT:
        temp_point = frame.topRight();
        if(temp_point.x() - p.x() > min_width){
            temp_point.setX(p.x());
        }else{
            temp_point.setX(temp_point.x() - min_width);
        }
//        frame.setTopLeft(temp_point);
        frame.setLeft(temp_point.x());
        frame.setRight(windowRect.right());
        frame.setTop(windowRect.top());
        frame.setBottom(windowRect.bottom());
        break;
    case RIGHT:
        temp_point = frame.topLeft();
        if(p.x() - temp_point.x() > min_width){
            temp_point.setX(p.x());
        }else{
            temp_point.setX(temp_point.x() + min_width);
        }
        frame.setTopRight(temp_point);
        break;
    }
    setGeometry(frame);
}

void FramelessWidget::widgetEventHandler(QEvent *e)
{
    switch (e->type()) {
    case QEvent::HoverMove:
//    case QEvent::HoverEnter:
        mouseHoverEventHandler(static_cast<QHoverEvent *>(e));
        break;
    case QEvent::MouseMove:
        mouseMoveEventHandler(static_cast<QMouseEvent *>(e));
        break;
    case QEvent::MouseButtonPress:
        mousePressEventHandler(static_cast<QMouseEvent *>(e));
        break;
    case QEvent::MouseButtonRelease:
        mouseReleaseEventHandler(static_cast<QMouseEvent *>(e));
        break;
    default:
        break;
    }
}

void FramelessWidget::mouseHoverEventHandler(QHoverEvent *e)
{
    if(!mouse_down){  /* keep not monitor if mouse is downed */
        mouseEdgeRect(e->pos());
        updateCursor();
    }
}

void FramelessWidget::mouseMoveEventHandler(QMouseEvent *e)
{
    if(mouse_down){
        current_point=mapToGlobal(e->pos());
        if(move&&last_point.y()<=edgeHeight){
            const QPoint point = current_point - last_point;
            static_cast<QWidget *>(this)->move(point);
        }else if(zoom){
            resizeWidget(current_point);
        }
    }
}

void FramelessWidget::mousePressEventHandler(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton){
        mouse_down = true;
//        move = (!zoom && !move) &1;
        move = !(zoom&1); /* mouse pos edge or not */
        last_point = e->pos();
        m_windowRectBeforeStretch = this->frameGeometry();
    }
}

void FramelessWidget::mouseReleaseEventHandler(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton){
        mouse_down = 0;
        move = 0;
        zoom = 0 ;
//        setCursor(Qt::ArrowCursor);
        releaseMouse();
    }
}


