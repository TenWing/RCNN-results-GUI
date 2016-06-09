#include <imageloader.h>
#include <tinyxml2.h>
#include <stdlib.h>

#include <iostream>

using namespace std;
using namespace tinyxml2;

ImageLoader::ImageLoader()
{

}

ImageLoader::~ImageLoader()
{

}

vector<Image> ImageLoader::loadImages(std::string fileName)
{
    vector<Image> images;

    XMLDocument document;
    XMLError error = document.LoadFile(fileName.c_str());

    if(error != XML_NO_ERROR)
        throw "Error opening file !";

    XMLElement* root = document.RootElement();

    XMLElement* imageElement = root->FirstChildElement();

    while(imageElement->NextSiblingElement())
    {
        string file = imageElement->FirstAttribute()->Value();
        Image image(file);

        XMLElement* objectElement = imageElement->FirstChildElement();
        while(objectElement && objectElement->NextSiblingElement())
        {
            string label = objectElement->FirstAttribute()->Value();
            double confidence = atof(objectElement->Attribute("confidence"));

            XMLElement* bboxElement = objectElement->FirstChildElement();
            double xmin = atof(bboxElement->Attribute("xmin"));
            double ymin = atof(bboxElement->Attribute("ymin"));
            double width = atof(bboxElement->Attribute("width"));
            double height = atof(bboxElement->Attribute("height"));

            Bbox bbox(xmin, ymin, width, height);
            Object object(label, confidence, bbox);

            image.addObject(object);
            objectElement = objectElement->NextSiblingElement();
        }

        images.push_back(image);
        imageElement = imageElement->NextSiblingElement();
    }

    return images;
}
