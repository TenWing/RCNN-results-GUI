#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

#include <resultset.h>
#include <resultsadder.h>
#include <imagedisplayer.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:

        /**
         * @brief enables the validation button when the text is filled
         * @param data the string of the text field
         */
        void validateEnabler(QString data);

        /**
         * @brief When the dataset has been named it is locked
         */
        void lockValidation();

        /**
         * @brief searches the folder of the dataset using a QFileDialog
         */
        void searchFolder();

    private:

        /**
         * @brief the results of detection for a dataset
         */
        Results* _results;

        /**
         * @brief the displayer of the images
         */
        ImageDisplayer* _imageDisplayer;

        /**
         * @brief the widget that loads result sets into the results
         */
        ResultsAdder* _resultsAdder;

        /**
         * @brief Push button to create the results
         */
        QPushButton* _validateDataset;

        /**
         * @brief the field that holds the dataset name
         */
        QLineEdit* _datasetName;

        /**
         * @brief button to browse the dataset location
         */
        QPushButton* _browseFolder;

        /**
         * @brief the folder chosen
         */
        QLabel* _folder;
};

#endif // MAINWINDOW_H
