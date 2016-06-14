#ifndef IMAGEDISPLAYER_H
#define IMAGEDISPLAYER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

#include <resultset.h>
#include <bboxdisplayer.h>
#include <imagewidget.h>

/**
 * @brief Containing widget to display the image, and the options to see the results od
 *        detection in it
 */
class ImageDisplayer : public QWidget
{
    Q_OBJECT

    public:

        explicit ImageDisplayer(QWidget *parent = 0);

        ~ImageDisplayer();

        /**
         * @brief sets the results sets of the image displayer
         * @param results the results to be set
         */
        void setResults(Results* results);

        /**
         * @brief The displayer fetches his results to update the images displayed
         */
        void fetchImages();

    signals:

    public slots:

        /**
         * @brief Goes to the next image and loop back to 1st when at the end
         */
        void nextImage();

        /**
         * @brief prevImage Goes to previous image and loop to the end when 1st reached
         */
        void prevImage();

        /**
         * @brief updates the slider's value
         * @param intValue the value from 0 to 100 to be converted to float
         */
        void updateSliderValue(int intValue);

        /**
         * @brief goes to a file chosen by the user
         */
        void goToFile();

    private:

        /**
         * @brief the results where the images are
         */
        Results* _results;

        /**
         * @brief the widget displaying the image
         */
        ImageWidget* _imageWidget;

        /**
         * @brief the widget displaying the bboxes
         */
        BboxDisplayer* _bboxDisplayer;

        /**
         * @brief the current index of th eimage being displayed
         */
        unsigned int _current;

        /**
         * @brief indicate which picture is displayed
         */
        QLabel* _fileIndexCurrent;

        /**
         * @brief indicate the amount of pictures in the results
         */
        QLabel* _fileIndexTotal;

        /**
         * @brief button to go to next picture
         */
        QPushButton* _nextButton;

        /**
         * @brief button to go to previous picture
         */
        QPushButton* _prevButton;

        /**
         * @brief label that describes the slider value
         */
        QLabel* _sliderValue;

        /**
         * @brief the slider for the threshold value
         */
        QSlider* _slider;

        /**
         * @brief a button to go to a chosen file
         */
        QPushButton* _goTo;

        /**
         * @brief a text field to jump to a given file
         */
        QLineEdit* _fileChoose;

        /**
         * @brief indicates if this widget is locked
         */
        bool _locked;

        /**
         * @brief the fileName of the image displayed
         */
        QLabel* _fileName;

        //############# METHODS ############

        /**
         * @brief updates the GUI to show the current image
         */
        void changeImage();

        /**
         * @brief locks the entire widget
         */
        void lock();

        /**
         * @brief unlock the entire widget
         */
        void unlock();

        /**
         * @brief fetches the results to set the right amount of Bbox
         */
        void fetchBbox();
};

#endif // IMAGEDISPLAYER_H
