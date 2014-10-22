#include "mainwindow.h"
#include "ui_mainwindow.h"


GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent) {
    setScene(&scene);
    QBrush brush(Qt::lightGray,Qt::SolidPattern);
    setBackgroundBrush(brush);
    setGeometry(10,10,300,300);
}

void GraphicsView::wheelEvent(QWheelEvent* event) {

    setTransformationAnchor(QGraphicsView::AnchorViewCenter);

    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        scale(scaleFactor, scaleFactor);
    } else {
        // Zooming out
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    QRgb clr;
    int blue=0;
    height=240;
    width=240;
    QImage TempImg(height,width, QImage::Format_RGB32);
    Img=TempImg; //Прежде чем рисовать надо задать высоту, ширину и формат изображения
    Temp_Img=TempImg;
    for (int i=0;i<width;i++)       //Циклы для заполнения квадрата разными цветами
        for (int j=0;j<height;j++)
        {
            clr = qRgb(i, j, blue); //Собираем цвет
            Img.setPixel(i,j,clr);  //Рисуем пиксель этим цветом в координатах i,j

            Temp_Img.setPixel(i, j, clr);
            blue++;
            if (blue==241) blue=0;
        }

    ui->setupUi(this);
    ui->progressBar->hide();

    View = new GraphicsView(ui->widget);
    View->scene.addPixmap(QPixmap::fromImage(Img));
    View2 = new GraphicsView(ui->widget_2);
    View2->scene.addPixmap(QPixmap::fromImage(Temp_Img));
     ui->label_4->setText(QString::number(ui->horizontalSlider->value()));
}
void MainWindow::on_pushButton_pressed()
{
    QString path=ui->lineEdit->text();  //Cчитываем путь
    Img.load(path,0); //Грузим картинку, 0 - для автоопределения формата картинки
    View->scene.clear();
    View->scene.addPixmap(QPixmap::fromImage(Img));
}
void MainWindow::on_pushButton_2_pressed()
{
    QString path=ui->lineEdit_2->text();  //Cчитываем путь
    Temp_Img.load(path,0); //Грузим картинку, 0 - для автоопределения формата картинки
    View2->scene.clear();
    View2->scene.addPixmap(QPixmap::fromImage(Temp_Img));
}


//MainWindow::~MainWindow()
//{
//    delete ui;
//}



void MainWindow::on_lineEdit_returnPressed()
{
    MainWindow::on_pushButton_pressed();
}


void MainWindow::on_lineEdit_2_returnPressed()
{
    MainWindow::on_pushButton_2_pressed();
}

void MainWindow::on_pushButton_3_pressed()
{

    int height=Img.height();
    int width=Img.width();
    int req_height=Temp_Img.height();
    int req_width=Temp_Img.width();

    ui->progressBar->show();
    ui->progressBar->setMaximum(height);

    // matrix matrixImg(height,width);


    int req_x_start = 0;
    int req_y_start = 0;//координаты начала

    int req_x_end = 0;
    int req_y_end = 0;// координаты конеца

   int req_qol = 0;//промежуточные координаты
   int req_sq = req_height*req_width;
   int percent = ui->horizontalSlider->value() ;
    for (int x=0; x<width-req_width; x++)
    {
        int y;
        ui->progressBar->setValue(x);
        for (y=0; y<height-req_height; y++)
          if(Img.pixel(x,y) == Temp_Img.pixel(0,0))
            {
                req_qol=0;

                req_x_start=x;
                req_y_start=y;

                for(int xx=0;xx<req_width;xx++)
                    for(int yy=0;yy<req_height;yy++)
                        if(Img.pixel(x+xx,y+yy) == Temp_Img.pixel(xx,yy))
                             req_qol++;



            if(percent<(req_qol/req_sq)*100)
            {

                req_x_end=req_x_start+req_width;
                req_y_end=req_y_start+req_height;


                for(int i= req_x_start;i<req_x_end;i++)
                    for(int n= req_y_start;n<req_y_start+3;n++) Img.setPixel(i,n,Qt::red);

                for(int i= req_x_start;i<req_x_start+3;i++)
                    for(int n= req_y_start;n<req_y_end;n++) Img.setPixel(i,n,Qt::green);

                for(int i= req_x_start;i<req_x_end;i++)
                    for(int n= req_y_end-3;n<req_y_end;n++) Img.setPixel(i,n,Qt::blue);

                for(int i= req_x_end-3;i<req_x_end;i++)
                    for(int n= req_y_start;n<req_y_end;n++) Img.setPixel(i,n,Qt::color1);

            }
            req_x_start=req_x_end=0;
            req_y_start=req_y_end=0;
          }
    }
    View->scene.clear();
    View->scene.addPixmap(QPixmap::fromImage(Img));
    ui->progressBar->setValue(ui->progressBar->maximum());
    ui->progressBar->hide();
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{
    ui->label_4->setText(QString::number(ui->horizontalSlider->value()));
}
