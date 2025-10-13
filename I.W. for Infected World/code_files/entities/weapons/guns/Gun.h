#pragma once //Gun.h


#include "entities/weapons/Weapon.h"

class Bullet;


struct GunInit
{
    GunInit() = delete;

    GunInit(const EntityInit& _Einit, const LivingEntity& _lv, Vector<Bullet>& refToBulletManager, const std::pair<double, double>& _damage, float _precision, size_t _nbBullets, float _velocityBullets, double _cd, int _rec, bool _av)
        : Einit{ _Einit },
        lv{_lv},
        refManager{refToBulletManager},
        damage{_damage},
        precision{ _precision },
        nbBullets{_nbBullets},
        velocityBullets{_velocityBullets},
        cooldown{_cd},
        recoil{_rec},
        av{_av}
    {}

    const EntityInit& Einit;
    const LivingEntity& lv;
    std::pair<double, double> damage;
    float precision;
    size_t nbBullets;
    float velocityBullets;
    double cooldown;
    int recoil;
    Vector<Bullet>& refManager;
    bool av;
};



class Gun :
    public Weapon
{
public: 
// Constructors & Destructors



    Gun() = delete;

    Gun(const GunInit& Ginit);

    Gun(Gun&&) = default;

    Gun(const Gun&) = default;

    Gun& operator=(const Gun&) = default;




    void randomize(Bullet& bullet, size_t nbBllts) noexcept;

    void initializeBullets() noexcept;

    void setShootTarget(const Vec2f& target) noexcept override;


   

private:

    float precision{}, velocity{}, nbBullets{};

    Vector<Bullet>& bullets;

};

