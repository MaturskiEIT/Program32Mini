#include "boja.h"
#include "ui_boja.h"
#include "konekcija.h"
#include <QMessageBox>

Boja::Boja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Boja)
{
    ui->setupUi(this);

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT BojaID AS Sifra, Naziv, Opis FROM Boja ORDER BY BojaId ASC;");

    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

Boja::~Boja()
{
    delete ui;
}

void Boja::on_pushButtonIzadji_clicked()
{
    this->close();
}

void Boja::on_lineEditSifra_editingFinished()
{
    QString BojaID = ui->lineEditSifra->text();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("SELECT COUNT(*) FROM Boja WHERE BojaId = :BojaID;");
    upit.bindValue(":BojaID", BojaID);

    upit.exec();

    upit.next();
    if(upit.value(0).toInt() > 0)
    {
        upit.prepare("SELECT Naziv, Opis FROM Boja WHERE BojaId = :BojaID;");
        upit.bindValue(":BojaID", BojaID);

        upit.exec();

        upit.next();
        ui->lineEditNaziv->setText(upit.value(0).toString());
        ui->lineEditOpis->setText(upit.value(1).toString());
    }

    baza.dbClose();
}

void Boja::on_pushButtonObrisi_clicked()
{
    QString BojaID = ui->lineEditSifra->text();

    Konekcija baza;
    baza.dbOpen();

    // Brisanje podataka u bazi o odabranoj boji
    QSqlQuery upit;
    upit.prepare("DELETE FROM Boja WHERE BojaID = :BojaID;");
    upit.bindValue(":BojaID", BojaID);
    upit.exec();
    QMessageBox::information(this, "Uspesno!!!", "Uspesno obrisani podaci o boji!!!");


    //Brisanje podataka iz polja
    ui->lineEditSifra->clear();
    ui->lineEditNaziv->clear();
    ui->lineEditOpis->clear();


    // Osvezavanje ispisa o bojama
    QSqlQuery upit;
    upit.prepare("SELECT BojaID AS Sifra, Naziv, Opis FROM Boja ORDER BY BojaId ASC;");

    upit.exec();
    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

void Boja::on_pushButtonUpisi_clicked()
{
    QString BojaID = ui->lineEditSifra->text();
    QString Naziv = ui->lineEditNaziv->text();
    QString Opis = ui->lineEditOpis->text();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("INSERT INTO Boja(BojaID, Naziv, Opis) VALUES (:BojaID, :Naziv, :Opis);");
    upit.bindValue(":BojaID", BojaID);
    upit.bindValue(":Naziv", Naziv);
    upit.bindValue(":Opis", Opis);

    upit.exec();

    QMessageBox::information(this, "Uspesno!!!", "Nova boja je uspesno prijavljena!!!");

    //Brisanje podataka iz polja
    ui->lineEditSifra->clear();
    ui->lineEditNaziv->clear();
    ui->lineEditOpis->clear();

    // Osvezavanje ispisa o bojama
    upit.prepare("SELECT BojaID AS Sifra, Naziv, Opis FROM Boja ORDER BY BojaId ASC;");

    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}

void Boja::on_pushButtonIzmeni_clicked()
{
    QString BojaID = ui->lineEditSifra->text();
    QString Naziv = ui->lineEditNaziv->text();
    QString Opis = ui->lineEditOpis->text();

    Konekcija baza;
    baza.dbOpen();

    QSqlQuery upit;

    upit.prepare("UPDATE Boja SET Naziv = :Naziv, Opis = :Opis WHERE BojaID = :BojaID;");
    upit.bindValue(":BojaID", BojaID);
    upit.bindValue(":Naziv", Naziv);
    upit.bindValue(":Opis", Opis);

    upit.exec();

    QMessageBox::information(this, "Uspesno!!!", "Podaci o boji su uspesno izmenjeni!!!");

    //Brisanje podataka iz polja
    ui->lineEditSifra->clear();
    ui->lineEditNaziv->clear();
    ui->lineEditOpis->clear();

    // Osvezavanje ispisa o bojama
    upit.prepare("SELECT BojaID AS Sifra, Naziv, Opis FROM Boja ORDER BY BojaId ASC;");

    upit.exec();

    QSqlQueryModel *model;
    model = new QSqlQueryModel();
    model->setQuery(upit);
    ui->tableView->setModel(model);

    baza.dbClose();
}
