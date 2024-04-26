#include<iostream>
#include<string>
#include<cstring>
using namespace std;

const int MaxW = 9999999;  // 假设结点权值不超过9999999
// 定义huffman树结点类
class HuffNode
{
public:
    int weight;     // 权值
    int parent;     // 父结点下标
    int leftchild;  // 左孩子下标
    int rightchild; // 右孩子下标
};
// 定义赫夫曼树类
class HuffMan
{
private:
    void MakeTree();    // 建树，私有函数，被公有函数调用
    void SelectMin(int pos, int* s1, int* s2);  // 从 1 到 pos 的位置找出权值最小的两个结点，把结点下标存在 s1 和 s2 中
public:
    int len;    // 结点数量
    int lnum;   // 叶子数量
    HuffNode* huffTree; // 赫夫曼树，用数组表示
    string* huffCode;   // 每个字符对应的赫夫曼编码
    void MakeTree(int n, int wt[]); // 公有函数，被主函数main调用
    void Coding();  // 公有函数，被主函数main调用
    void Destroy();
};
// 构建huffman树
void HuffMan::MakeTree(int n, int wt[])
{
    // 参数是叶子结点数量和叶子权值
    // 公有函数，对外接口
    int i;
    lnum = n;
    len = 2 * n - 1;
    huffTree = new HuffNode[2 * n];
    huffCode = new string[lnum + 1];    // 位置从 1 开始计算
    // huffCode实质是个二维字符数组，第 i 行表示第 i 个字符对应的编码
    // 赫夫曼树huffTree初始化
    for (i = 1; i <= n; i++)
        huffTree[i].weight = wt[i - 1]; // 第0号不用，从1开始编号
    for (i = 1; i <= len; i++)
    {
        if (i > n) huffTree[i].weight = 0;  // 前n个结点是叶子，已经设置
        huffTree[i].parent = 0;
        huffTree[i].leftchild = 0;
        huffTree[i].rightchild = 0;
    }
    MakeTree();  // 调用私有函数建树
}

void HuffMan::SelectMin(int pos, int* s1, int* s2)
{
    // 找出最小的两个权值的下标
    // 函数采用地址传递的方法，找出两个下标保存在 s1 和 s2 中
    int w1, w2, i;
    w1 = w2 = MaxW;  // 初始化w1和w2为最大值，在比较中会被实际的权值替换
    *s1 = *s2 = 0;
    for (i = 1; i <= pos; i++)
    {
        // 比较过程如下：
        // 如果第 i 个结点的权值小于 w1，且第 i 个结点是未选择的结点，提示：如果第 i 结点未选择，它父亲为 0
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
        // 把第 w1 和 s1 保存到 w2 和 s2，即原来的第一最小值变成第二最小值
        // 把第 i 结点的权值和下标保存到 w1 和 s1，作为第一最小值
        // 否则，如果第 i 结点的权值小于 w2，且第 i 结点是未选择的结点
        // 把第 i 结点的权值和下标保存到 w2 和 s2，作为第二最小值
    }
}
void HuffMan::MakeTree()
{//私有函数，被公有函数调用
    int i, s1, s2;
    //构造huffman树HuffTree的n-1个非叶子结点
    for (i = lnum + 1; i <= len; i++)
    {
//        SelectMin(i - 1, &s1, &s2);    //找出两个最小权值的下标放入s1和s2中
//        for (i = lnum + 1; i <= len; i++)
//        {
            SelectMin(i - 1, &s1, &s2);    //找出两个最小权值的下标放入s1，s1
            huffTree[s1].parent = i;        //将找出的两棵权值最小的字数合并为一颗子树
            huffTree[s2].parent = i;        //结点s1，s2的父亲设为i
            huffTree[i].leftchild = s1;    //i的左右孩子为s1,s2
            huffTree[i].rightchild = s2;
            huffTree[i].weight = huffTree[s1].weight + huffTree[s2].weight;    //i的权值等于s1,s2权值和
//        }
    }
}
// 销毁赫夫曼树
void HuffMan::Destroy()
{
    len = 0;
    lnum = 0;
    delete[]huffTree;
    delete[]huffCode;
}
// 赫夫曼编码
void HuffMan::Coding()
{
    char* cd;
    int i, c, f, start;

    //求n个叶结点的huffman编码
    cd = new char[lnum];        //分配求编码的工作空间
    cd[lnum - 1] = '\0';
    for (i = 1; i <= lnum; ++i)    //逐个字符求huffman编码
    {
        start = lnum - 1;    //编码结束符位置
        for (c = i, f = huffTree[i].parent; f != 0; c = f, f = huffTree[f].parent)    //从叶子到根逆向球编码
            if (huffTree[f].leftchild == c)
            {
                cd[--start] = '0';
            }
            else
            {
                cd[--start] = '1';
            }
        huffCode[i] = new char[lnum - start];    //为第i各字符编码分配空间
        huffCode[i].assign(&cd[start]);    //把cd中从start到末尾的编码复制到huffCode中
    }
    delete[]cd;    //释放工作空间
}
// 主函数
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
            cout << myHuff.huffTree[j].weight << '-';   // 输出各权值
            cout << myHuff.huffCode[j] << endl; // 输出各编码
        }
        myHuff.Destroy();
    }
    return 0;
}
