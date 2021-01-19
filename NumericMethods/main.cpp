#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <math.h> 
#include <locale.h> 
using namespace std;

void derivative1(double *&y, double h) {
	double f[4];
	f[0] = (1 / (6 * h)) * (-11 * y[0] + 18 * y[1] - 9 * y[2] + 2 * y[3]) - (h * h * h / 4);
	f[1] = (1 / (6 * h)) * (-2 * y[0] - 3 * y[1] + 6 * y[2] - y[3]) + (h * h * h / 12);
	f[2] = (1 / (6 * h)) * (y[0] - 6 * y[1] + 3 * y[2] + 2 * y[3]) - (h * h * h / 12);
	f[3] = (1 / (6 * h)) * (-2 * y[0] + 9 * y[1] - 18 * y[2] + 11 * y[3]) + (h * h * h / 4);
	y = f;
}
void derivative2(double *&y, double h) {
	double f[4];
	f[0] = (1 / (h * h)) * (2 * y[0] - 5 * y[1] + 4 * y[2] - y[3]) + (11 / 12 * (h * h));
	f[1] = (1 / (h * h)) * (y[0] - 2 * y[1] + y[2]) - (1 / 12 * (h * h));
	f[2] = (1 / (h * h)) * (y[1] - 2 * y[2] + y[3]) - (1 / 12 * (h * h));
	f[3] = (1 / (h * h)) * (-y[0] + 4 * y[1] - 5 * y[2] + 2 * y[3]) + (11 / 12 * (h * h));
	y = f;
}
class Interpolation {
	double *X, *Y;
	int n = 0;
	double LP(double* X, double* Y, double t)
	{
		int size = n;
		double sum = 0;
		for (int i = 0; i < size; i++) {
			double mul = 1;
			for (int j = 0; j < size; j++) {
				if (i != j)
					mul *= (t - X[j]) / (X[i] - X[j]);
			}
			sum += Y[i] * mul;
		}
		return sum;
	}

	double** input(int n)
	{
		int i, j, hl;
		double** arr;
		arr = new double*[n + 1];
		arr[0] = new double[n];
		arr[1] = new double[n];
		for (i = 0; i < n; i++) {
			cout << "Введите x[" << i << "]: ";
			cin >> arr[0][i];
			cout << "Введите y[" << i << "]: ";
			cin >> arr[1][i];
		}
		for (i = 2; i <= n; i++) {
			arr[i] = new double[n + 1 - i];
			cout << endl;
			for (j = 0; j < n + 1 - i; j++)
				arr[i][j] = (arr[i - 1][j + 1] - arr[i - 1][j]) / (arr[0][j + 1 + i - 2] - arr[0][j]);
		}
		cout << endl;
		return arr;
	}
	void output(double** arr, int n)
	{
		int i, j;
		for (i = 0; i < 2; i++) {
			cout << endl;
			for (j = 0; j < n; j++) {
				cout << arr[i][j] << " ";
			}
		}
		for (i = 2; i <= n; i++) {
			cout << endl;
			for (j = 0; j < n + 1 - i; j++)
				cout << arr[i][j] << " ";
		}
		cout << endl;
	}

