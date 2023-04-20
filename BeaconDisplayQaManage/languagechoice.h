#ifndef LANGUAGECHOICE_H
#define LANGUAGECHOICE_H

#include <QDialog>

namespace Ui {
class LanguageChoice;
}
typedef enum
{
    English,
    Chinese
}EmLanguageType;

extern int nLanguageType;
class LanguageChoice : public QDialog
{
    Q_OBJECT

public:
    explicit LanguageChoice(QWidget *parent = 0);
    ~LanguageChoice();

private slots:
    void on_OkButton_clicked();
signals:
    void emitSelectLanguage(int);
private:
    Ui::LanguageChoice *ui;
};

#endif // LANGUAGECHOICE_H
