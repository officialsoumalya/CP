#include <iostream>
#include<vector>
#include <cstring>
using namespace std;
typedef long long ll;
ll p,k,m,n;
vector<ll>b,c;
vector <vector<ll>> mul(vector<vector<ll>> A,vector<vector<ll>> B)
{
    vector<vector<ll>>C(k+2,vector<ll>(k+2));
    ll i,j,x;
    for(i=1;i<=k+1;i++)
    {
        for(j=1;j<=k+1;j++)
        {
            for(x=1;x<=k+1;x++)
            {
                C[i][j]=(C[i][j]+A[i][x]*B[x][j])%p;
            }
        }
    }
    return C;
}
vector<vector<ll>>pow(vector<vector<ll>> A,ll p)
{
    if(p==1)
    return A;
    if(p&1)
    {
        return mul(A,pow(A,p-1));
    }
    vector<vector<ll>> X=pow(A,p/2);
    return mul(X,X);
}
ll compute()
{
    if(!n)
    return 0;
    if(n<=k)
    return b[n-1];
    vector<ll> F1(k+2);
    F1[1]=0;
    ll i;
    for(i=2;i<=k+1;i++)
    {
        F1[i]=b[i-2];
    }
    vector< vector<ll> >T(k+2,vector<ll>(k+2));
    T[1][1]=1;
    ll j;
    for(i=1;i<=k+1;i++)
    {
        for(j=1;j<=k+1;j++)
        {
            if(i==1&&j==1)
            continue;
            if(i<=k)
            {
                if(j==i+1)
                T[i][j]=1;
                else
                T[i][j]=0;
            }
            else
            {
                if(j==1)
                T[i][j]=0;
                else
                T[i][j]=c[k-j+1];
            }
        }
    }
    vector< vector<ll> >Tn(k+2,vector<ll>(k+2));
    Tn=T;
    Tn=pow(Tn,n);
    // for(i=1;i<=k+1;i++)
    // {
    //     for(j=1;j<=k+1;j++)
    //     cout<<Tn[i][j]<<" ";
    //     cout<<endl;
    // }
    vector<vector<ll>>Tm(k+2,vector<ll>(k+2));
    Tm=T;
    Tm=pow(Tm,m-1);
    ll Sn=0;
    ll Sm=0;
    for(i=1;i<=k+1;i++)
    {
        Sn=(Sn%p+((F1[i]*Tn[1][i]%p)%p))%p;
        Sm=(Sm%p+((F1[i]*Tm[1][i]%p)%p))%p;
    }
    //cout<<Sm<<endl;
    ll S=(Sn-Sm)%p;
    return S;
}
int main()
{
    ll t;
    cin>>t;
    while(t--)
    {
        cin>>k;
        ll i,num;
        for(i=0;i<k;i++)
        {
            cin>>num;
            b.push_back(num);
        }
        for(i=0;i<k;i++)
        {
            cin>>num;
            c.push_back(num);
        }
        cin>>m>>n>>p;
        ll ans=compute();
        if(ans<0)
        ans+=p;
        cout<<ans<<endl;
        b.clear();
        c.clear();
    }
    return 0;
}
