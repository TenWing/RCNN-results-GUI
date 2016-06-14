#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QVBoxLayout>

#include <resultset.h>

#include <string>
#include <map>

/**
 * @brief The widget that draws the Image
 */
class ImageWidget : public QWidget
{
    Q_OBJECT

    public:

        explicit ImageWidget(QWidget *parent = 0);

        ~ImageWidget();

        /**
         * @brief sets the results once initiated
         * @param results the results to be linked
         */
        void setResults(Results* results);

        /**
         * @brief loads the image n°i in the results sets
         * @param i the index
         */
        void loadImage(unsigned int i);

        /**
         * @brief paints the Bbox if some model names have been checked
         */
        void paintBbox();

        /**
         * @brief sets the model names checked with their drawing color
         * @param modelNames the model names + color
         */
        void setModelNames(std::map<std::string, QColor> modelNames);

        /**
         * @brief erases everything that has been drawn
         */
        void eraseBbox();

        /**
         * @brief the new threshold value
         * @param threshold the threshold value
         */
        void setThreshold(double threshold);

        /**
         * @brief overrides the resize event to resize the picture
         * @param event event for qt resize
         */
        void resizeEvent(QResizeEvent * event);

    signals:

    public slots:

    private:

        /**
         * @brief the results of the detection
         */
        Results* _results;

        /**
         * @brief the current index of the file in the results
         */
        unsigned int _index;

        /**
         * @brief the threshold value to display object
         */
        double _threshold;

        /**
         * @brief the model names checked + their color
         */
        std::map<std::string, QColor> _modelNames;

        /**
         * @brief the image loaded
         */
        QImage _image;

        /**
         * @brief the HD image where bboxes are drawn
         */
        QImage _drawn;

        /**
         * @brief the label displaying the image
         */
        QLabel* _displayer;
};

#endif // IMAGEWIDGET_H
