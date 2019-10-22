/******************************************
* AUTHOR : Lokesh goel*
* NICK : InsaneNerd *
* INSTITUTION : NIT Kurukshetra *
******************************************/
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define MAX 1000000000
#define N 100005
#define pii pair<int,int>
#define vp vector<pair<int,int > >
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define gsz(x) ((int)(x).size())
#define F first
#define S second
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define endl "\n"
#define ms(x,v) memset(x,v,sizeof(x))
int main() {
	fastio;
	//queue<int>enter,exit;
	set<int>fine;
	int i,j,n,a[100005],b[100005];
	cin>>n;
	for(i=0;i<n;i++)
	{
		cin>>a[i];
		//inside.insert(a[i]);
	}
	for(i=0;i<n;i++)
		cin>>b[i];
	int fined=0;
	int count=0;
	j=n-1;
	for(i=n-1;i>=0&&j>=0;)
	{
		if(fine.find(b[j])!=fine.end())
		{
			
			j--;
			continue;
		}
		if(a[i]==b[j])
		{
			i--;
			j--;
			continue;
		}
		fined++;
		fine.insert(a[i]);
		i--;
	}
	cout<<fined;
	return 0;
}