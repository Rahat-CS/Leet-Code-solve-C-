#include<bits/stdc++.h>
using namespace std;

void recursion(int num){
cout<<num<< endl;
if (num ){
    recursion(num-1);
}
else return;
cout<<num<< endl;

}
int main()
{
    recursion(10);
    return 0;

}
