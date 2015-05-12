#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QString>
#include <QList>
#include <QLinkedList>
#include <QtAlgorithms>
#include <iterator>
#include <iostream>
#include <QProcess>
using namespace std;
Hole Myhole;
Hole Hole2;
Process Myprocess;
Hole tmpHole;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Myprocess.P_ID=0;
}
bool small_or_not(Hole x,Hole y)
{
   return x.H_size<y.H_size;
}
bool Big_or_not(Hole x,Hole y)
{
    return x.H_size>y.H_size;

}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_SaveBtn_clicked()
{
    Myhole.H_size=ui->HoleSize->text().toInt();
    Myhole.starting_addr=ui->HoleAddress->text().toInt();
    if(Holes.empty())
    {
        if(Myhole.H_size==NULL)
        {
            QMessageBox::critical(this,"Alert","Please Enter Holes Data");

        }
        else{
        Holes.push_back(Myhole);
        QMessageBox::information(this,"Message","Saved successfully");
        }
    }
    else
    {
        if(Myhole.H_size==NULL)
        {
            QMessageBox::critical(this,"Alert","Please Enter Holes Data");

        }
        if(Myhole.starting_addr<(Holes.back()).Ending_address())
        {
            QMessageBox::critical(this,"Alert","Un acceptable starting address, Please enter a starting address more than the previous end address hole");

        }
        else{
        Holes.push_back(Myhole);
        QMessageBox::information(this,"Message","Saved successfully");
        }

    }
    ui->HoleSize->clear();
    ui->HoleAddress->clear();
}

void MainWindow::on_PsaveBtn_clicked()
{
    Myprocess.P_size=ui->ProcessSize->text().toInt();
    if(Myprocess.P_size==NULL)
    {
        QMessageBox::critical(this,"Alret","Enter the Process size");
    }
    else
    {
        P.push_back(Myprocess);
    }
    ui->ProcessSize->clear();
    ui->ProcessShow->appendPlainText("P"+QString::number(Myprocess.P_ID)+"="+QString::number(Myprocess.P_size));
    Myprocess.P_ID++;
}

