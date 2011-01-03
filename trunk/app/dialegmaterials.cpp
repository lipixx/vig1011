#include "dialegmaterials.h"
#include "ui_dialegmaterials.h"

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
       glwidget->getMaterialObj(idActual,&backupMaterial);
       glwidget->modificantMaterials(true);
       nouMaterial = backupMaterial;

       //Set ui
       ui->label_idobj->setText(QString::number(idActual));
       ui->nlabel->setText(QString::number(backupMaterial.shininess));
       ui->nSlider->setValue((float)backupMaterial.shininess);

       ui->rlabel_kd->setText(QString::number((float)backupMaterial.kd.r*255));
       ui->rlabel_ks->setText(QString::number((float)backupMaterial.ks.r*255));
       ui->rlabel_ka->setText(QString::number((float)backupMaterial.ka.r*255));

       ui->glabel_kd->setText(QString::number((float)backupMaterial.kd.g*255));
       ui->glabel_ks->setText(QString::number((float)backupMaterial.ks.g*255));
       ui->glabel_ka->setText(QString::number((float)backupMaterial.ka.g*255));

       ui->blabel_kd->setText(QString::number((float)backupMaterial.kd.b*255));
       ui->blabel_ks->setText(QString::number((float)backupMaterial.ks.b*255));
       ui->blabel_ka->setText(QString::number((float)backupMaterial.ka.b*255));

       ui->alabel_kd->setText(QString::number((float)backupMaterial.kd.a));
       ui->alabel_ks->setText(QString::number((float)backupMaterial.ks.a));
       ui->alabel_ka->setText(QString::number((float)backupMaterial.ka.a));

       ui->rSlider_kd->setValue((float)backupMaterial.kd.r*255);
       ui->rSlider_ks->setValue((float)backupMaterial.ks.r*255);
       ui->rSlider_ka->setValue((float)backupMaterial.ka.r*255);

       ui->gSlider_kd->setValue((float)backupMaterial.kd.g*255);
       ui->gSlider_ks->setValue((float)backupMaterial.ks.g*255);
       ui->gSlider_ka->setValue((float)backupMaterial.ka.g*255);

       ui->bSlider_kd->setValue((float)backupMaterial.kd.b*255);
       ui->bSlider_ks->setValue((float)backupMaterial.ks.b*255);
       ui->bSlider_ka->setValue((float)backupMaterial.ka.b*255);

       ui->aSlider_kd->setValue((float)backupMaterial.kd.a*100);
       ui->aSlider_ks->setValue((float)backupMaterial.ks.a*100);
       ui->aSlider_ka->setValue((float)backupMaterial.ka.a*100);
    }
}

/*
 S'ha d'acabar el següent:
glwidget->getMaterialObj(idActual,&backupMaterial);
glwidget->modificantMaterials(true);

i per cada slider, fer els corresponents slots i signals!.
 */
void DialegMaterials::accepta()
{
    //Actualitzar material de l'objecte
    backupMaterial = nouMaterial;
    this->close();
}

void DialegMaterials::closeEvent(QCloseEvent *e)
{
    glwidget->setMaterialObj(idActual,&backupMaterial);
    glwidget->modificantMaterials(false);
    e->accept();
}

void DialegMaterials::updateN(int n)
{
    ui->nlabel->setText(QString::number((float)n));
    nouMaterial.shininess = (float) n;
    glwidget->setMaterialObj(idActual,&nouMaterial);
}

void DialegMaterials::updateR(int r)
{
    //kd 0 , ks 1, ka 2
    switch (ui->toolBox->currentIndex())
    {
    case 0:
        ui->rlabel_kd->setText(QString::number((float)r));
        nouMaterial.kd.r = (float) r/255;
        break;
    case 1:
        ui->rlabel_ks->setText(QString::number((float)r));
        nouMaterial.ks.r = (float) r/255;
        break;
    case 2:
        ui->rlabel_ka->setText(QString::number((float)r));
        nouMaterial.ka.r = (float) r/255;
        break;
    }
    glwidget->setMaterialObj(idActual,&nouMaterial);
}
void DialegMaterials::updateG(int g)
{
    //kd 0 , ks 1, ka 2
    switch (ui->toolBox->currentIndex())
    {
    case 0:
        ui->glabel_kd->setText(QString::number((float)g));
        nouMaterial.kd.g = (float) g/255;
        break;
    case 1:
        ui->glabel_ks->setText(QString::number((float)g));
        nouMaterial.ks.g = (float) g/255;
        break;
    case 2:
        ui->glabel_ka->setText(QString::number((float)g));
        nouMaterial.ka.g = (float) g/255;
        break;
    }
    glwidget->setMaterialObj(idActual,&nouMaterial);
}
void DialegMaterials::updateB(int b)
{
    //kd 0 , ks 1, ka 2
    switch (ui->toolBox->currentIndex())
    {
    case 0:
        ui->blabel_kd->setText(QString::number((float)b));
        nouMaterial.kd.b = (float) b/255;
        break;
    case 1:
        ui->blabel_ks->setText(QString::number((float)b));
        nouMaterial.ks.b = (float) b/255;
        break;
    case 2:
        ui->blabel_ka->setText(QString::number((float)b));
        nouMaterial.ka.b = (float) b/255;
        break;
    }
    glwidget->setMaterialObj(idActual,&nouMaterial);
}
void DialegMaterials::updateA(int a)
{
    //kd 0 , ks 1, ka 2
    switch (ui->toolBox->currentIndex())
    {
    case 0:
        ui->alabel_kd->setText(QString::number((float)a));
        nouMaterial.kd.a = (float) a/255;
        break;
    case 1:
        ui->alabel_ks->setText(QString::number((float)a));
        nouMaterial.ks.a = (float) a/255;
        break;
    case 2:
        ui->alabel_ka->setText(QString::number((float)a));
        nouMaterial.ka.a = (float) a/255;
        break;
    }
    glwidget->setMaterialObj(idActual,&nouMaterial);
}
