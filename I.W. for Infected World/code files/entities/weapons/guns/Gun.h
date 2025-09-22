#pragma once
#include "entities/weapons/Weapon.h"




struct GunInit
{
    GunInit() = delete;

    GunInit(const EntityInit& _Einit, const MoveableEntity& _mv, double _damage, float _randomizer, double _range, size_t _nbBullets, float _velocityBullets, double _cd, int _rec)
        : Einit{ _Einit },
        mv{_mv},
        damage{_damage},
        randomizer{ _randomizer },
        range{_range},
        nbBullets{_nbBullets},
        velocityBullets{_velocityBullets},
        cooldown{_cd},
        recoil{_rec}
    {}

    const EntityInit& Einit;
    const MoveableEntity& mv;
    double damage;
    float randomizer;
    double range;
    size_t nbBullets;
    float velocityBullets;
    double cooldown;
    int recoil;
};



class Gun :
    public Weapon
{
public: 
// Constructors & Destructors



    Gun() = delete;

    Gun(const GunInit& Ginit);


};