	double findanswer(double** arr, int n, double x) {
		int i, j, imin, hlp;
		double min, ans;
		min = fabs(x - arr[0][0]);
		imin = 0;
		for (i = 1; i < n; i++) {
			if (min > fabs(x - arr[0][i])) {
				min = fabs(x - arr[0][i]);
				imin = i;
			}
		}
		if ((arr[0][imin] == arr[0][0]) || (arr[0][imin] == arr[0][n]))
		{
			hlp = n;
		}
		else
			if (imin == n / 2)
			{
				hlp = n - 2;
			}
			else
				hlp = --n;
		if (imin <= n / 2) {
			min = 1;
			ans = 0;
			for (i = 1; i < hlp; i++)
			{
				if (i > 1)
					min *= x - arr[0][i - 1];
				ans += arr[i][imin] * min;
			}
		}
		if (imin > n / 2) {
			min = 1;
			ans = 0;
			for (i = 1; i < hlp; i++)
			{
				if (i > 1)
					min *= x - arr[0][n + 1 - i];
				ans += arr[i][n - imin] * min;
			}
		}
		return ans;
	}
public:
	void Lagrange() {
		setlocale(LC_ALL, "RUS");
		cout << "Вычисление интерполяционного многочлена Лагранжа\nВвод данных\nВведите количество узлов => ";
		cin >> n;
		X = new double[n];
		Y = new double[n];
		cout << "Значение X\n";
		for (int i = 0; i < n; i++) {
			cout << "Введите X[" << i << "]:";
			cin >> X[i];
		}
		cout << "Значение Y\n";
		for (int i = 0; i < n; i++) {
			cout << "Введите Y[" << i << "]:";
			cin >> Y[i];
		}
		cout << "Введите точку для поиска => ";
		double t = 0;
		cin >> t;
		cout << "\n   Результат\n";
		cout << "L(" << t << ") = " << LP(X, Y, t) << " " << endl;
		system("pause");
	}
	void Newton() {
		int n;
		double** arr;
		double ans, x;
		setlocale(LC_ALL, "rus");
		cout << "Введите количество точек: ";
		cin >> n;
		arr = input(n);
		output(arr, n);
		cout << "Введите x: ";
		cin >> x;
		ans = findanswer(arr, n, x);
		cout << "Решение методом разделенных разниц = " << ans << endl;
		system("pause");
	}
};
class SolutionEquations {
	double methodOfHalfDivide(double a, double b, double eps)//ПоловинногоДеления
	{
		double left, right, x, f;
		int iter = 0;
		if (F(a) > 0)
		{
			left = a;
			right = b;
		}
		else {
			right = a;
			left = b;
		}
		do {
			x = (left + right) / 2;
			if (F(x) > 0)
				left = x;
			else right = x;
			f = F(right) - F(left);
			iter++;
		} while (fabs(f) > eps && iter <= 1000);
		return x;
	}
	double leftRange() {
		int i = 0;
		double a = 0, h = 0.5;
		while (F(a)*F(a - h) > 0 && i <= 1000)
		{
			i++;
			a -= h;
		}
		if (i > 1000)
		{
			return 0.00001;
		}
		else {
			return a;
		}
	}
	double rightRange() {
		int i = 0;
		double a = 0, h = 0.5;
		while (F(a)*F(a + h) > 0 && i <= 1000)
		{
			i++;
			a += h;
		}
		if (i > 1000)
		{
			return 0.00001;
		}
		else {
			return a;
		};
	}
public:
	double F(double x) {
		return	x*x*x - 5*x*x - 10;
		//x3 + 0, 4x 2 + 0, 6x – 1, 6 = 0
		/*	if(x>=0)
			return sqrt(x)-2/(x-3)+1;
		else return 100500*/;
	}// здесь уравнение
	void calculate() {
		double eps, a, b;
		bool f1, f2;
		a = leftRange();
		b = rightRange();
		if (a != 0.00001) {
			cout << "Численное решение уравнений\n\nИнтервал от " << a - 0.5 << " до " << a << endl;
			cout << "Введите погрешность: "; cin >> eps;
			cout << "\nМетод половинного деления: x = " << methodOfHalfDivide(a - 0.5, a, eps) << endl;
			cout << "\nМетод хорд: x = " << hordes(a - 0.5, a, eps) << endl;
			cout << "\nМетод Ньютона: x = " << Newton(a - 0.5, a, eps) << endl;
		}
		else cout << "Корней слева от нуля не существует" << endl;
		if (b != 0.00001) {
			cout << "Численное решение уравнений\n\nИнтервал от " << b << " до " << b + 0.5 << endl;
			cout << "Введите погрешность: "; cin >> eps;
			cout << "\nМетод половинного деления: x = " << methodOfHalfDivide(b, b + 0.5, eps) << endl;
			cout << "\nМетод хорд: x = " << hordes(b, b + 0.5, eps)<< endl;
			cout << "\nМетод Ньютона: x = " << Newton(b, b + 0.5, eps) << endl;
		}
		else cout << "Корней справа от нуля не существует" << endl;
	}
	double hordes(double x1, double x2, double eps) {
		int i;
		double x, dx, xfix, *checker;
		checker = (double*) malloc(4 * sizeof(double));
		for (i = 0, x = x1; i<4, x < x2; i++, x += (x2 - x1) / 4)
		{
			checker[i] = F(x);
		}
		derivative2(checker, (x2 - x1) / 4);
		for (i = 0; i < 3; i++)
		{
			if (checker[i] * checker[i + 1] < 0) {
				cout << "Достаточное условие не выполняется, метод может не сойтись!"<<endl;
				break;
			}
		}
		i = 0;
		if (F(x1) > 0) {
			xfix = x1;
			x = x2;
		}
		else
		{
			xfix = x2;
			x = x1;
		}
		do {
			dx = x;
			x = x - (x - xfix) * F(x) / (F(x) - F(xfix));
			dx -= x;
			i++;
		} while (i<5000 && fabs(dx)>eps);
		if (i < 5000)
			return x;
		else
		{
			cout << "Корень не был найден.";
			return 0;
		}
}
	double Newton(double x1, double x2, double eps) {
		double x, *dera, h;
		bool f;
		int j = 0;
		dera = new double[4];
		if (F(x1) > 0) {
			x = x1;
			f = true;
			do {
				for (int i = 0, h = x; i < 4; i++, h += eps)
				{
					dera[i] = F(h);
				}
				derivative1(dera, eps);
				x = x - F(x) / dera[0];
				j++;
			} while (j<500 && F(x) / dera[0]>eps);
		}
		else
		{
			x = x2;
			f = false;
			do {
				for (int i = 3, h = x; i >= 0; i--, h -= eps)
				{
					dera[i] = F(h);
				}
				derivative1(dera, eps);
				x = x - F(x) / dera[3];
				j++;
			} while (j<500 && F(x) / dera[3]>=eps);
		}
		if (j < 500)
			return x;
		else
		{
			cout << "Корень не найден" << endl;
			return x;
		}
	}	
};
class Gaus {
public:
	void calculate() {
		double **data, k, help, *helper;
		int i, j, l, counter, hlp, n;
		setlocale(LC_ALL, "rus");
		printf("Введите порядок системы: ");
		cin>>n;
		data = (double**)malloc(n * sizeof(double*));
		for (i = 0; i < n; i++)
			data[i] = (double*)malloc((n + 1) * sizeof(double));
		printf("Вводите элементы расширенной матрицы: \n");
		for (i = 0; i<n; i++)
			for (j = 0; j<n + 1; j++)
			{
				printf("Введите элемент %d-%d: ", i + 1, j + 1);
				cin>>data[i][j];
			}
		printf("Ваша расширенная матрица: ");
		for (i = 0; i<n; i++) {
			printf("\n");
			for (j = 0; j<n + 1; j++)
				printf("%5.3lf ", data[i][j]);
		}
		for (i = 0; i<n - 1; i++) {
			hlp = 0;
			do {
				help = data[i][i];
				if (help == 0)
				{
					counter = 0;
					for (l = i + 1; l<n + 1; l++)
						if (data[i][l] == 0) counter++;
					//if (counter == n-i)
					change(data, i, n - hlp, n);
				}
				hlp++;
			} while ((help == 0) || (hlp > n - i));
			if (hlp > n - i) { printf("\nСистема несовместна, решений нет"); exit(0); }
			for (j = i + 1; j<n; j++) {
				k = -data[j][i] / help;
				for (l = i; l<n + 1; l++)
					data[j][l] = data[i][l] * k + data[j][l];
			}
		}
		printf("\nРезультат прямого шага Гаусса:\n");
		for (l = 0; l<n; l++) {
			printf("\n");
			for (j = 0; j<n + 1; j++)
				printf("%5.3lf ", data[l][j]);
		}
		helper = (double*)malloc(n * sizeof(double));
		//Обратный шаг
		if ((data[n - 1][n] * data[n - 1][n - 1] == 0) && ((data[n - 1][n] != 0 || data[n - 1][n - 1] != 0)))
		{
			printf("\nСистема несовместна, решений нет"); exit(0);
		}
		else {
			for (i = n - 1; i >= 0; i--)
			{
				for (j = 0; j<n; j++)
					if (j != i)
						data[i][n] -= data[i][j];
				helper[i] = data[i][n] / data[i][i];
				for (j = 0; j<i; j++)
					data[j][i] *= helper[i];
			}
			{
				printf("\nРешение уравнения: (");
				for (i = 0; i<n; i++)
					printf("%5.3lf ", helper[i]);
				printf(")");
			}
		}
	}
	void change(double **nc, int i1, int i2, int n) {
		int j;
		double *buf;
		buf = (double*)malloc((n + 1) * sizeof(double));
		for (j = 0; j < n + 1; j++)
		{
			buf[j] = nc[i1][j];
			nc[i1][j] = nc[i2][j];
			nc[i2][j] = buf[j];
		}
	}
};
class Iteration {
	void change(double **nc, int i1, int i2, int n) {
		int j;
		double buf;
		for (j = 0; j<n + 1; j++)
		{
			buf = nc[i1][j];
			nc[i1][j] = nc[i2][j];
			nc[i2][j] = buf;
		}
	}
public:
	void calculate() {
		double **data, k, help, *helper, **miss, *mishelp, copy, E;
		int i, j, l, *hlp, n, counter;
		setlocale(LC_ALL, "rus");
		printf("Введите порядок системы: ");
		cin >> n;
		data = (double**)malloc(n * sizeof(double*));
		miss = (double**)malloc(n * sizeof(double*));
		hlp = (int*)malloc(n * sizeof(int));
		helper = (double*)malloc(n * sizeof(int));
		for (i = 0; i < n; i++)
		{
			data[i] = (double*)malloc((n + 1) * sizeof(double));
			miss[i] = (double*)malloc((n + 1) * sizeof(double));
		};
		printf("Вводите элементы расширенной матрицы: \n");
		for (i = 0; i<n; i++)
			for (j = 0; j<n + 1; j++)
			{
				printf("Введите элемент %d-%d: ", i + 1, j + 1);
				cin >> data[i][j];
				miss[i][j] = 1;
				copy = data[i][j];
				while (floor(copy) != ceil(copy))
				{
					copy *= 10;
					miss[i][j] /= 10;
				}
				if ((data[i][j] - floor(data[i][j]) >= 0.001) && (data[i][j] - floor(data[i][j]) <= 0.009))
					miss[i][j] = 0.001;
				if (miss[i][j] == 1)   miss[i][j] = 0;
			}
		printf("\nВаша расширенная матрица: ");
		for (i = 0; i<n; i++) {
			printf("\n");
			for (j = 0; j<n + 1; j++)
				printf("%5.5lf ", data[i][j]);
		}
		printf("\n\nПогрешности элементов: ");
		for (i = 0; i<n; i++) {
			printf("\n");
			for (j = 0; j<n + 1; j++)
				printf("%lf ", miss[i][j]);
		}
		for (i = 0; i<n; i++) {
			hlp[i] = 0;
			help = fabs(data[i][0]);
			copy = help;
			for (j = 1; j<n; j++)
			{
				copy = copy + fabs(data[i][j]);
				if (fabs(data[i][j])>help)
				{
					help = fabs(data[i][j]);
					hlp[i] = j;
				}
			}
			if (fabs(copy - fabs(help))>fabs(help))
			{
				cout << "Нельзя решить методом простых итераций!"; system("pause"); exit(0);
			}
		}
		for (i = 0; i<n; i++)
			printf("%d", hlp[i]);
		for (i = 0; i<n; i++)
			for (j = i + 1; j<n; j++)
				if (hlp[j] == hlp[i]) { printf("\n\nНельзя решить методом простых итераций "); system("pause"); exit(0); }
		for (i = 0; i<n; i++)
		{
			for (j = i; j<n; j++)
				if (hlp[j] == i) {
					change(data, i, j, n);
					change(miss, i, j, n);
					help = hlp[i];
					hlp[i] = hlp[j];
					hlp[j] = help;
					break;
				}
		}
		printf("\nУравнения в правильном порядке: ");
		for (i = 0; i<n; i++) {
			cout << endl;
			for (j = 0; j<n + 1; j++)
				cout << data[i][j] << " ";
		}
		for (i = 0; i<n; i++)
		{
			data[i][n] = data[i][n] / data[i][i];
			miss[i][n] = (fabs(data[i][n])*miss[i][i] + fabs(data[i][i])*miss[i][n]) / (data[i][i] * data[i][i]);
			for (j = n - 1; j >= 0; j--)
			{
				if (j != i)
				{
					miss[i][j] = (fabs(data[i][j])*miss[i][i] + fabs(data[i][i])*miss[i][j]) / (data[i][i] * data[i][i]);
					data[i][j] = -data[i][j] / data[i][i];
				}
			}
			data[i][i] = data[i][n];
			miss[i][i] = miss[i][n];
		}
		printf("\n\nВведите E: ");
		cin >> E;
		do {
			for (i = 0; i<n; i++) {
				helper[i] = data[i][i]; //коэффициенты при главных элементах
				data[i][i] = data[i][n]; //текущий х1, х2 и т.д хранятся на главной диагонали
				miss[i][i] = miss[i][n];
			}
			for (i = 0; i<n; i++) {
				for (j = 0; j<n; j++)
				{
					if (j != i)
					{
						data[i][i] += data[i][j] * helper[j];
						miss[i][i] = miss[i][i] + fabs(data[i][j])*miss[j][j] + fabs(helper[j])*miss[i][j];
					}
				}
			//	helper[i] = data[i][i]; //превращаем в Зейделя одной строкой
			}
			help = 0;
			for (i = 0; i<n; i++)
			{
				if (fabs(fabs(helper[i]) - fabs(data[i][i]))>E)
				{
					help = 1; break;
				}
			}
			printf("\nВаша расширенная матрица: ");
			for (i = 0; i<n; i++) {
				printf("\n");
				for (j = 0; j<n + 1; j++)
					printf("%5.5lf ", data[i][j]);
			}
		} while (help);
		printf("\n\nКорни уравнения:");
		for (i = 0; i<n; i++)
			printf("\nx%d = %lf (погрешность %lf)", i, data[i][i], miss[i][i]);
		system("pause");
	}
};
class Integration {
	double F(double x) { return log(x)*log(x)*sqrt(x + 1); }
	double	methodOfLeftRectangles(double a, int n, double h)//методЛевыхПрямоугольников
	{
		double s = 0;
		for (int i = 0; i < n; i++) s += F(a + i * h) * h;
		cout << "Погрешность метода левых прямоугольников = " << h / 2 * (F(a + h * n) - F(a)) << endl;
		return s + h / 2 * (F(a + h * n) - F(a));
	}
	double methodOfRightRectangles(double a, int n, double h)//методПравыхПрямоугольников
	{
		double s = 0;
		for (int i = 1; i <= n; i++) s += F(a + i * h) * h;
		cout << "Погрешность метода правых прямоугольников = " << h / 2 * (F(a + h * n) - F(a)) << endl;
		return s - h / 2 * (F(a + h * n) - F(a));}
	double methodOfMiddleRectangles(double a, int n, double h)//методСреднихПрямоугольников
	{
		double s = 0;
		double *deva, *devb;
		deva = devb = new double[4];
		for (int i = 0; i < n; i++) s += F(a + i * h + h / 2) * h;
		for (int i = 0; i < 4; i++)
			deva[i] = F(a + i * h / 2);
		for (int i = 3; i >= 0; i--)
		devb[i] = F(a + n * h - i * h / 2); // заполняем точки для производной
		derivative1(deva, h / 2);
		derivative1(devb, h / 2);
		cout << "Погрешность метода средних прямоугольников = " << -h * h / 24 << " * " << (devb[3] - deva[0]) << endl;
		return s; // - h * h / 24 * (devb[3] - deva[0]);
	}
	double	MethodOfTrapezium(double a, int n, double h)//методТрапеций
	{
		double s = 0;
		double *deva, *devb;
		deva = devb = new double[4];
		s += F(a) / 2 * h;
		for (int i = 1; i < n; i++) s += F(a + i * h) * h;
		s += F(a + n * h) / 2 * h;
		for (int i = 0; i < 4; i++) // заполняем точки для производной
			deva[i] = F(a + i * h / 2);
		for (int i = 3; i >= 0; i--)
			devb[i] = F(a + n * h - i * h / 2); 
		derivative1(deva, h / 2);
		derivative1(devb, h / 2);
		cout << "Погрешность метода трапеций = " << -h * h * h / 12 << " * " << (devb[3] - deva[0]) << endl;
		return s ;
	}
	double MethodOfSimpson(double a, int n, double h)//методСимпсона
	{
		double s = 0;
		for (int i = 0; i <= n; i++) {
			if (i == 0 || i == n) s += F(a + i * h);
			else if (i % 2 == 0) s += F(a + i * h) * 2;
			else s += F(a + i * h) * 4;
		}
		return s * h / 3;
	}
	double MethodOfNutonKottesa(double ba, int n, double a, double h)//методНьютонаКотеса
	{
		double C[7], s = 0;
		switch (n) {
		case 1: { C[0] = (ba / 2); C[1] = C[0]; break; }
		case 2: { C[0] = (ba / 6); C[1] = (4 * ba / 6); C[2] = C[0]; break; }
		case 3: { C[0] = (ba / 8); C[1] = (3 * ba / 8); C[2] = C[1]; C[3] = C[0]; break; }
		case 4: { C[0] = (7 * ba / 90); C[1] = (16 * ba / 45); C[2] = (2 * ba / 15); C[3] = C[1]; C[4] = C[0]; break; }
		case 5: { C[0] = (19 * ba / 288); C[1] = (25 * ba / 96); C[2] = (25 * ba / 144); C[3] = C[2]; C[4] = C[1]; C[5] = C[0]; break; }
		case 6: { C[0] = (41 * ba / 840); C[1] = (9 * ba / 35); C[2] = (9 * ba / 280); C[3] = (34 * ba / 105); C[4] = C[2]; C[5] = C[1]; C[6] = C[0]; break; }
		};
		for (int i = 0; i <= n; i++) s += F(a + i * h) * C[i];
		return s;
	}
public:
	void calculate() {
		int n;
		double a, b, h;
		cout << "Численное интегрирование\n\nИнтервал от "; cin >> a;
		system("cls");
		cout << "Численное интегрирование\n\nИнтервал от " << a << " до "; cin >> b;
		cout << "Шагов "; cin >> n;
		cout << endl;
		h = (b - a) / n;
		cout << "Метод левых   прямоугольников: " << methodOfLeftRectangles(a, n, h) << endl;
		cout << "Метод правых  прямоугольников: " << methodOfRightRectangles(a, n, h) << endl;
		cout << "Метод средних прямоугольников: " << methodOfMiddleRectangles(a, n, h) << endl;
		cout << "Метод трапеций: " << MethodOfTrapezium(a, n, h) << endl;
		cout << "Метод Симпсона: ";
		if (n % 2 == 0) cout << MethodOfSimpson(a, n, h) << endl;
		else cout << "не четное число шагов" << endl;
		cout << "Метод Ньютона-Котеса: ";
		if (n <= 7) cout << MethodOfNutonKottesa(b - a, n, a, h) << endl;
		else cout << "число шагов больше 6" << endl;
		cout << endl;
	}
};
class Diffur{
	double func(double x, double y) {
		return x * x + y * x + y * y;
	}
	void eiler(double x, double y, double h, double b) {
		int i = 0;
		cout << "0     " << x << "      " << y << endl;
		for (x += h; x <= b + h; x += h)
		{
			i++;
			y = y + h * func(x - h, y);
			cout << i << "     " << x << "      " << y << endl;
		}
	}
	void runge(double x, double y, double h, double b) {
		double k1, k2, k3, k4;
		int i = 0;
		cout << "0     " << x << "      " << y << "         k1" << "          k2" << "          k3" << "          k4" << endl;
		for (x += h; x <= b + h; x += h)
		{
			i++;
			k1 = func(x - h, y);
			k2 = func(x - h / 2, y + h * k1 / 2);
			k3 = func(x - h / 2, y + h * k2 / 2);
			k4 = func(x, y + h * k3);
			y += h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
			cout << i << "     " << x << "      " << y << "         " << k1 << "          " << k2 << "          " << k3 << "          " << k4 << endl;
		}
	}
public:
		void calculate() {
			double a, b, h, y;
			cout << "Численное дифференцирование\n\nИнтервал от "; cin >> a;
			system("cls");
			cout << "Численное дифференцирование\n\nИнтервал от " << a << " до "; cin >> b;
			cout << "Шаг: "; cin >> h;
			cout << "Y(" << a << ") = "; cin >> y;
			cout << "\nМетод Эйлера\n"; eiler(a, y, h, b);
			cout << "\nМетод Рунге-Кутта\n"; runge(a, y, h, b);
			cout << endl;
		}
};
class Derivatives {
	void derivatives(double n) {
		double x[4], y[4], f[4][2], h;
		for (int i = 0; i < n; i++) {
			cout << "x" << i << " = "; cin >> x[i];
			cout << "y" << i << " = "; cin >> y[i];
		}
		h = x[1] - x[0];
		if (n == 3) {
			f[0][0] = (1 / (2 * h)) * (-3 * y[0] + 4 * y[1] - y[2]) + (h * h / 3);
			f[1][0] = (1 / (2 * h)) * (-y[0] + y[2]) - (h * h / 6);
			f[2][0] = (1 / (2 * h)) * (y[0] - 4 * y[1] + 3 * y[2]) + (h * h / 3);
			f[0][1] = (1 / (h * h)) * (y[0] - 2 * y[1] + y[2]) - h;
			f[1][1] = (1 / (h * h)) * (y[0] - 2 * y[1] + y[2]) - (h * h / 12);
			f[2][1] = (1 / (h * h)) * (y[0] - 2 * y[1] + y[2]) + h;
		}
		else if (n == 4) {
			f[0][0] = (1 / (6 * h)) * (-11 * y[0] + 18 * y[1] - 9 * y[2] + 2 * y[3]) - (h * h * h / 4);
			f[1][0] = (1 / (6 * h)) * (-2 * y[0] - 3 * y[1] + 6 * y[2] - y[3]) + (h * h * h / 12);
			f[2][0] = (1 / (6 * h)) * (y[0] - 6 * y[1] + 3 * y[2] + 2 * y[3]) - (h * h * h / 12);
			f[3][0] = (1 / (6 * h)) * (-2 * y[0] + 9 * y[1] - 18 * y[2] + 11 * y[3]) + (h * h * h / 4);
			f[0][1] = (1 / (h * h)) * (2 * y[0] - 5 * y[1] + 4 * y[2] - y[3]) + (11 / 12 * (h * h));
			f[1][1] = (1 / (h * h)) * (y[0] - 2 * y[1] + y[2]) - (1 / 12 * (h * h));
			f[2][1] = (1 / (h * h)) * (y[1] - 2 * y[2] + y[3]) - (1 / 12 * (h * h));
			f[3][1] = (1 / (h * h)) * (-y[0] + 4 * y[1] - 5 * y[2] + 2 * y[3]) + (11 / 12 * (h * h));
		}
		system("cls");
		cout << "Численное нахождение производных\n\nКол-во узлов (3 или 4): " << n << "\nШаг: " << h << "\n\n";
		for (int i = 0; i < n; i++) {
			cout << "x" << i << " = " << x[i] << "\ty" << i << " = " << y[i] << "\tf'(x" << i << ") = " << f[i][0] << "\tf''(x" << i << ") = " << f[i][1] << endl;}}
public:
	void calculate() {
		double n;
		cout << "Численное нахождение производных\n\nКол-во узлов (3 или 4): "; cin >> n;
		if (n == 3 || n == 4) derivatives(n);
		else cout << "Узлов должно быть 3 или 4!";
		cout << endl;	}};
