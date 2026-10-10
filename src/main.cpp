
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

const int MAX_MOKINIAI = 100;
const int MAX_PAZYMIU = 10;

int showMenu() {
  int pasirinkimas = 0;
  while (pasirinkimas < 1 || pasirinkimas > 7) {
    cout << "1 - Įvesti mokinį ir jo pažymius." << endl;
    cout << "2 - Peržiūrėti visų mokinių pažymius." << endl;
    cout << "3 - Peržiūrėti konkretaus mokinio pažymius." << endl;
    cout << "4 - Atnaujinti pažymį." << endl;
    cout << "5 - Apskaičiuoti mokinio vidurkį." << endl;
    cout << "6 - Pašalinti mokinį." << endl;
    cout << "7 - Išeiti." << endl;

    cin >> pasirinkimas;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
      pasirinkimas = 0;
    }
    if (pasirinkimas < 1 || pasirinkimas > 7)
      cout << "Netinkamas pasirinkimas." << endl;
  }

  return pasirinkimas;
}
int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  // 100 mokiniu, 10 pazimiu
  int pazymiai[MAX_MOKINIAI][MAX_PAZYMIU] = {};
  // mokiniu vardai
  string vardai[MAX_MOKINIAI] = {};

  int pazymiuKiekis[MAX_MOKINIAI] = {};
  int mokiniuKiekis = 0;

  while (true) {
    int pasirinkimas = showMenu();
    if (pasirinkimas == 7) {
      cout << "Viso gero!" << endl;
      break;
    }

    if (pasirinkimas == 1) {
      if (mokiniuKiekis == MAX_MOKINIAI) {
        cout << "Mokiniu limitas pasiektas." << endl;
        continue;
      }

      cout << "Iveskite mokinio varda: ";
      cin >> vardai[mokiniuKiekis];

      cout << "Kiek pazymiu? (0-10): ";
      cin >> pazymiuKiekis[mokiniuKiekis];

      // Ivesti kieki tol kol skaicius bus tinkamas...
      while (pazymiuKiekis[mokiniuKiekis] < 0 ||
             pazymiuKiekis[mokiniuKiekis] > MAX_PAZYMIU) {
        cout << "Iveskite skaiciu nuo 0 iki 10: ";
        cin >> pazymiuKiekis[mokiniuKiekis];
      }

      for (int i = 0; i < pazymiuKiekis[mokiniuKiekis]; i++) {
        cout << "Iveskite " << i + 1 << " pazymi (1-10): ";
        cin >> pazymiai[mokiniuKiekis][i];

        // Įvesti pažymi tol kol bus tinkamas
        while (pazymiai[mokiniuKiekis][i] < 1 ||
               pazymiai[mokiniuKiekis][i] > 10) {
          cout << "Iveskite skaiciu nuo 1 iki 10: ";
          cin >> pazymiai[mokiniuKiekis][i];
        }
      }

      mokiniuKiekis++;
    }
    if (pasirinkimas == 2) {
      cout << "Vardas | Pazymiai" << endl;
      cout << "-----------------" << endl;

      for (int i = 0; i < mokiniuKiekis; i++) {
        cout << vardai[i] << " | ";
        for (int j = 0; j < pazymiuKiekis[i]; j++) {
          cout << pazymiai[i][j] << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
    if (pasirinkimas == 3) {
      if (mokiniuKiekis == 0) {
        cout << "Mokiniu sarasas tuscias." << endl;
        continue;
      }

      int mokinioNumeris;
      cout << "Iveskite mokinio numeri (1-" << mokiniuKiekis << "): ";
      cin >> mokinioNumeris;
      while (mokinioNumeris < 1 || mokinioNumeris > mokiniuKiekis) {
        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki "
             << mokiniuKiekis << ": ";
        cin >> mokinioNumeris;
      }

      int mokinioIndeksas = mokinioNumeris - 1;
      cout << vardai[mokinioIndeksas] << " | ";
      for (int j = 0; j < pazymiuKiekis[mokinioIndeksas]; j++) {
        cout << pazymiai[mokinioIndeksas][j] << " ";
      }
      cout << endl << endl;
    }
  }

  return 0;
}
