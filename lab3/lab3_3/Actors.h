#pragma once
#include "Actor.h"
#include "ActorWithCard.h"

// HOMER
class Homer : public ActorWithCard
{
public:
	Homer(Bank& bank, Money cash);
	void Action( ActorWithCard& marge,
		ActorWithCard& burns,
		Actor& bart,
		Actor& lisa);
};

// MARGE
class Marge : public ActorWithCard
{
public:
	Marge(Bank& bank, Money cash);
	void Action(ActorWithCard& apu);
};

// BART
class Bart : public Actor
{
public:
	Bart(Money cash);
	void Action(Actor& apu);
};

// LISA
class Lisa : public Actor
{
public:
	Lisa(Money cash);
	void Action(Actor& apu);
};

// APU
class Apu : public ActorWithCard
{
public:
	Apu(Bank& bank, Money cash);
	void Action(ActorWithCard& burns);
};

// BURNS
class Burns : public ActorWithCard
{
public:
	Burns(Bank& bank, Money cash);
	void Action(ActorWithCard& homer, ActorWithCard& smithers);
};

// NELSON
class Nelson : public Actor
{
public:
	Nelson(Money cash);
	void Action(Actor& self, Actor& bart, ActorWithCard& apu);
};

// CHESTER
class Chester : public ActorWithCard
{
public:
	Chester(Bank& bank, Money cash);
	void Action(ActorWithCard& self, ActorWithCard& homer, ActorWithCard& apu);
};

// SMITHERS
class Smithers : public ActorWithCard
{
public:
	Smithers(Bank& bank, Money cash);
	void Action(ActorWithCard& apu);
};