#include "hint.h"

Hint::Hint()
{
}

Hint::Hint(QString hint)
{
    m_Hint = hint;
}

QString Hint::getString()
{
    return m_Hint;
}
