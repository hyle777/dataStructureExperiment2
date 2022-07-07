#include "widget.h"
#include "ui_widget.h"
#include <QStringList>
#include <QVector>
#include<QMessageBox>
#include<QPainter>
#include<QFileDialog>
#include<QElapsedTimer>
#include "StudentMes.h"
#include "bintree.cpp"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    selection=0;
    initWidget(0);
}

Widget::~Widget()
{

    delete ui;
}

void Widget::initWidget(binTreeNode<studentMes>* findnode)
{
    //列表控件初始化
    //设置列数
    ui->tableWidget->setColumnCount(7);

    //设置水平表头
    QStringList qsl;
    qsl<<"学号"<<"姓名"<<"性别"<<"年龄"<<"出生日期"<<"电话"<<"地址";
    ui->tableWidget->setHorizontalHeaderLabels(qsl);

    if(findnode!=0)
    {
        //设置行数
        ui->tableWidget->setRowCount(1);
        ui->tableWidget->setItem(0,0,new QTableWidgetItem(findnode->data.num));
        ui->tableWidget->setItem(0,1,new QTableWidgetItem(findnode->data.name));
        ui->tableWidget->setItem(0,2,new QTableWidgetItem(findnode->data.sex));
        ui->tableWidget->setItem(0,3,new QTableWidgetItem(findnode->data.age));
        ui->tableWidget->setItem(0,4,new QTableWidgetItem(findnode->data.birth));
        ui->tableWidget->setItem(0,5,new QTableWidgetItem(findnode->data.phone));
        ui->tableWidget->setItem(0,6,new QTableWidgetItem(findnode->data.address));
        return;
    }

    QElapsedTimer timer;
    timer.start();
    QVector<binTreeNode<studentMes>*> qstu;
    //获得先序遍历的学生列表
    if(selection==0){
        qDebug()<<"层次遍历时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
        bt.levelOrder(bt.getRoot(),qstu);
    }
    else if(selection==1){
        bt.preOrder(bt.getRoot(),qstu);
    qDebug()<<"前序遍历的时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    }
    else if(selection==2){
        bt.inOrder(bt.getRoot(),qstu);
        qDebug()<<"中序遍历时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    }
    else if(selection==3){
        bt.postOrder(bt.getRoot(),qstu);
        qDebug()<<"后序遍历时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    }
    else if(selection==4){
        bt.getMinAge(bt.getRoot(),qstu);
    qDebug()<<"获取最小值的时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    }


    //设置行数
    ui->tableWidget->setRowCount(qstu.length());

    //设置正文
    for(int i=0;i<qstu.length();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(qstu.at(i)->data.num ));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(qstu.at(i)->data.name));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(qstu.at(i)->data.sex));
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(qstu.at(i)->data.age));
        ui->tableWidget->setItem(i,4,new QTableWidgetItem(qstu.at(i)->data.birth));
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(qstu.at(i)->data.phone));
        ui->tableWidget->setItem(i,6,new QTableWidgetItem(qstu.at(i)->data.address));
    }

    qDebug()<<"更新窗口时间为"<<timer.elapsed()/1000.0<<"s"<<endl;

  }


//添加按钮的槽函数（点击）
void Widget::on_pushButton_clicked()
{
    if(filename=="") {QMessageBox::critical(this,"错误","请先选择文件再继续操作");return;}
    studentMes stu;
    stu.num=ui->lineEdit_num->text();
    stu.name=ui->lineEdit_name->text();
    stu.sex=ui->lineEdit_sex->text();
    stu.age=ui->lineEdit_age->text();
    stu.birth=ui->lineEdit_birth->text();
    stu.phone=ui->lineEdit_phone->text();
    stu.address=ui->lineEdit_address->text();
    if(stu.num!=""&&stu.name!="")
    {
    if(bt.serachNum(stu.num)!=0) {QMessageBox::critical(this,"错误","该学号已存在");return;}
    bt.insertNode(stu);
    }
    else
    {QMessageBox::critical(this,"错误","输入的学号和姓名不能为空");return;}
    bt.writeFile(filename);
    initWidget(0);
}

void Widget::on_pushButton_level_clicked()
{
    selection=0;
    initWidget(0);
}

void Widget::on_pushButton_pre_clicked()
{
    selection=1;
    initWidget(0);
}

void Widget::on_pushButton_in_clicked()
{
    selection=2;
    initWidget(0);
}

void Widget::on_pushButton_post_clicked()
{
    selection=3;
    initWidget(0);
}

//绘图事件
void Widget::paintEvent(QPaintEvent*)
{
    //创建画家 指定绘图设备（this表示在这个窗口）
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/background.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}

void Widget::on_pushButton_numsch_clicked()
{
    if(ui->lineEdit_numsch->text()=="") {QMessageBox::critical(this,"错误","输入学号不能为空");return;}
    QString findstr=ui->lineEdit_numsch->text();
    binTreeNode<studentMes>* t=bt.serachNum(findstr);
      if(t==0){QMessageBox::critical(this,"错误","该学号不存在");return;}
    initWidget(t);

}

void Widget::on_pushButton_numdel_clicked()
{
    QString str=ui->lineEdit_numsch->text();
    if(str=="") {QMessageBox::critical(this,"错误","输入学号不能为空");return;}
    bt.deleteNum(str);
    bt.writeFile(filename);
    initWidget(0);
}

void Widget::on_pushButton_namesch_clicked()
{
    if(ui->lineEdit_namesch->text()=="") {QMessageBox::critical(this,"错误","输入姓名不能为空");return;}
    QString findstr=ui->lineEdit_namesch->text();
    binTreeNode<studentMes>* t=bt.serachName(findstr);
      if(t==0){QMessageBox::critical(this,"错误","该姓名不存在");return;}
    initWidget(t);
}

void Widget::on_pushButton_namedel_clicked()
{
    QString str=ui->lineEdit_namesch->text();
    if(str=="") {QMessageBox::critical(this,"错误","输入姓名不能为空");return;}
    bt.deleteName(str);
    bt.writeFile(filename);
    initWidget(0);
}

void Widget::on_pushButton_phosch_clicked()
{
    if(ui->lineEdit_phosch->text()=="") {QMessageBox::critical(this,"错误","输入电话不能为空");return;}
    QString findstr=ui->lineEdit_phosch->text();
    binTreeNode<studentMes>* t=bt.serachPhone(findstr);
      if(t==0){QMessageBox::critical(this,"错误","该电话不存在");return;}
    initWidget(t);
}

void Widget::on_pushButton_phodel_clicked()
{
    QString str=ui->lineEdit_phosch->text();
    if(str=="") {QMessageBox::critical(this,"错误","输入学号不能为空");return;}
    bt.deletePhone(str);
    bt.writeFile(filename);
    initWidget(0);
}



void Widget::on_pushButton_getMinAge_clicked()
{
    selection=4;
    initWidget(0);
}

void Widget::on_pushButton_selectfile_clicked()
{
    QElapsedTimer timer;
    timer.start();
    if(bt.getRoot()!=0) delete bt.getRoot();
    QString path=QFileDialog::getOpenFileName(this,"打开文件","d:");
    ui->lineEdit_filename->setText(path);
    filename=path;
    bt.readFile(path);
    qDebug()<<"建树时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
    initWidget(0);
    qDebug()<<"更新窗口时间为"<<timer.elapsed()/1000.0<<"s"<<endl;
}