int main() {
	Integration Integr;
	SolutionEquations Solut;
	Derivatives Deri;
	Diffur Diffur;
	Gaus gaus_method;
	Iteration Itte;
	Interpolation Interpol;
	//Integration Интегрирование;
	//Differentiation Дифференцирование ;
	//SolutionEquations РешениеУравнений;
	//Gaus Гаусс;
	//Derivatives Производные;
	int flag;
	setlocale(0, "");
	int x = 0;
	while (true) {
		system("cls");
		cout << "Численные методы в программировании\n1 - Интегрирование\n2 - Дифференциальные уравнения\n" <<
			"3 - Решение уравнений\n4 - Производные\n5 - Гаусс\n6 - Решить систему уравнений методом итераций\n7 - Интерполяция методом Ньютона\n8 - Интерполяция методом Лагранджа\n0 - Выход\nДействие: ";
		cin >> flag;
		system("cls");
		switch (flag) {
		case 1: Integr.calculate(); break;
		case 2: Diffur.calculate(); break;
		case 3: Solut.calculate(); break;
		case 4: Deri.calculate(); break;
		case 5: gaus_method.calculate(); break;
		case 6: Itte.calculate(); break;
		case 7: Interpol.Newton(); break;
		case 8: Interpol.Lagrange(); break;
		default: return 0;}
		system("pause");}}
