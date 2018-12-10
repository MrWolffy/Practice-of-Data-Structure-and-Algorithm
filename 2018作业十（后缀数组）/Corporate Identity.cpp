#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define maxn 888888
int t1[maxn],t2[maxn],c[maxn],sa[maxn],Rank[maxn],height[maxn];
bool cmp(int *r,int a,int b,int l)
{
    return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int str[],int n,int m)
{
    n++;
    int i,j,p,*x=t1,*y=t2;
    for(i=0;i<m;i++)c[i]=0;
    for(i=0;i<n;i++)c[x[i]=str[i]]++;
    for(i=1;i<m;i++)c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
    for(j=1;j<=n;j<<=1)
    {
        p=0;
        for(i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<m;i++)c[i]=0;
        for(i=0;i<n;i++)c[x[y[i]]]++;
        for(i=1;i<m;i++)c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
            x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        if(p>=n)break;
        m=p;
    }
    int k=0;
    n--;
    for(i=0;i<=n;i++)Rank[sa[i]]=i;
    for(i=0;i<n;i++)
    {
        if(k)k--;
        j=sa[Rank[i]-1];
        while(str[i+k]==str[j+k])k++;
        height[Rank[i]]=k;
    }
}
int n,res,a[maxn],id[maxn],vis[4444];
char s[222],ans[222];
int check(int k)
{
    int cnt=0;
    memset(vis,0,sizeof(vis));
    for(int i=2;i<=res;i++)
    {
        if(height[i]<k)
        {
            memset(vis,0,sizeof(vis));
            cnt=0;
            continue;
        }
        if(!vis[id[sa[i-1]]])
            vis[id[sa[i-1]]]=1,cnt++;
        if(!vis[id[sa[i]]])
            vis[id[sa[i]]]=1,cnt++;
        if(cnt==n)
        {
            for(int j=0;j<k;j++)
                ans[j]=a[sa[i]+j];
            ans[k]='\0';
            return 1;
        }
    }
    return 0;
}
int main()
{
    while(~scanf("%d",&n),n)
    {
        res=0;
        for(int i=0;i<n;i++)
        {
            scanf("%s",s);
            int len=strlen(s);
            for(int j=0;j<len;j++)
                a[res]=s[j],id[res++]=i;
            a[res]='#'+i;
            id[res++]='#'+i;
        }
        a[res]=0;
        da(a,res,5000);
        int l=1,r=strlen(s),flag=0;
        while(l<=r)
        {
            int mid=(l+r)>>1;
            if(check(mid))
            {
                flag=1;
                l=mid+1;
            }
            else r=mid-1;
        }
        if(flag)printf("%s\n",ans);
        else printf("IDENTITY LOST\n");
    }
    return 0;
}