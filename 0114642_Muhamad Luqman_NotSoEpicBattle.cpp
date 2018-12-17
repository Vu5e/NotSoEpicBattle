#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Player
{
	int playerNumber;
	int health;
	int remainingHealth;
	int attack;
	int defense;
	float speed;
	char classType;
	bool assignedStats;

	Player(int j);
	void Action(Player &opponent);
	void Attack(Player &opponent);
	void Heal();
	void Dodge();
};

int InputConversion(string input);
bool ValidatingInput(string input);
void DisplayTitle();
void InitPlayerStats(Player &target, int health, int attack, int defense, float speed, char classType);
void JobAssign(Player &target);
void StatsAssign(Player &target);
void DisplayStatus(Player target);
void DisplayAllStatus(Player target01, Player target02);

int main()
{
	while(true)
	{
		srand(time(NULL));
		Player player01(1);
		Player player02(2);
		
		JobAssign(player01);
		do
		{
			system("cls");
			StatsAssign(player01);
		}
		while(!player01.assignedStats);
	
		JobAssign(player02);
		do
		{
			system("cls");
			StatsAssign(player02);
		}
		while(!player02.assignedStats);
		
		system("cls");
		DisplayTitle();
		DisplayAllStatus(player01, player02);
		system("pause");
		
		while(true)
		{
			if(player01.remainingHealth <= 0 || player02.remainingHealth <= 0)
				break;
			
			if (player01.speed >= player02.speed)
			{
				for(int playerNumber = 1; playerNumber <= 2; playerNumber++)
				{
					system("cls");
					DisplayTitle();
					DisplayAllStatus(player01, player02);
					cout << "Player " << playerNumber << " turn: " << endl;
					if (playerNumber == 1)
					{
						player01.Action(player02);
					}
					else
					{
						player02.Action(player01);
					}
					system("pause");
					
					if(player01.remainingHealth <= 0 || player02.remainingHealth <= 0)
					break;
				}
			}
			else
			{
				for(int playerNumber = 2; playerNumber >= 1; playerNumber--)
				{
					system("cls");
					DisplayTitle();
					DisplayAllStatus(player01, player02);
					cout << "Player " << playerNumber << " turn: " << endl;
					if (playerNumber == 1)
					{
						player01.Action(player02);
					}
					else
					{
						player02.Action(player01);
					}
					system("pause");
					
					if(player01.remainingHealth <= 0 || player02.remainingHealth <= 0)
					break;
				}
			}
		}
		
		if(player01.remainingHealth <= 0)
		{
			player01.remainingHealth = 0;
		}
		else
		{
			player02.remainingHealth = 0;
		}
		system("cls");
		DisplayTitle();
		DisplayAllStatus(player01, player02);
		if (player02.remainingHealth == 0)
		{
			cout << "Player 1 Wins" << endl;
		}
		else
		{
			cout << "Player 2 Wins" << endl;
		}
		cout << "Do you want to play again? (y/n)" << endl;
		string k;
		cin >> k;
		if (k == "Y" || k == "y")
			system("cls");
		else
			break;
	}

	system("pause");
	return 0;
}

Player::Player(int j)
{
	this->playerNumber = j;
	this->assignedStats = false;
}

void Player::Action(Player &opponent)
{								
	int chanceOfAttack = rand() % 35;
	if (chanceOfAttack == 0)
	{
		this->Heal();
	}
	else
	{
		chanceOfAttack = rand() % 10 + 1;
		if (chanceOfAttack <= opponent.speed)
			this->Dodge();
		else
			this->Attack(opponent);
	}
 }

void Player::Attack(Player &opponent)
{
	int damage = this->attack - opponent.defense;

	if (damage <= 0)
		damage = 2;

	opponent.remainingHealth -= damage;
	cout << damage << " damage dealt to opponent!" << endl;
}

void Player::Heal()
{
	this->remainingHealth = this->health;
	cout << "Recovered to the max health." << endl;
}

void Player::Dodge()
{
	cout << "Opponent dodged the attack." << endl;
}

int InputConversion(string input)
{
	if (input == "1")
	{
		return 1;
	}
	else if (input == "2")
	{
		return 2;
	}
	else if (input == "3")
	{
		return 3;
	}
	else if (input == "4")
	{
		return 4;
	}
	else if (input == "5")
	{
		return 5;
	}
	else
	{
		return 0;
	}
}

bool ValidatingInput(string input)
{
	if (InputConversion(input) == 0)
		return false;
		
	return true;
}

void DisplayTitle()
{
	cout << "==================================" << endl;
	cout << "||                              ||" << endl;
	cout << "||      Not So Epic Battle      ||" << endl;
	cout << "||                              ||" << endl;
	cout << "==================================" << endl;
}

void InitPlayerStats(Player &target, int health, int attack, int defense, float speed, char classType)
{
	target.health = health;
	target.attack = attack;
	target.defense = defense;
	target.speed = speed;
	target.classType = classType;
	target.remainingHealth = health;
}

