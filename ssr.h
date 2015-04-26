#ifndef SSR_H
#define SSR_H

#ifdef LANG_RU
/**
 * @author Руслан Кузьмин
 */
#endif
#ifdef LANG_EN
/**
 * @author Ruslan Kuzmin
 */
#endif


#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <stdarg.h>
#include <chrono>
#include <unistd.h> 

#ifdef LANG_RU
/**
 * Класс эксперементирования с машинным обучением и системой поиска закономерностей
 */
#endif
#ifdef LANG_EN
/**
 * Class with system search of regularties.
 */
#endif

class SSR {
public:
	enum PO
	{
	isParallelOpenCL,
	isParallelCUDA,
	isParallelThreads,
	isParallelOpenMP
	};
protected:
	//Опции параллельного выполнения функций
	//Среднее время выполнения функции
	double avgTime;
public:
	//Создать массив фиксированного размера в куче
	void createHeapArray(int n_args, ...);
	//Создать массив фиксированного размера в стеке
	void createStackArray(int n_args, ...);
	//Создание маски изменений в массиве
	//template < typename A >
	//std::vector<int>& ArrayParameters
	void compareInsideArray(int * framesPtr,bool * changesMaskPtr,int noise,int find_key,int AP[],
		PO ParallelOption,bool isDebugInfo,bool isMeasureTime,bool isMeasureAvgTime);
	//Поиск одиннаковых символов и фрагментов внутри массива
	//template < typename A >
	//void searchRepeatCharsAndFragmentsInArray(A * framesPtr,bool * changesMaskPtr,int noise,int [] ArrayParameters,
	//	PO ParallelOption,bool isDebugInfo=false,bool isMeasureTime=false,bool isMeasureAvgTime=false);
};

#endif

