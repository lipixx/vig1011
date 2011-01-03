#ifndef DIALEGMATERIALS_H
#define DIALEGMATERIALS_H

#include <QWidget>
#include <glwidget.h>
#include <material.h>

namespace Ui {
    class DialegMaterials;
}

class DialegMaterials : public QWidget
{
    Q_OBJECT

public:
    explicit DialegMaterials(QWidget *parent = 0);
    ~DialegMaterials();

    void updateData();
    void initialize(GLWidget *glw);
    void setLightTab(int);

private:
    Ui::DialegMaterials *ui;
    GLWidget *glwidget;
    Material nouMaterial, backupMaterial;
    int idActual;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void accepta();
    void updateN(int);
    void updateR(int);
    void updateG(int);
    void updateB(int);
    void updateA(int);
};

#endif // DIALEGMATERIALS_H
