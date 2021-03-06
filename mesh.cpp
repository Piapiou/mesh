#include "mesh.h"
#include <math.h>
#include <limits>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <pointcirculator.h>
#include <trianglecirculator.h>
#include <triangleiterator.h>
#include <iostream>

#define PI 3.14159265


Mesh::Mesh()
{
    vertices = QVector<Point>();
    triangles = QVector<Triangle>();
}

Mesh::Mesh(const Mesh &rhs)
{
    vertices = QVector<Point>(rhs.vertices);
    triangles = QVector<Triangle>(rhs.triangles);
}

Mesh::Mesh(QString fileName) {
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        vertices = QVector<Point>();
        triangles = QVector<Triangle>();

        QString line = in.readLine();
        line = in.readLine();
        QStringList fields = line.split(" ");

        int nVert = fields.at(0).toInt();
        int nPol = fields.at(1).toInt();


        for (int i = 0; i < nVert; i++) {
            line = in.readLine();
            fields = line.split(" ");
            vertices.append(Point(fields.at(0).toFloat(),fields.at(1).toFloat(),fields.at(2).toFloat()));
        }


        for (int i = 0; i < nPol; i++) {
            line = in.readLine();
            fields = line.split(" ");
            triangles.append(Triangle(fields.at(1).toInt(),fields.at(3).toInt(),fields.at(2).toInt()));
        }
   } else {
        printf("Error file open\n");
   }

}

Mesh Mesh::makeBox(const Point p1, const Point p2) {

    Mesh m = Mesh();
    m.vertices.append(Point(p1));
    m.vertices.append(Point(p1.x(), p1.y(), p2.z()));
    m.vertices.append(Point(p1.x(), p2.y(), p1.z()));
    m.vertices.append(Point(p1.x(), p2.y(), p2.z()));
    m.vertices.append(Point(p2.x(), p1.y(), p1.z()));
    m.vertices.append(Point(p2.x(), p1.y(), p2.z()));
    m.vertices.append(Point(p2.x(), p2.y(), p1.z()));
    m.vertices.append(Point(p2));

    m.triangles.append(Triangle(0,3,1));
    m.triangles.append(Triangle(0,2,3));
    m.triangles.append(Triangle(2,7,3));
    m.triangles.append(Triangle(2,6,7));
    m.triangles.append(Triangle(0,6,2));
    m.triangles.append(Triangle(0,4,6));
    m.triangles.append(Triangle(3,5,1));
    m.triangles.append(Triangle(3,7,5));
    m.triangles.append(Triangle(6,5,7));
    m.triangles.append(Triangle(6,4,5));
    m.triangles.append(Triangle(4,1,5));
    m.triangles.append(Triangle(4,0,1));

    return m;
}

Mesh Mesh::makeSphere(const Point center, float rayon, int pointByArc) {
    Mesh m = Mesh();
    float step = PI/pointByArc;
    float is = -PI/2;
    float ib = 0;


    for(is = -PI/2; is < PI/2+step; is += step) {
        m.vertices.append(Point(rayon*cos(ib)*(cos(is))+center.x(),
                                  rayon*sin(ib)*(cos(is))+center.y(),
                                  rayon*sin(is)+center.z()));
    }

    int bigLoop = 0;
    int smallLoop = 0;

    for (ib = step; ib <= 2*PI; ib += step) {
        is = -PI/2;
        m.vertices.append(Point(rayon*cos(ib)*(cos(is))+center.x(),
                                  rayon*sin(ib)*(cos(is))+center.y(),
                                  rayon*sin(is)+center.z()));

        for(is = -PI/2+step; is < PI/2+step; is += step) {

            m.vertices.append(Point(rayon*cos(ib)*(cos(is))+center.x(),
                                      rayon*sin(ib)*(cos(is))+center.y(),
                                      rayon*sin(is)+center.z()));

            m.triangles.append(Triangle((smallLoop)+(bigLoop)*(pointByArc+1), (smallLoop+1)+(bigLoop+1)*(pointByArc+1), (smallLoop)+(bigLoop+1)*(pointByArc+1)));
            m.triangles.append(Triangle((smallLoop)+(bigLoop)*(pointByArc+1), (smallLoop+1)+(bigLoop)*(pointByArc+1), (smallLoop+1)+(bigLoop+1)*(pointByArc+1)));

            smallLoop++;
        }
        smallLoop = 0;
        bigLoop++;
    }

    for(is = -PI/2; is < PI/2; is += step) {
        m.triangles.append(Triangle((smallLoop)+(bigLoop)*(pointByArc+1), (smallLoop+1), (smallLoop)));
        m.triangles.append(Triangle((smallLoop)+(bigLoop)*(pointByArc+1), (smallLoop+1)+(bigLoop)*(pointByArc+1), (smallLoop+1)));
        smallLoop++;
    }

    return m;
}

