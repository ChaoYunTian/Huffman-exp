#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<string>
#include<stdio.h>
#include<map>
#include<fstream>
using namespace std;
int a[26];                  //�洢ÿ����ĸ���ֵĴ���
char s[1000];
int m;      //һ�����ٸ���
int num=0;    //Ҷ�ӽڵ����
int len;
map<char,int> v;  //��ֵ����������Ӧ��ĸ�ͳ��ֵĴ���
typedef struct{
    char c;
    int weight;  //Ȩ��
    int parent,lchild,rchild;  //�ڵ��˫���±꣬���Һ��ӵ��±�
    char code;                   //�����
}htnode,*huffmantree;

//ͳ�ƶ��ĳ��ֵ���ĸ������ÿ����ĸ���ֵĴ���
void f1(){
    FILE *fi=freopen("a.txt","r",stdin);
    gets(s);                //gets()����ʱ�ո�Ҳ���룬ֱ�������ظ��
     len=strlen(s);
    cout<<len<<endl;        //���ĳ���
    for(int i=0;i<len;i++){

        if(s[i]-'a'>=0&&s[i]-'a'<=25){
            a[s[i]-'a']++;
        }
        if(s[i]-'A'>=0&&s[i]-'A'<=25){
            a[s[i]-'A']++;
        }
    }
    for(int i=0;i<26;i++){

        if(a[i]>0){
            num++;
        char cha;
        cha='a'+i;
        cout<<cha<<"--"<<a[i]<<" ";     //ÿ����ĸ���ֵĴ���  ��ΪȨ
        v.insert(pair<char,int>(cha,a[i]));
        }
    }
    cout<<endl;
    printf("��ĸ��������Ϊ��");
    cout<<num<<endl;
    cout<<endl;
    fclose(fi);
}


void Selectmin(huffmantree ht,int num2,int &s1,int &s2){        //�ҳ�����Ȩֵ��С�ĵ�
    s1=s2=0;    //��ʼ�������ڵ��λ��
    int i;
    for(i=1;i<=num2;i++){
        if(ht[i].parent==0){
            if(s1==0) s1=i;
            else{
                s2=i;
                break;
            }
        }
    }
    if(ht[s1].weight>ht[s2].weight){
        int t=s1;
        s1=s2;
        s2=t;
    }
    for(i=i+1;i<num2;i++){
        if(ht[i].parent==0){
            if(ht[i].weight<ht[s1].weight){
                s2=s1;
                s1=i;
            }
            else if(ht[i].weight<ht[s2].weight){
                s2=i;
            }
        }
    }
}


void creathuffmantree(huffmantree &ht,int num,map<char,int> v){     //����huffmantree
    m=2*num-1;
    ht = new htnode[m+1];   //htnode[0]����ڵ�
    for(int i=1;i<=m;i++){   //��ʼ��ÿ���ڵ��ֵ
        ht[i].parent=ht[i].lchild=ht[i].rchild=0;
        ht[i].code='9';       //��ʼ�����붼Ϊ-1
    }
    map<char, int>::reverse_iterator iter;
    int j=1;
    for(iter = v.rbegin(); iter !=v.rend(); iter++){

        //cout<<iter->first<<"  "<<iter->second<<endl;
        ht[j].c=iter->first;
        ht[j].weight=iter->second;
        j++;
    }

    ht[0].weight=num;
    for(int i=num+1;i<=m;i++){//����num���ڵ㣬��num+1��ʼ��ӽڵ�  �����num-1����Ҳ���ǵ�m
        int s1,s2;
        Selectmin(ht,i,s1,s2); //������ӽڵ��λ��  ����������Сֵs1<=s2
         //�����ڵ��˫������Ϊ�½ڵ��λ��
         ht[s1].parent=i;
         ht[s2].parent=i;
         ht[s1].code='0';     //����
         ht[s2].code='1';
         //����½ڵ㣬���Һ���
         ht[i].lchild=s1;
         ht[i].rchild=s2;
         ht[i].weight=ht[s1].weight+ht[s2].weight;//�½ڵ�Ȩֵ
    }
}

int huffmantreeWPL(huffmantree ht,int i,int d){ //����huffman�����ڵ�λ�ã��ڵ����
        if(ht[i].lchild==0&&ht[i].rchild==0){  //Ҷ�ӽڵ㣻����ýڵ�·��
            return ht[i].weight*d;
        }
        else{  // ���ýڵ㲻��Ҷ�ӽڵ㣬��ýڵ��·���������Һ��ӵ�·����
            return huffmantreeWPL(ht,ht[i].lchild,d+1)+huffmantreeWPL(ht,ht[i].rchild,d+1);
        }
}

