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
        dm.setLightTab(0);
        dm.show();
    }
}

void Principal::showLightDialog()
{
    if (ui->gLWidget->getIdPosicionantObjecte() != -1)
    {
        dm.updateData();
        dm.setLightTab(1);
        dm.show();
    }
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
