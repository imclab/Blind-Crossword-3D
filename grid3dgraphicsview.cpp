#include "grid3dgraphicsview.h"

#include <QResizeEvent>
#include <QTimeLine>
#include <QPrinter>
#include <QPrintDialog>

const double Grid3DGraphicsView::wheelZoomFactor = 1.25;

Grid3DGraphicsView::Grid3DGraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    m_NumScheduledScalings = 0;
}

void Grid3DGraphicsView::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta()/8;
    int numSteps = numDegrees/15;
    m_NumScheduledScalings += numSteps;

    if(m_NumScheduledScalings * numSteps < 0)
    {
        m_NumScheduledScalings = numSteps;
    }

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(scalingTime(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(zoomAnimationFinished()));
    anim->start();
}

void Grid3DGraphicsView::print()
{
    QPrinter printer;

    QPrintDialog* printDialog = new QPrintDialog(&printer, this);

    if(printDialog->exec() == QDialog::Accepted)
    {
        QPainter painter(&printer);
        painter.setRenderHint(QPainter::TextAntialiasing);
        painter.setRenderHint(QPainter::HighQualityAntialiasing);

        scene()->render(&painter);
    }
}

void Grid3DGraphicsView::updateSceneRect(const QRectF &rect)
{
    fitInView(rect, Qt::KeepAspectRatioByExpanding);
}

// http://qt-project.org/wiki/SmoothZoomInQGraphicsView
void Grid3DGraphicsView::zoomAnimationFinished()
{
    if(m_NumScheduledScalings > 0)
    {
        m_NumScheduledScalings--;
    }
    else
    {
        m_NumScheduledScalings++;
        sender()->~QObject();
    }
}

void Grid3DGraphicsView::scalingTime(qreal x)
{
    float factor = 1.0f + static_cast<float>(m_NumScheduledScalings) / 300.0f;
    scale(factor, factor);
}
