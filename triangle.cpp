#include "triangle.h"

Triangle::Triangle() {
    p1 = -1;
    p2 = -1;
    p3 = -1;
    adj1 = -1;
    adj2 = -1;
    adj3 = -1;
}

Triangle::Triangle(int i1, int i2, int i3)
{
    p1 = i1;
    p2 = i2;
    p3 = i3;
    adj1 = -1;
    adj2 = -1;
    adj3 = -1;
}

int Triangle::x() {
    return p1;
}

int Triangle::y() {
    return p2;
}

int Triangle::z() {
    return p3;
}

Triangle Triangle::operator =(Triangle t) {
    return Triangle(t.x(), t.y(), t.z());
}

void Triangle::setAdj1(int i) {
    adj1 = i;
}

void Triangle::setAdj2(int i) {
    adj2 = i;
}

void Triangle::setAdj3(int i) {
    adj3 = i;
}

int Triangle::getAdj(int nt) {
    switch (nt) {
    case 1 : return adj1;
    case 2 : return adj2;
    case 3 : return adj3;
    }    
}
