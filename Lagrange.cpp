// аппрксимация функцией Лагранжа (вроде как)

#include <iostream>
#include <windows.h>
#include <math.h>
#include "stdio.h"
using namespace std;
const int N = 10; // количество узлов, при 20 все идеально
const int pi = 3.161592;
double func7 (double y){  // рассматриваемая функция
    return 3*y - cos(y) - 1;
};
double func7_alt (double y){
    return abs(y)*(3*y - cos(y) - 1);
};
double func17 (double y){  // еще одна рассматриваемая функция
    return y*y+1-tan(y);
};
double el(double y, int j, double x[N]){  // множитель Лагранжа
    double result1 = 1, result2 = 1;
    for (int i = 0; i < N; i++){
        if (i != j){
            result1 = result1*(y - x[i]);
            result2 = result2*(x[j] - x[i]);
        }
    }
    return result1/result2;
};
 double P (double y, double x[N]){  // функция Лагранжа
    double result = 0;
    for (int i = 0; i < N; i++){
        result += func7(x[i])*el(y, i, x);  // func7, func7_alt и func17 менять вручную, внизу тоже
    }
    return result;
};

int main()
{
    setlocale(LC_ALL, "Russian");  //мы ж русские
    double a = -10, b = 10; // отрезок, если его меняем, менять надо и элементы массива z[]
    double x[N]; // массив узлов
    double z[5] = {-7, -3.5, 0, 4.2, 6};  // массив любых переменных для функций (в рамках отрезка), меняем в зависимости  от отрезка [a, b]
    double j = 0; // заменяет счетчик i в некоторых вычислениях
    cout << "Равностоящие узлы" << endl;
    for (int i = 0; i < N; i++){ // задаем РАВНОСТОЯЩИЕ узлы
        x[i] = a + j*(b-a)/(N-1);
        j++;
        printf("%.3f ", x[i]);
    }
    cout << endl;
    printf("%3s \t %18s  %20s \n", "x", "Искомая функция", "Функция Лагранжа");  // заглавие "таблицы"; наставил разных значений, чтобы было ровно
    for (int i = 0; i < 5; i++){
        double res_func = func7(z[i]);  // функцию менять вручную
        double res_P = P(z[i], x);
        if (z[i] >= 0){  // для красоты
            printf("%+4.2f \t %10.4f \t\t %7.4f \n", z[i], res_func, res_P);  // сама "таблица"; опять же, все ради выравнивания
        }
        else{
            printf("%4.2f \t %10.4f \t\t %7.4f \n", z[i], res_func, res_P);
        }
        /* собственно че это все такое непонятное:
         * в "" задаем параметры для будущих слов/цифр/чего угодно после знака % в той же последовательности, в которой мы потом пишем сами переменные, а так же всякие штуки типа \t и \n
         * переменные пишутся через запятую после ""
         * \t - табуляция; \n - новая строка
         * + - ставим + перед числом
         * число до точки - длина строки, выделенной для записи переменной. Если длина больше необходимого - слева ставятся пробелы, если меньше - ничего не происходит
         * число после точки (а точнее запись .число) - количество знаков после запятой/точки (округление)
         * f - float, по умолчанию минимум 6 знаков после запятой (нам столько не надо поэтому используем .2 и .4); s - string, для текста
        */
    }
    cout << '\n' << endl;
    // теперь узлы - корни полинома Чебышева
    cout << "Узлы - корни полинома Чебышева" << endl;
    j = 0;
    for (int i = 0; i < N; i++){
        x[i] = 0.5*((b-a)*cos(pi*(2*j+1)/(2*N)) + b + a);
        j++;
        printf("%.3f ", x[i]);
    }
    cout << endl;
    printf("%3s \t %18s  %20s \n", "x", "Искомая функция", "Функция Лагранжа"); // тут все то же самое, что и для равностоящих
    for (int i = 0; i < 5; i++){
        double res_func = func7(z[i]);  // функцию менять вручную
        double res_P = P(z[i], x);
        if (z[i] >= 0){
            printf("%+4.2f \t %10.4f \t\t %7.4f \n", z[i], res_func, res_P);
        }
        else{
            printf("%4.2f \t %10.4f \t\t %7.4f \n", z[i], res_func, res_P);
        }
    }
    system("pause");
    return 0;
}