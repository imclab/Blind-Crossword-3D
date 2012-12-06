#ifndef UTILITIES_H
#define UTILITIES_H

#include <QStringList>

namespace Utilities
{
    bool readFile(QStringList& linelist, QString path);

    bool existsFile(QString path);
}

#endif // UTILITIES_H