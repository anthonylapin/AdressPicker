#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowTitle("Address picker");
}



MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::parseFormToStringList() {
    QStringList data;

    data << ui->txtFirstName->text();
    data << ui->txtLastName->text();
    data << ui->selectCity->currentText();
    data << ui->txtStreet->text();
    data << ui->txtNum->text();
    data << getSelectedRadioButton();

    return data.join(';');
}

QString MainWindow::getSelectedRadioButton() {
    if (ui->radioMale->isChecked()) {
        return "male";
    } else if (ui->radioFemale->isChecked()) {
        return "female";
    } else {
        return "";
    }
}

void MainWindow::saveChanges(QString data) {
    QFile file(QCoreApplication::applicationDirPath() + "/address.csv");

    if (file.open(QIODevice::ReadWrite | QIODevice::Append)) {
            QTextStream stream(&file);
            stream << data << '\n';
            file.close();
    }
}

bool MainWindow::checkTextFieldsEmpty() {
    foreach(QLineEdit *line, this->findChildren<QLineEdit*>()) {
        if (line->text().isEmpty()) {
            return true;
        }
    }
    return false;
}

bool MainWindow::checkRadioButtonsEmpty() {
    if (!ui->radioFemale->isChecked() && !ui->radioMale->isChecked()) {
        return true;
    }

    return false;
}

void MainWindow::clearAllFields() {
    clearRadioButtons();
    clearTextFields();
}

void MainWindow::clearRadioButtons() {
    clearRadioButton(ui->radioMale);
    clearRadioButton(ui->radioFemale);
}

void MainWindow::clearRadioButton(QRadioButton* btn) {
    btn->setAutoExclusive(false);
    btn->setChecked(false);
    btn->setAutoExclusive(true);
}

void MainWindow::clearTextFields() {
    foreach(QLineEdit *line, this->findChildren<QLineEdit*>()) {
        line->clear();
    }
}

void MainWindow::setComboboxDefaultValue() {
    ui->selectCity->setCurrentIndex(0);
}

void MainWindow::on_btnClear_clicked()
{
    clearAllFields();
    setComboboxDefaultValue();
}

void MainWindow::on_btnSave_clicked()
{
    if (checkTextFieldsEmpty() || checkRadioButtonsEmpty()) {
        QMessageBox::warning(this, "Something wrong", "At least one text field is empty or no radio button is checked.");
        return;
    }

    QString data = parseFormToStringList();
    saveChanges(data);

    on_btnClear_clicked();
}
