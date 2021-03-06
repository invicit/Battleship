// ConsoleApplication3.cpp : Defines the entry point for the console application.
// 

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()
#include <locale> 
#include <Windows.h>
#include <conio.h>
using namespace std;


class Game {

	class Player {
	public:
		char **playerArea;
		int Number;
		Game *gra;
		int ShipsTypes[4];
		//vector <unsigned int*> ShipsInfo;

		Player(int Numb, Game *game) {
			Number = Numb;
			gra = game;
			ShipsTypes[0] = gra->ShipType1();
			ShipsTypes[1] = gra->ShipType2();
			ShipsTypes[2] = gra->ShipType3();
			ShipsTypes[3] = gra->ShipType4();
		}


		void DefinePlayerArea() {
			playerArea = new char *[gra->Rows() + 2];
			for (int i = 0; i <= gra->Rows() + 2; i++) {
				playerArea[i] = new char[28];
			}
			for (int i = 0; i < gra->Rows() + 2; i++) {
				for (int j = 0; j < 28; j++) {
					playerArea[i][j] = ' ';
				}
			}
		}


		//rysuje tabele gracza (cheat)
		void DrawPlayerArea() {
			system("cls");
			cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
			for (int i = 1; i < gra->Rows() + 1; i++) {
				for (int j = 1; j < 27; j++) {
					cout << " " << playerArea[i][j] << " ";
				}
				cout << i << '\n';
			}
		}

		//kolumny -> inty
		int TranslateCol(char col) { return static_cast<int>(toupper(col)) - 64; }

		//tlumaczene coordow na inty
		int *Coordinates(char *position) {

			char as;
			char rest[99];
			as = position[0];
			for (int i = 0; i < 99; i++) {
				rest[i] = position[1 + i];
			}

			int pos[2];
			pos[0] = TranslateCol(position[0]);
			pos[1] = atoi(rest);

			return pos;
		}


		//funkcja pytajaca graca jak dodac statki
		void Insert() {
			char position;
			string wiersz;
			int ShipInsertInfo[4]; //zmienna przechowyjaca wszystko o polozeniu statku [0]-typ [1]-kolumna [2]-wiersz [3]-sposob
			char *type = new char; //2 3 4 5
			string method; //pionowo-1 poziomo-2 ukosP-3 ukosL-4


			
			while (ShipsTypes[0] != 0 || ShipsTypes[1] != 0 || ShipsTypes[2] != 0 || ShipsTypes[3] != 0) {
				cout << "Podaj rodzaj statku, pole gdzie ma byc pierwszy maszt i sposob rozmieszcznia (pionowo,poziomo,poskosie)\n";
				cout << "Rodzaj (5, 4, 3, 2)\n";
				cout << "Polozenie  np. C17 (bez spacji)\n";
				cout << "Sposob (pionowo, poziomo, ukosP, ukosL)\n\n";
				
				cout <<"Pieciomasztowce "<< ShipsTypes[0]<<"\n"<<"Czteromasztowce "<<ShipsTypes[1]<<"\n"<<"Trojmasztowce "<<ShipsTypes[2]<<"\n"<<"Dwumasztowce "<< ShipsTypes[3]<<"\n"<< endl;
				cout << "\nPodaj rodzaj statku\n";
				bool flag = 0;
				do {
					cin >> type;
					if (type[1] != NULL || isalpha(type[0]) || (type[0] != '2' && type[0] != '3' && type[0] != '4' && type[0] != '5') || (type[0] == '5' && ShipsTypes[0] == 0) || (type[0] == '4' && ShipsTypes[1] == 0) || (type[0] == '3' && ShipsTypes[2] == 0) || (type[0] == '2' && ShipsTypes[3] == 0)) { cout << "Wprowadz to poprawnie(rodzaj)\n"; flag = 0; }
					else { ShipInsertInfo[0] = atoi(type); flag = 1; }

				} while ((type[0] != '2' && type[0] != '3' && type[0] != '4' && type[0] != '5') || (flag != true));

				cout << "\nPodaj polozenie (kolumna)\n";
				do {
					getchar();
					position=getchar();
					if ((65 > static_cast<int>(position) || static_cast<int>(position) > 90) && (97 > static_cast<int>(position) || static_cast<int>(position)>122)) { cout << "Wprowadz to poprawnie (polozenie)\n"; }
					else {
						ShipInsertInfo[1] = TranslateCol(position);
					}
				} while ((65 > static_cast<int>(position) || static_cast<int>(position) > 90) && (97 > static_cast<int>(position) || static_cast<int>(position)>122));


				cout << "\nPodaj polozenie (wiersz)\n";
				do {
					cin >> wiersz;
					if (wiersz.find_first_not_of("1234567890") != string::npos) { cout << "Wprowadz to poprawnie (wiersz)\n"; }
					else if (stoi(wiersz) > gra->Rows() || stoi(wiersz) < 1) { cout << "Wprowadz to poprawnie (wiersz)\n"; }
					else {

						ShipInsertInfo[2] = stoi(wiersz);
						break;
					}
				} while (1);


				cout << "\nPodaj sposob ulozenian\n";
				do {
					locale loc;
					cin >> method;
					for (string::size_type i = 0; i < method.length(); ++i)
					{
						method[i] = tolower(method[i], loc);
					}
					if (method.compare("pionowo") && method.compare("poziomo") && method.compare("ukosp") && method.compare("ukosl")) cout << "Wprowadz to poprawnie(metoda)\n";
					else {
						if (!method.compare("pionowo")) { ShipInsertInfo[3] = 1; }
						else if (!method.compare("poziomo")) { ShipInsertInfo[3] = 2; }
						else if (!method.compare("ukosp")) { ShipInsertInfo[3] = 3; }
						else if (!method.compare("ukosl")) { ShipInsertInfo[3] = 4; }
					}
				} while (method.compare("pionowo") && method.compare("poziomo") && method.compare("ukosp") && method.compare("ukosl"));

				//cout << ShipInsertInfo[0] << ShipInsertInfo[1] << ShipInsertInfo[2] << ShipInsertInfo[3];
				this->addShip(ShipInsertInfo);
				system("cls");
			}
			if (Number == 0) {
				gra->area0P = this->playerArea;
			}
			if (Number == 1) {
				gra->area1P = this->playerArea;
			}
		}

