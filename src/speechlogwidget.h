/*! \brief A widget that displays a log of the text that the text to speech engine is passed. For debugging purposes.
 *
 *
 *  \author Samuel Twidale
 *  \copyright GNU General Public License v3.0
 */


#ifndef SPEECHLOGWIDGET_H
#define SPEECHLOGWIDGET_H

#include <QTextEdit>

class SpeechLogWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit SpeechLogWidget(QObject *parent = 0);

protected:
    void focusInEvent(QFocusEvent *e);
};

#endif // SPEECHLOGWIDGET_H
