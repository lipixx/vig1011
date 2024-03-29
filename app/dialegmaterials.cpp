#include "dialegmaterials.h"
#include "ui_dialegmaterials.h"
#include <QColorDialog>

DialegMaterials::DialegMaterials(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialegMaterials)
{
    ui->setupUi(this);
    idActual = -1;
    QDoubleValidator *validator = new QDoubleValidator(-100, 100, 3, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->xPos->setValidator(validator);
    ui->zPos->setValidator(validator);
    ui->yPos->setValidator(validator);
}

DialegMaterials::~DialegMaterials()
{
    delete ui;
}

void DialegMaterials::initialize(GLWidget *glw)
{
     glwidget = glw;
     setejaBotons(0);
     feature_en = true;
}

void DialegMaterials::debug_llums(bool b)
{
    glwidget->activarDebugLlums(b);
}

void DialegMaterials::dialegColorA()
{
    QColor color = QColorDialog::getColor(QColor(glwidget->amb_light[ui->lightSelectedBox->currentIndex()][0]*255,glwidget->amb_light[ui->lightSelectedBox->currentIndex()][1]*255,glwidget->amb_light[ui->lightSelectedBox->currentIndex()][2]*255), this);
    ui->boto_ambient->setPalette(color);
    glwidget->amb_light[ui->lightSelectedBox->currentIndex()][0] = color.redF();
    glwidget->amb_light[ui->lightSelectedBox->currentIndex()][1] = color.greenF();
    glwidget->amb_light[ui->lightSelectedBox->currentIndex()][2] = color.blueF();
    glwidget->redefineixLlum(ui->lightSelectedBox->currentIndex(),ui->llum_activat->checkState());
}
void DialegMaterials::dialegColorS()
{
    QColor color = QColorDialog::getColor(QColor(glwidget->diff_light[ui->lightSelectedBox->currentIndex()][0]*255,glwidget->diff_light[ui->lightSelectedBox->currentIndex()][1]*255,glwidget->diff_light[ui->lightSelectedBox->currentIndex()][2]*255), this);
    ui->boto_specular->setPalette(color);
    glwidget->diff_light[ui->lightSelectedBox->currentIndex()][0] = color.redF();
    glwidget->diff_light[ui->lightSelectedBox->currentIndex()][1] = color.greenF();
    glwidget->diff_light[ui->lightSelectedBox->currentIndex()][2] = color.blueF();
    glwidget->redefineixLlum(ui->lightSelectedBox->currentIndex(),ui->llum_activat->checkState());
}
void DialegMaterials::dialegColorD()
{
    QColor color = QColorDialog::getColor(QColor(glwidget->spec_light[ui->lightSelectedBox->currentIndex()][0]*255,glwidget->spec_light[ui->lightSelectedBox->currentIndex()][1]*255,glwidget->spec_light[ui->lightSelectedBox->currentIndex()][2]*255), this);
    ui->boto_difos->setPalette(color);
    glwidget->spec_light[ui->lightSelectedBox->currentIndex()][0] = color.redF();
    glwidget->spec_light[ui->lightSelectedBox->currentIndex()][1] = color.greenF();
    glwidget->spec_light[ui->lightSelectedBox->currentIndex()][2] = color.blueF();
    glwidget->redefineixLlum(ui->lightSelectedBox->currentIndex(),ui->llum_activat->checkState());
}

void DialegMaterials::setPosition()
{
    if (feature_en) {
    int i = ui->lightSelectedBox->currentIndex();
    glwidget->pos_light[i][0] = ui->xPos->text().toFloat();
    glwidget->pos_light[i][1] = ui->yPos->text().toFloat();
    glwidget->pos_light[i][2] = ui->zPos->text().toFloat();
    glwidget->updateGL();
    }
}

void DialegMaterials::activaLlum(bool activacio)
{
    glwidget->redefineixLlum(ui->lightSelectedBox->currentIndex(),activacio);
}

void DialegMaterials::updateLlums()
{
    feature_en = false;
    setejaBotons(ui->lightSelectedBox->currentIndex());      
    feature_en = true;
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
       ui->nlabel->setText(QString::number(backupMaterial.shininess*12.8));
       ui->nSlider->setValue((float)backupMaterial.shininess*12.8);

       ui->rlabel_kd->setText(QString::number((float)backupMaterial.kd.r*255));
       ui->rlabel_ks->setText(QString::number((float)backupMaterial.ks.r*255));
       ui->rlabel_ka->setText(QString::number((float)backupMaterial.ka.r*255));

       ui->glabel_kd->setText(QString::number((float)backupMaterial.kd.g*255));
       ui->glabel_ks->setText(QString::number((float)backupMaterial.ks.g*255));
       ui->glabel_ka->setText(QString::number((float)backupMaterial.ka.g*255));

       ui->blabel_kd->setText(QString::number((float)backupMaterial.kd.b*255));
       ui->blabel_ks->setText(QString::number((float)backupMaterial.ks.b*255));
       ui->blabel_ka->setText(QString::number((float)backupMaterial.ka.b*255));

       ui->alabel_kd->setText(QString::number((float)backupMaterial.kd.a*100));
       ui->alabel_ks->setText(QString::number((float)backupMaterial.ks.a*100));
       ui->alabel_ka->setText(QString::number((float)backupMaterial.ka.a*100));

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

void DialegMaterials::setejaBotons(int i)
{
    ui->boto_ambient->setPalette(QColor (glwidget->amb_light[i][0]*255,glwidget->amb_light[i][1]*255,glwidget->amb_light[i][2]*255));
    ui->boto_difos->setPalette(QColor (glwidget->diff_light[i][0]*255,glwidget->diff_light[i][1]*255,glwidget->diff_light[i][2]*255));
    ui->boto_specular->setPalette(QColor (glwidget->spec_light[i][0]*255,glwidget->spec_light[i][1]*255,glwidget->spec_light[i][2]*255));

    QString tmp;
    tmp.setNum(glwidget->pos_light[i][0]);
    ui->xPos->setText(tmp);
    tmp.setNum(glwidget->pos_light[i][1]);
    ui->yPos->setText(tmp);
    tmp.setNum(glwidget->pos_light[i][2]);
    ui->zPos->setText(tmp);

    ui->llum_activat->setChecked(glwidget->light_state[i]);
}

void DialegMaterials::accepta()
{
    if (ui->tabMaterials->isEnabled()) backupMaterial = nouMaterial;
    this->close();
}

void DialegMaterials::closeEvent(QCloseEvent *e)
{
    if (ui->tabMaterials->isEnabled())
    {
    glwidget->setMaterialObj(idActual,&backupMaterial);
    glwidget->modificantMaterials(false);
    }
    e->accept();
}

void DialegMaterials::updateN(int n)
{
    ui->nlabel->setText(QString::number((float)n));
    nouMaterial.shininess = (float) n/12.8;
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
        nouMaterial.kd.a = (float) a/100;
        break;
    case 1:
        ui->alabel_ks->setText(QString::number((float)a));
        nouMaterial.ks.a = (float) a/100;
        break;
    case 2:
        ui->alabel_ka->setText(QString::number((float)a));
        nouMaterial.ka.a = (float) a/100;
        break;
    }
    glwidget->setMaterialObj(idActual,&nouMaterial);
}

void DialegMaterials::setLightTab(int index, bool activar_altre)
{
    ui->lightSelectedBox->setCurrentIndex(0);
    setejaBotons(0);

    ui->tabWidget->setCurrentIndex(index);    
    if (!activar_altre)
    {
        switch (index)
        {
        case 0:
             ui->tabLlums->setDisabled(true);
            break;
        case 1:
             ui->tabMaterials->setDisabled(true);
            break;
        }
    }
    else
    {
        switch (index)
        {
        case 0:
             ui->tabLlums->setEnabled(true);
            break;
        case 1:
             ui->tabMaterials->setEnabled(true);
            break;
        }
    }
}
