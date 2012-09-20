#include "grid3dgraphicsscene.h"

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>

#include "graphicsgriditem.h"
#include "lettergrid.h"


Grid3DGraphicsScene::Grid3DGraphicsScene(LetterGrid* letters, std::vector<CrosswordEntry3D>* entries, QPixmap* backgroundImage) :
    QGraphicsScene(), m_RefGrid(letters), m_RefCrosswordEntries(entries), m_RefBackgroundImage(backgroundImage), m_PreviousSelectedCrosswordEntryNumber(1u), m_CurrentlySelectedCrosswordEntryNumber(1u)
{
}

void Grid3DGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->drawPixmap(rect.left(), rect.top(), rect.width(), rect.height(), *m_RefBackgroundImage);
}

void Grid3DGraphicsScene::build2DGrid(unsigned int xDim, unsigned int yDim, uivec3 offset, unsigned int gridNumber)
{
    QGraphicsItemGroup* grid = new QGraphicsItemGroup();
    grid->setFlag(QGraphicsItem::ItemIsMovable);

    for(unsigned int y = 0; y < yDim; y++)
    {
        for(unsigned int x = 0; x < xDim; x++)
        {
            uivec3 index = uivec3(x, y, gridNumber);
            Letter* letter = m_RefGrid->getRefLetterAt(index);

            GraphicsGridItem* item = new GraphicsGridItem(letter, gridNumber);
            item->setPos(QPointF(x * GraphicsGridItem::sc_Size + offset.getX(), y * GraphicsGridItem::sc_Size));

            if(letter->getChar() != QChar())
            {
                item->setColor(Qt::white);
            }
            else
            {
                item->setColor(QColor(20, 20, 20));
            }

            item->setParentItem(grid);

            m_GraphicsGridItems.push_back(item);
            addItem(item);
            grid->addToGroup(item);
        }
    }

    addItem(grid);
}

void Grid3DGraphicsScene::buildPuzzleGrid()
{
    this->clear();
    m_GraphicsGridItems.clear();

    m_CurrentlySelectedCrosswordEntryNumber = 1;
    m_PreviousSelectedCrosswordEntryNumber = 1;

    for(unsigned int z = 0; z < m_RefGrid->getDimensions().getZ(); z++)
    {
        build2DGrid(m_RefGrid->getDimensions().getX(), m_RefGrid->getDimensions().getY(), uivec3(z * (m_RefGrid->getDimensions().getX() + 1) * GraphicsGridItem::sc_Size, 0, 0), z);
    }

    for(unsigned int i = 0; i < m_RefCrosswordEntries->size(); i++)
    {
        if(m_RefCrosswordEntries->at(i).getDirection() != Directions::WINDING)
        {
            unsigned int entryNumber = m_RefCrosswordEntries->at(i).getEntryString().toUInt();
            uivec3 startingPos =  m_RefCrosswordEntries->at(i).getStartingPosition();

            uivec3 index = m_RefCrosswordEntries->at(i).getStartingPosition();

            GraphicsGridItem* item = m_GraphicsGridItems.at(index.toGridIndex(m_RefGrid->getDimensions()));
            item->setCrosswordEntryNumber(entryNumber);
        }
    }

    setSceneRect(itemsBoundingRect());

    repaintPuzzleGrid();
}

void Grid3DGraphicsScene::repaintPuzzleGrid()
{
    update();
}

void Grid3DGraphicsScene::highlightSelection(CrosswordEntry3D selectedCrosswordEntry)
{
    if(selectedCrosswordEntry.getDirection() != Directions::WINDING)
    {
        m_CurrentlySelectedCrosswordEntryNumber = selectedCrosswordEntry.getEntryString().toUInt();

        for(unsigned int i = 0; i < m_GraphicsGridItems.size(); i++)
        {
            GraphicsGridItem* currentItem = m_GraphicsGridItems.at(i);

            if(currentItem->getCrosswordEntryNumber().toUInt() == m_PreviousSelectedCrosswordEntryNumber)
            {
                currentItem->setColor(Qt::white);
            }

            if(currentItem->getCrosswordEntryNumber().toUInt() == selectedCrosswordEntry.getEntryString().toUInt())
            {
                currentItem->setColor(Qt::cyan);
            }
        }

        update();

        m_PreviousSelectedCrosswordEntryNumber = selectedCrosswordEntry.getEntryString().toUInt();
    }
}
