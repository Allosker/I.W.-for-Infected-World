#pragma once //Gun.h


#include "entities/weapons/Weapon.h"

class Bullet;


struct GunInit
{
    GunInit() = delete;

    GunInit(const EntityInit& _Einit, const LivingEntity& _lv, Vector<Bullet>& refToBulletManager, double _damage, float _precision, double _range, size_t _nbBullets, float _velocityBullets, double _cd, int _rec)
        : Einit{ _Einit },
        lv{_lv},
        refManager{refToBulletManager},
        damage{_damage},
        precision{ _precision },
        range{_range},
        nbBullets{_nbBullets},
        velocityBullets{_velocityBullets},
        cooldown{_cd},
        recoil{_rec}
    {}

    const EntityInit& Einit;
    const LivingEntity& lv;
    double damage;
    float precision;
    double range;
    size_t nbBullets;
    float velocityBullets;
    double cooldown;
    int recoil;
    Vector<Bullet>& refManager;
};



class Gun :
    public Weapon
{
public: 

    friend class Bullet;
// Constructors & Destructors



    Gun() = delete;

    Gun(const GunInit& Ginit);

    Gun(Gun&&) = default;

    Gun(const Gun&) = default;

    Gun& operator=(const Gun&) = default;




    void randomize(Bullet& bullet) noexcept;

    void initializeBullets() noexcept;

    void setShootTarget(const Vec2f& target) noexcept override;


private:

    float precision{}, velocity{}, nbBullets{}, maxDist{};

    Vector<Bullet>& bullets;

};

