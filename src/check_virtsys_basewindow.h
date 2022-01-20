

/*
 *Describution: header-file defined some API for other called
 *mean as a windows manager-control center  ,
 *you can do it for operation  add / delete /modify
 *fix/and so on  for desiging self window
 *
 *Data: January Monday 2022 +12:00 
 *
 *Author: jiangxiaoyu
 *
 *Email:jiangxiaoyu@<work.com>
 */




#ifndef __CHECK_VIRTSYS_BASEWINDOW__
#define __CHECK_VIRTSYS_BASEWINDOW__

#include<iostream>
#include<QWidget>
#include <QStackedWidget>

#define UINT16 unsigned short
#define UINT32 unsigned int
#define UINT64 unsigned long long int




namespace  BASEWINDOW{

    enum sortMethod{

    };


    class check_virtsys_basewindow{

    public:
        /* define construct deconstruct function*/
        check_virtsys_basewindow();
        ~check_virtsys_basewindow();


          QStackedWidget *_baseStaWid_();

          void checkvirtsys_add_window(QWidget *wid);

          void checkvirtsys_delete_window(QWidget * wid);

          void checkvirtsys_sort_window(sortMethod sort);

          void checkvirtsys_insert_window(UINT16 pre_site,UINT16 nxt_site,QWidget wid);

          void checkvirtsys_setFront_window(QWidget * wid);
        /* get all windows  show/hide */
        /*\ code:
         * 	return checkvirtsys_Count_windows();
         */
          unsigned short checkvirtsys_allCount_windows();

          unsigned short checkvirtsys_showedCount_windows();

          unsigned short checkvirtsys_hidedCount_windows();
    private:
         /* using pimpl mode to protect private-api/data*/
         class baseWindow;
         baseWindow * baseWinPimpl;
         baseWindow * _baseWinPimpl_();
         void  check_objcls_isExist();
         void checkvirtsys_baseWinInit();
    public:

    };
}
#endif // **
