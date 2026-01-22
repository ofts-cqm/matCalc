#include "evaluationpage.h"
#include "calculatorPage/ui_evaluationpage.h"
#include <QtGui/qevent.h>
#include "calculatorlineedit.h"
#include "../calc/calculator.h"

static QString operatorMap[26];

EvaluationPage::EvaluationPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EvaluationPage)
{
    QWidget *mainWidget = new QWidget(this);
    this->setFixedSize(336, 500);
    ui->setupUi(mainWidget);
    instance = this;

    this->input = new CalculatorLineEdit();
    ui->EditFrame->setLayout(new QVBoxLayout());
    ui->EditFrame->layout()->addWidget(input);

    operatorMap['A' - 'A'] = "+";
    operatorMap['S' - 'A'] = "-";
    operatorMap['M' - 'A'] = "*";
    operatorMap['D' - 'A'] = "/";
    operatorMap['X' - 'A'] = "^";
    operatorMap['N' - 'A'] = "-";
    operatorMap['L' - 'A'] = "(";
    operatorMap['R' - 'A'] = ")";
    operatorMap['E' - 'A'] = "e^";

    connect(ui->N0, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N1, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N2, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N3, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N4, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N5, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N6, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N7, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N8, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->N9, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->NANS, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->NE, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Nabs, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Narccos, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Narcsin, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Narctan, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Ncos, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Nsin, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Ntan, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Ncosh, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Nsinh, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Ntanh, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Nlog, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->Nln, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OA, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OS, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OM, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OD, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OX, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->ON, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OL, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OR, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->OE, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->SC, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->SD, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
    connect(ui->SE, &QPushButton::clicked, this, &EvaluationPage::onButtonPressed);
}

void EvaluationPage::onButtonPressed(){
    QString command = sender()->objectName();
    if (command[0] == 'N') input->appendInput(command.last(command.size() - 1));
    else if (command[0] == 'O') input->appendInput(operatorMap[command[1].toLatin1() - 'A']);
    else if (command == "SC") input->clearInput();
    else if (command == "SE") input->evaluate();
    else if (command == "SD"){
        if (Calculator::radianMode){
            Calculator::radianMode = false;
            ui->SD->setText("DEG");
        }else{
            Calculator::radianMode = true;
            ui->SD->setText("RAD");
        }
    }
}

void EvaluationPage::restore(const QString &history){
    instance->input->setPlainText(history);
}

void EvaluationPage::closeEvent(QCloseEvent *event) {
    event->ignore();
    this->hide();
}

EvaluationPage::~EvaluationPage()
{
    delete ui;
}

EvaluationPage *EvaluationPage::instance = nullptr;
