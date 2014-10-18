#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bitset>
#include <QtGui>
#include <QColor>
#include <QtCore>

#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class GraphicsView : public QGraphicsView
{
public:

    QGraphicsScene scene;
    GraphicsView(QWidget* parent = 0);

protected:
  //  virtual void dragEnterEvent(QDragEnterEvent *event);
    virtual void wheelEvent(QWheelEvent* event);
};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    int height;
    int width;

    QImage Img;
    QImage Temp_Img;
    QPixmap Pix;
    GraphicsView *View;
     GraphicsView *View2;
    QGraphicsScene scene;

private slots:

   void on_pushButton_pressed();

   void on_lineEdit_returnPressed();

   void on_pushButton_2_pressed();

   void on_lineEdit_2_returnPressed();

   void on_pushButton_3_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
