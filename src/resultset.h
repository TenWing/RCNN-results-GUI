#ifndef RESULTSET_H
#define RESULTSET_H

#include <image.h>

#include <string>
#include <vector>
#include <map>

/**
 * @brief A results set holds the results of a detection with py-faster-rcnn
 *         in one picture, the results can be from multiple model operations
 */
class ResultSet
{
    public:

        /**
         * @brief Builds a ResultSet
         * @param fileName the file name of the picture where the detection has been launched
         */
        ResultSet(std::string fileName);

        ~ResultSet();

        /**
         * @brief adds results of a detection on this picture
         * @param modelName the name of the model that produced the detections
         * @param results the objects detected
         */
        void addResults(std::string modelName, std::vector<Object> results);

        /**
         * @brief getter fileName
         * @return a string
         */
        std::string getFileName() const;

        /**
         * @brief gives the detected objects by a given model
         * @param modelName th ename of the model
         * @return a vector of objects
         */
        std::vector<Object> objects(std::string modelName) const;

        /**
         * @brief gets all the model names
         * @return a vector of strings
         */
        std::vector<std::string> modelNames() const;

    private:

        /**
         * @brief the file name of the picture where the detection has been launched
         */
        std::string _fileName;

        /**
         * @brief a map of all the results linked with the model that gave them
         */
        std::map<std::string, std::vector<Object>> _results;
};

/**
 * @brief The Results contains all the results sets on an entire dataset
 */
class Results
{
    public:

        /**
         * @brief Builds the results
         * @param dataset the dataset that has been processed
         */
        Results(std::string dataset);

        ~Results();

        /**
         * @brief add results given by an XML file of detection to this dataset
         * @param name the name of the model who produced the results
         * @param images the results of the detection
         * @return 0 if success else its an error code
         */
        int addResults(std::string name, std::vector<Image> images);

        /**
         * @brief returns the amount of pictures in the dataset
         * @return an integer
         */
        unsigned int resultsSize();

        /**
         * @brief Accessor to view a specific resultset
         * @param i the index of accession
         * @return a constant reference to a result set (read only)
         */
        const ResultSet & resultSet(unsigned int i);

        /**
         * @brief sets the location of the dataset
         * @param location the new location
         */
        void setLocation(std::string location);

        /**
         * @brief get the folder string where the pictures are
         * @return a std string
         */
        std::string datasetLocation();

   private:

        /**
         * @brief the name of the dataset that has been processed
         */
        std::string _dataset;

        /**
         * @brief _resultsets the resultsets on the entire dataset
         */
        std::vector<ResultSet> _resultsets;

        /**
         * @brief folder name where the dataset is located
         */
        std::string _location;
};

#endif // RESULTSET_H
