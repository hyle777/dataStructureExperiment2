#ifndef BINTREENODE_H
#define BINTREENODE_H
//程序名：bintree.h
//      程序功能：二叉树节点模板类的定义
//          作者：cayl
//          日期：2021.11.14
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//
template<class T>
struct binTreeNode
{
    //删除的标志 0 表示未删除 1表示已删除
    int flag;

    //模板参数 学生数据及相关信息
    T data;

    //左，右孩子节点
    binTreeNode<T>* leftChild,*rightChild;

    //无参构造函数
    binTreeNode(){flag=0;leftChild=rightChild=0;}
    //含参构造函数
    binTreeNode(T data){flag=0;this->data=data;leftChild=rightChild=0;}
};

#endif // BINTREENODE_H
