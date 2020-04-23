#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
#define MOD 1000000000
ll k,n;
vector<ll> c,b;
vector<vector<ll>> mul(vector<vector<ll>> A, vector<vector<ll>> B)
{
    vector<vector<ll>> C(k+1,vector<ll>(k+1));
    ll i,j,x;
    for(i=1;i<=k;i++)
    {
        for(j=1;j<=k;j++)
        {
            for(x=1;x<=k;x++)
            {
                C[i][j]=(C[i][j]+A[i][x]*B[x][j])%MOD;
            }
        }
    }
    return C;
}
vector<vector<ll>> pow(vector<vector<ll>> A,ll p)
{
    //fast exponentiation
    if(p<=1)
    return A;
    if(p&1)
    return mul(A,pow(A,p-1));
    vector<vector<ll>> X=pow(A,p/2);
    return mul(X,X);
}
ll compute()
{
    if(n<=k)
    return b[n-1];
    vector<ll>F1(k+1);
    ll i;
    
    //intial vector F1
    for(i=1;i<=k;i++)
    F1[i]=b[i-1];

    //transformation matrix
    vector<vector<ll>> T(k+1,vector<ll>(k+1));
    ll j;
    for(i=1;i<=k;i++)
    {
        for(j=1;j<=k;j++)
        {
            if(i<k)
            {
                if(j==i+1)
                T[i][j]=1;
                else
                T[i][j]=0;
                continue;
            }
            T[i][j]=c[k-j];
        }
    }
    T=pow(T,n-1);
    ll res=0;
    for( i=1;i<=k;i++)
    {
        res=(res+T[1][i]*F1[i])%MOD;
    }
    return res%MOD;
}
int main()
{
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int t;
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
        cin>>n;
        cout<<compute()<<endl;
        b.clear();
        c.clear();
    }
}