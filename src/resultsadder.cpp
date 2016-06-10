#include <resultsadder.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <iostream>
#include <vector>

#include <QMessageBox>
#include <QFileDialog>

using namespace std;

ResultsAdder::ResultsAdder(ImageDisplayer* displayer, QWidget *parent) :
    QWidget(parent), _loader(), _results(nullptr), _xmlFile(), _displayer(displayer),
    _modelName(new QLineEdit(this)),
    _xmlFileBrowser(new QPushButton(" Browse XML file ", this)),
    _xmlLabel(new QLabel("No file selected", this)),
    _addResultsButton(new QPushButton("Add results",this))
{
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* middleLayout = new QHBoxLayout();
    QWidget* middleWidget = new QWidget(this);
    middleWidget->setLayout(middleLayout);
    QLabel* title = new QLabel("Adding detection results to dataset", this);
    QLabel* modelLabel = new QLabel("Model name :", this);
    _modelName->setEnabled(false);
    _xmlFileBrowser->setEnabled(false);
    _addResultsButton->setEnabled(false);

    middleLayout->addWidget(modelLabel);
    middleLayout->addWidget(_modelName);
    middleLayout->addSpacerItem(new QSpacerItem(25,1));
    middleLayout->addWidget(_xmlFileBrowser);
    middleLayout->addWidget(_xmlLabel);

    mainLayout->addWidget(title);
    mainLayout->setAlignment(title, Qt::AlignHCenter);
    mainLayout->addWidget(middleWidget);
    mainLayout->addWidget(_addResultsButton);

    setLayout(mainLayout);

    connect(_modelName, SIGNAL(textChanged(QString)), this, SLOT(unlockValidate()));
    connect(_xmlFileBrowser, SIGNAL(clicked(bool)), this, SLOT(searchXML()));
    connect(_addResultsButton, SIGNAL(clicked(bool)), this, SLOT(loadXML()));
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
    _xmlFileBrowser->setEnabled(true);
}

void ResultsAdder::unlockValidate()
{
    if(_modelName->text().size() != 0)
        _addResultsButton->setEnabled(true);
    else
        _addResultsButton->setEnabled(false);
}

void ResultsAdder::loadXML()
{
    if(_xmlFile.size() == 0)
    {
        QMessageBox box(this);
        box.setText("You have to choose a XML file !");
        box.setWindowTitle("Error happened");
        box.exec();

        return;
    }

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
        images = _loader.loadImages(_xmlFile.toStdString());
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

void ResultsAdder::searchXML()
{
    _xmlFile = QFileDialog::getOpenFileName(this,
                                            tr("Open XML results"),
                                            "",
                                            tr("XML Files (*.xml)"));
    QStringList list = _xmlFile.split("/");
    _xmlLabel->setText(list.value(list.length()-1));
}
