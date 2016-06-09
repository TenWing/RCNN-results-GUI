#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <string>

/**
 * @brief Represents a Bounding Box around an object (rectangular)
 */
class Bbox
{
	public:

		/**
		 * @brief Builds a bounding box
		 * @param xmin the x coordinate of the top-left corner
		 * @param ymin the y coordinate of the top-left corner
         * @param width the width of the bbox
         * @param height the height of the bbox
		 */
        Bbox(double xmin, double ymin, double width, double height);

		~Bbox();

        /**
         * @brief gets the box surrounding the object like that : xmin ymin width height
         * @return a vector of float of size 4
         */
        std::vector<double> getBox();

	private:

		/**
		 * @brief the x coordinate of the top-left corner
		 */
        double _xmin;

		/**
		 * @brief the y coordinate of the top-left corner
		 */
        double _ymin;

		/**
		 * @brief the x coordinate of the bot-right corner
		 */
        double _width;

		/**
		 * @brief the y coordinate of the bot-right corner
		 */
        double _height;
};

/**
 * @brief An object in a picture
 */
class Object
{
	public:

		/**
		 * @brief Builds an object with his label and the bounding box around him
		 * @param label the name of the object
		 * @param confidence the confidence score of detection
         * @param bbox the bounding box around the object
		 */
        Object(std::string label, double confidence, Bbox bbox);

		~Object();

        /**
         * @brief getter of the Bbox of the object
         * @return the Bbox of the object
         */
        Bbox getBbox();

        /**
         * @brief getter to the label of the object
         * @return a string
         */
        std::string getLabel();

        /**
         * @brief getter to the confidence of this object in the picture
         * @return a float value
         */
        double getConfidence();

	private:

		/**
		 * @brief the name of the object
		 */
		std::string _label;

		/**
		 * @brief the confidence score of detection
		 */
        double _confidence;

		/**
		 * @brief the bounding box around the object
		 */
		Bbox _bbox;
};

/**
 * @brief The Image class contains all the information about the objects in it etc.
 */
class Image
{
	public:

		/**
		 * @brief Builds an Image given a line divided into substrings
         * @param fileName the name of the file that is the picture
		 */
        Image(std::string fileName);

		~Image();

        /**
         * @brief adds an object detected to this image
         * @param object th eobject added
         */
        void addObject(Object object);

        /**
         * @brief Accessor to the file name of the picture
         * @return a string giving the file name
         */
        std::string getFileName();

        /**
         * @brief gets the objects detected in the picture
         */
        std::vector<Object> getObjects();

	private:

		/**
		 * @brief the objects detected in the image
		 */
		std::vector<Object> _objects;

		/**
		 * @brief the fileName of the picture
		 */
		std::string _fileName;
};

#endif
