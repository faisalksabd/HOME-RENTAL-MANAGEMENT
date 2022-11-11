#include "building_customize_menu.h"
#include "qsqlquery.h"
#include "ui_building_customize_menu.h"
#include<QMessageBox>
#include<QSql>
#include<QSqlDatabase>
#include<admin_after_login.h>
#include<string.h>
building_customize_menu::building_customize_menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::building_customize_menu)
{
     hide();
    ui->setupUi(this);
     QSqlQuery qy(QSqlDatabase::database("myconnect"));
             qy.prepare("select * from building");
             qy.exec();
             if(qy.next())
             {
             ui->lineEdit_BUILD_NAME->setText(qy.value(0).toString());
             ui->lineEdit_ADDRESS->setText(qy.value(1).toString());
             ui->textEdit->setText(qy.value(2).toString());

            }
}

building_customize_menu::~building_customize_menu()
{
    delete ui;
}




void building_customize_menu::on_pushButton_ADMIT_clicked()
{
    QString FLOOR=ui->lineEdit_FLOOR->text();
    QString a;
    QString FLAT=ui->lineEdit_FLAT->text().toUpper();
    QString name=ui->lineEdit_BUILD_NAME->text();
    QString address=ui->lineEdit_ADDRESS->text();
    QString type=ui->textEdit->toPlainText();
    QSqlDatabase db= QSqlDatabase::addDatabase("QSQLITE","myconnect");
     db.setDatabaseName("C:/sqlitestudio/database/faisal_sql.sqlite");
     if(FLAT==""||FLOOR=="")
     {
         QMessageBox::warning(this,"BUILDING","PLEASE INSERT DATA");
     }
     else
    {
         QMessageBox::StandardButton reply;
    reply=QMessageBox::question(this,"BUILDING","ARE SURE WANT TO ADMIT",QMessageBox::Yes|QMessageBox::No);

     if(reply==QMessageBox::Yes)
    {

     if(db.open())
     {
         QSqlQuery qy(QSqlDatabase::database("myconnect"));
         QSqlQuery qy1(QSqlDatabase::database("myconnect"));

         qy1.prepare(QString("DELETE FROM renter"));
         qy1.exec();
    for(char i='1';i<=FLOOR;i++)
    {
        for(char j='A';j<=FLAT;j++)
        {
          a=i;
          a=a+j;
            qy.prepare("insert into renter(FLAT)""values(:i)");
            qy.bindValue(":i",a);
            qy.exec();
        }
    }
    QMessageBox::information(this,"BUILDING","SUCESSFULLY ADDED");
     }
     else
     {
          QMessageBox::warning(this,"BUILDING","DATABASE NOT OPENED");
     }
    }
}


}


void building_customize_menu::on_pushButton_back_clicked()
{
     hide();
    admin_after_login ad;
    ad.setModal(true);
    ad.exec();
}


void building_customize_menu::on_pushButton_EDIT_clicked()
{
    QString type=ui->textEdit->toPlainText();
    QString name=ui->lineEdit_BUILD_NAME->text();
    QString address=ui->lineEdit_ADDRESS->text();
    QSqlQuery qy(QSqlDatabase::database("myconnect"));
    QSqlQuery qy1(QSqlDatabase::database("myconnect"));
    QSqlQuery qy2(QSqlDatabase::database("myconnect"));

   // qy1.prepare(QString("DELETE FROM renter"));
    //qy1.exec();
    qy2.prepare("UPDATE building set name=:name,address=:address,type=:type");
    qy2.bindValue(":name",name);
    qy2.bindValue(":address",address);
    qy2.bindValue(":type",type);
    // qy2.exec();
    if(qy2.exec())
    {
         QMessageBox::information(this,"BUILDING","EDITED");
    }
    else
    {
        QMessageBox::warning(this,"BUILDING","query not successfull");
    }

}
