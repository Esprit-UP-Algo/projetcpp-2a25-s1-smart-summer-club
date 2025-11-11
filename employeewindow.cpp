#include "employeewindow.h"
#include "ui_employeewindow.h"
#include <QMessageBox>
#include <QDate>

EmployeeWindow::EmployeeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeWindow),
    selectedId(0)
{
    ui->setupUi(this);
    afficherEmployees();
}

EmployeeWindow::~EmployeeWindow()
{
    delete ui;
}

void EmployeeWindow::afficherEmployees()
{
    Employee e;
    ui->tableView->setModel(e.afficher());

    // Connect selection signal
    if(ui->tableView->model()) {
        connect(ui->tableView->selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &EmployeeWindow::selectionChanged);
    }
}

void EmployeeWindow::selectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    if(selected.indexes().isEmpty())
        return;

    int row = selected.indexes().first().row();
    auto model = ui->tableView->model();

    ui->lineEdit_nom->setText(model->index(row,1).data().toString());
    ui->lineEdit_prenom->setText(model->index(row,2).data().toString());
    ui->lineEdit_poste->setText(model->index(row,3).data().toString());
    ui->lineEdit_fonction->setText(model->index(row,4).data().toString());
    ui->lineEdit_genre->setText(model->index(row,5).data().toString());
    ui->lineEdit_mail->setText(model->index(row,6).data().toString());
    ui->lineEdit_tel->setText(model->index(row,7).data().toString());
    ui->dateEdit_naissance->setDate(QDate::fromString(model->index(row,8).data().toString(),"yyyy-MM-dd"));
    ui->lineEdit_adresse->setText(model->index(row,9).data().toString());
    ui->lineEdit_salaire->setText(model->index(row,10).data().toString());

    selectedId = model->index(row,0).data().toInt();
}

void EmployeeWindow::on_pushButton_ajouter_clicked()
{
    Employee e(ui->lineEdit_nom->text(),
               ui->lineEdit_prenom->text(),
               ui->lineEdit_poste->text(),
               ui->lineEdit_fonction->text(),
               ui->lineEdit_genre->text(),
               ui->lineEdit_mail->text(),
               ui->lineEdit_tel->text(),
               ui->dateEdit_naissance->date(),
               ui->lineEdit_adresse->text(),
               ui->lineEdit_salaire->text().toDouble());

    if(e.ajouter()) {
        QMessageBox::information(this,"Ajouter","Employee ajouté avec succès!");
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de l'ajout!");
    }
}

void EmployeeWindow::on_pushButton_modifier_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un employee!");
        return;
    }

    Employee e(selectedId,
               ui->lineEdit_nom->text(),
               ui->lineEdit_prenom->text(),
               ui->lineEdit_poste->text(),
               ui->lineEdit_fonction->text(),
               ui->lineEdit_genre->text(),
               ui->lineEdit_mail->text(),
               ui->lineEdit_tel->text(),
               ui->dateEdit_naissance->date(),
               ui->lineEdit_adresse->text(),
               ui->lineEdit_salaire->text().toDouble());

    if(e.modifier()) {
        QMessageBox::information(this,"Modifier","Employee modifié avec succès!");
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de la modification!");
    }
}

void EmployeeWindow::on_pushButton_supprimer_clicked()
{
    if(selectedId == 0) {
        QMessageBox::warning(this,"Erreur","Veuillez sélectionner un employee!");
        return;
    }

    Employee e;
    if(e.supprimer(selectedId)) {
        QMessageBox::information(this,"Supprimer","Employee supprimé avec succès!");
        selectedId = 0;
        afficherEmployees();
    } else {
        QMessageBox::warning(this,"Erreur","Échec de la suppression!");
    }
}
