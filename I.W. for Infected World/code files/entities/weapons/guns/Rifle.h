#pragma once



#include "entities/weapons/guns/Gun.h"



class Rifle :
    public Gun
{
public:

    Rifle() = delete;

    Rifle(const GunInit& Ginit);


};

