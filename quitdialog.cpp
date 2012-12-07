#include "quitdialog.h"

#include <QShortcut>
#include <QVBoxLayout>
#include <QLabel>

#include "itexttospeech.h"
#include "version.h"

QuitDialog::QuitDialog(QWidget *parent) :
    QDialog(parent)
{
    setFont(QFont("Lucida Console", 20, -1, false));

    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

    m_QuitTitle = QString("Quit ").append(Version::getApplicationName()).append(" 3D?");
    m_QuitBody = "Are you sure you want to quit the program? Unsaved progress will be lost. Press Y to quit. Press N to return to the crossword puzzle.";

    m_AcceptedText = QString("Thank you for playing").append(Version::getApplicationName()).append(".");
    m_RejectedText = "Continue to solve the crossword puzzle.";

    QGridLayout *gLayout = new QGridLayout;
    gLayout->setColumnStretch(1, 2);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);


    QLabel* label = new QLabel(m_QuitBody);
    gLayout->addWidget(label);

    setWindowTitle(m_QuitTitle);

    QShortcut* quitShortcut = new QShortcut(QKeySequence(Qt::Key_Y), this);
    connect(quitShortcut, SIGNAL(activated()), this, SLOT(accept()));

    QShortcut* returnShortcut = new QShortcut(QKeySequence(Qt::Key_N), this);
    connect(returnShortcut, SIGNAL(activated()), this, SLOT(reject()));
}

QString QuitDialog::getTitleString() const
{
    return m_QuitTitle;
}

QString QuitDialog::getBodyString() const
{
    return m_QuitBody;
}

QString QuitDialog::getAcceptedText() const
{
    return m_AcceptedText;
}

QString QuitDialog::getRejectedText() const
{
    return m_RejectedText;
}
