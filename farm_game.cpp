#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Poultry
{
public:
	Poultry(const char* name, float weight, float Maxweight, float price, int num);
	const char* getName();
	float getWeight();
	float getMaxWeight();
	float getPrice();
	int getNum();
	void eatFood(float food);

	// implement this function for money calculating
	friend float getMoney(Poultry[]);

private:
	const char* name;
	float weight;
	int Maxweight;
	float price;
	int num;

};

// default constructor,initialize name,weight,Maxweight,price ansd num respectively
Poultry::Poultry(const char* n, float w, float Maxw, float p, int m)
{
	name = n;
	weight = w;
	Maxweight = Maxw;
	price = p;
	num = m;
}

const char* Poultry::getName()
{
	return name;

}


float Poultry::getWeight()
{
	return weight;

}

float Poultry::getMaxWeight()
{
	return Maxweight;

}

float Poultry::getPrice()
{
	return price;

}

int Poultry::getNum()
{
	return num;

}

void Poultry::eatFood(float food)
{
	num = ((food + weight) / Maxweight) + num;
	weight = fmod((food + weight), Maxweight);



}

// Complete the function
// money = (Chickens'Num  *  Chickens'Price )
//         + (Rabbits'Num  *  Rabbits'Price )
//         + (Pigs'Num  *  Pigs'Price ),

float getMoney(Poultry pou[])
{
	float money = 0;
	for (int i = 0; i < 3; i++) {
		money = money + (pou[i].getNum() * pou[i].getPrice());
	}
	return money;
}
// When the chosen feeding mode is 2, define a function to calculate an array named food with size 3,
// each element in food array means:
// food[0]: Weight of food for feeding Chickens;
// food[1]: Weight of food for feeding Rabbits;
// food[2]: Weight of food for feeding Pigs;
// input: TotalFood , array food[3]
void Feed(float TotalFood, float* food);



int main()
{

	Poultry myPou[3] = { Poultry("Chickens",1,7,30,2),Poultry("Rabbits",3,30,110,2),Poultry("Pigs",20,400,2200,2) };
	Poultry sysPou[3] = { Poultry("Chickens",1,7,30,2),Poultry("Rabbits",3,30,110,2),Poultry("Pigs",20,400,2200,2) };
	const float TotalFood = 1200;
	int seed, model;
	float mean = TotalFood / 3;

	// game begins
	cout << "###########################      Farming Together!     ###########################" << endl;
	cout << "Enter the seed for random number generation:"<<endl;
	cin >> seed;
	srand(seed); // this sets the seed of random number generation
	cout << "Now, you have:" << endl;
	for (int i = 0; i < 3; i++)
	{
		cout << myPou[i].getNum() << " " << myPou[i].getName() << ":" << endl;
		cout << "*****" << " price: " << myPou[i].getPrice() << " weight: " << myPou[i].getWeight() << " Maxweight: " << myPou[i].getMaxWeight();
		cout << endl;
	}
	cout << "Total Food: " << TotalFood << "kg" << endl;

	cout << "###########################  Your Feeding Begin! ###########################" << endl;
	cout << "Select a feeding mode (1:Average  2:Custom):";
	cin >> model;
	switch (model) {
	case 1:
		
		for (int i = 0; i < 3; i++) {
			myPou[i].eatFood((TotalFood / 3));
		}		
		break;
	case 2:
		float food[3] = {0};
		Feed(TotalFood, food);
		for (int i = 0; i < 3; i++) {
			myPou[i].eatFood(food[i]);
		}
		break;
	}
	cout << "After feeding, you have: " << getMoney(myPou) << "$, including:" << endl;
	for (int i = 0; i < 3; i++)
		cout << "*****" << myPou[i].getNum() << " " << myPou[i].getName() << endl;


	cout << "###########################  System's Feeding Begin! ###########################" << endl;
	float temp1, temp2 = 0;
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			temp1 = rand() % int(mean);
			cout << "System feed" << temp1 << "kg food for Chickens" << endl;
			temp2 += temp1;
		}
		if (i == 1)
		{
			temp1 = rand() % int(mean);
			cout << "System feed" << temp1 << "kg food for Rabbits" << endl;
			temp2 += temp1;
		}
		if (i == 2)
		{
			temp1 = TotalFood - temp2;
			temp2 = 0;
			cout << "System feed" << temp1 << "kg food for Pigs" << endl;
		}
		sysPou[i].eatFood(temp1);
	}

	cout << "Now system have: " << getMoney(sysPou) << "$,and:" << endl;
	for (int i = 0; i < 3; i++)
		cout << "*****" << sysPou[i].getNum() << sysPou[i].getName() << endl;


	cout << "###########################  Results! ###########################" << endl;

	if (getMoney(myPou)>getMoney(sysPou))
		cout << "Clever!" << endl;
	else
		cout << "Failed!" << endl;


	return 0;
}


void Feed(float TotalFood, float* food)
{
	float left;
	bool flag = true;
	while (flag)
	{
		left = TotalFood;
		cout << "How many food are you going to feed the Chickens (food left: " << left << "kg)?"<<endl;
		cin >> food[0];
		left -= food[0];
		if (left < 0)
		{
			cout << "Input Error! You consumed more than " << TotalFood << "kg food. Pls input again!" << endl;
			continue;
		}
		else
		{
			cout << "How many food are you going to feed the Rabbits (food left: " << left << "kg)?"<<endl;
			cin >> food[1];
			left -= food[1];
			if (left < 0)
			{
				cout << "Input Error! You consumed more than " << TotalFood << "kg food. Pls input again!" << endl;
				continue;
			}
			else
			{
				cout << "How many food are you going to feed the Pigs (food left: " << left << "kg)?"<<endl;
				cin >> food[2];
				left -= food[2];
				if (left < 0)
				{
					cout << "Input Error! You consumed more than " << TotalFood << "kg food. Pls input again!" << endl;
					continue;
				}
				else
					flag = false;

			}
		}
	}


}
