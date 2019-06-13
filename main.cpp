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
int a[26];                  //存储每个字母出现的次数
char s[1000];
int m;      //一共多少个点
int num=0;    //叶子节点个数
int len;
map<char,int> v;  //键值对容器，对应字母和出现的次数
typedef struct{
    char c;
    int weight;  //权重
    int parent,lchild,rchild;  //节点的双亲下标，左右孩子的下标
    char code;                   //结点编号
}htnode,*huffmantree;

//统计短文出现的字母种数和每个字母出现的次数
void f1(){
    FILE *fi=freopen("a.txt","r",stdin);
    gets(s);                //gets()读入时空格也读入，直到遇到回格键
     len=strlen(s);
    cout<<len<<endl;        //短文长度
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
        cout<<cha<<"--"<<a[i]<<" ";     //每个字母出现的次数  作为权
        v.insert(pair<char,int>(cha,a[i]));
        }
    }
    cout<<endl;
    printf("字母的种类数为：");
    cout<<num<<endl;
    cout<<endl;
    fclose(fi);
}


void Selectmin(huffmantree ht,int num2,int &s1,int &s2){        //找出两个权值最小的点
    s1=s2=0;    //初始化两个节点的位置
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


void creathuffmantree(huffmantree &ht,int num,map<char,int> v){     //创建huffmantree
    m=2*num-1;
    ht = new htnode[m+1];   //htnode[0]不存节点
    for(int i=1;i<=m;i++){   //初始化每个节点的值
        ht[i].parent=ht[i].lchild=ht[i].rchild=0;
        ht[i].code='9';       //初始化编码都为-1
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
    for(int i=num+1;i<=m;i++){//已有num个节点，从num+1开始添加节点  共添加num-1个，也就是到m
        int s1,s2;
        Selectmin(ht,i,s1,s2); //传入添加节点的位置  返回两个最小值s1<=s2
         //将两节点的双亲设置为新节点的位置
         ht[s1].parent=i;
         ht[s2].parent=i;
         ht[s1].code='0';     //编码
         ht[s2].code='1';
         //添加新节点，左右孩子
         ht[i].lchild=s1;
         ht[i].rchild=s2;
         ht[i].weight=ht[s1].weight+ht[s2].weight;//新节点权值
    }
}

int huffmantreeWPL(huffmantree ht,int i,int d){ //传入huffman树，节点位置，节点深度
        if(ht[i].lchild==0&&ht[i].rchild==0){  //叶子节点；算出该节点路径
            return ht[i].weight*d;
        }
        else{  // 若该节点不是叶子节点，则该节点的路径等于左右孩子的路径和
            return huffmantreeWPL(ht,ht[i].lchild,d+1)+huffmantreeWPL(ht,ht[i].rchild,d+1);
        }
}

void printfhuffman(huffmantree ht){    //输出huffman树各节点的信息
    for(int i=1;i<=m;i++){
        cout<<"叶子结点： "<<ht[i].c<<" ";
        cout<<std::left<<setw(10)<<"    序号： "<<i<<" ";
        cout<<std::left<<setw(10)<<"    权值： "<<ht[i].weight<<" ";
        cout<<std::left<<setw(10)<<"    父亲结点: "<<ht[i].parent<<" ";
        cout<<std::left<<setw(10)<<"    左孩子： "<<ht[i].lchild<<" ";
        cout<<std::left<<setw(10)<<"    右孩子： "<<ht[i].rchild<<" "<<endl;
    }
    cout<<endl;
    cout<<"字母编码"<<endl;
    cout<<endl;

}

void Encoding(huffmantree ht,int i){    //输出叶子节点的编码
    if(ht[i].parent==0){
        return;
    }
    else{
        Encoding(ht,ht[i].parent);
    }
    cout<<ht[i].code;


}
void huffmantreeEncoding(huffmantree ht){       //叶子节点的编码
  //  freopen("b.txt","w",stdout);
    for(int i=1;i<=num;i++){  //只输出前num,即叶子节点的编码
        if(ht[i].lchild==0&&ht[i].rchild==0) //如果该节点为叶子节点
        {
           // char ch;

            cout<<ht[i].c<<"--";
            //printf("%d：",ht[i].weight);
            cout<<"编码：";
            Encoding(ht,i);    //用递归输出该节点的编码
            printf("\n");
        }
    }
}

void BianMa(huffmantree ht){    //进行编码，存入b中
    FILE *fi=freopen("a.txt","r",stdin);
    FILE *fo=freopen("b.txt","w",stdout);
    gets(s);                //gets()读入时空格也读入，回车键结束
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

void Compareyima(huffmantree ht){      //对b中码文进行译码，结果存入文件c中，同时比较文件a,c是否一致，以检验编码、译码的正确性
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
    while(b[j]!='\0'){    //遍历字符数组/编码串
      if(b[j]=='0')
        i=ht[i].lchild;   //走向左孩子
      else if(b[j]=='1')
        i=ht[i].rchild;    //走向右孩子
      else{
        printf("%c",b[j]);
      }
      if(ht[i].lchild==0){   //看是否该节点为叶子节点
        printf("%c",ht[i].c);//是的话输出，并返回根节点
        i=m;
      }
      j++;   //无论是否找到叶子节点都读取下一个编码串字符

    }
}

int main()
{
    using std::cout;
    cout.setf(std::ios::right);  //输出格式为左对齐
    cout<<"短文字母数为："<<endl;
    huffmantree ht;
    f1();
    creathuffmantree(ht,num,v); //num为叶子结点数
    cout<<"WPL = "<<huffmantreeWPL(ht,m,0)<<endl;   //树的带权路径长度为WPL
    printfhuffman(ht);
    huffmantreeEncoding(ht);
    BianMa(ht);
    Compareyima(ht);
    return 0;
}
