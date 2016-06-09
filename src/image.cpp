#include <image.h>
#include <sstream>

using namespace std;

Bbox::Bbox(double xmin, double ymin, double width, double height) :
    _xmin(xmin), _ymin(ymin), _width(width), _height(height)
{

}

Bbox::~Bbox()
{

}

vector<double> Bbox::getBox()
{
    vector<double> coords;
    coords.push_back(_xmin);
    coords.push_back(_ymin);
    coords.push_back(_width);
    coords.push_back(_height);

    return coords;
}

Object::Object(string label, double confidence, Bbox bbox) :
    _label(label), _confidence(confidence), _bbox(bbox)
{

}

Object::~Object()
{

}

Bbox Object::getBbox()
{
    return _bbox;
}

string Object::getLabel()
{
    return _label;
}

double Object::getConfidence()
{
    return _confidence;
}

Image::Image(string fileName) :
    _objects(),_fileName(fileName)
{

}

Image::~Image()
{

}

void Image::addObject(Object object)
{
    _objects.push_back(object);
}

string Image::getFileName()
{
    return _fileName;
}

vector<Object> Image::getObjects()
{
    return _objects;
}
