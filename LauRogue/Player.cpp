#include "Player.h"

#include <string>
#include <iostream>

using namespace std;

Player::Player() {
	system("cls");
	cout << "";
};

Player::Player(const int& health, const int& fortitude, const int& strength, const int& dexterity, const int& speed, const int& luck) {
	this->health = health;
	this->fortitude = fortitude;
	this->strength = strength;
	this->dexterity = dexterity;
	this->speed = speed;
	this->luck = luck;
	this->maxHealth = fortitude * 40;
	this->damage = strength * dexterity;
};

void Player::update() {
	
};

int Player::getHealth() { return health; };
int Player::getMaxHealth() { return maxHealth; };
int Player::getDamage() { return damage; };
int Player::getFortitude() { return fortitude; };
int Player::getStrength() { return strength; };
int Player::getDexterity() { return dexterity; };
int Player::getSpeed() { return speed; };
int Player::getLuck() { return luck; };

void Player::setHealth(int& n) {
	health = n;
};

void Player::setFortitude(int& n) {
	fortitude = n;
};

void Player::setStrength(int& n) {
	strength = n;
};

void Player::setDexterity(int& n) {
	dexterity = n;
};

void Player::setSpeed(int& n) {
	speed = n;
};

void Player::setLuck(int& n) {
	luck = n;
};

int Player::getX() { return x; };
int Player::getY() { return y; };

void Player::setX(int& n) {
	x = n;
};

void Player::setY(int& n) {
	y = n;
};
