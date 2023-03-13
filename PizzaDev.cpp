#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <string>

using namespace std;

const unsigned short int sizeOfMenu = 35;                       // zmienna zapisujaca ilosc pozycji w menu
int counter;                                                    // zmienna zapisujaca ilosc pozycji w zamowieniu
int total;                                                      // zmienna zapisujaca sume zamowienia (PLN)

void restaurantData()                                           // wczytywanie pliku tekstowego z menu
{
    ifstream restaurantInfo("restaurantInfo.txt");
    if (restaurantInfo.is_open())
    {
        string line;
        while (getline(restaurantInfo, line))
        {
            cout << line << endl;
        }
        restaurantInfo.close();
    }
}

void enterName(string name)                                     // wprowadzenie imienia uzytkownika
{
    cout << "Jak masz na imie?" << endl;
    cin >> name;
    system("cls");
    cout << "Witaj, " << name << "!" << endl;
}

void deliveryHour(char c, int hour, int min)                    // funkcja ustalajaca godzine dostawy
{
    cout << "Podaj preferowana godzine dowozu (HH:MM): \n";
    cin >> hour >> c >> min;                                    // uzytkownik wpisuje godzine

    if (hour < 0 || hour > 24 || min < 0 || min > 59)           // sprawdza poprawnosc godziny (0-24)
    {
        cout << "Niepoprawna godzina, sprobuj jeszcze raz\n";
        deliveryHour(c, hour, min);
    }
    else if (hour >= 20 || hour < 10)                           // sprawdza czy godzina miesci sie w godzinach otwarcia
    {
        cout << "Nasza restauracja jest zamknieta w tych godzinach.\n";
        deliveryHour(c, hour, min);
    }
    else                                                        // gdy godzina jest poprawna, przechodzi dalej
    {
        cout << "Teraz przejdz do zlozenia zamowienia";
    }
}

bool delivery(string street, string house_number, string postcode, string city)     // funkcja dostawy, ustala i zapisuje adres klienta i godzine dowozu
{
    cout << "Wpisz adres dowozu" << endl << "Ulica: ";
    cin.ignore();
    getline(cin, street);
    cout << "Numer budynku i/lub lokalu: ";
    getline(cin, house_number);
    cout << "Kod pocztowy: ";
    getline(cin, postcode);
    cout << "Miejscowosc (bez polskich znakow): ";
    getline(cin, city);


    if (city == "Poznan" || city == "poznan")
    {
        cout << "--Adres zapisano--\n";

        char c = NULL;
        int hour = NULL, min = NULL;
        deliveryHour(c, hour, min);
        return true;                                            // program zapisuje wprowadzone dane po poprawnym wpisaniu miasta
    }
    else
    {
        cout << "Niestety, nasza restauracja nie realizuje obecnie dowozow do Twojej miejscowosci" << endl;
        return false;                                           // program konczy swoje dzialanie
    }
}

void onSite()                                                   // generowanie numeru stolika dla uzytkownika
{
    int max;
    max = 20;                                                   //liczba stolikow w naszej restauracji to 20
    srand(time(0));                                             //random number generator
    cout << "Numer Twojego stolika to " << rand() % max;
}

bool userChoice()                                               // wybor zamowienia na miejscu lub z dostawa
{
    char sign = NULL;
    string ulica, nr_domu, kod_pocztowy, miejscowosc;

    do
    {
        cout << "Dzisiaj zamawiam: " << endl;
        cout << "1) Z dostawa" << endl << "2) Na miejscu" << endl;
        cin >> sign;

        if (sign == '1')
        {
            return delivery(ulica, nr_domu, kod_pocztowy, miejscowosc);
        }
        else if (sign == '2')
        {
            onSite();
            return true;
        }
        else
        {
            cout << "Niepoprawny numer, wybierz jeszcze raz";
        }
        cout << endl;
    } while (true);
}

