#include "dialegmaterials.h"
#include "ui_dialegmaterials.h"
#include "color.h"

DialegMaterials::DialegMaterials(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialegMaterials)
{
    ui->setupUi(this);
}

DialegMaterials::~DialegMaterials()
{
    delete ui;
}

void DialegMaterials::initialize(GLWidget *glw)
{
     glwidget = glw;
}

void DialegMaterials::updateData()
{
   int idActual = glwidget->getIdPosicionantObjecte();
    //Color color = glwidget->getColor(idActual);
    if (idActual != -1)
    {
         ui->label_idobj->setText(QString::number(idActual));
    }
}

void DialegMaterials::accepta()
{
    //actualitzar material de l'objecte
    this->close();
}
