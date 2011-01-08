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
    void setLightTab(int,bool);

private:
    Ui::DialegMaterials *ui;
    GLWidget *glwidget;
    Material nouMaterial, backupMaterial;
    int idActual;
    void setejaBotons(int i);
    bool feature_en;

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void accepta();
    void updateN(int);
    void updateR(int);
    void updateG(int);
    void updateB(int);
    void updateA(int);
    void debug_llums(bool);
    void dialegColorA();
    void dialegColorS();
    void dialegColorD();
    void setPosition();
    void updateLlums();
    void activaLlum(bool);
};

#endif // DIALEGMATERIALS_H
