// Written: fmckenna

/* *****************************************************************************
Copyright (c) 2016-2017, The Regents of the University of California (Regents).
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those
of the authors and should not be interpreted as representing official policies,
either expressed or implied, of the FreeBSD Project.

REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS 
PROVIDED "AS IS". REGENTS HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, 
UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

*************************************************************************** */

// Written: Michael Gardner

#include "UQ_JsonEngine.h"

#include <QComboBox>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>

#include <QDebug>

UQ_JsonEngine::UQ_JsonEngine(QWidget *parent)
: UQ_Engine(parent)
{

    QVBoxLayout *layout = new QVBoxLayout();

    //
    // the selection part
    //
    theRandomVariables = new RandomVariablesContainer();
    theJsonConfigureWidget = new JsonConfiguredWidget( theRandomVariables );
    layout->addWidget(theJsonConfigureWidget);
    layout->addStretch();
    this->setLayout(layout);
}

UQ_JsonEngine::~UQ_JsonEngine()
{}

int
UQ_JsonEngine::getMaxNumParallelTasks(void) {
  return 1;
    // return theCurrentEngine->getMaxNumParallelTasks();
}

bool
UQ_JsonEngine::outputToJSON(QJsonObject &rvObject) {
  return theJsonConfigureWidget->outputToJSON(rvObject);
}

bool
UQ_JsonEngine::inputFromJSON(QJsonObject &rvObject) {
  return theJsonConfigureWidget->inputFromJSON(rvObject);
}

int
UQ_JsonEngine::processResults(QString &filenameResults, QString &filenameTab) {
  return 0;
}

RandomVariablesContainer *
UQ_JsonEngine::getParameters() {
  return theRandomVariables;
}

UQ_Results *
UQ_JsonEngine::getResults(void) {
  return new UQ_Results();
    // return theCurrentEngine->getResults();
}

QString
UQ_JsonEngine::getProcessingScript() {
    // return QString("parseDAKOTA.py");
  return QString("doesNotExist.py");
}