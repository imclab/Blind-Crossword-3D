#include "advancedcluereader.h"

ClueReader::ClueReader() : index(0u), separator(QChar(Qt::Key_Space))
{
}

QString ClueReader::advanceWord()
{
    QStringList words = text.split(separator);

    if(index >= words.length() - 1)
    {
        index = 0;
    }
    else
    {
        index++;
    }

    return getWord();
}

QString ClueReader::getWord()
{
    QStringList words = text.split(separator);

    if(!words.at(index).isNull())
    {
        return words.at(index);
    }
    else
    {
        return "No clue selected";
    }
}

void ClueReader::setText(CrosswordEntry3D entry)
{
    index = 0;
    this->text = entry.getClue();
}