void MainWindow::on_AllocationBox_activated(const QString &arg1)
{
    Printed_list=Final_List;
    QList<Process>::iterator it1;
    QList<Hole>::iterator it2;
    QList<Hole>::iterator it3;
    int x;
    if(arg1=="First fit")
    {
        for(it1=P.begin();it1!=P.end();it1++)//iterator to start at first process
           {
            for(it2=Printed_list.begin();it2!=Printed_list.end();it2++)
            {
                if((it1->P_size==it2->H_size)&&(it2->Is_Hole))
                {
                    (*it2).Is_Process=true;
                    (*it2).Is_Hole=false;
                    (*it2).Is_full=false;
                    (*it2).ID=(*it1).P_ID;
                    break;

                }
                if((it1->P_size<it2->H_size)&&(it2->Is_Hole))
                {
                    int old_size=it2->H_size;
                   (*it2).H_size=it1->P_size;
                    (*it2).ID=it1->P_ID;
                    (*it2).Is_Hole=false;
                    it2->Is_Process=true;
                    it2->Is_full=false;
                    Hole2.starting_addr=it2->Ending_address();
                    Hole2.H_size=old_size-it1->P_size;
                    Hole2.Is_Hole=true;
                    Hole2.Is_full=false;
                    Hole2.Is_Process=false;
                    ++it2;
                    Printed_list.insert(it2,Hole2);
                    break;
                }
            }
       }
    }

    if(arg1=="Best fit")
    {
        qSort(Holes.begin(),Holes.end(),small_or_not);

        for(it1=P.begin();it1!=P.end();it1++)
        {
            for(it3=Holes.begin();it3!=Holes.end();it3++)
            {
                    //cout<<it3->H_size<<endl;
                  if((it1->P_size<it3->H_size))
                  {
                      x=it3->H_size;
                      it3->H_size=it3->H_size-it1->P_size;
                      qSort(Holes.begin(),Holes.end(),small_or_not);
                      break;

                  }
                  else
                  {
                      x=0;
                  }
            }
            for(it2=Printed_list.begin();it2!=Printed_list.end();it2++)
            {
                if((it1->P_size==it2->H_size)&&(it2->Is_Hole))
                {
                    (*it2).Is_Process=true;
                    (*it2).Is_Hole=false;
                    (*it2).Is_full=false;
                    (*it2).ID=(*it1).P_ID;
                    break;

                }
                if((x==it2->H_size)&&(it2->Is_Hole)&&(x!=0))
                {
                    int old_size=it2->H_size;
                   (*it2).H_size=it1->P_size;
                    (*it2).ID=it1->P_ID;
                    (*it2).Is_Hole=false;
                    it2->Is_Process=true;
                    it2->Is_full=false;
                    Hole2.starting_addr=it2->Ending_address();
                    Hole2.H_size=old_size-it1->P_size;
                    Hole2.Is_Hole=true;
                    Hole2.Is_full=false;
                    Hole2.Is_Process=false;
                    ++it2;
                    Printed_list.insert(it2,Hole2);
                    break;

                }
        }
    }
  }
    if(arg1=="Worst fit")
    {
        qSort(Holes.begin(),Holes.end(),Big_or_not);

        for(it1=P.begin();it1!=P.end();it1++)
        {
            for(it3=Holes.begin();it3!=Holes.end();it3++)
            {
                    cout<<it3->H_size<<endl;
                  if((it1->P_size<it3->H_size))
                  {
                      x=it3->H_size;
                      it3->H_size=it3->H_size-it1->P_size;
                      qSort(Holes.begin(),Holes.end(),Big_or_not);

                      break;
                  }
                  else
                  {
                      x=0;
                  }
            }
            for(it2=Printed_list.begin();it2!=Printed_list.end();it2++)
            {
                if((it1->P_size==it2->H_size)&&(it2->Is_Hole))
                {
                    (*it2).Is_Process=true;
                    (*it2).Is_Hole=false;
                    (*it2).Is_full=false;
                    (*it2).ID=(*it1).P_ID;
                    break;

                }
                if((x==it2->H_size)&&(it2->Is_Hole)&&(x!=0))
                {
                    int old_size=it2->H_size;
                   (*it2).H_size=it1->P_size;
                    (*it2).ID=it1->P_ID;
                    (*it2).Is_Hole=false;
                    it2->Is_Process=true;
                    it2->Is_full=false;
                    Hole2.starting_addr=it2->Ending_address();
                    Hole2.H_size=old_size-it1->P_size;
                    Hole2.Is_Hole=true;
                    Hole2.Is_full=false;
                    Hole2.Is_Process=false;
                    ++it2;
                    Printed_list.insert(it2,Hole2);
                    break;
                }
        }
    }

    }

}
void MainWindow::on_FinishBtn_clicked()
{
    QList<Hole> ::iterator it;

    //after click finish  the final list will be created
    for(it=Holes.begin();it!=Holes.end();++it)
    {
        if(it==Holes.begin())
        {
            if((*it).starting_addr==0)

            {
                (*it).Is_Hole=true;
                (*it).Is_full=false;
                (*it).Is_Process=false;
                Final_List.push_back(*it);
            }
            else{
                tmpHole.starting_addr=0;
                tmpHole.H_size=(*it).starting_addr;
                tmpHole.Is_Hole=false;
                tmpHole.Is_full=true;
                tmpHole.Is_Process=false;
                Final_List.push_back(tmpHole);
                (*it).Is_Hole=true;
                (*it).Is_full=false;
                (*it).Is_Process=false;
                Final_List.push_back(*it);
            }
        }
        else{


            if((*it).starting_addr==(*(it-1)).Ending_address())
            {
                (*it).Is_Hole=true;
                (*it).Is_full=false;
                (*it).Is_Process=false;
                Final_List.push_back(*it);

            }
            else{
                tmpHole.starting_addr=(*(it-1)).Ending_address();
                tmpHole.H_size=(*it).starting_addr-(*(it-1)).Ending_address();
                tmpHole.Is_Hole=false;
                tmpHole.Is_full=true;
                tmpHole.Is_Process=false;
                Final_List.push_back(tmpHole);
                (*it).Is_Hole=true;
                (*it).Is_Process=false;
                (*it).Is_full=false;
                Final_List.push_back(*it);
            }


        }

    }
    QMessageBox::information(this,"Alert","Done");
    ui->HoleSize->clear();
    ui->HoleAddress->clear();
}
void MainWindow::on_PrintBtn_clicked()
{
    QList<Hole>::iterator it;
    for(it=Final_List.begin();it!=Final_List.end();it++)
    {
        if((*it).Is_Hole)
        {
            ui->PrintShow->appendPlainText("Starting address: "+QString::number((*it).starting_addr));
            ui->PrintShow->appendPlainText("Hole");
            ui->PrintShow->appendPlainText("End address: "+QString::number((*it).Ending_address()));
            ui->PrintShow->appendPlainText("--------------------");
        }
        if((*it).Is_full)
        {
            ui->PrintShow->appendPlainText("Starting address: "+QString::number((*it).starting_addr));
            ui->PrintShow->appendPlainText("Busy");
            ui->PrintShow->appendPlainText("End address: "+QString::number((*it).Ending_address()));
            ui->PrintShow->appendPlainText("--------------------");
        }

    }
}

void MainWindow::on_ShowBtn_clicked()
{

    QList<Hole>::iterator it;
    for(it=Printed_list.begin();it!=Printed_list.end();it++)
    {
        if((*it).Is_full)
        {
            ui->FinalMemoryPrint->appendPlainText("Starting address: "+QString::number((*it).starting_addr));
            ui->FinalMemoryPrint->appendPlainText("Busy");
            ui->FinalMemoryPrint->appendPlainText("End address: "+QString::number((*it).Ending_address()));
            ui->FinalMemoryPrint->appendPlainText("--------------------");

        }
        if((*it).Is_Hole)
        {
            ui->FinalMemoryPrint->appendPlainText("Starting address: "+QString::number((*it).starting_addr));
            ui->FinalMemoryPrint->appendPlainText("Hole");
            ui->FinalMemoryPrint->appendPlainText("End address: "+QString::number((*it).Ending_address()));
            ui->FinalMemoryPrint->appendPlainText("--------------------");

        }
        if((*it).Is_Process)
        {
            ui->FinalMemoryPrint->appendPlainText("Starting address: "+QString::number((*it).starting_addr));
            ui->FinalMemoryPrint->appendPlainText("P"+QString::number((*it).ID));
            ui->FinalMemoryPrint->appendPlainText("End address: "+QString::number((*it).Ending_address()));
            ui->FinalMemoryPrint->appendPlainText("--------------------");

        }
    }
}

void MainWindow::on_ResetBtn_clicked()
{   qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}
