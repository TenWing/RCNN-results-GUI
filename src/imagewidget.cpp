#include <imagewidget.h>

#include <QPainter>

#include <iostream>

using namespace std;

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent), _results(nullptr), _index(0), _threshold(0), _modelNames(),
    _image(), _displayer(new QLabel(this)), _layout(new QVBoxLayout()), _fileName(new QLabel(this))
{
    setMinimumSize(500,400);
    setLayout(_layout);
    _layout->addWidget(_fileName);
    _layout->addWidget(_displayer);
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::setResults(Results *results)
{
    _results = results;
}

void ImageWidget::loadImage(unsigned int i)
{
    _index = i;
    QString fileName = QString::fromStdString(_results->datasetLocation()) + "/" + QString::fromStdString(_results->resultSet(i).getFileName());
    _fileName->setText(QString::fromStdString(_results->resultSet(i).getFileName()));
    _image = QImage(fileName);

    if(_image.isNull())
        throw "Error while opening Picture\nMaybe you did not choose the right folder";

    QImage scaled = _image.scaled(500,400,Qt::KeepAspectRatio);
    _displayer->setPixmap(QPixmap::fromImage(scaled));
    paintBbox();
}

void ImageWidget::paintBbox()
{
    QImage drawn(_image);
    QPainter p(&drawn);
    QFont font = p.font();
    font.setPointSize(72);
    font.setBold(true);
    p.setFont(font);

    for(map<string, QColor>::iterator it = _modelNames.begin(); it != _modelNames.end(); it++)
    {
        string model = it->first;
        QColor color = it->second;
        QPen paintpen(color);
        paintpen.setWidth(10);
        p.setPen(paintpen);
        ResultSet set = _results->resultSet(_index);
        vector<Object> objects = set.objects(model);
        for(unsigned int j = 0; j < objects.size(); j++)
        {
            Object object = objects[j];
            if(object.getConfidence() > _threshold)
            {
                vector<double> coords = object.getBbox().getBox();
                p.drawLine(coords[0], coords[1], coords[0] + coords[2], coords[1]);
                p.drawLine(coords[0] + coords[2], coords[1], coords[0] + coords[2], coords[1] + coords[3]);
                p.drawLine(coords[0] + coords[2], coords[1] + coords[3], coords[0], coords[1] + coords[3]);
                p.drawLine(coords[0], coords[1] + coords[3], coords[0], coords[1]);
                p.drawText(coords[0] + 10, coords[1] + 75, QString::fromStdString(object.getLabel()));
            }
        }
    }

    QImage scaled = drawn.scaled(500,400,Qt::KeepAspectRatio);
    _displayer->setPixmap(QPixmap::fromImage(scaled));
}

void ImageWidget::setModelNames(std::map<string, QColor> modelNames)
{
    _modelNames = modelNames;
}

void ImageWidget::eraseBbox()
{
    _modelNames.clear();
    QImage scaled = _image.scaled(500,400,Qt::KeepAspectRatio);
    _displayer->setPixmap(QPixmap::fromImage(scaled));
}

void ImageWidget::setThreshold(double threshold)
{
    _threshold = threshold;
}