void ordering(string orderedMeals[], int quantityTab[], int priceTab[])
{
    string line;                                                // zmienna do wczytywania tekstu z plikow
    fstream myFile;                                             // zmienna otwierajaca wszystskie pliki tekstowe
    myFile.open("PizzaDevMenu.txt", ios::in);                   // wczytywanie pliku tekstowego z menu restauracji
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            cout << line << endl;
        }
        myFile.close();
    }

    int i = 0;                                                  // licznik do tablicy menu
    string fmenu[sizeOfMenu];                                   // deklaracja tablicy z nazwami menu

    myFile.open("fmenu.txt", ios::in);                          // wczytywanie pliku tekstowego z nazwami pozycji z menu
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            fmenu[i] = line;                                    // zapisywanie kazdej linijki do tablicy
            i++;
        }
        myFile.close();
    }

    i = 0;
    int prices[sizeOfMenu];

    myFile.open("prices.txt", ios::in);                         // wczytywanie pliku tekstowego z cenami pozycji z menu
    if (myFile.is_open())
    {
        while (getline(myFile, line))
        {
            prices[i] = stoi(line);                             // zapisywanie kazdej linijki do tablicy
            i++;
        }
        myFile.close();
    }

    counter = 0;
    total = 0;

    char w = 'T';
    while (w == 'T')
    {
        int mealNum;
        int quantity;

        do {
            cout << "\nWybierz numer do zamowienia: ";              // wybor dania
            cin >> mealNum;

            if (mealNum >= 1 && mealNum <= sizeOfMenu) {            // sprawdzenie poprawnosci wybranego numeru zamowienia
                break;
            }
            else {
                cout << "\nWybrana pozycja nie znajduje sie w menu. Prosze wybrac numer od 1 do " << sizeOfMenu << ".\n";
            }
        } while (1);

        cout << "\nWybrales: " << fmenu[mealNum - 1] << endl;       // wyswietlenie zamowionego dania
        orderedMeals[counter] = fmenu[mealNum - 1];                 // zapisywanie nazwy dania w tablicy orderedMeals

        cout << "\nIlosc: ";                                        // ilosc zamowionego dania
        cin >> quantity;
        quantityTab[counter] = quantity;

        cout << "Czy chcesz zamowic kolejna rzecz? (TAK - T / NIE - N)" << endl; // okreslenie czy chce sie zamowic kolejne danie
        cin >> w;
        w = toupper(w);

        int mealPrice = prices[mealNum - 1] * quantity;              // uwzglednienie ilosci zamowionego dania w cenie
        priceTab[counter] = mealPrice;                               // zapisanie cen zamowionych dan w priceTab
        total = total + mealPrice;

        cout << "\n\n\t\t\tTWOJ RACHUNEK\n\n";
        for (int i = 0; i <= counter; i++) {
            cout << orderedMeals[i] << " * " << quantityTab[i] << "\t\t\t" << priceTab[i] << " PLN" << endl;
        }
        cout << "\n------------------------------------------------------------\n";
        cout << "Razem" << "\t\t - \t\t" << total << " PLN\n" << endl;

        counter++;
    }
}

void createBill(string orderedMeals[], int quantityTab[], int priceTab[]) {     // wczytanie pliku tekstowego z rachunkiem
    int waitingTime;
    waitingTime = 70;
    srand(time(0));

    cout << "Twoje zamowienie jest w trakcie realizacji. Przyblizony czas oczekiwania to okolo ";
    cout << (rand() % waitingTime) + 10 << " min.\n";                 // czas oczekiwanie miesci sie w przedziale 10-80 min
    cout << "Oto Twoj rachunek: \n\n";

    ofstream bill;                                                    // utworzenie obiektu na wyniki
    bill.open("bill.txt");                                            // przypisanie obiektu z plikiem

    if (!bill.is_open()) {
        cout << "Otwarcie pliku nie powiodlo sie.\nProgram zostanie zakonczony.";
        exit(EXIT_FAILURE);
    }

    bill << "\t\t\t\tRACHUNEK\n\n";
    for (int i = 0; i < counter; i++) {
        bill << orderedMeals[i] << " * " << quantityTab[i] << "\t\t\t" << priceTab[i] << " PLN" << endl;
    }
    bill << "\n------------------------------------------------------------\n";
    bill << "Razem" << "\t\t\t - \t\t\t" << total << " PLN\n" << endl;
    bill << "DZIEKUJEMY I ZAPRASZAMY PONOWNIE!" << endl << endl;

    bill.close();
}

void printBill() {                                          // drukowanie rachunku na podstawie zamowienia uzytkownika
    string line;
    fstream bill;

    bill.open("bill.txt");

    while (bill.good()) {
        getline(bill, line);
        cout << line << endl;
    }

    bill.close();
}

int main()
{
    restaurantData();
    cout << endl;

    string imie;
    enterName(imie);

    if (userChoice())
    {
        cout << endl;

        const int max = 10;
        string orderedMeals[max];
        int quantityTab[max];
        int priceTab[max];

        ordering(orderedMeals, quantityTab, priceTab);
        createBill(orderedMeals, quantityTab, priceTab);
        printBill();
    }
    system("pause");
    return 0;
}