bool pointIsLeftToVector(Point p1, Point p2, Point i) {
    return ((p2.x()-p1.x())*(i.y()-p1.y())-
            (p2.y()-p1.y())*(i.x()-p1.x()) > 0);
}

Mesh Mesh::makePlanFromTxt(const QString fileName) {
    Mesh m = Mesh();

    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        m.vertices = QVector<Point>();
        m.triangles = QVector<Triangle>();
        QString line = in.readLine();
        int nPoint = line.toInt();
        QStringList fields;

        for (int i = 0; i < nPoint; i++) {
            line = in.readLine();
            fields = line.split(" ");
            m.vertices.append(Point(fields.at(0).toFloat(),fields.at(1).toFloat(),0));
        }

        m.addTriangle(Triangle(0,1,2));
        m.addTriangle(Triangle(-1,1,0));
        m.addTriangle(Triangle(-1,2,1));
        m.addTriangle(Triangle(-1,0,2));


        printf("Start triangulation\n");
        for (int i = 3; i < nPoint; i++) {
            printf("Add point (%f,%f,%f)\n",m.vertices[i].x(),m.vertices[i].y(),m.vertices[i].z());
            bool pointInside = true;
            TriangleCirculator tc = TriangleCirculator(m,-1);
            QVector<Triangle> vt = QVector<Triangle>(m.triangles);
            while(tc.hasNext()) {
                int tri = tc.next();
                Triangle t = vt[tri];
                printf(" -> (%d %d %d)", t.x(), t.y(),t.z());
                if (!pointIsLeftToVector(m.vertices[t.y()],m.vertices[t.z()],m.vertices[i])) {
                    printf("*");
                    m.addTriangle(Triangle(t.z(),i,t.y()));
                    pointInside = false;
                }
            }

            printf("\n");

            if (!pointInside) {
                m.removePoint(-1);
                m.setAdjTri();
                for (int tri = 0; tri < m.triangles.length(); tri++) {
                    if (m.triangles[tri].x() != -1 && m.triangles[tri].y() != -1 && m.triangles[tri].z() != -1) {
                        if (m.triangles[tri].getAdj(1) == -1) {
                            m.addTriangle(Triangle(-1,m.triangles[tri].z(),m.triangles[tri].y()));
                            m.setAdjTri();
                        }
                        if (m.triangles[tri].getAdj(2) == -1) {
                            m.addTriangle(Triangle(-1,m.triangles[tri].x(),m.triangles[tri].z()));
                            m.setAdjTri();
                        }
                        if (m.triangles[tri].getAdj(3) == -1) {
                            m.addTriangle(Triangle(-1,m.triangles[tri].y(),m.triangles[tri].x()));
                            m.setAdjTri();
                        }
                    }
                }
            }

            // Cas du triangle interne
            if (pointInside) {
                for (int tri = 0; tri < m.triangles.length(); tri++) {
                    Triangle t = m.getTriangles()->at(tri);
                    if (t.x() != -1 && t.y() != -1 && t.z() != -1) {
                        if (pointIsLeftToVector(m.vertices[t.y()],m.vertices[t.x()],m.vertices[i])
                         && pointIsLeftToVector(m.vertices[t.z()],m.vertices[t.y()],m.vertices[i])
                         && pointIsLeftToVector(m.vertices[t.x()],m.vertices[t.z()],m.vertices[i])) {
                            m.addTriangle(Triangle(i,t.x(),t.y()));
                            m.addTriangle(Triangle(i,t.y(),t.z()));
                            m.addTriangle(Triangle(i,t.z(),t.x()));
                            m.removeTriangle(tri);
                            break;
                        }
                    }
                }
            }


            // Affichage
            for (int h = 0; h < m.triangles.length(); h++) {
                if (m.triangles[h].x() != -1 && m.triangles[h].y() != -1 && m.triangles[h].z() != -1)
                    printf("%d(%f,%f) %d(%f,%f) %d(%f,%f)\n",
                       m.triangles[h].x(),m.vertices[m.triangles[h].x()].x(),m.vertices[m.triangles[h].x()].y(),
                       m.triangles[h].y(),m.vertices[m.triangles[h].y()].x(),m.vertices[m.triangles[h].y()].y(),
                       m.triangles[h].z(),m.vertices[m.triangles[h].z()].x(),m.vertices[m.triangles[h].z()].y());
                else
                    printf("%d %d %d\n",m.triangles[h].x(),m.triangles[h].y(),m.triangles[h].z());
            }

        }
        m.removePoint(-1);
        for (int x = 0; x < m.triangles.length(); x++) {
            printf("%d(%f,%f) %d(%f,%f) %d(%f,%f)\n",
                   m.triangles[x].x(),m.vertices[m.triangles[x].x()].x(),m.vertices[m.triangles[x].x()].y(),
                   m.triangles[x].y(),m.vertices[m.triangles[x].y()].x(),m.vertices[m.triangles[x].y()].y(),
                   m.triangles[x].z(),m.vertices[m.triangles[x].z()].x(),m.vertices[m.triangles[x].z()].y());
        }

        m.lawsonFlip();
    } else {
        printf("Error file open\n");
    }

    return m;
}

