#ifndef BINTREE_H
#define BINTREE_H
//程序名：bintree.h
//      程序功能：二叉树结构模板类的定义（包含建立，插入，查询（按学号，姓名，电话），删除（按学号，姓名，电话）
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

#include "BinTreeNode.h"
#include <QVector>

template<class T>
class binTree
{
private:

    //根节点
    binTreeNode<T>* root;

    //为某个节点申请空间并初始化
    void addNode(binTreeNode<T>* &node,T data,int flag);

    //将文件读入的QByteArray数据类型转化为QString
    QString byteArrayToUnicode(const QByteArray &array);

public:

    binTree();
    //获得根节点 递归遍历函数需要调用（
    //可以将递归遍历函数设置为私有 再用其他接口调用 则不需要这个函数）
    binTreeNode<T>* getRoot(){return this->root;}

    //    1------
    //    新建学生通讯录（以层次遍历的方式进行学生信息的输入）
    //    文件中输入 readFile函数中调用
    void buildTree(QVector<T*> da,QVector<int> flag);
    //    2------
    //    向学生通讯录插入学生信息
    void insertNode(T data);

    //    3------
    //    在通讯录中查询学生信息（按学号查询）
    binTreeNode<T>* serachNum(QString num);

    //    4------
    //    在通讯录中查询学生信息（按姓名查询）
    binTreeNode<T>* serachName(QString name);

    //    5------
    //    在通讯录中查询学生信息（按电话号码查询）
    binTreeNode<T>* serachPhone(QString phone);

    //    6------
    //    在通讯录删除学生信息（先按上述 3-5 的查询方式定位被删除学生）
    bool deleteNum(QString num);
    bool deleteName(QString name);
    bool deletePhone(QString phone);

    //    7------
    //    输出年龄最小的学生信息
    void getMinAge(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu);

    //    8------
    //    在屏幕中输出全部学生信息（可以选择是以前序、中序、后序遍历的方式）
    //先序遍历
    void preOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu);
    //中序遍历
    void inOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu);
    //后序遍历
    void postOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu);
    //层次遍历
    void levelOrder(binTreeNode<T>* root,QVector<binTreeNode<T>*> &qstu);
    //    9------
    //    从文件中读取通讯录信息（层次遍历）
    void readFile(QString filename);
    //    10------
    //    向文件写入学生通讯录信息
    void writeFile(QString filename);

};

#endif // BINTREE_H
