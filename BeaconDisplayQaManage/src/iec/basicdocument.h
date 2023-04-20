#ifndef BASICDOCUMENT_H
#define BASICDOCUMENT_H
#include"userdefine.h"
#include <QWidget>

class BasicDocument : public QWidget
{
    Q_OBJECT
public:
    explicit BasicDocument(QWidget *parent = nullptr);
    StIecReport* getDocument();

protected:
   StIecReport* mp_stIecReport;
private:

      BasicDocument* mp_Parent;

signals:

public slots:
};

#endif // BASICDOCUMENT_H
