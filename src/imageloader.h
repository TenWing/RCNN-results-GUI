#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <image.h>

#include <vector>
#include <string>

/**
 * @brief The ImageLoader loads images from an XML file using TinyXML
 */
class ImageLoader
{
    public:

        /**
         * @brief Builds the Image Loader
         */
        ImageLoader();

        ~ImageLoader();

        /**
         * @brief loads images from a given XML file
         * @param fileName the name of the XML file given
         * @return a vector of all the images
         */
        std::vector<Image> loadImages(std::string fileName);
};

#endif // IMAGELOADER_H
