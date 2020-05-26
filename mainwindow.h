#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow : public QMainWindow
{
    public:
        MainWindow();
        void paintEvent(QPaintEvent *event);
        void applyBtnClick();
    private:
        QLabel *redLabel, *greenLabel, *blueLabel;
        QLabel *labelH, *labelS, *labelV;
        QLineEdit *redEdit, *greenEdit, *blueEdit;
        QPushButton *applyBtn;
};
#endif // MAINWINDOW_H
