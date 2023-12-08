/*
 * File: ConiferousTree.h
 * Author: Jared McKneely
 * Description: Implementation file for the ConiferousTree class, a child
 *              class of the BaseObject abstract class.
 */

#ifndef _CONIFEROUS_TREE_H
#define _CONIFEROUS_TREE_H

#include "BaseObject.h"
#include "WeatherData.h"
#include "Utilities.h"

class ConiferousTree : public BaseObject {
  public:
    ConiferousTree();
    ~ConiferousTree();
    void setTextureFactor(float tf);
    void setTrunkTexture(unsigned int *tex);
    void setLeafTexture(unsigned int *tex);
    void setSnowyLeafTexture(unsigned int *tex);
    void draw();
  protected:
    // Protected member functions
    void drawTrunkSection(double x1, double x2,
                          double y1, double y2,
                          double z1, double z2,
                          double ph);
    void drawLeaves(double x1, double x2,
                    double y1, double y2,
                    double z1, double z2,
                    double ph);

    // Geometry variables
    const int d = 30;

    // Texture variables
    float texFact = 1.0;
    unsigned int *treeTrunkTexture;
    unsigned int *leafTexture;
    unsigned int *snowyLeafTexture;

    // Color & lighting variables
    float colorArray[4] = {1.0, 1.0, 1.0, 1.0};
    float specularArray[4] = {0.25, 0.25, 0.25, 1.0};
    float emissionArray[4] = {0.0, 0.0, 0.0, 1.0};
    float diffuseArray[4] = {0.1, 0.1, 0.1, 1.0};

    // Objects
    WeatherData* data = nullptr;
};

#endif