		//funkcja zarzadzajaca umieszczaniem statkow w odpowieni sposob
		void addShip(int *ShipInsertInfo) {
			//cout << "Add Ships\n";
			switch (ShipInsertInfo[3])
			{
			case 1: {
				//cout << "Pionowo\n";
				Vertical(ShipInsertInfo);
				break; }


			case 2: {
				//cout<< "Poziomo1\n";
				Horizontal(ShipInsertInfo);
				break; }


			case 3: {
				//cout << "UkosP \n";
				DiagonalR(ShipInsertInfo);
				break; }


			case 4: {
				//cout << "UkosL\n";
				DiagonalL(ShipInsertInfo);
				break; }
			}

		}


		//funkcje antykolizyjne
		bool isHorizontalPossible(int *Info) {
			if (Info[1] < 1 || (Info[1] + Info[0])>27 || Info[2]<1 || Info[2]>gra->Rows() + 1) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			if ((playerArea[Info[2] - 1][Info[1] - 1] != ' ') || (playerArea[Info[2]][Info[1] - 1] != ' ') || (playerArea[Info[2] + 1][Info[1] - 1] != ' ')) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			if ((playerArea[Info[2] - 1][Info[1] + Info[0]] != ' ') || (playerArea[Info[2]][Info[1] + Info[0]] != ' ') || (playerArea[Info[2] + 1][Info[1] + Info[0]] != ' ')) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			for (int i = 0; i < Info[0]; i++) {
				if (playerArea[Info[2]][Info[1] + i] != ' ' || playerArea[Info[2] + 1][Info[1] + i] != ' ' || playerArea[Info[2] - 1][Info[1] + i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n";  return 0; }
			}

			return 1;
		}

		bool isVerticalPossible(int *Info) {

			if (Info[2]<1 || (Info[2] + Info[0]) > gra->Rows() + 1 || Info[1] < 1 || Info[1]>27) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			if (playerArea[Info[2] - 1][Info[1]] != ' ' || playerArea[Info[2] - 1][Info[1] - 1] != ' ' || playerArea[Info[2] - 1][Info[1] + 1] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			if (playerArea[Info[2] + Info[0]][Info[1]] != ' ' || playerArea[Info[2] + Info[0]][Info[1] - 1] != ' ' || playerArea[Info[2] + Info[0]][Info[1] + 1] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			for (int i = 0; i < Info[0]; i++) {
				if (playerArea[Info[2] + i][Info[1]] != ' ' || playerArea[Info[2] + i][Info[1] - 1] != ' ' || playerArea[Info[2] + i][Info[1] + 1] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }
			}
			return 1;

		}

		bool isDiagonalRPossible(int *Info) {

			if ((playerArea[Info[2]][Info[1]] != ' ') || (playerArea[Info[2] - 1][Info[1]] != ' ') || (playerArea[Info[2]][Info[1] - 1] != ' ') || (playerArea[Info[2] - 1][Info[1] - 1] != ' ')) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }

			for (int i = 1; i < Info[0] + 1; i++) {

				if (playerArea[Info[2] + i][Info[1] + i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //1
				if (playerArea[Info[2] + i][Info[1] + i - 1] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //2
				if (playerArea[Info[2] + i - 1][Info[1] + i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //3
				if (playerArea[Info[2] + i][Info[1] + i - 2] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //4
				if (playerArea[Info[2] + i - 2][Info[1] + i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //5
			}



			return 1;

		}

		bool isDiagonalLPossible(int *Info) {
			if ((playerArea[Info[2]][Info[1]] != ' ') || (playerArea[Info[2] - 1][Info[1]] != ' ') || (playerArea[Info[2]][Info[1] + 1] != ' ') || (playerArea[Info[2] - 1][Info[1] + 1] != ' ')) { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; }

			for (int i = 1; i < Info[0] + 1; i++) {

				if (playerArea[Info[2] + i][Info[1] - i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //1
				if (playerArea[Info[2] + i][Info[1] - i - 1] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //2
				if (playerArea[Info[2] + i - 1][Info[1] - i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //3
				if (playerArea[Info[2] + i][Info[1] - i - 2] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //4
				if (playerArea[Info[2] + i - 2][Info[1] - i] != ' ') { cout << "\nNie mozna umiescic tego statku na tej pozycji, wprowadz dane dla teg statku jeszcze raz\n"; return 0; } //5
			}
			return 1;
		}


		//funkcje lokujace statki w arenie gracza 
		void Horizontal(int *ShipInsertInfo) {
			if (isHorizontalPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {
					playerArea[ShipInsertInfo[2]][ShipInsertInfo[1] + i] = static_cast<char>(ShipInsertInfo[0] + 48);
				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					cout << "Cos sie popsulo \n";
					break;
				}
			}
			else return;
		}

		void Vertical(int *ShipInsertInfo) {
			system("pause");
		
			if (isVerticalPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {
					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1]] = static_cast<char>(ShipInsertInfo[0] + 48);
				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					cout << "Cos sie popsulo \n";
					break;
				}
			}
			else
			{
				return;
			}
		}

		void DiagonalR(int *ShipInsertInfo) {
			if (isDiagonalRPossible(ShipInsertInfo))
			{
				for (int i = 0; i < ShipInsertInfo[0]; i++) {

					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1] + i] = static_cast<char>(ShipInsertInfo[0] + 48);

				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					cout << "Cos sie popsulo \n";
					break;
				}
			}
			else {
				return;
			}
		}

		void DiagonalL(int *ShipInsertInfo) {

			if (isDiagonalLPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {

					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1] - i] = static_cast<char>(ShipInsertInfo[0] + 48);

				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					cout << "Cos sie popsulo \n";
					break;
				}
			}
			else {
				return;
			}

		}



		void OrderToShoot() {
			int rowcol[2];
			rowcol[0] = 0;
			rowcol[1] = 0;
			char position;
			string wiersz;
			while (1) {
				do {
					cout << "Podaj koordynaty strzalu (kolumna)\n";
					
					cin >> position;
					if (!isalpha(position)) { cout << "Wprowadz to poprawnie (polozenie)\n"; }
					else {
						rowcol[0] = TranslateCol(position);
						break;
					}
				} while (1);


				cout << "Podaj koordynaty strzalu (wiersz)\n";
				do {
					cin >> wiersz;
					system("pause");
					if (wiersz.find_first_not_of("1234567890") != string::npos) { cout << "Wprowadz to poprawnie (wiersz)\n"; }
					else if (stoi(wiersz) > gra->Rows() || stoi(wiersz) < 1) { cout << "Wprowadz to poprawnie (wiersz)\n"; }
					else {

						rowcol[1] = stoi(wiersz);
						break;
					}
				} while (1);

			//cout << rowcol[1] << rowcol[0];
			//	system("pause");
					AttackEnemyShip(rowcol[1], rowcol[0]);
					break; 

			}
		}

		void AttackEnemyShip(int x, int y) {
			if (this->Number == 0) {
				while (1) {
					if (gra->area1P[x][y] == ' ')
					{
						gra->area1[x][y] = 'X';
						gra->area1P[x][y] = '*';
						break;
					}
					else if (gra->area1P[x][y] == '*') {
						cout << "Juz tu strzelales\n";
						OrderToShoot();
					}
					else {
						gra->area1[x][y] = gra->area1P[x][y];
						gra->area1P[x][y] = '*';
						gra->player1pkt--;
						break;
					}
				}
			}
			if (this->Number == 1) {
				while (1) {
					if (gra->area0P[x][y] == ' ')
					{
						gra->area0[x][y] = 'X';
						gra->area0P[x][y] = '*';
						break;
					}
					else if (gra->area0P[x][y] == '*') {
						cout << "Juz tu strzelales\n";
						OrderToShoot();
					}
					else {
						gra->area0[x][y] = gra->area0P[x][y];
						gra->area0P[x][y] = '*';
						gra->player0pkt--;
						break;
					}
				}
			}
		}
	};

	class CPU {
	public:
		char **playerArea;
		int Number;
		Game *gra;
		int ShipsTypes[4];
		vector <int> xLastShoots;
		vector <int> yLastShoots;
		int fireflag;


		int row;
		int howmuch;
		int wehave = 0;
		vector <int> x;
		vector <int> y;

		int AttackedShip = 0;

		CPU(int Numb, Game *game) {
			Number = Numb;
			gra = game;
			ShipsTypes[0] = gra->ShipType1();
			ShipsTypes[1] = gra->ShipType2();
			ShipsTypes[2] = gra->ShipType3();
			ShipsTypes[3] = gra->ShipType4();
			howmuch = 26 * gra->Rows();
			row = gra->Rows();
			xLastShoots.clear();
			yLastShoots.clear();
			fireflag = 0;
		}

		void DefinePlayerArea() {
			playerArea = new char *[gra->Rows() + 2];
			for (int i = 0; i <= gra->Rows() + 2; i++) {
				playerArea[i] = new char[28];
			}
			for (int i = 0; i < gra->Rows() + 2; i++) {
				for (int j = 0; j < 28; j++) {
					playerArea[i][j] = ' ';
				}
			}
		}

		//rysuje tabele CPU (cheat)
		void DrawPlayerArea() {
			system("cls");
			cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
			for (int i = 1; i < gra->Rows() + 1; i++) {
				for (int j = 1; j < 27; j++) {
					cout << " " << playerArea[i][j] << " ";
				}
				cout << i << '\n';
			}
		}

		void Insert() {
			int flag;
//			char position[3];
			int ShipInsertInfo[4]; //zmienna przechowyjaca wszystko o polozeniu statku [0]-typ [1]-kolumna [2]-wiersz [3]-sposob
			int type = -1; //2 3 4 5
			string method; //pionowo-1 poziomo-2 ukosP-3 ukosL-4
			while (ShipsTypes[0] != 0 || ShipsTypes[1] != 0 || ShipsTypes[2] != 0 || ShipsTypes[3] != 0) {		
				type = getRandomNumber(2, 5);
				if ((type != 2 && type != 3 && type != 4 && type != 5) || (type == 5 && ShipsTypes[0] == 0) || (type == 4 && ShipsTypes[1] == 0) || (type == 3 && ShipsTypes[2] == 0) || (type == 2 && ShipsTypes[3] == 0)) {}
				else {
					flag = 1;
					ShipInsertInfo[0] = type;
					ShipInsertInfo[1] = getRandomNumber(1, 25);
					ShipInsertInfo[2] = getRandomNumber(1, gra->Rows());
					ShipInsertInfo[3] = getRandomNumber(1, 4);
					//cout << ShipInsertInfo[0] << ShipInsertInfo[1] << ShipInsertInfo[2] << ShipInsertInfo[3] << endl;
					//system("pause");
					addShip(ShipInsertInfo);
				}
			}
			if (Number == 0) {
				gra->area0P = this->playerArea;
			}
			if (Number == 1) {
				gra->area1P = this->playerArea;
			}
		}
	
		int getRandomNumber(int min, int max)
		{
			static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  
			return min + static_cast<int>((max - min + 1) * (rand() * fraction));
		}
	
		void addShip(int *ShipInsertInfo) {
			//cout << "Add Ships\n";
			switch (ShipInsertInfo[3])
			{
			case 1: {
				//cout << "Pionowo\n";
				Vertical(ShipInsertInfo);
				break; }


			case 2: {
				//cout<< "Poziomo1\n";
				Horizontal(ShipInsertInfo);
				break; }


			case 3: {
				//cout << "UkosP \n";
				DiagonalR(ShipInsertInfo);
				break; }


			case 4: {
				//cout << "UkosL\n";
				DiagonalL(ShipInsertInfo);
				break; }
			}
			return;

		}


		bool isHorizontalPossible(int *Info) {
			if (Info[1] < 1 || (Info[1] + Info[0])>27 || Info[2]<1 || Info[2]>gra->Rows() + 1) return 0;
			if ((playerArea[Info[2] - 1][Info[1] - 1] != ' ') || (playerArea[Info[2]][Info[1] - 1] != ' ') || (playerArea[Info[2] + 1][Info[1] - 1] != ' ')) { return 0; }
			if ((playerArea[Info[2] - 1][Info[1] + Info[0]] != ' ') || (playerArea[Info[2]][Info[1] + Info[0]] != ' ') || (playerArea[Info[2] + 1][Info[1] + Info[0]] != ' ')) { return 0; }
			for (int i = 0; i < Info[0]; i++) {
				if (playerArea[Info[2]][Info[1] + i] != ' ' || playerArea[Info[2] + 1][Info[1] + i] != ' ' || playerArea[Info[2] - 1][Info[1] + i] != ' ') { return 0; }
			}

			return 1;
		}

		bool isVerticalPossible(int *Info) {

			if (Info[2]<1 || (Info[2] + Info[0]) > gra->Rows() + 1 || Info[1] < 1 || Info[1]>27) { return 0; }
			if (playerArea[Info[2] - 1][Info[1]] != ' ' || playerArea[Info[2] - 1][Info[1] - 1] != ' ' || playerArea[Info[2] - 1][Info[1] + 1] != ' ') { return 0; }
			if (playerArea[Info[2] + Info[0]][Info[1]] != ' ' || playerArea[Info[2] + Info[0]][Info[1] - 1] != ' ' || playerArea[Info[2] + Info[0]][Info[1] + 1] != ' ') { return 0; }
			for (int i = 0; i < Info[0]; i++) {
				if (playerArea[Info[2] + i][Info[1]] != ' ' || playerArea[Info[2] + i][Info[1] - 1] != ' ' || playerArea[Info[2] + i][Info[1] + 1] != ' ') { return 0; }
			}
			return 1;

		}

		bool isDiagonalRPossible(int *Info) {

			if ((playerArea[Info[2]][Info[1]] != ' ') || (playerArea[Info[2] - 1][Info[1]] != ' ') || (playerArea[Info[2]][Info[1] - 1] != ' ') || (playerArea[Info[2] - 1][Info[1] - 1] != ' ')) { return 0; }
		
			for (int i = 1; i < Info[0]+1; i++) {

				if (playerArea[Info[2]+i][Info[1]+i] != ' ') { return 0; } //1
				if (playerArea[Info[2] + i][Info[1] + i - 1] != ' ') { return 0; } //2
				if (playerArea[Info[2] + i - 1][Info[1] + i] != ' ') { return 0; } //3
				if (playerArea[Info[2] + i][Info[1] + i - 2] != ' ') { return 0; } //4
				if (playerArea[Info[2] + i - 2][Info[1] + i] != ' ') { return 0; } //5
			}

			

			return 1;

		}

		bool isDiagonalLPossible(int *Info) {
			if ((playerArea[Info[2]][Info[1]] != ' ') || (playerArea[Info[2] - 1][Info[1]] != ' ') || (playerArea[Info[2]][Info[1] + 1] != ' ') || (playerArea[Info[2] - 1][Info[1] + 1] != ' ')) { return 0; }

			for (int i = 1; i < Info[0] + 1; i++) {

				if (playerArea[Info[2] + i][Info[1] - i] != ' ') {  return 0; } //1
				if (playerArea[Info[2] + i][Info[1] - i - 1] != ' ') {  return 0; } //2
				if (playerArea[Info[2] + i - 1][Info[1] - i] != ' ') {   return 0; } //3
				if (playerArea[Info[2] + i][Info[1] - i - 2] != ' ') {  return 0; } //4
				if (playerArea[Info[2] + i - 2][Info[1] - i] != ' ') {  return 0; } //5
			}
			return 1;
		}

		//funkcje lokujace statki w arenie gracza 
		void Horizontal(int *ShipInsertInfo) {
			if (isHorizontalPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {
					playerArea[ShipInsertInfo[2]][ShipInsertInfo[1] + i] = static_cast<char>(ShipInsertInfo[0] + 48);
				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					return;
					//cout << "Cos sie popsuloH \n";
					break;
				}
			}
			else return;
		}

		void Vertical(int *ShipInsertInfo) {
			if (isVerticalPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {
					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1]] = static_cast<char>(ShipInsertInfo[0] + 48);
				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					return;
					//cout << "Cos sie popsuloV \n";
					break;
				}
			}
			else
			{
				return;
			}
		}

		void DiagonalR(int *ShipInsertInfo) {
			if (isDiagonalRPossible(ShipInsertInfo))
			{
				for (int i = 0; i < ShipInsertInfo[0]; i++) {

					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1] + i] = static_cast<char>(ShipInsertInfo[0] + 48);

				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					return;
					//cout << "Cos sie popsuloDR \n";
					break;
				}
			}
			else {
				return;
			}
		}

		void DiagonalL(int *ShipInsertInfo) {

			if (isDiagonalLPossible(ShipInsertInfo)) {
				for (int i = 0; i < ShipInsertInfo[0]; i++) {

					playerArea[ShipInsertInfo[2] + i][ShipInsertInfo[1] - i] = static_cast<char>(ShipInsertInfo[0] + 48);

				}
				switch (ShipInsertInfo[0])
				{

				case 2: ShipsTypes[3]--; break;

				case 3: ShipsTypes[2]--; break;

				case 4: ShipsTypes[1]--; break;

				case 5: ShipsTypes[0]--; break;

				default:
					return;
					//	cout << "Cos sie popsuloDL \n";
					break;
				}
			}
			else {
				return;
			}

		}


		void OrderToShoot() {

			AttackEnemyShip();
		}

		void AttackEnemyShip() {

			int shoot[2];
			bool flag = false;
			while (1) {
				shoot[0] = getRandomNumber(1, row);
				shoot[1] = getRandomNumber(1, 26);
			//	cout << "dl vektora:" << yLastShoots.size() << endl << fireflag << endl;
				if (howmuch == wehave) { break; }
				//cout << howmuch << "\n" << wehave << "\n";
				if (howmuch - wehave < 0.2 * howmuch) {
					for (int i = 1; i <= gra->Rows(); i++) {
						for (int j = 1; j < 27; j++) {

							if ((gra->area1P[i][j] != '*') && (Number == 0)) {
								shoot[0] = i;
								shoot[1] = j;
								flag = true;
								break;
								//cout << "bum0\n";
							}
							if (gra->area0P[i][j] != '*' && Number == 1) {
								shoot[0] = i;
								shoot[1] = j;
								flag = true;
								break;
								//cout << "bum1\n" << shoot[0] << shoot[1] << endl;
							}
						}
						if (flag == true) {
							break;
						}
					}

				}

				//first blood
				else if (xLastShoots.size() == 1 && yLastShoots.size() == 1) {

					shoot[0] = xLastShoots[0] + getRandomNumber(-1, 1);
					shoot[1] = yLastShoots[0] + getRandomNumber(-1, 1);

					if (fireflag > 1000) {
						shoot[0] = getRandomNumber(1, row);
						shoot[1] = getRandomNumber(1, 26);
						fireflag = 0;
					}
				//	if (shoot[1] < 1) { shoot[0] += 2; }
				//	if (shoot[1] > 25) { shoot[0] -= 2; }
				//	if (shoot[0] < 1) { shoot[1] += 2; }
				//	if (shoot[0] > gra->Rows() - 1) { shoot[1] -= 2; }
				}
				//random
				else if (xLastShoots.size() == 0 && xLastShoots.size() == 0) {
					shoot[0] = getRandomNumber(1, row);
					shoot[1] = getRandomNumber(1, 26);
				}
				//two down
				else if (xLastShoots.size() == 2 && xLastShoots.size() == 2)
				{
					int a = xLastShoots[1] - xLastShoots[0];
					int b = yLastShoots[1] - yLastShoots[0];

					//1
					if (a > 0 && b > 0) {
						shoot[0] = xLastShoots[1] + 1;
						shoot[1] = yLastShoots[1] + 1;
					}
					//2
					else if (a < 0 && b < 0)
					{
						shoot[0] = xLastShoots[1] - 1;
						shoot[1] = yLastShoots[1] - 1;
					}
					//3
					else if (a > 0 && b < 0)
					{
						shoot[0] = xLastShoots[1] + 1;
						shoot[1] = yLastShoots[1] - 1;
					}
					//4
					else if (a < 0 && b > 0)
					{
						shoot[0] = xLastShoots[1] - 1;
						shoot[1] = yLastShoots[1] + 1;
					}
					//5
					else if (a == 0 && b > 0)
					{
						shoot[0] = xLastShoots[1];
						shoot[1] = yLastShoots[1] + 1;
					}
					//6
					else if (a == 0 && b < 0)
					{
						shoot[0] = xLastShoots[1];
						shoot[1] = yLastShoots[1] - 1;
					}
					//7
					else if (a < 0 && b == 0)
					{
						shoot[0] = xLastShoots[1] - 1;
						shoot[1] = yLastShoots[1];
					}
					//8
					else if (a > 0 && b == 0)
					{
						shoot[0] = xLastShoots[1] + 1;
						shoot[1] = yLastShoots[1];
					}
					else
					{
						shoot[0] = getRandomNumber(1, row);
						shoot[1] = getRandomNumber(1, 26);
					}
				}
		
				if (AttackedShip == 0) {
					shoot[0] = getRandomNumber(1, row);
					shoot[1] = getRandomNumber(1, 26);
				}

				while (shoot[0] < 1 || shoot[1] > 26 || shoot[0] < 1 || shoot[0] > row)
				{
					shoot[0] = getRandomNumber(1, row);
					shoot[1] = getRandomNumber(1, 26);
					xLastShoots.clear();
					yLastShoots.clear();
					fireflag = 0;
					AttackedShip = 0;
				}
	/**		if (shoot[0] < 1 || shoot[1] > 26 || shoot[1] < 1 || shoot[2] > gra->Rows()-2) {
					shoot[0] = getRandomNumber(1, row);
					shoot[1] = getRandomNumber(1, 26);
					xLastShoots.clear();
					yLastShoots.clear();
					fireflag = 0;
					AttackedShip = 0;

				} **/


				if (this->Number == 0 && shoot[0] > 0 && shoot[0] <= gra->Rows() && shoot[1] > 0 && shoot[1] < 27) {

					if (gra->area1P[shoot[0]][shoot[1]] == ' ')
					{

						if (fireflag > 1000) {
							xLastShoots.clear();
							yLastShoots.clear();
							AttackedShip = 0;
						}
						gra->area1[shoot[0]][shoot[1]] = 'X';
						gra->area1P[shoot[0]][shoot[1]] = '*';
						fireflag = 0;
						wehave++;
						break;
					}
					else if (gra->area1P[shoot[0]][shoot[1]] == '*') {
						fireflag++;
						if (fireflag>1000) {
							xLastShoots.clear();
							yLastShoots.clear();
							fireflag = 0;
							AttackedShip = 0;
						}
					}
					else if (isdigit(gra->area1P[shoot[0]][shoot[1]])) {
						gra->area1[shoot[0]][shoot[1]] = gra->area1P[shoot[0]][shoot[1]];
						if (isdigit(gra->area1[shoot[0]][shoot[1]]) && AttackedShip == 0) { AttackedShip += (static_cast<int>(gra->area1[shoot[0]][shoot[1]]) - 48); }
						gra->area1P[shoot[0]][shoot[1]] = '*';
						AttackedShip--;
						fireflag = 0;

						if (xLastShoots.size() == 2 && xLastShoots.size() == 2 && AttackedShip != 0) {
							xLastShoots.erase(xLastShoots.begin());
							yLastShoots.erase(yLastShoots.begin());
						}


						//xLastShoots.clear();
						//yLastShoots.clear();

						xLastShoots.push_back(shoot[0]);
						yLastShoots.push_back(shoot[1]);

						//cout << "dl vektora:" << yLastShoots.size() << endl;

						if (xLastShoots.size() == 3 && xLastShoots.size() == 3 && AttackedShip == 0) {
							xLastShoots.clear();
							yLastShoots.clear();
							fireflag = 0;
							AttackedShip = 0;
						}
						wehave++;
						gra->player1pkt--;
						break;


					}
				}
	
				else if (this->Number == 1 && shoot[0] > 0 && shoot[0] <= gra->Rows() && shoot[1] > 0 && shoot[1] < 27) {


					if (gra->area0P[shoot[0]][shoot[1]] == ' ')
					{
						if (fireflag > 1000) {
							AttackedShip = 0;
							xLastShoots.clear();
							yLastShoots.clear();
						}
						gra->area0[shoot[0]][shoot[1]] = 'X';
						gra->area0P[shoot[0]][shoot[1]] = '*';
						wehave++;
						fireflag = 0;
						break;
					}
					else if (gra->area0P[shoot[0]][shoot[1]] == '*') {
						fireflag++;
						if (fireflag>1000) {
							xLastShoots.clear();
							yLastShoots.clear();
							fireflag = 0;
							AttackedShip = 0;
						}
					}
					else if (isdigit(gra->area0P[shoot[0]][shoot[1]])) {
						gra->area0[shoot[0]][shoot[1]] = gra->area0P[shoot[0]][shoot[1]];
						if (isdigit(gra->area0[shoot[0]][shoot[1]]) && AttackedShip == 0) { AttackedShip = (static_cast<int>(gra->area0[shoot[0]][shoot[1]]) - 48); }
						gra->area0P[shoot[0]][shoot[1]] = '*';
						AttackedShip--;
						fireflag = 0;

						if ((xLastShoots.size() == 2) && (xLastShoots.size() == 2) && (AttackedShip != 0)) {
							xLastShoots.erase(xLastShoots.begin());
							yLastShoots.erase(yLastShoots.begin());
						}

						//xLastShoots.clear();
						//yLastShoots.clear();

						xLastShoots.push_back(shoot[0]);
						yLastShoots.push_back(shoot[1]);

						//cout << "dl vektora:" << yLastShoots.size() << endl;

						if ((xLastShoots.size() == 3) && (xLastShoots.size() == 3) && (AttackedShip == 0)) {
							xLastShoots.clear();
							yLastShoots.clear();
							fireflag = false;
						}
						wehave++;
						gra->player0pkt--;
						break;


					}
				}

			}


		}

	};


	char **area;
	int iloscWierszy;
	int ShipsTypes[4];
public:
	int ShipType1() { return ShipsTypes[0]; }
	int ShipType2() { return ShipsTypes[1]; }
	int ShipType3() { return ShipsTypes[2]; }
	int ShipType4() { return ShipsTypes[3]; }
	
	
	char **area0P;
	char **area1P; // przechowuje polozenie statkow graczy


	char **area0;
	char **area1;


	int player0pkt;
	int player1pkt;


	int Rows() { return iloscWierszy; }

	void Play() {
		int choice;
		cout << "Wybierz tryb rozgrywki\n";
		cout << "Gracz vs CPU:   1\n";
		cout << "Gracz vs Gracz: 2\n";
		cout << "CPU vs CPU:     3\n";
		cin >> choice;
		system("pause");
		system("cls");
		this->Config();
		this->DefineArea();
		//this->DrawArea();
		system("cls");
		switch (choice) {
		case 1: {
			char key;
			Player *gracz0 = new Player(0, this);
			CPU *gracz1 = new CPU(1, this);
			gracz0->DefinePlayerArea();
			gracz0->Insert();
			cout << "Tak rozlokowales statki\n\n\n";
			gracz0->DrawPlayerArea();
			cout << "Tak rozlokowales statki\n\n\n";
			system("pause");
			system("cls");
			gracz1->DefinePlayerArea();
			gracz1->Insert();
			system("cls");
			while (1) {
					
					system("cls");
					cout << "Tutaj strzela Gracz 1\n";
					this->DrawArea1();
					cout << "\n" << "Gracz2 HP: " << player1pkt;
					cout << "\n\n\n";
					if (player1pkt == 0) { cout << "Gracz 1 wygrywa\n"; break; }
					
					if (player0pkt == 0) { cout << "Gracz 2 wygrywa\n"; break; }
					cout << "Tutaj strzela Gracz 2\n";
					this->DrawArea0();
					cout << "\n" << "Gracz1 HP: " << player0pkt << endl;
					
					gracz0->OrderToShoot();
					gracz1->OrderToShoot();
					cout << "\n\nSekunda na cheat\nCheat wyzwala sie poprzez przytrzymanie klawisza / ";
					Sleep(1000);
					while (_kbhit()) {
						key = _getch();
						if (key == 47) {
							system("cls");
							this->DrawArea1P();
							Sleep(100);

						}
					}
					system("cls");
					

			}break;
		}
		case 2: {
			char key;
			Player *gracz0 = new Player(0, this);
			Player *gracz1 = new Player(1, this);
			gracz0->DefinePlayerArea();
			cout << "Gracz1\n\n\n";
			gracz0->Insert();
			//	gracz0->DrawPlayerArea();
			system("pause");
			system("cls");
			gracz1->DefinePlayerArea();
			cout << "Gracz2\n\n\n";
			gracz1->Insert();
			system("cls");
			while (1) {

				cout << "Tutaj strzela Gracz 1\n";
				this->DrawArea1();
				cout << "\n" << "Gracz2 HP: " << player1pkt;
				cout << "\n\n";
				gracz0->OrderToShoot();
				system("cls");
				cout << "Tutaj strzela Gracz 1\n";
				this->DrawArea1();
				cout << "\n" << "Gracz2 HP: " << player1pkt;
				cout << "\n\n";
				system("pause");
				if (player1pkt == 0) { cout << "Gracz 1 wygrywa\n"; break; }
				system("cls");

				cout << "Tutaj strzela Gracz 2\n";
				this->DrawArea0();
				cout << "\n" << "Gracz1 HP: " << player0pkt;
				cout << "\n\n";
				gracz1->OrderToShoot();
				system("cls");
				cout << "Tutaj strzela Gracz 2\n";
				this->DrawArea0();
				cout << "\n" << "Gracz1 HP: " << player0pkt;
				cout << "\n\n";
				system("pause");
				if (player0pkt == 0) { cout << "Gracz 2 wygrywa\n"; break; }
				cout << "\n\nSekunda na cheat\nCheat wyzwala sie poprzez przytrzymanie klawisza / ";
				Sleep(1000);
				while (_kbhit()) {
					key = _getch();
					if (key == 47) {
						system("cls");
						cout << "Tutaj strzela Gracz 1\n";
						this->DrawArea1P();
						cout << "\n\n";
						cout << "Tutaj strzela Gracz 2\n";
						this->DrawArea0P();
						Sleep(100);

					}
				}
				system("cls");
				system("cls");

			//	if (player1pkt == 0) { cout << "Gracz 1 wygrywa\n"; break; }	
			//	if (player0pkt == 0) { cout << "Gracz 2 wygrywa\n"; break; }

			}break;
		}
		case 3: {
			CPU *gracz0 = new CPU(0, this);
			CPU *gracz1 = new CPU(1, this);
			gracz0->DefinePlayerArea();
			gracz0->Insert();
			//	gracz0->DrawPlayerArea();
			system("pause");
			system("cls");
			gracz1->DefinePlayerArea();
			gracz1->Insert();
			system("cls");
			while (1) {
				gracz0->OrderToShoot();
				cout << "Tutaj strzela Gracz 1\n";
				this->DrawArea1();
				cout << "\n" << "Gracz2 HP: " << player1pkt;
				cout << "\n\n\n";
				if (player1pkt == 0) { cout << "Gracz 1 wygrywa\n"; break; }
				gracz1->OrderToShoot();
				if (player0pkt == 0) { cout << "Gracz 2 wygrywa\n"; break; }
				cout << "Tutaj strzela Gracz 2\n";
				this->DrawArea0();
				cout << "\n" << "Gracz1 HP: " << player0pkt;
				Sleep(200);
				system("cls");

			}break;
		}
		default: {
			CPU *gracz0 = new CPU(0, this);
			CPU *gracz1 = new CPU(1, this);
			gracz0->DefinePlayerArea();
			gracz0->Insert();
			//	gracz0->DrawPlayerArea();
			system("pause");
			system("cls");
			gracz1->DefinePlayerArea();
			gracz1->Insert();
			system("cls");
			while (1) {
				gracz0->OrderToShoot();
				cout << "Tutaj strzela Gracz 1\n";
				this->DrawArea1();
				cout << "\n" << "Gracz2 HP: " << player1pkt;
				cout << "\n\n\n";
				if (player1pkt == 0) { cout << "Gracz 1 wygrywa\n"; break; }
				gracz1->OrderToShoot();
				cout << "Tutaj strzela Gracz 2\n";
				this->DrawArea0();
				if (player0pkt == 0) { cout << "Gracz 2 wygrywa\n"; break; }
				cout << "\n" << "Gracz1 HP: " << player0pkt;
				Sleep(200);
				system("cls");

			}break;
		}
		}
		cout << "papapa\n";
		//system("pause");
		system("exit");
	}


	void Config() {
		while (1) {
			cout << "Ile wierszy\n";
			cin >> iloscWierszy;

			if (iloscWierszy >= 3 && iloscWierszy <= 10000) {
				area = new char *[iloscWierszy + 2];
				for (int i = 0; i <= iloscWierszy+2; i++) {
					area[i] = new char[28];
				}
				break;
			}
			else {
				cout << "Niewlasciwa liczba podaj min 3 \n";
			}
		}
		int a = (24 * iloscWierszy);
		ShipsTypes[0]=(static_cast<int>(a * 0.03 / 5));
		ShipsTypes[1]=(static_cast<int>(a * 0.03 / 4));
		ShipsTypes[2]=(static_cast<int>(a * 0.03 / 3));
		ShipsTypes[3]=(static_cast<int>(a * 0.03 / 2));
		cout << "Gramy w nastepujacej konfiguracji \n";
		cout << "Tabela 26x" << iloscWierszy << endl;
		cout << "Pieciomasztowce " << ShipsTypes[0] << endl;
		cout << "Czteromasztowce " << ShipsTypes[1] << endl;
		cout << "Trzyomasztowce " << ShipsTypes[2] << endl;
		cout << "Dwumasztowce " << ShipsTypes[3] << endl;

		player0pkt = 5 * ShipsTypes[0] + 4 * ShipsTypes[1] + 3 * ShipsTypes[2] + 2 * ShipsTypes[3];
		player1pkt = 5 * ShipsTypes[0] + 4 * ShipsTypes[1] + 3 * ShipsTypes[2] + 2 * ShipsTypes[3];
		system("pause");
	}

	void DefineArea() {
		for (int i = 0; i < iloscWierszy + 2; i++) {
			for (int j = 0; j < 28; j++) {
				area[i][j] = '*';
			}
			area0 = new char *[iloscWierszy + 2];
			for (int i = 0; i <= iloscWierszy + 2; i++) {
				area0[i] = new char[28];
			}

			for (int i = 0; i < iloscWierszy + 2; i++) {
				for (int j = 0; j < 28; j++) {
					area0[i][j] = '*';
				}
			}

			area1 = new char *[iloscWierszy + 2];
			for (int i = 0; i <= iloscWierszy + 2; i++) {
				area1[i] = new char[28];
			}

			for (int i = 0; i < iloscWierszy + 2; i++) {
				for (int j = 0; j < 28; j++) {
					area1[i][j] = '*';
				}
			}

			area0P = new char *[iloscWierszy + 2];
			for (int i = 0; i <= iloscWierszy + 2; i++) {
				area0P[i] = new char[28];
			}

			for (int i = 0; i < iloscWierszy + 2; i++) {
				for (int j = 0; j < 28; j++) {
					area0P[i][j] = '*';
				}
			}

			area1P = new char *[iloscWierszy + 2];
			for (int i = 0; i <= iloscWierszy + 2; i++) {
				area1P[i] = new char[28];
			}
		}

		for (int i = 0; i < iloscWierszy + 2; i++) {
			for (int j = 0; j < 28; j++) {
				area1P[i][j] = '*';
			}
		}
	}

	//rysuje tabele gracza (cheat)
	void DrawArea0P() {
		//system("cls");
		cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
		for (int i = 1; i < iloscWierszy + 1; i++) {
			for (int j = 1; j < 27; j++) {
				cout << " " << area0P[i][j] << " ";
			}
			cout << i << '\n';
		}
	}

	void DrawArea1P() {
		//system("cls");
		cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
		for (int i = 1; i < iloscWierszy + 1; i++) {
			for (int j = 1; j < 27; j++) {
				cout << " " << area1P[i][j] << " ";
			}
			cout << i << '\n';
		}
	}

	void DrawArea0() {
		//system("cls");
		cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
		for (int i = 1; i < iloscWierszy + 1; i++) {
			for (int j = 1; j < 27; j++) {
				cout << " " << area0[i][j] << " ";
			}
			cout << i << '\n';
		}
	}

	void DrawArea1() {
		//system("cls");
		cout << " A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  P  Q  R  S  T  U  V  W  X  Y  Z\n";
		for (int i = 1; i < iloscWierszy + 1; i++) {
			for (int j = 1; j < 27; j++) {
				cout << " " << area1[i][j] << " ";
			}
			cout << i << '\n';
		}
	}

		
};



int main()
{
	
	srand(static_cast<unsigned int>(time(NULL)));
	Game *a = new Game();
	a->Play();

	

	

	system("pause");
    return 0;
}

