#include "terrain.h"
#include <math.h>

Terrain::Terrain(const Point p1, const Point p2, float zMin, float zMax, int length, int width)
{
    bedrock = QVector<float>(length*width);
    soil = QVector<float>(length*width);

    a = Point(p1);
    b = Point(p2);

    this->length = length;
    this->width = width;

    for(int i = 0; i < soil.length(); i++){
        soil[i] = 0;
    }

    for(int i = 0; i < bedrock.length(); i++){
        bedrock[i] = zMin + (float)rand()/(RAND_MAX/(zMax-zMin)) ;
    }


    /*
     * public static float[][] generateSimplexNoise(int width, int height){
      float[][] simplexnoise = new float[width][height];
      float frequency = 5.0f / (float) width;

      for(int x = 0; x < width; x++){
         for(int y = 0; y < height; y++){
            simplexnoise[x][y] = (float) noise(x * frequency,y * frequency);
            simplexnoise[x][y] = (simplexnoise[x][y] + 1) / 2;   //generate values between 0 and 1
         }
      }

      return simplexnoise;
   }
     */
}

Mesh Terrain::toMesh() {

    Mesh m = Mesh();

    int i = 0;
    for (int j = 0; j < width; j++) {
        m.addVertice(Point(b.x()-a.x()*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[j]+soil[j]));
    }

    for (int i = 1; i < length; i++) {
        int j = 0;
        m.addVertice(Point(b.x()-a.x()*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[i*length]+soil[i*length]));
        for (int j = 1; j < width; j++) {
            m.addVertice(Point(b.x()-a.x()*((float)i/length)+a.x(),(b.y()-a.y())*((float)j/width)+a.y(), a.z()+bedrock[j+i*length]+soil[j+i*length]));
            m.addTriangle(Triangle((i-1)*width+j-1,i*width+j,i*width+j-1));
            m.addTriangle(Triangle((i-1)*width+j-1,(i-1)*width+j,i*width+j));
        }
    }

    return m;
}