Point orthocenter(Point A, Point B, Point C) {

   double D = 2*(A.x()*(B.y()-C.y())+B.x()*(C.y()-A.y())+C.x()*(A.y()-B.y()));

   double X=((A.x()*A.x()+A.y()*A.y())*(B.y()-C.y())
            +(B.x()*B.x()+B.y()*B.y())*(C.y()-A.y())
            +(C.x()*C.x()+C.y()*C.y())*(A.y()-B.y()))/D;
   double Y=((A.x()*A.x()+A.y()*A.y())*(C.x()-B.x())
            +(B.x()*B.x()+B.y()*B.y())*(A.x()-C.x())
            +(C.x()*C.x()+C.y()*C.y())*(B.x()-A.x()))/D;

    return Point(X,Y,0);
}

bool dansCercle(Point p, Point q, Point r, Point s) {
    Point O = orthocenter(p,q,r);
    std::cout << O.x() << " - " << O.y() << '\n' << std::flush;
    std::cout << p.x() << " - " << p.y() << " >> " << (p.x()-O.x())*(p.x()-O.x())+(p.y()-O.y())*(p.y()-O.y()) << '\n' << std::flush;
    std::cout << q.x() << " - " << q.y() << " >> " << (q.x()-O.x())*(q.x()-O.x())+(q.y()-O.y())*(q.y()-O.y()) << '\n' << std::flush;
    std::cout << r.x() << " - " << r.y() << " >> " << (r.x()-O.x())*(r.x()-O.x())+(r.y()-O.y())*(r.y()-O.y()) << '\n' << std::flush;
    std::cout << s.x() << " - " << s.y() << " >> " << (s.x()-O.x())*(s.x()-O.x())+(s.y()-O.y())*(s.y()-O.y()) << '\n' << std::flush;
    std::cout << ((p.x()-O.x())*(p.x()-O.x())+(p.y()-O.y())*(p.y()-O.y()) > (s.x()-O.x())*(s.x()-O.x())+(s.y()-O.y())*(s.y()-O.y())) << '\n' << std::flush;

    return ((p.x()-O.x())*(p.x()-O.x())+(p.y()-O.y())*(p.y()-O.y()) > (s.x()-O.x())*(s.x()-O.x())+(s.y()-O.y())*(s.y()-O.y()));
}

QPair<int,int> pointCommun(Triangle t1, Triangle t2) {
    if (t1.x() != t2.x() && t1.x() != t2.y() && t1.x() != t2.z())
        return QPair<int,int>(t1.y(),t1.z());
    if (t1.y() != t2.x() && t1.y() != t2.y() && t1.y() != t2.z())
        return QPair<int,int>(t1.z(),t1.x());
    return QPair<int,int>(t1.x(),t1.y());
}

