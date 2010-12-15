#include "dialegmaterials.h"
#include "ui_dialegmaterials.h"
#include "color.h"

DialegMaterials::DialegMaterials(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialegMaterials)
{
    ui->setupUi(this);
    idActual = -1;
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
   idActual = glwidget->getIdPosicionantObjecte();

   if (idActual != -1)
    {
       glwidget->getColorObj(idActual,&backupColor);
       glwidget->modificantColors(true);
       nouColor = backupColor;
       ui->label_idobj->setText(QString::number(idActual));
       ui->rlabel->setText(QString::number((float)backupColor.r*255));
       ui->glabel->setText(QString::number((float)backupColor.g*255));
       ui->blabel->setText(QString::number((float)backupColor.b*255));
       ui->alabel->setText(QString::number((float)backupColor.a));
       ui->rSlider->setValue((float)backupColor.r*255);
       ui->gSlider->setValue((float)backupColor.g*255);
       ui->bSlider->setValue((float)backupColor.b*255);
       ui->aSlider->setValue((float)backupColor.a*100);
    }
}

void DialegMaterials::accepta()
{
    //Actualitzar material de l'objecte
    backupColor = nouColor;
    this->close();
}

void DialegMaterials::closeEvent(QCloseEvent *e)
{
    glwidget->setColorObj(idActual,&backupColor);
    glwidget->modificantColors(false);
    e->accept();
}

void DialegMaterials::updateR(int r)
{
    ui->rlabel->setText(QString::number((float)r));
    nouColor.r = (float) r/255;
    glwidget->setColorObj(idActual,&nouColor);
}
void DialegMaterials::updateG(int g)
{
    ui->glabel->setText(QString::number((float)g));
    nouColor.g = (float) g/255;
    glwidget->setColorObj(idActual,&nouColor);
}
void DialegMaterials::updateB(int b)
{
    ui->blabel->setText(QString::number((float)b));
    nouColor.b = (float) b/255;
    glwidget->setColorObj(idActual,&nouColor);
}
void DialegMaterials::updateA(int a)
{
    ui->alabel->setText(QString::number((float)a));
    nouColor.a = (float) a/100;
    glwidget->setColorObj(idActual,&nouColor);
}

