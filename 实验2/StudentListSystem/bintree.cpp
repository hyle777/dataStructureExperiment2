//程序名：bintree.cpp
//      程序功能：二叉树结构模板类的实现（包含建立，插入，查询（按学号，姓名，电话），删除（按学号，姓名，电话）
//                  前序，中序，后序，层次遍历，写文件，读文件等函数）
//          作者：cayl
//          日期：2021.11.14
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//

#include "bintree.h"
#include <QQueue>
#include <QDebug>
#include <QFile>
#include<QTextCodec>
#include"StudentMes.h"

template<class T>
binTree<T>::binTree()
{
    root=0;
}

//////////////////////////////////////////////////////////////////////////////
//  建立二叉树函数
//  函数功能：将da数组里面的元素和flag数组的标志（按层次遍历的顺序）建立二叉树
//函数参数：
//       da 模板参数数组：存储二叉数每个节点的数据（按层次遍历排序）
//       flag 标志参数数组：存储二叉树每个节点的标志（按层次遍历的顺序）
//参数返回值：无
template<class T>
void binTree<T>::buildTree(QVector<T*> da,QVector<int> flag)
{
    if(da.length()==0) return;
    addNode(root,*da.at(0),flag.at(0));
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    int i=1;
    while(!qu.empty()&&i<da.length())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //左节点为空 可添加节点
        addNode(t->leftChild,*da.at(i),flag.at(i));i++;
        qu.push_back(t->leftChild);

        if(i<da.length()){//符合条件
        //右节点为空 可添加节点
        addNode(t->rightChild,*da.at(i),flag.at(i));i++;
        qu.push_back(t->rightChild);}
    }

}


//////////////////////////////////////////////////////////////////////////////
//  插入函数
//  函数功能：将一个节点层次遍历插入到二叉树上
//函数参数：
//       data 模板参数，表示节点的数据
//参数返回值：无
template<class T>
void binTree<T>::insertNode(T data)
{
    if(root==0) {
        addNode(root,data,0);
        //writeFile(QString filename);
        return;}
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        if(t->leftChild==0)//左节点为空 可添加节点
        {addNode(t->leftChild,data,0);break;}
        else//不空则入队列
            qu.push_back(t->leftChild);
        if(t->rightChild==0)//右节点为空 可添加节点
        {addNode(t->rightChild,data,0);break;}
        else//不空则入队列
            qu.push_back(t->rightChild);

    }
    //writeFile();
}

template<class T>
void binTree<T>::addNode(binTreeNode<T>* &node,T data,int flag)
{
    node=new binTreeNode<T>;
    node->data=data;
    node->flag=flag;
    node->leftChild=node->rightChild=0;
}


//////////////////////////////////////////////////////////////////////////////
//  前序遍历函数
//  函数功能：将一个新值插入到第i位置上
//函数参数：
//       i 表示插入位置
//       x 表示待插入的元素值
//参数返回值：
//     1： 表示插入成功
//     0：表示插入失败

template<class T>
void binTree<T>::preOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu)
{

    if(root==0) return;

    //放到数组
    if(root->flag==0)
    qstu.append(root);


    preOrder(root->leftChild,qstu);
    preOrder(root->rightChild,qstu);
}

//中序遍历 递归做法
template<class T>
void binTree<T>::inOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu)
{
    if(root==0) return;

    inOrder(root->leftChild,qstu);

    //访问
//    QDebug qdb=qDebug();
//    qdb<<root->data;

    //放到数组
    if(root->flag==0)
    qstu.append(root);


    inOrder(root->rightChild,qstu);
}

//后序遍历 递归算法
template<class T>
void binTree<T>::postOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu)
{
    if(root==0) return;

    //访问
    postOrder(root->leftChild,qstu);
    postOrder(root->rightChild,qstu);

    //放到数组
    if(root->flag==0)
    qstu.append(root);

//    QDebug qdb=qDebug();
//    qdb<<root->data;
}

template<class T>
void binTree<T>::levelOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu)
{
    if(root==0) return;
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //访问
        if(t->flag==0)
        qstu.append(t);
        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
    }
}

//层次遍历的顺序
template<class T>
binTreeNode<T>* binTree<T>::serachNum(QString num)
{
    if(root==0) return 0;
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //访问
        if(t->data.compareNum(num)&&t->flag==0) {return t;}

        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
    }
    return 0;
}

