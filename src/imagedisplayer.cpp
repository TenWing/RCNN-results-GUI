#include <imagedisplayer.h>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QLineEdit>
#include <QMessageBox>

#include <iostream>
#include <vector>

using namespace std;

ImageDisplayer::ImageDisplayer(QWidget *parent) :
    QWidget(parent), _results(nullptr), _imageWidget(new ImageWidget(this)),
    _bboxDisplayer(new BboxDisplayer(this, _imageWidget)), _current(0),
    _fileIndexCurrent(new QLabel("1", this)),
    _fileIndexTotal(new QLabel("1", this)), _nextButton(new QPushButton(">", this)),
    _prevButton(new QPushButton("<", this)), _sliderValue(new QLabel("0", this)),
    _slider(new QSlider(Qt::Horizontal ,this)),
    _goTo(new QPushButton("Go to file", this)), _fileChoose(new QLineEdit(this)),
    _locked(false)
{
    QHBoxLayout* mainLayout = new QHBoxLayout();
    setLayout(mainLayout);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    QWidget* rightWidget = new QWidget(this);
    rightWidget->setLayout(rightLayout);

    QLabel* boxOptions = new QLabel("Display Bboxes", this);

    _slider->setRange(0,100);
    QWidget* sliderWidget = new QWidget(this);
    QHBoxLayout* sliderLayout = new QHBoxLayout();
    QLabel* sliderInfo = new QLabel("Threshold of confidence", this);
    sliderWidget->setLayout(sliderLayout);
    sliderLayout->addWidget(_slider);
    sliderLayout->addWidget(_sliderValue);
    connect(_slider, SIGNAL(sliderMoved(int)), this, SLOT(updateSliderValue(int)));

    QWidget* fileIndex = new QWidget(this);
    QHBoxLayout* fileIndexLayout = new QHBoxLayout();
    fileIndex->setLayout(fileIndexLayout);
    QLabel* fileIndexLabel = new QLabel("File ", this);
    QLabel* fileIndexSlash = new QLabel("/", this);
    fileIndexLayout->addWidget(fileIndexLabel);
    fileIndexLayout->addWidget(_fileIndexCurrent);
    fileIndexLayout->addWidget(fileIndexSlash);
    fileIndexLayout->addWidget(_fileIndexTotal);

    QWidget* goToWidget = new QWidget();
    QHBoxLayout* goToLayout = new QHBoxLayout();
    goToWidget->setLayout(goToLayout);
    goToLayout->addWidget(_goTo);
    goToLayout->addWidget(_fileChoose);
    connect(_goTo, SIGNAL(clicked(bool)), this, SLOT(goToFile()));

    _goTo->setEnabled(false);
    _prevButton->setEnabled(false);
    _nextButton->setEnabled(false);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QWidget* buttons = new QWidget(this);
    buttons->setLayout(buttonsLayout);
    buttonsLayout->addWidget(_prevButton);
    buttonsLayout->addWidget(_nextButton);
    connect(_nextButton, SIGNAL(clicked(bool)), this, SLOT(nextImage()));
    connect(_prevButton, SIGNAL(clicked(bool)), this, SLOT(prevImage()));

    rightLayout->addWidget(boxOptions);
    rightLayout->addWidget(_bboxDisplayer);
    rightLayout->setAlignment(boxOptions, Qt::AlignHCenter);
    rightLayout->addWidget(sliderInfo);
    rightLayout->addWidget(sliderWidget);
    rightLayout->setAlignment(sliderInfo, Qt::AlignHCenter);
    rightLayout->addWidget(fileIndex);
    rightLayout->addWidget(goToWidget);
    rightLayout->addWidget(buttons);

    mainLayout->addWidget(_imageWidget);
    mainLayout->addWidget(rightWidget);

    lock();
}

ImageDisplayer::~ImageDisplayer()
{

}

void ImageDisplayer::setResults(Results *results)
{
    _results = results;
    _imageWidget->setResults(results);
}

void ImageDisplayer::fetchImages()
{
    _nextButton->setEnabled(true);
    _prevButton->setEnabled(true);
    _goTo->setEnabled(true);

    _fileIndexTotal->setText(QString::number(_results->resultsSize()));

    fetchBbox();

    changeImage();
}

void ImageDisplayer::nextImage()
{
    _current++;
    if(_current >= _results->resultsSize())
        _current = 0;

    changeImage();
}

void ImageDisplayer::prevImage()
{
    if(_current == 0)
        _current = _results->resultsSize();

    _current--;

    changeImage();
}

void ImageDisplayer::updateSliderValue(int intValue)
{
    double value = (double)intValue / 100.0;
    _sliderValue->setText(QString::number(value));
    _imageWidget->setThreshold(value);
    _imageWidget->paintBbox();
}

void ImageDisplayer::goToFile()
{
   QString text = _fileChoose->text();
   unsigned int value = text.toUInt();
   if(value >= 1 && value <= _results->resultsSize())
   {
       _current = value-1;
       changeImage();
   }
}

void ImageDisplayer::changeImage()
{
    _fileIndexCurrent->setText(QString::number(_current+1));
    try
    {
        _imageWidget->loadImage(_current);
        if(_locked)
            unlock();
    }
    catch(const char* error)
    {
        QMessageBox box(this);
        box.setWindowTitle("Error happened");
        box.setText(error);
        box.exec();
        lock();
    }
}

void ImageDisplayer::lock()
{
    _locked = true;
    _slider->setEnabled(false);
    _bboxDisplayer->clear();
    _imageWidget->eraseBbox();
}

void ImageDisplayer::unlock()
{
    _locked = false;
    _slider->setEnabled(true);

    fetchBbox();
}

void ImageDisplayer::fetchBbox()
{
    _bboxDisplayer->clear();
    vector<string> modelNames = _results->resultSet(0).modelNames();
    for(unsigned int i = 0; i < modelNames.size(); i++)
        _bboxDisplayer->addCheckBox(modelNames[i]);
}

//C:\Users\TenWing\Documents\Kingston\XML\XML_output\natalia_imagenet.xml
//C:\Users\TenWing\Documents\Kingston\XML\XML_output\natalia_mscoco.xml
