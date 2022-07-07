#ifndef WIDGET_H
#define WIDGET_H

//程序名：widget.h
//      程序功能：窗口类的定义（包含初始化和更新窗口函数，绘图事件及按钮的相关槽函数）
//          作者：cayl
//          日期：2021.11.14
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//

#include <QWidget>
#include "StudentMes.h"
#include "bintree.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //初始化和更新窗口
    void initWidget(binTreeNode<studentMes>* findnode);
    //绘图事件
    void paintEvent(QPaintEvent*);


private slots://
    //点击添加按钮
    void on_pushButton_clicked();

    //点击层次遍历按钮
    void on_pushButton_level_clicked();

    //点击前序遍历按钮
    void on_pushButton_pre_clicked();

    //点击中序遍历按钮
    void on_pushButton_in_clicked();

    //点击后序遍历按钮
    void on_pushButton_post_clicked();

    //点击学号搜素按钮
    void on_pushButton_numsch_clicked();

    //点击学号删除按钮
    void on_pushButton_numdel_clicked();

    //点击名字搜素按钮
    void on_pushButton_namesch_clicked();

    //点击名字删除按钮
    void on_pushButton_namedel_clicked();

    //点击电话搜素按钮
    void on_pushButton_phosch_clicked();

    //点击电话删除按钮
    void on_pushButton_phodel_clicked();

    //点击获取最小年龄学生按钮
    void on_pushButton_getMinAge_clicked();

    //点击选择文件按钮
    void on_pushButton_selectfile_clicked();

private:
    //ui界面的指针
    Ui::Widget *ui;

    //二叉树类对象 调用相关函数
    binTree<studentMes> bt;

    //遍历方式的选择
    int selection;

    QString filename;


};
#endif // WIDGET_H
