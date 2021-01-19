#include <iostream.h>
#include <math.h>
#include <conio.h>

using namespace std;

struct tangle{
tangle* point1, point2;
int inf;
static int leng;
tangle(int infa){
cout<<"Введите элемент древа: ";
cin>>inf;
}
};

void additem(*tangle now, int inf){
    *tangle now1;
if (now == NULL){
    now = new tangle(inf);
    now->point1 = NULL;
    now->point2 = NULL;
    leng++;
    now1 = now->point1;
    }
else
{
    additem(now->point1, inf);
}
if (now->leng%3 == 0)
{
    now->point1->point2 = now;
    innerconnect(now1);
}
if ((now->leng-1)%3 == 0)
{
    innerconnect(now1);
}
    }

void innerconnect(tangle* now1){
if (now1->point2 == NULL)
{
    now1->point2 = now1;
}
else innerconnect(now1);
}

void print (tangle *t,int u)
{
    if (t==NULL) return;
    else
    {
    print(t->point1,++u);
    for (int i=0;i<u;++i) cout<<"|";
    cout<<t->inf<<endl;
    u--;
    }
}

/*tangle* TreeCreation(*tangle now, int len){
    tangle* newo;
    if (len == 1){
        newo = new tangle;//1
        newo->point1 = new tangle;//2
        newo->point1->point1 = new tangle;//3
        newo->point1->point1->point1 = new tangle;//4
        newo->point2 = newo->point1->point1;//1-3
        newo->point1->point2 = newo->point1->point1->point1;//2-4

    }

}*/

void main(){
}
