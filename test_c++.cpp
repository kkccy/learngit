#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int MaxW = 9999999;  // ������Ȩֵ������9999999
// ����huffman�������
class HuffNode
{
public:
    int weight;     // Ȩֵ
    int parent;     // ������±�
    int leftchild;  // �����±�
    int rightchild; // �Һ����±�
};
// ����շ�������
class HuffMan
{
private:
    void MakeTree();    // ������˽�к����������к�������
    void SelectMin(int pos, int* s1, int* s2);  // �� 1 �� pos ��λ���ҳ�Ȩֵ��С��������㣬�ѽ���±���� s1 �� s2 ��
public:
    int len;    // �������
    int lnum;   // Ҷ������
    HuffNode* huffTree; // �շ��������������ʾ
    string* huffCode;   // ÿ���ַ���Ӧ�ĺշ�������
    void MakeTree(int n, int wt[]); // ���к�������������main����
    void Coding();  // ���к�������������main����
    void Destroy();
};
// ����huffman��
void HuffMan::MakeTree(int n, int wt[])
{
    // ������Ҷ�ӽ��������Ҷ��Ȩֵ
    // ���к���������ӿ�
    int i;
    lnum = n;
    len = 2 * n - 1;
    huffTree = new HuffNode[2 * n];
    huffCode = new string[lnum + 1];    // λ�ô� 1 ��ʼ����
    // huffCodeʵ���Ǹ���ά�ַ����飬�� i �б�ʾ�� i ���ַ���Ӧ�ı���
    // �շ�����huffTree��ʼ��
    for (i = 1; i <= n; i++)
        huffTree[i].weight = wt[i - 1]; // ��0�Ų��ã���1��ʼ���
    for (i = 1; i <= len; i++)
    {
        if (i > n) huffTree[i].weight = 0;  // ǰn�������Ҷ�ӣ��Ѿ�����
        huffTree[i].parent = 0;
        huffTree[i].leftchild = 0;
        huffTree[i].rightchild = 0;
    }
    MakeTree();  // ����˽�к�������
}

void HuffMan::SelectMin(int pos, int* s1, int* s2)
{
    // �ҳ���С������Ȩֵ���±�
    // �������õ�ַ���ݵķ������ҳ������±걣���� s1 �� s2 ��
    int w1, w2, i;
    w1 = w2 = MaxW;  // ��ʼ��w1��w2Ϊ���ֵ���ڱȽ��лᱻʵ�ʵ�Ȩֵ�滻
    *s1 = *s2 = 0;
    for (i = 1; i <= pos; i++)
    {
        // �ȽϹ������£�
        // ����� i ������ȨֵС�� w1���ҵ� i �������δѡ��Ľ�㣬��ʾ������� i ���δѡ��������Ϊ 0
        if (huffTree[i].weight < w1 && huffTree[i].parent == 0)
        {
            w2 = w1;
            *s2 = *s1;
            w1 = huffTree[i].weight;
            *s1 = i;
        }
        else if (huffTree[i].weight < w2 && huffTree[i].parent == 0)
        {
            w2 = huffTree[i].weight;
            *s2 = i;
        }
        // �ѵ� w1 �� s1 ���浽 w2 �� s2����ԭ���ĵ�һ��Сֵ��ɵڶ���Сֵ
        // �ѵ� i ����Ȩֵ���±걣�浽 w1 �� s1����Ϊ��һ��Сֵ
        // ��������� i ����ȨֵС�� w2���ҵ� i �����δѡ��Ľ��
        // �ѵ� i ����Ȩֵ���±걣�浽 w2 �� s2����Ϊ�ڶ���Сֵ
    }
}
void HuffMan::MakeTree()
{//˽�к����������к�������
    int i, s1, s2;
    //����huffman��HuffTree��n-1����Ҷ�ӽ��
    for (i = lnum + 1; i <= len; i++)
    {
//        SelectMin(i - 1, &s1, &s2);    //�ҳ�������СȨֵ���±����s1��s2��
//        for (i = lnum + 1; i <= len; i++)
//        {
            SelectMin(i - 1, &s1, &s2);    //�ҳ�������СȨֵ���±����s1��s1
            huffTree[s1].parent = i;        //���ҳ�������Ȩֵ��С�������ϲ�Ϊһ������
            huffTree[s2].parent = i;        //���s1��s2�ĸ�����Ϊi
            huffTree[i].leftchild = s1;    //i�����Һ���Ϊs1,s2
            huffTree[i].rightchild = s2;
            huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;    //i��Ȩֵ����s1,s2Ȩֵ��
//        }
    }
}
// ���ٺշ�����
void HuffMan::Destroy()
{
    len = 0;
    lnum = 0;
    delete[]huffTree;
    delete[]huffCode;
}
// �շ�������
void HuffMan::Coding()
{
    char* cd;
    int i, c, f, start;

    //��n��Ҷ����huffman����
    cd = new char[lnum];        //���������Ĺ����ռ�
    cd[lnum - 1] = '\0';
    for (i = 1; i <= lnum; ++i)    //����ַ���huffman����
    {
        start = lnum - 1;    //���������λ��
        for (c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent)    //��Ҷ�ӵ������������
            if (huffTree[f].leftchild == c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
        huffCode[i] = new char[lnum - start];    //Ϊ��i���ַ��������ռ�
        huffCode[i].assign(&cd[start]);    //��cd�д�start��ĩβ�ı��븴�Ƶ�huffCode��
    }
    delete[]cd;    //�ͷŹ����ռ�
}
// ������
int main()
{
    int t, n, i, j;
    int wt[800];
    cin >> t;
    for (i = 0; i < t; i++)
    {
        HuffMan myHuff;
        cin >> n;
        for (int k = 0; k < n; k++) {
            cin >> wt[k];
        }
        myHuff.MakeTree(n, wt);
        myHuff.Coding();
        for (j = 1; j <= n; j++)
        {
            cout << myHuff.huffTree[j].weight << '-';   // �����Ȩֵ
            cout << myHuff.huffCode[j] << endl; // ���������
        }
        myHuff.Destroy();
    }
    return 0;
}