QPair<int,int> pointExclu(Triangle t1, Triangle t2) {
    QPair<int,int> result = QPair<int,int>();
    if (t1.x() != t2.x() && t1.x() != t2.y() && t1.x() != t2.z())
        result.first = t1.x();
    else if (t1.y() != t2.x() && t1.y() != t2.y() && t1.y() != t2.z())
        result.first = t1.y();
    else
        result.first = t1.z();

    if (t2.x() != t1.x() && t2.x() != t1.y() && t2.x() != t1.z())
        result.second = t2.x();
    else if (t2.y() != t1.x() && t2.y() != t1.y() && t2.y() != t1.z())
        result.second = t2.y();
    else
        result.second = t2.z();
    return result;
}

void Mesh::flip(int p1, int p2) {
    int i = 0;
    int j = -1;
    while (j == -1 && i < triangles.size()) {
        Triangle t = triangles[i];
        if (t.have(p1,p2) && !t.have(-1)) {
            if (t.getAdj(1) != -1) {
                Triangle ta = triangles[t.getAdj(1)];
                if (ta.have(p1,p2)) {
                    j = t.getAdj(1);
                }
            }
            if (t.getAdj(2) != -1) {
                Triangle tb = triangles[t.getAdj(2)];
                if (j == -1 && tb.have(p1,p2)) {
                    j = t.getAdj(2);
                }
            }
            if (t.getAdj(3) != -1) {
                Triangle tc = triangles[t.getAdj(3)];
                if (j == -1 && tc.have(p1,p2)) {
                    j = t.getAdj(3);
                }
            }
        }
        if (j == -1)
            i++;
    }

    if (j != -1) {
        Triangle t1 = triangles[i];
        Triangle t2 = triangles[j];
        QPair<int,int> out = pointExclu(t1,t2);

        std::cout << t1.x() << " - " << t1.y() << " - " << t1.z() << "\n" << std::flush;
        std::cout << t2.x() << " - " << t2.y() << " - " << t2.z() << "\n" << std::flush;
        std::cout << out.first << " - " << out.second << " - " << p1 << " - " << p2 << "\n" << std::flush;

        if ((t1.x() == p1 && t1.y() == p2)
          ||(t1.y() == p1 && t1.z() == p2)
          ||(t1.z() == p1 && t1.x() == p2)){
            int x = p1;
            p1 = p2;
            p2 = x;
        }

        if (j > i)
            triangles.remove(j);
        triangles.remove(i);
        if (j < i)
            triangles.remove(j);



//            if (liste.length() < 15) break;

        triangles.append(Triangle(out.second,p1,out.first));
        triangles.append(Triangle(out.first,p2,out.second));
        setAdjTri();
    }
}

void Mesh::lawsonFlip() {
    bool noChange;
    do {
        noChange = true;
        setAdjTri();
        QVector<QPair<int,int>> liste = QVector<QPair<int,int>>();
        std::cout << "Start lawson flip\n" << std::flush;
        for (int i = 0; i < triangles.length(); i++) {
            Triangle t = triangles[i];
            if (i < t.getAdj(1)) {
                Triangle ta = triangles[t.getAdj(1)];
                if (dansCercle(vertices[ta.x()],vertices[ta.y()],vertices[ta.z()],vertices[t.x()])) {
                    liste.append(QPair<int,int>(t.y(),t.z()));
                    noChange = false;
                }
            }
            if (i < t.getAdj(2)) {
                Triangle ta = triangles[t.getAdj(2)];
                if (dansCercle(vertices[ta.x()],vertices[ta.y()],vertices[ta.z()],vertices[t.y()])) {
                    liste.append(QPair<int,int>(t.z(),t.x()));
                    noChange = false;
                }
            }
            if (i < t.getAdj(3)) {
                Triangle ta = triangles[t.getAdj(3)];
                if (dansCercle(vertices[ta.x()],vertices[ta.y()],vertices[ta.z()],vertices[t.z()])) {
                    liste.append(QPair<int,int>(t.x(),t.y()));
                    noChange = false;
                }
            }
        }
        while (liste.length() > 0) {
            std::cout << liste[0].first << ',' << liste[0].second << '\n' << std::flush;
            flip(liste[0].first,liste[0].second);

            liste.pop_front();
        }
    } while(!noChange);
    std::cout << "End lawson flip\n" << std::flush;

}

