/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 *
 *  \author Samuel Twidale
 *  \copyright GNU General Public License v3.0
 */


#ifndef VERSION_H
#define VERSION_H

#include <QString>

class Version
{
public:
    static QString getApplicationVersion();
    static QString getApplicationVersionDescription();
    static QString getApplicationName();

private:
    static const QString sc_Major;
    static const QString sc_Minor;
    static const QString sc_ApplicationName;
};

#endif // VERSION_H
