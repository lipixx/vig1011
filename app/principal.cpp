#include "principal.h"
#include "ui_principal.h"
#include "dialegmaterials.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    dm.initialize(ui->gLWidget);
    connect(ui->ajudaBut, SIGNAL(clicked()),this,SLOT(showAjudaDialog()));
}

Principal::~Principal()
{
    delete ui;
}

void Principal::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void Principal::actualitzaParamsObj(double esc,double alt)
{
    if (esc == -1)
    {
        ui->altura->setReadOnly(true);
        ui->escalat->setReadOnly(true);
        ui->altura->setValue(0);
        ui->escalat->setValue(0);
    }
    else
    {
        ui->altura->setReadOnly(false);
        ui->altura->setValue(alt);
        ui->escalat->setReadOnly(false);
        ui->escalat->setValue(esc);
    }
}

void Principal::showMatDialog()
{
    if (ui->gLWidget->getIdPosicionantObjecte() != -1)
    {
        dm.updateData();
        dm.setLightTab(0,true);
        dm.show();
    }
}

void Principal::showAjudaDialog()
{
    aj.show();
}

void Principal::setStatusLlums()
{
  ui->gLWidget->redefineixLlum(0,ui->st_focus0->isChecked());
  ui->gLWidget->redefineixLlum(1,ui->st_focus1->isChecked());
}

void Principal::resetLights()
{
  ui->st_focus0->setChecked(true);
  ui->st_focus1->setChecked(true);
  ui->horizontalSlider->setValue(50);
  ui->label_3->setText("50");
  ui->gLWidget->initializeLights();
}

void Principal::showLightDialog()
{
    if (ui->gLWidget->getIdPosicionantObjecte() == -1) dm.setLightTab(1,false);
    else
    {
        dm.updateData();
        dm.setLightTab(1,true);
    }
    dm.show();
}

void Principal::closeEvent( QCloseEvent *e )
{
    if (!dm.isHidden()) dm.close();
    if (!aj.isHidden()) aj.close();
       e->accept();
}

void Principal::setFilferrosCheckBox(bool act)
{
    ui->filferrosCheckBox->setChecked(act);
}
