// ConsoleApplication3.cpp: определяет точку входа для консольного приложения.
//
#include "stdio.h"
#include "iostream"
#include "math.h"

using namespace std;
void rotate(int a){
 int b = a; char n = 1;
 int help[5];
 while (b >= 1)
 {
  help[n-1] = b % 10;
  printf("%d\n", help[n-1]);
  b /= 10;
  n++;
 }
 n--;
 a = 0;
 for (int i = 1; i < n; i++)
 {
  a += help[i-1] * (double) pow(10, n-i);
 }

  printf("%d\n", a);
 //return a;
}

void rotate(double a){
 float b = a; int b2; char n = 1, h = 0;
 int help[10];
 while (b != floor(b)){
  b *= 10;
  h++;
 }
 b2 = b;
 while (b2 >= 1)
 {
       help[n - 1] = b2 % 10;
  b2 /= 10;
 // help[n - 1] = b2 % 10;
  n++;
 }
 n--;
 for (int i = 1; i <= n; i++)
 {
  a += help[i - 1] * pow(10, n - i);
 }
 a /= pow(10, h);
 cout << a;
}


int main()
{
 rotate(801);
 return 0;
}
