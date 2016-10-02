#include "terrain.h"
#include <math.h>
#include <QImage>

float convo(QImage img, float x, float y) {
    /*float dx = 1-(x - (int)x);
    float dy = 1-(y - (int)y);
    //float pixel1 = (float)img.pixelColor((int)x%img.width(),(int)y%img.height()).red()*dx*dy;
    //float pixel2 = (float)img.pixelColor((int)(x+1)%img.width(),(int)y%img.height()).red()*(1.0-dx)*dy;
    //float pixel3 = (float)img.pixelColor((int)x%img.width(),(int)(y+1)%img.height()).red()*dx*(1.0-dy);
    //float pixel4 = (float)img.pixelColor((int)(x+1)%img.width(),(int)(y+1)%img.height()).red()*(1.0-dx)*(1.0-dy);

    Point p11 = Point(x, y, (float)img.pixelColor((int)x%img.width(),(int)y%img.height()).red());
    Point p21 = Point(x+1, y, (float)img.pixelColor((int)(x+1)%img.width(),(int)y%img.height()).red());
    Point p12 = Point(x, y+1, (float)img.pixelColor((int)x%img.width(),(int)(y+1)%img.height()).red());
    Point p22 = Point(x+1, y+1, (float)img.pixelColor((int)(x+1)%img.width(),(int)(y+1)%img.height()).red());

    Point p11_21 = Point();

    Point p11_21_1 = Point(x+0.5, y, (float)img.pixelColor((int)x%img.width(),(int)y%img.height()).red());
    Point p11_21_2 = Point(x+0.5, y, (float)img.pixelColor((int)(x+1)%img.width(),(int)y%img.height()).red());

    Point p11_12_1 = Point(x, y+0.5, (float)img.pixelColor((int)x%img.width(),(int)y%img.height()).red());
    Point p11_12_2 = Point(x, y+0.5, (float)img.pixelColor((int)x%img.width(),(int)(y+1)%img.height()).red());

    Point p22_21_1 = Point(x+1, y+0.5, (float)img.pixelColor((int)(x+1)%img.width(),(int)(y+1)%img.height()).red());
    Point p22_21_2 = Point(x+1, y+0.5, (float)img.pixelColor((int)x%img.width(),(int)(y+1)%img.height()).red());

    Point p22_12_1 = Point(x+0.5, y+1, (float)img.pixelColor((int)(x+1)%img.width(),(int)(y+1)%img.height()).red());
    Point p22_12_2 = Point(x+0.5, y+1, (float)img.pixelColor((int)(x+1)%img.width(),(int)y%img.height()).red());
    */

    return 0;
}

Terrain::Terrain(const Point p1, const Point p2, float zMin, float zMax, int length, int width)
{
    fprintf(stderr,"Building terrain %dx%d...\n",width,length);
    bedrock = QVector<float>(length*width);
    soil = QVector<float>(length*width);

    a = Point(p1);
    b = Point(p2);

    this->length = length;
    this->width = width;

    for(int i = 0; i < soil.length(); i++){
        soil[i] = 0;
    }

    QImage img = QImage(":/img/terrain.png");
    QVector<float> amp = QVector<float>(); amp.append(0.8);
                                    //amp.append(0.1);
                                    //amp.append(0.03);


    QVector<float> fre = QVector<float>(); fre.append(1.0);
                                    fre.append(3.0);
                                    fre.append(10.0);

    for(int i = 0; i < width; i++){
        for(int j = 0; j < length; j++){
            float z = 0;
            for (int k = 0; k < amp.length(); k++) {
                float x = i*fre[k]*img.width()/width;
                float y = j*fre[k]*img.height()/length;
                float pixel = convo(img,x,y);

                z += (pixel/255)*amp[k];

            }
            bedrock[i*width+j] = zMin + (zMax-zMin)*z;
        }
    }
}

Mesh Terrain::toMesh() {

    fprintf(stderr,"Building Mesh...\n");
    Mesh m = Mesh();

    int i = 0;
    for (int j = 0; j < width; j++) {
        m.addVertice(Point((b.x()-a.x())*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[j]+soil[j]));
    }

    for (int i = 1; i < length; i++) {
        int j = 0;
        m.addVertice(Point((b.x()-a.x())*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[i*length]+soil[i*length]));
        for (int j = 1; j < width; j++) {
            m.addVertice(Point((b.x()-a.x())*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[j+i*length]+soil[j+i*length]));
            m.addTriangle(Triangle((i-1)*width+j-1,i*width+j,i*width+j-1));
            m.addTriangle(Triangle((i-1)*width+j-1,(i-1)*width+j,i*width+j));
        }
    }

    return m;
}

