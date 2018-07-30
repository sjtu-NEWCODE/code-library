//Tsinsen A1280 �˫���Ĵ� 
#include<iostream>
#include<cstring>
using namespace std;

const int maxn = 100005;// n(�ռ临�Ӷ�o(n*ALP)),ʵ�ʿ�n����
const int ALP = 26;

struct PAM{ // ÿ���ڵ����һ�����Ĵ�
    int next[maxn][ALP]; // nextָ��,����Trie��
    int fail[maxn]; // failʧ���׺����
    int cnt[maxn]; // �˻��Ĵ����ָ���
    int num[maxn];
    int len[maxn]; // ���Ĵ�����
    int s[maxn]; // �����ӵ��ַ�
    int last; //ָ����һ���ַ����ڵĽڵ㣬������һ��add
    int n; // ������ַ�����
    int p; // �ڵ����

    int newnode(int w)
	{// ��ʼ���ڵ㣬w=����
        for(int i=0;i<ALP;i++)
            next[p][i] = 0;
        cnt[p] = 0;
        num[p] = 0;
        len[p] = w;
        return p++;
    }
    void init()
	{
        p = 0;
        newnode(0);
        newnode(-1);
        last = 0;
        n = 0;
        s[n] = -1; // ��ͷ��һ���ַ�����û�е��ַ�����������
        fail[0] = 1;
    }
    int get_fail(int x)
	{ // ��KMPһ����ʧ�����һ���������
        while(s[n-len[x]-1] != s[n]) x = fail[x];
        return x;
    }
    int add(int c)
	{
        c -= 'a';
        s[++n] = c;
        int cur = get_fail(last);
        if(!next[cur][c])
		{
            int now = newnode(len[cur]+2);
            fail[now] = next[get_fail(fail[cur])][c];
            next[cur][c] = now;
            num[now] = num[fail[now]] + 1;
        }
        last = next[cur][c];
        cnt[last]++;
        return len[last];
    }
    void count()
	{
        // ���ͳ��һ��ÿ���ڵ���ָ���
        // �����ۼӶ��ӵ�cnt,����SAM��parent��
        // ����parent���˹�ϵ
        for(int i=p-1;i>=0;i--)
            cnt[fail[i]] += cnt[i];
    }
}pam;
char S[101010];
int l[101010],r[101010];
int main()
{
	cin>>S;
	int len=strlen(S);
	pam.init();
	for(int i=0;i<len;i++)
		l[i]=pam.add(S[i]);
	pam.init();
	for(int i=len-1;i>=0;i--)
		r[i]=pam.add(S[i]);
	pam.init();
	int ans=0;
	for(int i=0;i<len-1;i++)
		ans=max(ans,l[i]+r[i+1]);
	cout<<ans<<endl;
	return 0;
}
