#ifndef QSQLQUERYRELATINALTABLEMODEL_H
#define QSQLQUERYRELATINALTABLEMODEL_H

#include<QSqlRelationalTableModel>
class QSqlQueryRelatinalTableModel : public QSqlRelationalTableModel
{
public:
QSqlQueryRelatinalTableModel();
void setQuery(const QSqlQuery &query);
};

#endif // QSQLQUERYRELATINALTABLEMODEL_H
