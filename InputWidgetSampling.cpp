// Written: fmckenna

#include "InputWidgetSampling.h"
#include <DakotaResultsSampling.h>

#include <QPushButton>
#include <QScrollArea>
#include <QJsonArray>
#include <QJsonObject>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QPushButton>
#include <sectiontitle.h>
#include <InputWidgetEDP.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>


InputWidgetSampling::InputWidgetSampling(QWidget *parent)
    : SimCenterWidget(parent),uqSpecific(0)
{
    layout = new QVBoxLayout();

    QVBoxLayout *methodLayout= new QVBoxLayout;
    QLabel *label1 = new QLabel();
    label1->setText(QString("Method"));
    samplingMethod = new QComboBox();
    samplingMethod->addItem(tr("LHS"));
    samplingMethod->addItem(tr("Monte Carlo"));
    
    methodLayout->addWidget(label1);
    methodLayout->addWidget(samplingMethod);
    
    QVBoxLayout *samplesLayout= new QVBoxLayout;
    QLabel *label2 = new QLabel();
    label2->setText(QString("# Samples"));
    numSamples = new QLineEdit();
    numSamples->setText(tr("10"));
    numSamples->setMaximumWidth(100);
    numSamples->setMinimumWidth(100);

    
    samplesLayout->addWidget(label2);
    samplesLayout->addWidget(numSamples);
    
    QVBoxLayout *seedLayout= new QVBoxLayout;
    QLabel *label3 = new QLabel();
    label3->setText(QString("Seed"));
    srand(time(NULL));
    int randomNumber = rand() % 1000 + 1;

    randomSeed = new QLineEdit();
    randomSeed->setText(QString::number(randomNumber));
    randomSeed->setMaximumWidth(100);
    randomSeed->setMinimumWidth(100);
    
    seedLayout->addWidget(label3);
    seedLayout->addWidget(randomSeed);
    
    QHBoxLayout *mLayout = new QHBoxLayout();
    mLayout->addLayout(methodLayout);
    mLayout->addLayout(samplesLayout);
    mLayout->addLayout(seedLayout);
    mLayout->addStretch();

    layout->addLayout(mLayout);

    theEdpWidget = new InputWidgetEDP();
    layout->addWidget(theEdpWidget,1);

    this->setLayout(layout);
}

InputWidgetSampling::~InputWidgetSampling()
{

}


void InputWidgetSampling::clear(void)
{

}



void
InputWidgetSampling::outputToJSON(QJsonObject &jsonObject)
{
    QJsonObject uq;
    uq["method"]=samplingMethod->currentText();
    uq["samples"]=numSamples->text().toInt();
    uq["seed"]=randomSeed->text().toDouble();
    theEdpWidget->outputToJSON(uq);
    jsonObject["samplingMethodData"]=uq;
}


void
InputWidgetSampling::inputFromJSON(QJsonObject &jsonObject)
{
    this->clear();

    QJsonObject uq = jsonObject["samplingMethodData"].toObject();
    QString method =uq["method"].toString();
    int samples=uq["samples"].toInt();
    double seed=uq["seed"].toDouble();

    numSamples->setText(QString::number(samples));
    randomSeed->setText(QString::number(seed));
    int index = samplingMethod->findText(method);
    samplingMethod->setCurrentIndex(index);

    theEdpWidget->inputFromJSON(uq);
}

void InputWidgetSampling::uqSelectionChanged(const QString &arg1)
{

}

int InputWidgetSampling::processResults(QString &filenameResults, QString &filenameTab) {

    return 0;
}

DakotaResults *
InputWidgetSampling::getResults(void) {
    return new DakotaResultsSampling();
}