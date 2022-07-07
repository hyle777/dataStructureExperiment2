#ifndef STUDENTMES_H
#define STUDENTMES_H
//程序名：studentmes.h
//      程序功能：学生信息类的定义（包含复制构造函数，比较学号，姓名，电话函数，写文件，读文件函数）
//          作者：cayl
//          日期：2021.11.14
//          版本：1.0
//      修改内容：无
//      修改日期：
//      修改作者：
//
//
//
#include<QString>
#include<QFile>
#include<QDebug>

struct studentMes{
    //学号 姓名 性别 年龄 出生日期 电话 地址
    QString num;
    QString name;
    QString sex;
    QString age;
    QString birth;
    QString phone;
    QString address;

    //无参构造函数
    studentMes(){}
    //复制构造函数 =重载
    studentMes& operator=(studentMes& x) {
        this->num=x.num;
        this->name=x.name;
        this->sex=x.sex;
        this->age=x.age;
        this->birth=x.birth;
        this->phone=x.phone;
        this->address=x.address;
        return *this;
    }

    //比较学号
    bool compareNum(QString str)
    {
        if(num==str) return true;
        return false;
    }

    //比较姓名
    bool compareName(QString str)
    {
        if(name.compare(str)==0) return true;
        return false;
    }

    //比较电话
    bool comparePhone(QString str)
    {
        if(phone.compare(str)==0) return true;
        return false;
    }

    //将该结构写到文件中
    void myWrite(QFile& file)
    {
        QString str=num+"\t"+name+"\t"+sex+"\t"+age+"\t"+birth+"\t"+phone+"\t"+address+"\n";
        file.write(str.toLocal8Bit().data());
    }

    //从文件中读取该结构
    void myread(QString str)
    {
       if(str!="\n"){
       this->num=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->name=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->sex=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->age=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->birth=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->phone=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\t')+1);}
       if(str!="\n"){
       this->address=str.mid(0,str.indexOf('\t'));
       str.remove(0,str.indexOf('\n')+1);}
    }


    //qDebug()调试重载
    friend QDebug& operator<<(QDebug& qdb,studentMes &stu)
    {
        qdb<<stu.num;
        return qdb;
    }
};

#endif // STUDENTMES_H
