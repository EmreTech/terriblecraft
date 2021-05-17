#include "perlin_noise.hpp"

#include <math.h>

PerlinNoise::PerlinNoise()
{
    for (int i = 0; i < 256; i++)
        p[256 + i] = p[i] = permutation.at(i);
}

PerlinNoise& PerlinNoise::getInstance()
{
    static PerlinNoise pn;
    return pn;
}

double PerlinNoise::generateNoise(float x, float y, float z)
{
    const int X = static_cast<int>(floor(x)) & 255;
    const int Y = static_cast<int>(floor(y)) & 255;
    const int Z = static_cast<int>(floor(z)) & 255;

    x -= floor(x);
    y -= floor(y);
    z -= floor(z);

    const double u = fade(x), v = fade(y), w = fade(z);

    const int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    const int B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),    
            grad(p[BA], x-1, y  , z)), 
            lerp(u, grad(p[AB], x  , y-1, z),  
            grad(p[BB], x-1, y-1, z))),
            lerp(v, lerp(u, grad(p[AA+1], x  , y  , z-1 ),  
            grad(p[BA+1], x-1, y  , z-1 )), 
            lerp(u, grad(p[AB+1], x  , y-1, z-1 ),
            grad(p[BB+1], x-1, y-1, z-1 ))));
}

double PerlinNoise::fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double PerlinNoise::grad(int hash, double x, double y, double z)
{
    int h = hash & 15;
    double u = (h < 8 ? x : y), v = (h < 4 ? y : (h == 12 || h == 14 ? x : z));
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}