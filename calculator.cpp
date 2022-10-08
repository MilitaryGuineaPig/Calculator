#include "calculator.h"
#include "./ui_calculator.h"

double firstNum,secondNum;
double resNum=0;
bool a = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    connect(ui->btt0,SIGNAL(released()),this,SLOT(ZeroPressed()));

    connect(ui->btt1,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt2,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt3,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt4,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt5,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt6,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt7,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt8,SIGNAL(released()),this,SLOT(NumPressed()));
    connect(ui->btt9,SIGNAL(released()),this,SLOT(NumPressed()));

    connect(ui->ChangeSign,SIGNAL(released()),this,SLOT(ChangeSignPressed()));
    connect(ui->Perc,SIGNAL(released()),this,SLOT(ChangeSignPressed()));

    connect(ui->Clear,SIGNAL(released()),this,SLOT(on_Clear_released()));

    connect(ui->Add,SIGNAL(released()),this,SLOT(operations()));
    connect(ui->Divide,SIGNAL(released()),this,SLOT(operations()));
    connect(ui->Multiply,SIGNAL(released()),this,SLOT(operations()));
    connect(ui->Subtrat,SIGNAL(released()),this,SLOT(operations()));

    connect(ui->Equals,SIGNAL(released()),this,SLOT(on_Equals_released()));
    //ui->Add->setCheckable(true);
    //ui->Divide->setCheckable(true);
    //ui->Multiply->setCheckable(true);
    //ui->Subtrat->setCheckable(true);
}
Calculator::~Calculator(){
    delete ui;
}
void Calculator::ZeroPressed(){
    QString newVal;
    QString check = ui->Display->text();
    bool checkL = true;
    bool checkI = true;
    if (a){
        ui->Display->setText("");
        a = false;
    }
        if (ui->Display->text() == "0"){}
        else if (check.endsWith(QChar('.'))){

                newVal = ui->Display->text() + "0" ;
                ui->Display->setText(newVal);
                ui->Clear->setText("C");
                checkL = false;
        }
        else if (check.contains(QChar('.')) && checkL  ){
            newVal = ui->Display->text() + "0" ;
            ui->Display->setText(newVal);
            ui->Clear->setText("C");
            checkL = true;
            checkI = false;
        }
        else if (ui->Display->text() != "0" && checkI){
            newVal = ui->Display->text() + "0" ;
            ui->Display->setText(newVal);
            ui->Clear->setText("C");
            checkI = true;
        }
}
void Calculator::NumPressed(){
    if (a){
        ui->Display->setText("");
        a = false;
    }
    QPushButton *button = (QPushButton *)sender();
    double calcVal ;
    QString newVal;
    calcVal = (ui->Display->text() + button->text()).toDouble();
    newVal = QString::number(calcVal,'g',15);
    ui->Display->setText(newVal);
    ui->Clear->setText("C");
}
void Calculator::on_dot_released(){
    QString check = ui->Display->text();
    if ( check.contains(QChar('.'))){
    }
    else {
        ui->Display->setText(ui->Display->text() + tr("."));
        ui->Clear->setText("C");
    }
}
void Calculator::ChangeSignPressed(){
    QPushButton *button = (QPushButton *)sender();
    double calcVal;
    QString newVal;
    QString check = ui->Display->text();
    if (button->text() == "+/-"){
        if (ui->Display->text().toDouble() != 0){
            calcVal = ui->Display->text().toDouble();
            calcVal = calcVal * -1;
            newVal = QString::number(calcVal,'g',15);
            ui->Display->setText(newVal);
        }
        else if (ui->Display->text().toDouble() == 0 && !check.contains(QChar('-')) ){
            QString zeroVal = "-" + ui->Display->text();
            ui->Display->setText(zeroVal);
        }
        else if (check.contains(QChar('-'))){
            check.remove(0,1);
            ui->Display->setText(check);
        }
    }
    if (button->text() == "%"){
        calcVal = ui->Display->text().toDouble();
        calcVal = calcVal * 0.01;
        newVal = QString::number(calcVal,'g',15);
        ui->Display->setText(newVal);
    }
}
void Calculator::on_Clear_released(){
    QPushButton *button = (QPushButton *)sender();
    double calcVal=0;
    QString newVal;
    if (button->text() == "C"){
        ui->Display->setText(QString::number(calcVal));
        button->setText("AC");
    }
    if (button->text() == "AC"){
        calcVal = ui->Display->text().toDouble();
        calcVal = 0;
        newVal = QString::number(calcVal,'g',15);
        ui->Display->setText(QString::number(calcVal));
    }
}

void Calculator::on_Equals_released(){
    double calcVal;
    QString newNum;
    secondNum = ui->Display->text().toDouble();

    if (ui->Add->isChecked()){
        calcVal = firstNum + secondNum;
        newNum = QString::number(calcVal,'g',15);
        ui->Display->setText(newNum);
        ui->Add->setChecked(false);
    }
    else if (ui->Divide->isChecked()){
        calcVal = firstNum / secondNum;
        newNum = QString::number(calcVal,'g',15);
        ui->Display->setText(newNum);
        ui->Divide->setChecked(false);
    }
    else if (ui->Multiply->isChecked()){
        calcVal = firstNum * secondNum;
        newNum = QString::number(calcVal,'g',15);
        ui->Display->setText(newNum);
        ui->Multiply->setChecked(false);
    }
    else if (ui->Subtrat->isChecked()){
        calcVal = firstNum - secondNum;
        newNum = QString::number(calcVal,'g',15);
        ui->Display->setText(newNum);
        ui->Subtrat->setChecked(false);
    }
}

void Calculator::operations(){
    QPushButton *button = (QPushButton *)sender();
    firstNum = ui->Display->text().toDouble();

    button->setChecked(true);

    a = true;
}