Mesh Mesh::makeCylinder(const Point center, float height, float rayon, int pointByArc) {
    Mesh m = Mesh();
    m.vertices.append(Point(center));
    m.vertices.append(Point(center.x(),center.y(),center.z()+height));

    float step = PI/pointByArc;
    int current = 2;

    for (float i = step; i < 2*PI; i += step) {
        m.vertices.append(Point(rayon*cos(i)+center.x(), rayon*sin(i)+center.y(), center.z()));
        m.vertices.append(Point(rayon*cos(i)+center.x(), rayon*sin(i)+center.y(), center.z()+height));
        m.triangles.append(Triangle(0,current,current+2));
        m.triangles.append(Triangle(current,current+3,current+2));
        m.triangles.append(Triangle(current,current+1,current+3));
        m.triangles.append(Triangle(1,current+3,current+1));
        current += 2;
    }


    m.vertices.append(Point(rayon*cos(2*PI)+center.x(), rayon*sin(2*PI)+center.y(), center.z()));
    m.vertices.append(Point(rayon*cos(2*PI)+center.x(), rayon*sin(2*PI)+center.y(), center.z()+height));
    m.triangles.append(Triangle(0,current,2));
    m.triangles.append(Triangle(current,3,2));
    m.triangles.append(Triangle(current,current+1,3));
    m.triangles.append(Triangle(1,3,current+1));

    return m;
}

Mesh Mesh::makeCone(const Point center, float height, float rayon, int pointByArc) {
    Mesh m = Mesh();
    m.vertices.append(Point(center));
    m.vertices.append(Point(center.x(),center.y(),center.z()+height));

    float step = PI/pointByArc;
    int current = 2;

    for (float i = step; i < 2*PI; i += step) {
        m.vertices.append(Point(rayon*cos(i)+center.x(), rayon*sin(i)+center.y(), center.z()));
        m.triangles.append(Triangle(0,current,current+1));
        m.triangles.append(Triangle(1,current+1,current));
        current += 1;
    }


    m.vertices.append(Point(rayon*cos(2*PI)+center.x(), rayon*sin(2*PI)+center.y(), center.z()));
    m.triangles.append(Triangle(0,current,2));
    m.triangles.append(Triangle(1,2,current));

    return m;
}

Mesh Mesh::operator=(const Mesh &rhs)
{    
    Mesh m = Mesh();
    m.vertices = QVector<Point>(rhs.vertices);
    m.triangles = QVector<Triangle>(rhs.triangles);
    return m;
}

Point Mesh::getMiddle() {
    float x = 0;
    float y = 0;
    float z = 0;
    for (int i = 0; i < vertices.length(); i++) {
        x += vertices[i].x(); y += vertices[i].y(); z += vertices[i].z();
    }

    return Point(x/vertices.length(),y/vertices.length(),z/vertices.length());
}

QVector<Point> * Mesh::getVertices() {
    return &vertices;
}

QVector<Triangle> * Mesh::getTriangles() {
    return &triangles;
}

void Mesh::addVertice(Point v) {
    vertices.append(Point(v));
}

void Mesh::addTriangle(Triangle t) {
    triangles.append(Triangle(t));
}


float min(float a, float b) {
    return (b<a)?b:a;
}

float Mesh::distance(const Point p) {
    float result = std::numeric_limits<float>::max();
    for (int i = 0; i < vertices.length(); i++) {
        result = min(result, pow(p.x()-vertices[i].x(),2)+pow(p.y()-vertices[i].y(),2)+pow(p.z()-vertices[i].z(),2));
    }
    return sqrt(result);
}

void Mesh::scale(const Point scale) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX((vertices[i].x()-middle.x())*scale.x()+middle.x());
       vertices[i].setY((vertices[i].y()-middle.y())*scale.y()+middle.y());
       vertices[i].setZ((vertices[i].z()-middle.z())*scale.z()+middle.z());
    }
}

void Mesh::scale(float scale) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX((vertices[i].x()-middle.x())*scale+middle.x());
       vertices[i].setY((vertices[i].y()-middle.y())*scale+middle.y());
       vertices[i].setZ((vertices[i].z()-middle.z())*scale+middle.z());
    }
}