void JobAssign(Player &target)
{
	while(true)
	{
		string k;
		system("cls");
		DisplayTitle();
		cout << "Player " << target.playerNumber << " panel: " << endl;
		cout << "Welcome to Not So Epic Battle Arena. Please choose your character's class type." << endl;
		cout << "1. Warrior" << endl;
		cout << "2. Mage" << endl;
		cout << "3. Assassin" << endl;
		cout << "4. Paladin" << endl;
		cout << "5. Druid" << endl;
		cout << endl;
		cout << "The chosen character: ";
		cin >> k;
		
		if (k == "1")
		{
			InitPlayerStats(target, 15, 2, 2, 1, 'W');
			break;
		}
		else if (k == "2")
		{
			InitPlayerStats(target, 10, 4, 1, 1, 'M');
			break;
		}
		else if (k == "3")
		{
			InitPlayerStats(target, 10, 2, 1, 3, 'A');
			break;
		}
		else if (k == "4")
		{
			InitPlayerStats(target, 9, 3, 2, 1, 'P');
			break;
		}
		else if (k == "5")
		{
			InitPlayerStats(target, 13, 4, 2, 2, 'D');
			break;
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			system("pause");
		}
	}
}

void StatsAssign(Player &target)
{
	string className;
	if (target.classType == 'W')
		className = "Warrior";
	else if (target.classType == 'M')
		className = "Mage    ";
	else if (target.classType == 'A')
		className = "Assassin";
	else if (target.classType == 'P')
		className = "Paladin";
	else 
		className = "Druid";
	
	int extraStat = 4;
	int tempHealth = 0, tempAttack = 0, tempDefense = 0, tempSpeed = 0;
	
	do
	{		
		string k;
		DisplayTitle();
		cout << "Player " << target.playerNumber << " panel: " << endl;
		cout << "============================" << endl;
		cout << "||                        ||" << endl;
		cout << "||  Class: " << className << "       ||" << endl;
		cout << "||  Health: ";
		
		if (target.health < 10)
		{
			cout << " " << target.health;
		}
		else
		{
			cout << target.health;
		}
		
		cout << " + ";
		
		if (tempHealth < 10)
		{
			cout << tempHealth << " ";
		}
		else
		{
			cout << tempHealth;
		}
		cout << "       ||" << endl;
		cout << "||  Attack Damage: " << target.attack << " + " << tempAttack << "  ||" << endl;
		cout << "||  Defense: " << target.defense << " + " << tempDefense << "        ||" << endl;
		cout << "||  Speed: " << target.speed << " + " << tempSpeed << "          ||" << endl;
		cout << "||                        ||" << endl;
		cout << "============================" << endl;
		
		if (extraStat == 0)
		{
			do
			{
				cout << "Are you sure this is how you want to allocate your extra points? (Y/N)" << endl;
				cin >> k;
				if ((k == "Y") || (k == "y")) 
				{
					target.health += tempHealth;
					target.attack += tempAttack;
					target.defense += tempDefense;
					target.speed += tempSpeed;
					target.assignedStats = true;
					return;
				}
				else if ((k == "N") || (k == "n"))
					return;
				else
				{
					cout << "Invalid input. Please try again." << endl;
					system("pause");
				}
			} while(true);
		}
		
		cout << "You have " << extraStat << " extra stats to allocate. Where would you like to allocate them?" << endl;
		cout << "1. Health" << endl;
		cout << "2. Attack Damage" << endl;
		cout << "3. Defense" << endl;
		cout << "4. Speed" << endl;
		cin >> k;
		
		if (ValidatingInput(k))
		{
			do
			{
				string amount;
				cout << "How many points would you like to put in? (Extra stat points: " << extraStat << ")" << endl;
				cin >> amount;
				if (ValidatingInput(amount))
				{
					int temp = InputConversion(amount);
					if (temp > extraStat)
						cout << "You do not have enough stat points to be assigned. Please try again." << endl;
					else
					{
						extraStat -= temp;
						int choice = InputConversion(k);
						switch(choice)
						{
							case 1:
								tempHealth += temp * 5;
								break;
							case 2:
								tempAttack += temp;
								break;
							case 3:
								tempDefense += temp;
								break;
							case 4:
								tempSpeed += temp;
								break;
						}
						break;
					}
				}
				else
				{
					cout << "Invalid input. Please try again." << endl;
					system("pause");
				}
			} while(true);
		}
		else
		{
			cout << "Invalid input. Please try again." << endl;
			system("pause");
		}
		
		system("cls");
	} while(true);
}

void DisplayStatus(Player target)
{
	string className;
	if (target.classType == 'W')
		className = "Warrior";
	else if (target.classType == 'M')
		className = "Mage     ";
	else if (target.classType == 'A')
		className = "Assassin";
	else if (target.classType == 'P')
		className = "Paladin";
	else 
		className = "Druid";
	
	cout << "============================" << endl;
	cout << "||                        ||" << endl;
	cout << "||  Player " << target.playerNumber << "'s            ||" << endl;
	cout << "||  Class: " << className << "       ||" << endl;
	cout << "||  Health: ";
	if (target.remainingHealth < 10)
	{
		cout << " " << target.remainingHealth;
	}
	else
	{
		cout << target.remainingHealth; 
	}
	cout << "            ||" << endl;
	cout << "||  Attack Damage: " << target.attack << "      ||" << endl;
	cout << "||  Defense: " << target.defense << "            ||" << endl;
	cout << "||  Speed: " << target.speed << "              ||" << endl;
	cout << "||                        ||" << endl;
	cout << "============================" << endl;
}

void DisplayAllStatus(Player target01, Player target02)
{
	DisplayStatus(target01);
	cout << "             VS             " << endl;
	DisplayStatus(target02);
}
