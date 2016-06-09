#include <resultset.h>

#include <iostream>

using namespace std;

ResultSet::ResultSet(std::string fileName) :
    _fileName(fileName), _results()
{

}

ResultSet::~ResultSet()
{

}

void ResultSet::addResults(string modelName, std::vector<Object> results)
{
    _results[modelName] = results;
}

std::vector<Object> ResultSet::objects(string modelName) const
{
    return _results.at(modelName);
}

std::vector<string> ResultSet::modelNames() const
{
    vector<string> collection;
    for(map<string, vector<Object>>::const_iterator it = _results.begin(); it != _results.end(); it++)
        collection.push_back(it->first);

    return collection;
}

string ResultSet::getFileName() const
{
    return _fileName;
}

Results::Results(string dataset) :
    _dataset(dataset), _resultsets(), _location()
{

}

Results::~Results()
{

}

int Results::addResults(string name, std::vector<Image> images)
{
    if(!_resultsets.empty())
    {
        if(images.size() != _resultsets.size())
            return 1; // Different dataset due to size

        for(unsigned int i = 0; i < images.size(); i++)
        {
            if(images[i].getFileName() != _resultsets[i].getFileName())
                return 2; // Different dataset due to different files
        }

        for(unsigned int i = 0; i < images.size(); i++)
        {
            _resultsets[i].addResults(name, images[i].getObjects());
        }
    }
    else
    {
        for(unsigned int i = 0; i < images.size(); i++)
        {
            ResultSet resultset(images[i].getFileName());
            resultset.addResults(name, images[i].getObjects());
            _resultsets.push_back(resultset);
        }
    }

    return 0;
}

unsigned int Results::resultsSize()
{
    return (unsigned int) _resultsets.size();
}

const ResultSet &Results::resultSet(unsigned int i)
{
    return _resultsets[i];
}

void Results::setLocation(string location)
{
    _location = location;
}

string Results::datasetLocation()
{
    return _location;
}