void Mesh::rotate(const QMatrix4x4 m) {
    const Point middle = getMiddle();

    for (int i = 0; i < vertices.length(); i++) {
       vertices[i].setX(vertices[i].x()-middle.x());
       vertices[i].setY(vertices[i].y()-middle.y());
       vertices[i].setZ(vertices[i].z()-middle.z());
       vertices[i] = Point(m * vertices[i]);
       vertices[i].setX(vertices[i].x()+middle.x());
       vertices[i].setY(vertices[i].y()+middle.y());
       vertices[i].setZ(vertices[i].z()+middle.z());
    }
}

void Mesh::translate(const Point v) {
    for (int i = 0; i < vertices.length(); i++) {
       vertices[i] += v;
    }
}

void Mesh::merge(Mesh m) {
    int mLength = vertices.length();
    vertices.append(m.vertices);
    for (int i = 0; i < m.triangles.length(); i++) {
        triangles.append(Triangle(m.triangles[i].x()+mLength, m.triangles[i].y()+mLength, m.triangles[i].z()+mLength));
    }
}

void Mesh::setAdjTri() {

    QMap<QPair<int,int>,QPair<int,int>> mmap = QMap<QPair<int,int>,QPair<int,int>>();
    for (int i = 0; i < triangles.length(); i++) {
        triangles[i].setAdj1(-1);
        triangles[i].setAdj2(-1);
        triangles[i].setAdj3(-1);
        QPair<int,int> t3 = mmap.find(QPair<int,int>(triangles[i].x(),triangles[i].y())).value();
        if (!t3.second)
            t3 = mmap.find(QPair<int,int>(triangles[i].y(),triangles[i].x())).value();
        if (t3.second) {
            triangles[i].setAdj3(t3.first);
            switch (t3.second) {
            case 1 : triangles[t3.first].setAdj1(i); break;
            case 2 : triangles[t3.first].setAdj2(i); break;
            default : triangles[t3.first].setAdj3(i);
            }
        } else {
            mmap.insert(QPair<int,int>(triangles[i].x(),triangles[i].y()),QPair<int,int>(i,3));
        }

        QPair<int,int> t2 = mmap.find(QPair<int,int>(triangles[i].x(),triangles[i].z())).value();
        if (!t2.second)
            t2 = mmap.find(QPair<int,int>(triangles[i].z(),triangles[i].x())).value();

        if (t2.second) {
            triangles[i].setAdj2(t2.first);
            switch (t2.second) {
            case 1 : triangles[t2.first].setAdj1(i); break;
            case 2 : triangles[t2.first].setAdj2(i); break;
            default : triangles[t2.first].setAdj3(i);
            }
        } else {
            mmap.insert(QPair<int,int>(triangles[i].x(),triangles[i].z()),QPair<int,int>(i,2));
        }


        QPair<int,int> t1 = mmap.find(QPair<int,int>(triangles[i].y(),triangles[i].z())).value();
        if (!t1.second)
            t1 = mmap.find(QPair<int,int>(triangles[i].z(),triangles[i].y())).value();

        if (t1.second) {
            triangles[i].setAdj1(t1.first);
            switch (t1.second) {
            case 1 : triangles[t1.first].setAdj1(i); break;
            case 2 : triangles[t1.first].setAdj2(i); break;
            default : triangles[t1.first].setAdj3(i);
            }
        } else {
            mmap.insert(QPair<int,int>(triangles[i].y(),triangles[i].z()),QPair<int,int>(i,1));
        }


    }

}

void Mesh::toOBJ(QString filePath) {
    fprintf(stderr,"Export obj...\n");
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream( &file );
        stream << "o mesh" << endl << endl;
        for (int i = 0; i < vertices.length(); i++) {
            stream << "v " << vertices[i].x() << " " << vertices[i].y() << " " << vertices[i].z() << endl;
        }

        for (int i = 0; i < triangles.length(); i++) {
            stream << "f " << triangles[i].x()+1 << "// " << triangles[i].y()+1 << "// " << triangles[i].z()+1 << "//" << endl;
        }
    } else {
        printf("Error file open\n");
    }
}

void Mesh::removePoint(int i) {
    for (int x = 0; x < triangles.length(); x++) {
        if (triangles[x].x() == i || triangles[x].y() == i || triangles[x].z() == i)
            triangles.remove(x--);
    }
    if (i != -1)
        vertices.remove(i);
}

void Mesh::removeTriangle(int i) {
    triangles.remove(i);
}

Mesh::~Mesh()
{

}
