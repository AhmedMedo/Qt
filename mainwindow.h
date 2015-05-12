#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QList>

struct Hole
{
    int H_size;
    int starting_addr;
    int Ending_address()
    {
        return H_size+starting_addr;

    }
    bool Is_Hole;//to check in the list if the empty place is a hole or not
    bool Is_Process;//to declare a process in the printed list
    bool Is_full;
    int ID;

};
struct Process
{   int P_size;
    int P_ID;
};
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:

    void on_SaveBtn_clicked();
    void on_PsaveBtn_clicked();
    void on_AllocationBox_activated(const QString &arg1);
    void on_FinishBtn_clicked();
    void on_PrintBtn_clicked();
    void on_ShowBtn_clicked();
    void on_ResetBtn_clicked();

private:
    Ui::MainWindow *ui;
    QList<Hole> Holes;// list of holes only
    QList<Process> P;// list of process
    QList<Hole> Final_List;//for the memory befor allocation including holes and Busy locations
    QList<Hole> Printed_list;//for the memory after allocation

};

#endif // MAINWINDOW_H
