/*! \brief Brief description.
 *         Brief description continued.
 *
 *  Detailed description starts here.
 *
 *  \author Samuel Twidale
 *  \copyright GNU General Public License v3.0
 */

#ifndef GRAPHICALGRIDVIEW_H
#define GRAPHICALGRIDVIEW_H

#include <QGraphicsView>

class CrosswordEntry;

class GraphicalGridView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicalGridView(QWidget *parent = 0);

protected:
    virtual void wheelEvent(QWheelEvent *event);

private:
    const static double wheelZoomFactor;
    int m_NumScheduledScalings;

private slots:
    void zoomAnimationFinished();
    void scalingTime(qreal x);
};

#endif // GRAPHICALGRIDVIEW_H