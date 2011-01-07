#include "principal.h"
#include "ui_principal.h"
#include "dialegmaterials.h"

Principal::Principal(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Principal)
{
    ui->setupUi(this);
    dm.initialize(ui->gLWidget);
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

void Principal::showMatDialog()
{
    if (ui->gLWidget->getIdPosicionantObjecte() != -1)
    {
        dm.updateData();
        dm.setLightTab(0,true);
        dm.show();
    }
}

void Principal::setStatusLlums()
{
  std::vector < bool > llums_status;

 llums_status.push_back(ui->st_focus0->isChecked());
 llums_status.push_back(ui->st_focus1->isChecked());

  ui->gLWidget->setLights(llums_status);
}

void Principal::showLightDialog()
{
    if (ui->gLWidget->getIdPosicionantObjecte() == -1) dm.setLightTab(1,false);
    else
    {
        dm.setLightTab(1,true);
        dm.updateData();
    }
    dm.show();
}

void Principal::closeEvent( QCloseEvent *e )
{
    if (!dm.isHidden()) dm.close();
       e->accept();
}

void Principal::setFilferrosCheckBox(bool act)
{
    ui->filferrosCheckBox->setChecked(act);
}
