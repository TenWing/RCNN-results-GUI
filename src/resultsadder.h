#ifndef RESULTSADDER_H
#define RESULTSADDER_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

#include <resultset.h>
#include <imageloader.h>
#include <imagedisplayer.h>

/**
 * @brief A widget to add some results of detection to a results container with a GUI
 */
class ResultsAdder : public QWidget
{
    Q_OBJECT

    public:

        ResultsAdder(ImageDisplayer* displayer, QWidget* parent = 0);

        ~ResultsAdder();

        /**
         * @brief sets the results once they are initialized elsewhere
         * @param results the initialized results
         */
        void setResults(Results* results);

        /**
         * @brief unlocks this widget
         */
        void unlock();

    public slots:

        /**
         * @brief unlock the validation button if conditions met
         */
        void unlockValidate();

        /**
         * @brief loads an XML file into the results
         */
        void loadXML();

        /**
         * @brief browse the files to search the XML result file
         */
        void searchXML();

    private:

        /**
         * @brief the object loading data from XML
         */
        ImageLoader _loader;

        /**
         * @brief reference to the results of a detection
         */
        Results* _results;

        /**
         * @brief the xml file for the results
         */
        QString _xmlFile;

        /**
         * @brief the image displayer
         */
        ImageDisplayer* _displayer;

        /**
         * @brief The name of the model who produced the results
         */
        QLineEdit* _modelName;

        /**
         * @brief button to browse the xml results file
         */
        QPushButton* _xmlFileBrowser;

        /**
         * @brief displays the xml file chosen
         */
        QLabel* _xmlLabel;

        /**
         * @brief validation button for loading
         */
        QPushButton* _addResultsButton;

};

#endif // RESULTSADDER_H
