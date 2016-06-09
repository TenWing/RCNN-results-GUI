#include <resultsadder.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <iostream>
#include <vector>

#include <QMessageBox>

using namespace std;

ResultsAdder::ResultsAdder(ImageDisplayer* displayer, QWidget *parent) :
    QWidget(parent), _loader(), _results(nullptr), _displayer(displayer),
    _modelName(new QLineEdit(this)),
    _xmlFile(new QLineEdit(this)), _addResultsButton(new QPushButton("Add results",this))
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* middleLayout = new QHBoxLayout();
    QWidget* middleWidget = new QWidget(this);
    middleWidget->setLayout(middleLayout);
    QLabel* title = new QLabel("Adding detection results to dataset", this);
    QLabel* modelLabel = new QLabel("Model name :", this);
    _modelName->setEnabled(false);
    QLabel* xmlLabel = new QLabel("Results XML :", this);
    _xmlFile->setEnabled(false);
    _addResultsButton->setEnabled(false);

    middleLayout->addWidget(modelLabel);
    middleLayout->addWidget(_modelName);
    middleLayout->addSpacerItem(new QSpacerItem(25,1));
    middleLayout->addWidget(xmlLabel);
    middleLayout->addWidget(_xmlFile);

    mainLayout->addWidget(title);
    mainLayout->setAlignment(title, Qt::AlignHCenter);
    mainLayout->addWidget(middleWidget);
    mainLayout->addWidget(_addResultsButton);

    setLayout(mainLayout);

    connect(_modelName, SIGNAL(textChanged(QString)), this, SLOT(unlockValidate()));
    connect(_xmlFile, SIGNAL(textChanged(QString)), this, SLOT(unlockValidate()));
    connect(_addResultsButton, SIGNAL(clicked(bool)), this, SLOT(loadXML()));

    //TEST VALUES
    _xmlFile->setText("C:/Users/TenWing/Documents/Kingston/XML/XML_output/natalia_imagenet.xml");
}

ResultsAdder::~ResultsAdder()
{

}

void ResultsAdder::setResults(Results *results)
{
    _results = results;
}

void ResultsAdder::unlock()
{
    _modelName->setEnabled(true);
    _xmlFile->setEnabled(true);
}

void ResultsAdder::unlockValidate()
{
    if(_modelName->text().size() != 0 && _xmlFile->text().size() != 0)
        _addResultsButton->setEnabled(true);
    else
        _addResultsButton->setEnabled(false);
}

void ResultsAdder::loadXML()
{
    vector<Image> images;

    if(_results->resultsSize() != 0)
    {
        vector<string> models = _results->resultSet(0).modelNames();
        for(unsigned int i = 0; i < models.size(); i++)
        {
            if(_modelName->text().toStdString() == models[i])
            {
                QMessageBox box(this);
                box.setText("You already added results of detection for this model");
                box.setWindowTitle("Error happened");
                box.exec();
                return;
            }
        }
    }

    try
    {
        images = _loader.loadImages(_xmlFile->text().toStdString());
        _results->addResults(_modelName->text().toStdString(), images);
        _displayer->fetchImages();
    }
    catch(const char* error)
    {
        QMessageBox box(this);
        box.setText(QString::fromStdString(error));
        box.setWindowTitle("Error happened");
        box.exec();
    }
}
