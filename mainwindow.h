#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRadioButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSave_clicked();

    void on_btnClear_clicked();

private:
    Ui::MainWindow *ui;

    QString parseFormToStringList();
    QString getSelectedRadioButton();

    void saveChanges(QString data);

    bool checkRadioButtonsEmpty();
    bool checkTextFieldsEmpty();

    void clearAllFields();
    void clearRadioButtons();
    void clearRadioButton(QRadioButton* btn);
    void clearTextFields();
    void setComboboxDefaultValue();
};
#endif // MAINWINDOW_H
