#include<bits/stdc++.h>
using namespace std;

void recursion(int num){
cout<<num<< endl;
if (num <10){
    recursion(num+1);
}
}
int main()
{
    recursion(1);
    return 0;

}
