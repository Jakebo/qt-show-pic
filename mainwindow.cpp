#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&thread, SIGNAL(NextPic()), this, SLOT(NextPic()));

    img = new QImage();

    // Set default image
    if (img->load("1.png"))
        ui->img_lab->setPixmap(QPixmap::fromImage(*img));
    else
        ui->img_lab->setText("Default image not found");

    thread.start();
}

void MainWindow::NextPic()
{
	static int idx = 2;
	QString imgPath = QString::number(idx) + tr(".png");
	
    if (!img->load(imgPath)) {
		img->load("1.png");
		idx = 2;
	}

	ui->img_lab->setPixmap(QPixmap::fromImage(*img));
	++idx;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete img;
}
