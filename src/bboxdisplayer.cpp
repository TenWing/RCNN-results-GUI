#include <bboxdisplayer.h>

#include <iostream>
#include <QHBoxLayout>
#include <QPalette>

using namespace std;

BboxDisplayer::BboxDisplayer(QWidget *parent, ImageWidget* imageWidget) :
    QWidget(parent), _checkBoxes(), _layout(new QVBoxLayout()), _imageWidget(imageWidget)
{
    setLayout(_layout);
}

BboxDisplayer::~BboxDisplayer()
{

}

void BboxDisplayer::addCheckBox(std::string model)
{
    QCheckBox* checkBox = new QCheckBox(QString::fromStdString(model), this);

    QPalette p = checkBox->palette();
    if(_checkBoxes.size() == 0)
        p.setColor(QPalette::Active, QPalette::WindowText, Qt::red);
    else if(_checkBoxes.size() == 1)
        p.setColor(QPalette::Active, QPalette::WindowText, Qt::blue);
    else
        p.setColor(QPalette::Active, QPalette::WindowText, Qt::green);

    checkBox->setPalette(p);

    _layout->addWidget(checkBox);
    _checkBoxes.push_back(checkBox);

    connect(checkBox, SIGNAL(clicked(bool)), this, SLOT(drawBboxes()));
}

void BboxDisplayer::clear()
{
    for(unsigned int i = 0; i < _checkBoxes.size(); i++)
    {
        QCheckBox* checkBox = _checkBoxes[i];
        _layout->removeWidget(checkBox);
        delete checkBox;
    }

    _checkBoxes.clear();
}

void BboxDisplayer::drawBboxes()
{
    map<string, QColor> modelNames;
    for(unsigned int i = 0; i < _checkBoxes.size(); i++)
    {
        QCheckBox* checkBox = _checkBoxes[i];
        if(checkBox->isChecked())
        {
            modelNames[checkBox->text().toStdString()] = checkBox->palette().color(QPalette::WindowText);
        }
    }

    if(modelNames.size() != 0)
    {
        _imageWidget->setModelNames(modelNames);
        _imageWidget->paintBbox();
    }
    else
        _imageWidget->eraseBbox();
}