template<class T>
binTreeNode<T>* binTree<T>::serachName(QString name)
{
    if(root==0) return 0;
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //访问
        if(t->data.compareName(name)&&t->flag==0) {return t;}

        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
    }
    return 0;
}

template<class T>
binTreeNode<T>* binTree<T>::serachPhone(QString phone)
{
    if(root==0) return 0;
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //访问
        if(t->data.comparePhone(phone)&&t->flag==0) {return t;}

        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
    }
    return 0;
}

template<class T>
bool binTree<T>::deleteNum(QString num){
    binTreeNode<T>* findNode=serachNum(num);
    if(findNode==0) return false;
    findNode->flag=1;
    //writeFile();
    return true;
}

template<class T>
bool binTree<T>::deleteName(QString name){
    binTreeNode<T>* findNode=serachName(name);
    if(findNode==0) return false;
    findNode->flag=1;
    //writeFile();
    return true;
}

template<class T>
bool binTree<T>::deletePhone(QString phone){
    binTreeNode<T>* findNode=serachPhone(phone);
    if(findNode==0) return false;
    findNode->flag=1;
    //writeFile();
    return true;
}






//层次遍历的顺序
template<class T>
void binTree<T>::readFile(QString filename)
{
    QFile file(filename);
    //文件是否打开
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug()<<"文件打开失败！"<<endl;
        return;}
    //读取文件的一行
    QByteArray con=file.readLine();
    //格式转换 不然会出现中文乱码的现象
    QString str=byteArrayToUnicode(con);


    QVector<T*> qvec;
    QVector<int> flag;
    while(str!=""&&str!='\n')
    {
        QString tmp=str.mid(0,str.indexOf('\t'));
        str.remove(0,str.indexOf('\t')+1);
        int x=tmp.toInt();
        T* temp=new T;
        temp->myread(str);
        qvec.push_back(temp);
        flag.push_back(x);

        QByteArray con=file.readLine();
        str=byteArrayToUnicode(con);
    }

    file.close();

    buildTree(qvec,flag);
}

template<class T>
void binTree<T>::writeFile(QString filename)
{
    if(root==0) return;

    //创建或打开文件
    QFile file(filename);
    //判断文件是否打开
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug()<<"文件打开失败！"<<endl;
        return;}
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);
    while(!qu.empty())
    {
        binTreeNode<T>* t=qu.front();
        qu.pop_front();

        //访问
        //调用write写文件
        //标志写入文件
        QString str=QString::number(t->flag)+"\t";
        file.write(str.toLocal8Bit().data());
        //模板参数不能直接调用
        //file.write(t->data);
        t->data.myWrite(file);

        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
    }

    file.close();
}

template<class T>
QString binTree<T>::byteArrayToUnicode(const QByteArray &array)
{
    // state用于保存转换状态，它的成员invalidChars，可用来判断是否转换成功
    // 如果转换成功，则值为0，如果值大于0，则说明转换失败
    QTextCodec::ConverterState state;
    // 先尝试使用utf-8的方式把QByteArray转换成QString
    QString text = QTextCodec::codecForName("UTF-8")->toUnicode(array.constData(), array.size(), &state);
    // 如果转换时无效字符数量大于0，说明编码格式不对
    if (state.invalidChars > 0)
    {
        // 再尝试使用GBK的方式进行转换，一般就能转换正确(当然也可能是其它格式，但比较少见了)
        text = QTextCodec::codecForName("GBK")->toUnicode(array);
    }
    return text;
}

template<class T>
void binTree<T>::getMinAge(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu)
{
    if(root==0) return;
    QQueue<binTreeNode<T>*> qu;
    qu.push_back(root);

    while(!qu.empty()){
        binTreeNode<T>* t=qu.front();
        qu.pop_front();
        //访问
        if(t->flag==0){
            if(t->data.age!=""){
                int tage=t->data.age.toInt();
                if(qstu.empty()) qstu.push_back(t);
                else{
                int topage=qstu.front()->data.age.toInt();
                if(tage<topage){
                while(!qstu.empty()) qstu.pop_front();
                qstu.append(t);
                }
                else if(tage==topage)
                qstu.append(t);}
            }
        }
        if(t->leftChild!=0) qu.push_back(t->leftChild);
        if(t->rightChild!=0) qu.push_back(t->rightChild);
        }
}


