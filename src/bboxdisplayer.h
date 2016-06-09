#ifndef BBOXDISPLAYER_H
#define BBOXDISPLAYER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QCheckBox>

#include <string>
#include <vector>

#include <imagewidget.h>

/**
 * @brief The Widget that displays checkboxes to draw some Bbox
 */
class BboxDisplayer : public QWidget
{
    Q_OBJECT

    public:

        BboxDisplayer(QWidget *parent = 0, ImageWidget* imageWidget = 0);

        ~BboxDisplayer();

        /**
         * @brief adds a checkbox to display bbox in the picture
         * @param model the model name that made the detections
         */
        void addCheckBox(std::string model);

        /**
         * @brief erases all the checkboxes added
         */
        void clear();

    signals:

    public slots:

        /**
         * @brief draws the bboxes in the picture
         */
        void drawBboxes();

    private:

        /**
         * @brief collection Combo boxes + label to erase them easily
         */
        std::vector<QCheckBox*> _checkBoxes;

        /**
         * @brief the layout that adds the check boxes
         */
        QVBoxLayout* _layout;

        /**
         * @brief the widget where the bboxes are drawn
         */
        ImageWidget* _imageWidget;
};

#endif // BBOXDISPLAYER_H
