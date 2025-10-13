#pragma once // CoolDown.h
// ===========================
// Author: Allosker
// --
// File Name: CoolDown.h
// --
// Description: This class manages a timer that stops if the ellapsed time has reached the limit. It also contains a 'update()' function that returns the current state of the cooldown.
// ===========================


#include "umbrella headers/sfml.h"



// CoolDown manages a timer that stops if the ellapsed time has reached the limit
class CoolDown
{
public:
// Constructors & Destructors

	CoolDown(double cd)
		: cooldown{cd}
	{
		timer.reset();
	}

	CoolDown()
	{
		timer.reset();
	}


// Setters



	void setCoolDown(double cd) noexcept
	{
		cooldown = cd;
	}

	void add(double acd) noexcept
	{
		cooldown += acd;
	}


// Getters



	bool isFinished() const noexcept
	{
		return finished;
	}


// Actors



	// Returns whether the cooldown is finished or not
	virtual bool update() noexcept
	{
		if (timer.getElapsedTime().asSeconds() >= cooldown)
		{
			finished = true;
			timer.stop();
			return true;
		}
		else
		{
			if(!firstTime)
				finished = false;
			return false;
		}
	}

	void start() noexcept
	{
		timer.restart();
		firstTime = false;
	}


protected:



	Clock timer;

	double cooldown{};


	bool finished{ true };


	bool firstTime{ true };

};