#include "ssr.h"
using namespace std;


#ifdef LANG_RU
/**
 * Создание многомерного массива фиксированного размера в куче
 * @param n_args Количество измерений массивы
 * @param ... Количество элементов в каждом измерении
 */
#endif
void SSR::createHeapArray(int n_args, ...)
{
    va_list ap;
    va_start(ap, n_args);
    int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    va_end(ap);
}

#ifdef LANG_RU
/**
 * Создание многомерного массива фиксированного размера в стеке 
 * @param n_args Количество измерений массивыа
 * @param ... Количество элементов в каждом измерении
 */
#endif
void SSR::createStackArray(int n_args, ...)
{
    va_list ap;
    va_start(ap, n_args);
    int max = va_arg(ap, int);
    for(int i = 2; i <= n_args; i++) {
        int a = va_arg(ap, int);
        if(a > max) max = a;
    }
    va_end(ap);
}


/*
unsigned char MultiArray[5][2]={{0,1},{2,3},{4,5},{6,7},{8,9}},{{10,11},{12,13},{14,15},{16,17},{18,19}};
unsigned char SingleArray[10]={0,1,2,3,4,5,6,7,8,9};
*/
#ifdef LANG_RU
/**
 * Проход по всему многомерному массиву или структуре , с целью выяснения изменений случившихся в массиве
 * @param Array Многомерный массив или структура
 * @param noise Уровень шума в значениях масссива
 * @param ArrayParameters Вектор содержащий в себе количество измернений массива и их размерность
 * @param find_key Уровень измерения массива с которого будет производиться сравнение
 * @param ParallelOptions Настройки параллельной обработки записанные в enum
 * @param isDebugInfo Выводить ли информацию в консоль или куда либо о ходе работы функции
 * @param isMeasureTime Измерять ли время выполнения функции
 * @param isMeasureAvgTime Измерять ли среднее время выполнения функции
 */
#endif
//template <typename A>
void SSR::compareInsideArray(int * frames,bool * changesMask,int noise,int find_key,int AP[],
	PO ParallelOption,bool isDebugInfo,bool isMeasureTime,bool isMeasureAvgTime)
{


	int sizeArrayParameters;//Размер массива описывающий массив
	for(sizeArrayParameters=0;AP[sizeArrayParameters]!=0;sizeArrayParameters++){};
	int * iterators=new int[sizeArrayParameters];
	int * iterators_max=new int[sizeArrayParameters];
	for(int iterInit=sizeArrayParameters;iterInit!=0;iterInit--)
	{
		int keyIterInit=iterInit-1;
		if(iterInit==sizeArrayParameters){
			iterators_max[keyIterInit]=AP[keyIterInit];
		}else{
			iterators_max[keyIterInit]=iterators_max[keyIterInit+1]*AP[keyIterInit];
		}
	}
	//Размер входящего массива
	int size=iterators_max[0];
	//Подсчет максимального числа элементов с разрешениях массива
    	if(isDebugInfo){
	cout<<"SSR::compareInsideArray debug info:"<<endl;
	cout << "size= " << size << endl;
	cout << "sizeArrayParameters= " << sizeArrayParameters << endl;
		for(int debugIter=0;debugIter<sizeArrayParameters;debugIter++)
		{cout<<"iterrators_max["<<debugIter<<"]="<<iterators_max[debugIter]<<endl;};
	}

	//Changes
	//Если условие поиска не содержательно
	if(find_key>=sizeArrayParameters-1)
	{
	cout<<"Bad find key"<<endl;
	return;
	}
	//sleep(1);
	//Timer start
	auto start = std::chrono::system_clock::now();

	int mod;
	for(int j=0;j<size;j++)
	{
		//Вычисление ключей массива или структуры по порядковому номеру
		mod=j; //Изменяющийся остаток от целочисленного деления
		for(int l=0;l<sizeArrayParameters;l++)
		{
			if(l==(sizeArrayParameters-1)){
				iterators[l]=mod;
			}else{
				iterators[l]=mod/iterators_max[l+1];
				mod=(int)mod%iterators_max[l+1];
			}
		}
		//Debug info
		if(isDebugInfo){
			cout<<"array";
			for(int debugIter=0;debugIter<sizeArrayParameters;debugIter++)
			{cout<<"["<<iterators[debugIter]<<"]";};
			cout <<"="
			<<frames[j]
			<<endl;
		}

		//Сравнивание одиннаковых точек подмассивов
		if(iterators[find_key]!=0){
	
			int pos_delta=j-iterators_max[find_key+1];
			if(abs(frames[j]-frames[pos_delta])<=noise)
			{
				changesMask[j]=false;	
				//Debug info
				if(isDebugInfo){
					cout<<" Not changed "<<endl;
				}
			}
			else
			{
				changesMask[j]=true;
				if(isDebugInfo){	
					cout<<" Changed "<<endl;
				}
			}
		}
		else
		{
			//Debug info
			if(isDebugInfo){	
				cout<<"Exception: iterators[find_key]=0"<<endl;
			}
		}

	}

	//Вывод сколько прошло времени
	if(isMeasureTime){
	//Timer stop
	auto end = std::chrono::system_clock::now();
	//auto elapsed = end - start;
	auto elapsedNano = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	auto elapsedMill = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto elapsedSec = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout <<"Time SSR::compareInsideArray:"<<endl
		<<"Freq.       :  " << 1000000000/elapsedNano.count() <<endl
		//<< elapsed.count()  <<endl
		<<"NanoSec     :  "<<elapsedNano.count() <<endl
		<<"MilliSec    :  "<<elapsedMill.count() <<endl
		<<"Seconds     :  "<<elapsedSec.count() <<'\n';
	}
}

#ifdef LANG_RU
/**
 * Поиск в многомерном массиве повторяющихся значений
 * @param Array Многомерный массив или структура
 * @param noise Уровень шума в значениях масссива
 * @param ArrayParameters Вектор содержащий в себе количество измернений массива и их размерность
 * @param ParallelOptions Настройки параллельной обработки записанные в enum
 * @param isDebugInfo Выводить ли информацию в консоль или куда либо о ходе работы функции
 * @param isMeasureTime Измерять ли время выполнения функции
 * @param isMeasureAvgTime Измерять ли среднее время выполнения функции
 */
#endif
/*
template < typename A >
void SSR::searchRepeatCharsAndFragmentsInArray(A * framesPtr,bool * changesMaskPtr,int noise,vector<int> & ArrayParameters,
	PO ParallelOption,bool isDebugInfo,bool isMeasureTime,bool isMeasureAvgTime)
{

	int repeat[255];
	for(int i=0;i<255;i++)repeat[i]=0;

	int sizeArrayParameters=ArrayParameters.size();
	int * iterrators = new int[sizeArrayParameters];
	//Fill null and calculate size array
	int size=0;
	for(int i=0;i<sizeArrayParameters;i++)
	{
	iterrators[i]=0;
	}
	//Changes
	for(int j=0;j<size;j++)
	{
			if(changesMask[j]==true){
			 	int keyRepeat=frames[j];
				for(int iterNoise=-noise;iterNoise<=noise;iterNoise++)
				{
					if(keyRepeat>-iterNoise)
					repeat[keyRepeat+iterNoise]++;
				}
			}
			//Debug info
			if(isDebugInfo){
			cout<<"In function SSR::searchRepeatCharsAndFragmentsInArray"
			<<endl;
			}
	}

}
*/




