#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <stdarg.h>
#include <iostream>
#include "ssr.h"

#ifdef LANG_RU
/**
 * Глобальные переменные массивов в куче
 */
#endif
#ifdef LANG_EN
/**
 * Global variables arrays in heap
 */
#endif
#define NUMBER_FRAMES 3
#define SIZE_FRAME 3



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    //Инициализация
    int noise=0;
    int framesAP[10]={3,3,0};
    int frames[3][3]= {
     {1, 0, 0} ,
     {0, 1, 0} ,
     {0, 0, 1}
    };
    bool changesMask[3][3];
    //Выполнение
    //Init system of search regularities
    SSR * ssr=new SSR;
    //Поиск изменений от подмассива к подмасссиву
    ssr->compareInsideArray((int *)&frames[0],(bool *) &changesMask[0],noise,0,framesAP,SSR::isParallelOpenMP
                ,false /*isDebugInfo*/,true /*isMeasureTime*/,true /*bool isMeasureAvgTime*/);

    ssr->compareInsideArrayOpenMP((int *)&frames[0],(bool *) &changesMask[0],noise,0,framesAP,SSR::isParallelOpenMP
                ,false /*isDebugInfo*/,true /*isMeasureTime*/,true /*bool isMeasureAvgTime*/);

    //Поиск закономерностей
    //ssr.searchRepeatCharsAndFragmentsInArray<int>(&frames[0][0],&changesMask[0][0],noise,framesAP,SSR::isParallelOpenMP
    //			,true /*isDebugInfo*/,true /*isMeasureTime*/,true /*bool isMeasureAvgTime*/);


    //return a.exec();
    return 0;
}



