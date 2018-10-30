#include "powerbar.h"

PowerBar::PowerBar()
{

}

void PowerBar::createSquare()
{
    unsigned int numVertices = 4;
    unsigned int numFaces = 1;

    std::unique_ptr <QVector4D[]> vertices = std::make_unique <QVector4D[]>(numVertices);
    std::unique_ptr <QVector4D[]> colors = std::make_unique <QVector4D[]>(numVertices);
    std::unique_ptr <unsigned int []> indices = std::make_unique <unsigned int []>( numFaces * 3);

    if ( numVertices > 0)
    {
        float minLim = std::numeric_limits <float>::lowest();
        float maxLim = std::numeric_limits <float>::max();
        QVector4D max(minLim, minLim, minLim, 1.0);
        QVector4D min(maxLim, maxLim, maxLim, 1.0);
        for (unsigned int i = 0; i < numVertices ; ++i)
            {
                float x , y , z;

                max.setX(std::max(max.x(), x));
                max.setY(std::max(max.y(), y));
                max.setZ(std::max(max.z(), z));
                min.setX(std::min(min.x(), x));
                min.setY(std::min(min.y(), y));
                min.setZ(std::min(min.z(), z));
                vertices[i] = QVector4D (x , y , z , 1.0);
            }
        this->midPoint = QVector3D(( min + max ) * 0.5);
        this->invDiag = 2.0 / (max - min).length();

        for (unsigned int i = 0; i < numFaces ; ++ i)
            {
                unsigned int a , b , c;
                indices [i * 3 + 0] = a;
                indices [i * 3 + 1] = b;
                indices [i * 3 + 2] = c;
            }

        for (unsigned int i = 0; i < numVertices; i++){
                colors[i] = color;
            }
}
