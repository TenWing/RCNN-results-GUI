#include <mainwindow.h>
#include <resultsadder.h>
#include <imagedisplayer.h>
#include <iostream>

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSpacerItem>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _results(nullptr),
      _imageDisplayer(new ImageDisplayer(this)), _resultsAdder(new ResultsAdder(_imageDisplayer, this)),
      _validateDataset(new QPushButton("Validate", this)), _datasetName(new QLineEdit(this)),
      _browseFolder(new QPushButton("Browse folder location of the dataset", this)),
      _folder(new QLabel("No folder selected", this))
{
    setGeometry(100,100,800,600);
    setCentralWidget(new QWidget(this));

    QVBoxLayout* mainLayout = new QVBoxLayout();
    centralWidget()->setLayout(mainLayout);

    QWidget* topWidget = new QWidget();
    QWidget* leftWidget = new QWidget();
    QWidget* datasetWidget = new QWidget();
    QHBoxLayout* datasetNameLayout = new QHBoxLayout();
    QHBoxLayout* topLayout = new QHBoxLayout();
    QVBoxLayout* datasetLayout = new QVBoxLayout();
    QLabel* datasetTitle = new QLabel("Dataset Information", this);
    QLabel* datasetLabel = new QLabel("Name :",this);
    _validateDataset->setEnabled(false);
    _browseFolder->setEnabled(false);
    connect(_browseFolder, SIGNAL(clicked(bool)), this, SLOT(searchFolder()));

    leftWidget->setLayout(datasetLayout);
    datasetLayout->addWidget(datasetTitle);
    datasetLayout->setAlignment(datasetTitle, Qt::AlignHCenter);
    datasetLayout->addWidget(datasetWidget);
    datasetLayout->addWidget(_browseFolder);
    datasetLayout->addWidget(_folder);
    datasetLayout->setAlignment(_folder, Qt::AlignHCenter);

    datasetWidget->setLayout(datasetNameLayout);
    datasetNameLayout->addWidget(datasetLabel);
    datasetNameLayout->addWidget(_datasetName);
    datasetNameLayout->addWidget(_validateDataset);

    topLayout->addWidget(leftWidget);
    topLayout->addSpacerItem(new QSpacerItem(100,0));
    topLayout->addWidget(_resultsAdder);
    topWidget->setLayout(topLayout);

    mainLayout->addWidget(topWidget);
    mainLayout->addWidget(_imageDisplayer);

    connect(_datasetName, SIGNAL(textChanged(QString)), this, SLOT(validateEnabler(QString)));
    connect(_validateDataset, SIGNAL(clicked(bool)), this, SLOT(lockValidation()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::validateEnabler(QString data)
{
    if(data.size())
        _validateDataset->setEnabled(true);
    else
        _validateDataset->setEnabled(false);
}

void MainWindow::lockValidation()
{
    _browseFolder->setEnabled(true);
    _validateDataset->setEnabled(false);
    _datasetName->setEnabled(false);
    _results = new Results(_datasetName->text().toStdString());
    _resultsAdder->setResults(_results);
    _imageDisplayer->setResults(_results);
    _resultsAdder->unlock();
}

void MainWindow::searchFolder()
{
    QString directory =
            QFileDialog::getExistingDirectory(this,
                                              tr("Open Directory"),"",
                                              QFileDialog::ShowDirsOnly |
                                              QFileDialog::DontResolveSymlinks);

    if(directory.size() != 0)
    {
        _results->setLocation(directory.toStdString());
        QStringList list = directory.split("/");
        _folder->setText("[...]/"+list.value(list.length()-1));
    }
}
