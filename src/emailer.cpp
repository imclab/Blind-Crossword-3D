#include "emailer.h"

#include <QString>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>

#include "utilities.h"
#include "crosswordbase.h"

#include "version.h"

const QString Emailer::sc_FeedbackEmailAddressFileLocation = QString("/Config/feedback_email_address.txt");
const QString Emailer::sc_AnswersEmailAddressFileLocation = QString("/Config/answers_email_address.txt");

bool Emailer::openFeedbackEmail()
{
    QDir dir;
    QString emailAddress = getEmailAddress(dir.absolutePath().append(sc_FeedbackEmailAddressFileLocation));

    QString emailSubject = Version::getApplicationVersionDescription().append(" feedback message");

    QString emailBody;

    emailBody.append(QString("This feedback email was sent from ").append(Version::getApplicationVersionDescription()));

    QUrl mailtoURL = QUrl(QString("mailto:").append(emailAddress)
                          .append("?subject=").append(emailSubject)
                          .append("&body=").append(emailBody));

    if(QDesktopServices::openUrl(mailtoURL))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Emailer::openSendResultsEmail(CrosswordBase& puzzle)
{
    QDir dir;
    QString emailAddress = getEmailAddress(dir.absolutePath().append(sc_AnswersEmailAddressFileLocation));

    QString emailSubject = puzzle.getTitle().append(" answers");

    QString emailBody;
    emailBody.append(puzzle.getInformation().append("%0A%0A"));

    //copy and sort by calendar date
    std::vector<CrosswordEntry> entries = puzzle.getEntries();
    std::sort(entries.begin(), entries.end(), SortByIdentifier());

    for(unsigned int i = 0; i < entries.size(); i++)
    {
        QString id = entries.at(i).getIdentifier();
        QString entryName = entries.at(i).getEntry();
        QString direction = entries.at(i).getDirection();
        QString answer = entries.at(i).getGuess().getString();

        emailBody.append(id).append(" - ").append(QUrl::toPercentEncoding(entryName))
                .append(" ").append(QUrl::toPercentEncoding(direction))
                .append(" --- ").append(QUrl::toPercentEncoding(answer))
                .append("%0A");
    }

    QUrl mailtoURL = QUrl(QString("mailto:").append(emailAddress)
                          .append("?subject=").append(emailSubject)
                          .append("&body=").append(emailBody));

    if(QDesktopServices::openUrl(mailtoURL))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Emailer::openEmail(QString address, QString subject, QString content)
{
    QUrl mailtoURL = QUrl(QString("mailto:").append(QUrl::toPercentEncoding(address))
                          .append("?subject=").append(QUrl::toPercentEncoding(subject))
                          .append("&body=").append(QUrl::toPercentEncoding(content)));

    if(QDesktopServices::openUrl(mailtoURL))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString Emailer::getEmailAddress(const QString path) const
{
    QStringList emailAddresses;
    QString emailAddress;

    Utilities::readFile(emailAddresses, path);

    if(!emailAddresses.isEmpty())
    {
        emailAddress = emailAddresses.takeFirst();
    }
    else
    {
        emailAddress = "enter@your.email_address_here.com";
    }

    return emailAddress;
}
