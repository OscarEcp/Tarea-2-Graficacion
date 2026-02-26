#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QSize>
#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Establecemos el tamaño de la ventana al que se ajustará la imagen.
    this->setFixedSize(QSize(457,600));

    // Cargarmos la imagen en un QImage para modificar los pixeles más efcientemente.
    QImage imagenOriginal("Pixar_UP.png");

    // Ajustamos la imagen al tamaño de la ventana ignorando que se mantenga la escala de la imagen
    // para que así ocupe todo el espacio de despliegue.
    imagenOriginal = imagenOriginal.scaled(QSize(457,600), Qt::IgnoreAspectRatio);

    // Recorremos la imagen para buscar los pixeles con el valor rgb a cambiar y les asignamos un nuevo color.
    for (int x = 0; x < imagenOriginal.width(); ++x) {
        for (int y = 0; y < imagenOriginal.height(); ++y) {

            if (imagenOriginal.pixelColor(x,y).red() == 65 && imagenOriginal.pixelColor(x,y).green() == 142
                && imagenOriginal.pixelColor(x,y).blue() == 202)
            {
                imagenOriginal.setPixelColor(x, y, QColor(170, 15, 200));
            }
        }
    }

    // Convertimos de QImage a QPixmap para dibujar en pantalla con menos recursos.
    imagenPixmap = QPixmap::fromImage(imagenOriginal);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    // Con QRect definimos el área en la que se va a dibujar la imagen desde el pixmap estableciendo las coordenadas de origen y fin.
    QRect rect(0, 0, 457, 600);
    painter.drawPixmap(rect, imagenPixmap);
}
