#include "mainwindow.h"
#include <QtWidgets>
#include <QList>
#include <QDebug>

float redColor, greenColor,blueColor;
double h,s,v;
double MAX = 0, MIN = 0;
QString strMax, strMin;
QString strRedColor,strGreenColor,strBlueColor;
QString strH,strS,strV;
QColor fillColor;
float var_R,var_G,var_B;
float del;


MainWindow::MainWindow(){
    setWindowTitle("Converter RGB to HSV");
    setFixedSize(550,200);
    strRedColor = QString::number(redColor);
    strGreenColor = QString::number(greenColor);
    strBlueColor = QString::number(blueColor);

    fillColor.setRgb(redColor,greenColor,blueColor,255);


    QFont lblFont(QFont("Courier",20,QFont::Bold));
    QFont editFont("System", 12, QFont::Normal);
    QFont btnFont("Times",16, QFont::Bold);

    redLabel = new QLabel(this);
    redLabel -> setText("R:"+ strRedColor);
    redLabel -> setGeometry(5,5,330,40);
    redLabel -> setFont(lblFont);

    redEdit = new QLineEdit(this);
    redEdit -> setText(strRedColor);
    redEdit -> setGeometry(5,50,50,30);
    redEdit -> setFont(editFont);

    //         ///           //

    greenLabel = new QLabel(this);
    greenLabel -> setText("G:"+ strGreenColor);
    greenLabel -> setGeometry(125,5,330,40);
    greenLabel -> setFont(lblFont);

    greenEdit = new QLineEdit(this);
    greenEdit -> setText(strGreenColor);
    greenEdit -> setGeometry(125,50,50,30);
    greenEdit -> setFont(editFont);

    //          //          //

    blueLabel = new QLabel(this);
    blueLabel -> setText("B:"+ strBlueColor);
    blueLabel -> setGeometry(245,5,330,40);
    blueLabel -> setFont(lblFont);

    blueEdit = new QLineEdit(this);
    blueEdit -> setText(strBlueColor);
    blueEdit -> setGeometry(245,50,50,30);
    blueEdit -> setFont(editFont);

    //          //          //


    labelH = new QLabel(this);
    labelH -> setGeometry(5,100,330,40);
    labelH-> setText("H: "+ strMax);
    labelH-> setFont(lblFont);


    labelS = new QLabel(this);
    labelS -> setGeometry(5,125,330,40);
    labelS-> setText("S: "+ strMin);
    labelS-> setFont(lblFont);

    labelV = new QLabel(this);
    labelV -> setGeometry(5,150,330,40);
    labelV-> setText("V: "+ strV);
    labelV-> setFont(lblFont);

    applyBtn = new QPushButton("Apply",this);
    applyBtn -> setGeometry(470,145,75,30);
    applyBtn -> setFont(editFont);

   connect(applyBtn,&QPushButton::clicked,this,&MainWindow::applyBtnClick);
    //QColor color = QColorDialog::getColor(blueColor);
   // if (!color.isValid() ) {
    // Cancel
   // }
}
void MainWindow::applyBtnClick(){

    if (redColor > 256 || greenColor > 256 || blueColor > 256){
        QMessageBox::warning(0, "Warning", "RGB parameters out of range");
    }
    else {
    strRedColor = redEdit -> text();
    redColor = strRedColor.toInt();
    redLabel -> setText("R: "+ strRedColor);

    strGreenColor = greenEdit -> text();
    greenColor = strGreenColor.toInt();
    greenLabel -> setText("G: "+ strGreenColor);

    strBlueColor = blueEdit -> text();
    blueColor = strBlueColor.toInt();
    blueLabel -> setText("B: "+ strBlueColor);

    // Переменные для вычислений HSV
    var_R = redColor/255;
    var_G = greenColor/255;
    var_B = blueColor/255;

    //Нахождение Мин. и Макс. значения
    MIN = var_R < var_G ? var_R : var_G;
    MIN = MIN  < var_B ? MIN  : var_B;

    MAX = var_R > var_G ? var_R : var_G;
    MAX = MAX  > var_B ? MAX  : var_B;

    // разница значений
    del = MAX-MIN;

    strMax = QString::number(qRound(MAX*100));

    // Вычисление H
    if (MAX==MIN){
        h = 0;
    }
    if(MAX==var_R && var_G >=var_B){
        h = 60*((var_G-var_B)/del);
    }
    if(MAX==var_R && var_G<var_B){
       h = 60*((var_G-var_B)/del)+360;
    }

    if(MAX==var_G){
        h = 60*((var_B-var_R)/del)+120;
    }
    if(MAX==var_B){
        h = 60*((var_R-var_G)/del)+240;
    }

    // Вычисление S
    if (MAX == 0){
        s = 0;
    }
    else {
        s = 1-(MIN/MAX);
    }

    strH = QString::number(qRound(h));
    strS = QString::number(qRound(s*100));

 // Вывод вычисленных значений
    labelH-> setText("H: "+ strH + "°");
    labelS-> setText("S: "+ strS + " %");
    labelV-> setText("V: "+ strMax +" %");

    fillColor.setRgb(redColor,greenColor,blueColor,255);
    update();
    }


}




void MainWindow::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setPen(QPen(fillColor,6,Qt::SolidLine,Qt::RoundCap));
    painter.setBrush(fillColor);
    painter.drawRect(340,5,200,135);
}
