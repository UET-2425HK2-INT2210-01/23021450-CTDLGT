#include <bits/stdc++.h>
using namespace std;
void sapsep(int a[],int n) {
int min;
for(int i=0;i<n;i++) {
min = i;
for(int j=i+1;j<n;j++) {
if(a[j]<a[min])
min=j;
}
int c=a[i];a[i]=a[min];a[min]=c;
}
for(int i=0;i<n;i++) {
cout<<a[i]<<" ";
}
}
int main() {
int n;
cin>>n;
int a[n];
for(int i=0;i<n;i++) {
cin>>a[i];
}
sapsep(a,n);
}