void printfhuffman(huffmantree ht){    //���huffman�����ڵ����Ϣ
    for(int i=1;i<=m;i++){
        cout<<"Ҷ�ӽ�㣺 "<<ht[i].c<<" ";
        cout<<std::left<<setw(10)<<"    ��ţ� "<<i<<" ";
        cout<<std::left<<setw(10)<<"    Ȩֵ�� "<<ht[i].weight<<" ";
        cout<<std::left<<setw(10)<<"    ���׽��: "<<ht[i].parent<<" ";
        cout<<std::left<<setw(10)<<"    ���ӣ� "<<ht[i].lchild<<" ";
        cout<<std::left<<setw(10)<<"    �Һ��ӣ� "<<ht[i].rchild<<" "<<endl;
    }
    cout<<endl;
    cout<<"��ĸ����"<<endl;
    cout<<endl;

}

void Encoding(huffmantree ht,int i){    //���Ҷ�ӽڵ�ı���
    if(ht[i].parent==0){
        return;
    }
    else{
        Encoding(ht,ht[i].parent);
    }
    cout<<ht[i].code;


}
void huffmantreeEncoding(huffmantree ht){       //Ҷ�ӽڵ�ı���
  //  freopen("b.txt","w",stdout);
    for(int i=1;i<=num;i++){  //ֻ���ǰnum,��Ҷ�ӽڵ�ı���
        if(ht[i].lchild==0&&ht[i].rchild==0) //����ýڵ�ΪҶ�ӽڵ�
        {
           // char ch;

            cout<<ht[i].c<<"--";
            //printf("%d��",ht[i].weight);
            cout<<"���룺";
            Encoding(ht,i);    //�õݹ�����ýڵ�ı���
            printf("\n");
        }
    }
}

void BianMa(huffmantree ht){    //���б��룬����b��
    FILE *fi=freopen("a.txt","r",stdin);
    FILE *fo=freopen("b.txt","w",stdout);
    gets(s);                //gets()����ʱ�ո�Ҳ���룬�س�������
    len=strlen(s);
    for(int i=0;i<len;i++){
        for(int j=1;j<=num;j++){
            if(s[i]==ht[j].c){
                Encoding(ht,j);
            }
        }
        if(s[i]<'a'||s[i]>'z'){
            cout<<s[i];
        }
    }
    fclose(fo);
    fclose(fi);

}

void Compareyima(huffmantree ht){      //��b�����Ľ������룬��������ļ�c�У�ͬʱ�Ƚ��ļ�a,c�Ƿ�һ�£��Լ�����롢�������ȷ��
    FILE *fi1=freopen("a.txt","r",stdin);
    gets(s);
    //int len1=strlen(s);
    fclose(fi1);
    FILE *fi2=freopen("b.txt","r",stdin);
    char b[1010];
    gets(b);
    //int len2=strlen(b);
    fclose(fi2);
    freopen("c.txt","w",stdout);
    int i=m;
    int j=0;
    while(b[j]!='\0'){    //�����ַ�����/���봮
      if(b[j]=='0')
        i=ht[i].lchild;   //��������
      else if(b[j]=='1')
        i=ht[i].rchild;    //�����Һ���
      else{
        printf("%c",b[j]);
      }
      if(ht[i].lchild==0){   //���Ƿ�ýڵ�ΪҶ�ӽڵ�
        printf("%c",ht[i].c);//�ǵĻ�����������ظ��ڵ�
        i=m;
      }
      j++;   //�����Ƿ��ҵ�Ҷ�ӽڵ㶼��ȡ��һ�����봮�ַ�

    }
}

int main()
{
    using std::cout;
    cout.setf(std::ios::right);  //�����ʽΪ�����
    cout<<"������ĸ��Ϊ��"<<endl;
    huffmantree ht;
    f1();
    creathuffmantree(ht,num,v); //numΪҶ�ӽ����
    cout<<"WPL = "<<huffmantreeWPL(ht,m,0)<<endl;   //���Ĵ�Ȩ·������ΪWPL
    printfhuffman(ht);
    huffmantreeEncoding(ht);
    BianMa(ht);
    Compareyima(ht);
    return 0;
}
