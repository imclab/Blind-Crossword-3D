/*! \brief Opens a print dialog and enables a user to print crossword answers.
 *
 *  Opens a print dialog for printing a user's answers to a crossword.
 *
 *  \author Samuel Twidale
 *  \copyright GNU General Public License v3.0
 */

#ifndef PRINTER_H
#define PRINTER_H

#include <QString>

#include "crosswordbase.h"

class QTextDocument;
class QWidget;

class Printer
{
public:
    Printer(); 

    QString openPrintDialog(CrosswordBase& puzzle, QWidget* parentWidget);

private:
    static const QString sc_PostalAddressFileLocation;

    QString getPostalAddress(const QString path) const;
    QTextDocument* getPuzzleDocumentForPrinting(CrosswordBase& puzzle) const;
};

#endif // PRINTER_H
