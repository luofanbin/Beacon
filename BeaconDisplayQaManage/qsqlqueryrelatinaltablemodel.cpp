#include "qsqlqueryrelatinaltablemodel.h"

QSqlQueryRelatinalTableModel::QSqlQueryRelatinalTableModel()
{

}
void QSqlQueryRelatinalTableModel::setQuery(const QSqlQuery &query)
{
    QSqlRelationalTableModel::setQuery(query);
}
