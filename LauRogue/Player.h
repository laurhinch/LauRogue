#pragma once

class Player
{
private:
	int health = 0;
	int maxHealth = 0;
	int damage = 0;
	int fortitude = 0;
	int strength = 0;
	int dexterity = 0;
	int speed = 0;
	int luck = 0;

	int x = 0;
	int y = 0;

public:
	
private:

public:
	Player();
	Player(const int& health, const int& fortitude, const int& strength, const int& dexterity, const int& speed, const int& luck);
	void update();
	int getHealth();
	int getMaxHealth();
	int getDamage();
	int getFortitude();
	int getStrength();
	int getDexterity();
	int getSpeed();
	int getLuck();
	void setHealth(int &n);
	void setFortitude(int &n);
	void setStrength(int &n);
	void setDexterity(int &n);
	void setSpeed(int &n);
	void setLuck(int &n);

	int getX();
	int getY();
	void setX(int &n);
	void setY(int &n);

};

