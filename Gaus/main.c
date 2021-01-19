#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

void change(double **nc, int i1, int i2, int n){
int j;
double *buf;

buf = (double*) malloc((n+1)*sizeof(double));
for (j=0; j<n+1;j++)
{
    buf[j] = nc[i1][j];
    nc[i1][j] = nc[i2][j];
    nc[i2][j] = buf[j];
}
}

int main()
{
double **data, k, help, *helper, **miss, *mishelp, copy;
int i, j, l, hlp, n, counter;
setlocale(LC_ALL, "rus");
printf("Введите порядок системы: ");
scanf("%d", &n);
data = (double**)  malloc(n*sizeof(double*));
miss = (double**)  malloc(n*sizeof(double*));
for (i = 0; i < n; i++)
{
    data[i] = (double*)  malloc((n+1)*sizeof(double));
    miss[i] = (double*)  malloc((n+1)*sizeof(double));
};
printf("Вводите элементы расширенной матрицы: \n");
for (i = 0; i<n; i++)
    for (j=0; j<n+1; j++)
{
  printf("Введите элемент %d-%d: ", i+1, j+1);
  scanf("%lf", &data[i][j]);
        miss[i][j] = 1;
        copy = data[i][j];
while (floor(copy)!=ceil(copy))
    {
        copy*=10;
        miss[i][j]/=10;
        //printf("+");
    }
    if ((data[i][j]-floor(data[i][j])>=0.001)&&(data[i][j]-floor(data[i][j])<=0.009))
        miss[i][j] = 0.001;
     if (miss[i][j]==1)   miss[i][j] = 0;
}
printf("\nВаша расширенная матрица: ");
for (i = 0; i<n; i++){
        printf("\n");
    for (j=0; j<n+1; j++)
        printf("%5.5lf ", data[i][j]);}

        printf("\n\nПогрешности элементов: ");
for (i = 0; i<n; i++){
        printf("\n");
    for (j=0; j<n+1; j++)
        printf("%lf ", miss[i][j]);}

for (i = 0; i<n-1; i++){
        hlp = 0;
        do {
        help = data[i][i];
        if (help == 0)
        {
            counter = 0;
            for (l=i+1; l<n+1; l++)
                if (data[i][l]==0) counter++;
                //if (counter == n-i)
                    change(data, i, n-hlp, n);
                    change(miss, i, n-hlp, n);
        }hlp++;} while((help==0)||(hlp > n-i));
if (hlp > n-i) {printf("\n\nСистема несовместна, решений нет"); exit(0); }
    for (j=i+1; j<n; j++){
        k = -data[j][i]/help;
            for (l=i; l<n+1; l++){
                miss[j][l] = fabs(data[i][l])*((fabs(data[j][i])*miss[i][i]+fabs(data[i][i])*miss[j][i])/(help*help))+fabs(k)*miss[i][l]+miss[j][l];
                data[j][l] = data[i][l]*k+data[j][l];}
        }
        }
        printf("\n\nРезультат прямого шага Гаусса:");
for (l = 0; l<n; l++){
        printf("\n");
    for (j=0; j<n+1; j++)
        printf("%5.5lf ", data[l][j]);}


        printf("\n\nПогрешности первого шага:");
for (l = 0; l<n; l++){
        printf("\n");
    for (j=0; j<n+1; j++)
        printf("%5.5lf ", miss[l][j]);}


    helper = (double*) malloc (n*sizeof(double));
    mishelp = (double*) malloc (n*sizeof(double));
    //Обратный шаг

    if ((data[n-1][n]*data[n-1][n-1]==0)&&((data[n-1][n]!=0||data[n-1][n-1]!=0)))
        {printf("\n\nСистема несовместна, решений нет"); exit(0); } else {
for (i=n-1;i>=0;i--)
{
    for (j=0; j<n; j++)
    if (j!=i){
        data[i][n] -= data[i][j];
        miss[i][n] = miss[i][n] + miss[i][j];
        }
        if((data[i][n]==0)&&(data[i][i]==0))
        {
            printf("\n\nСистема несовместна, решений нет");
            exit(0);
        }
    helper[i] = data[i][n]/data[i][i];
    mishelp[i] = (fabs(data[i][n]*miss[i][i])+fabs(data[i][i]*miss[i][n]))/(data[i][i]*data[i][i]);
    for (j=0; j<i; j++){
            miss[j][i] = fabs(data[j][i]*mishelp[i])+fabs(helper[i]*miss[j][i]);
        data[j][i] *= helper[i];
        }
}

printf("\nРешение уравнения: (");
for (i=0;i<n;i++)
    printf("%5.5lf (погрешность %lf) ", helper[i], mishelp[i]);
    printf(")");
}

//let's free that memory
free(helper);
free(mishelp);

for (i = 0; i < n; i++)
{
    free(data[i]);
    free(miss[i]);
};

free(data);
free(miss);

return 0;
}


