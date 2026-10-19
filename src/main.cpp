
#include <iomanip>
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
      // ignoruoja 10000 chars po new line
      // nes kitaip pasidaro recursive loop
      cin.ignore(10000, '\n');

      pasirinkimas = 0;
    }

    if (pasirinkimas < 1 || pasirinkimas > 7)
      cout << "Netinkamas pasirinkimas." << endl;
  }

  return pasirinkimas;
}

int main() {
  // UTF8 formatas konsolei kad leistu lietuviskas raides
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
    // Išeiti.
    if (pasirinkimas == 7) {
      cout << "Viso gero!" << endl;
      break;
    }

    // Įvesti mokinį ir jo pažymius
    if (pasirinkimas == 1) {
      if (mokiniuKiekis == MAX_MOKINIAI) {
        cout << "Mokiniu limitas pasiektas." << endl;
        continue;
      }

      cout << "Iveskite mokinio varda: ";
      // istrina 10000 characters po \n !!!!
      cin.ignore(10000, '\n');

      getline(cin, vardai[mokiniuKiekis]);

      cout << "Kiek pazymiu? (0-10): ";
      cin >> pazymiuKiekis[mokiniuKiekis];

      while (cin.fail() ||
             pazymiuKiekis[mokiniuKiekis] < 0 ||
             pazymiuKiekis[mokiniuKiekis] > MAX_PAZYMIU) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Iveskite skaiciu nuo 0 iki 10: ";
        cin >> pazymiuKiekis[mokiniuKiekis];
      }


      for (int i = 0; i < pazymiuKiekis[mokiniuKiekis]; i++) {
        cout << "Iveskite " << i + 1 << " pazymi (1-10): ";
        cin >> pazymiai[mokiniuKiekis][i];

        while (cin.fail() || pazymiai[mokiniuKiekis][i] < 1 ||
               pazymiai[mokiniuKiekis][i] > 10) {
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Iveskite skaiciu nuo 1 iki 10: ";
          cin >> pazymiai[mokiniuKiekis][i];
        }
      }

      mokiniuKiekis++;
    }

    // Peržiūrėti visų mokinių pažymius.
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

    // Peržiūrėti konkretaus mokinio pažymius.
    if (pasirinkimas == 3) {
      if (mokiniuKiekis == 0) {
        cout << "Mokiniu sarasas tuscias." << endl;
        continue;
      }

      int mokinioNumeris;
      cout << "Iveskite mokinio numeri (1-" << mokiniuKiekis << "): ";
      cin >> mokinioNumeris;
      while (cin.fail() || mokinioNumeris < 1 ||
             mokinioNumeris > mokiniuKiekis) {
        cin.clear();
        cin.ignore(10000, '\n');
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

    // Atnaujinti pažymį.
    if (pasirinkimas == 4) {
      if (mokiniuKiekis == 0) {
        cout << "Mokiniu sarasas tuscias." << endl;
        continue;
      }

      for (int i = 0; i < mokiniuKiekis; i++) {
        cout << i + 1 << " - " << vardai[i] << endl;
      }

      int mokinioNumeris;
      cout << "Iveskite mokinio numeri (1-" << mokiniuKiekis << "): ";
      cin >> mokinioNumeris;
      while (cin.fail() || mokinioNumeris < 1 ||
             mokinioNumeris > mokiniuKiekis) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki "
             << mokiniuKiekis << ": ";
        cin >> mokinioNumeris;
      }

      // mokinio num to index num
      int mokinioIndeksas = mokinioNumeris - 1;
      if (pazymiuKiekis[mokinioIndeksas] == 0) {
        cout << "Mokinys pazymiu neturi." << endl;
        continue;
      }

      int pazymioNumeris;
      cout << "Iveskite pazymio numeri (1-" << pazymiuKiekis[mokinioIndeksas]
           << "): ";
      cin >> pazymioNumeris;
      while (cin.fail() || pazymioNumeris < 1 ||
             pazymioNumeris > pazymiuKiekis[mokinioIndeksas]) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisingas pazymio numeris. Iveskite skaiciu nuo 1 iki "
             << pazymiuKiekis[mokinioIndeksas] << ": ";
        cin >> pazymioNumeris;
      }

      int naujasPazymys;
      cout << "Iveskite nauja pazymi (1-10): ";
      cin >> naujasPazymys;
      while (cin.fail() || naujasPazymys < 1 || naujasPazymys > 10) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Iveskite skaiciu nuo 1 iki 10: ";
        cin >> naujasPazymys;
      }

      pazymiai[mokinioIndeksas][pazymioNumeris - 1] = naujasPazymys;
      cout << "Pazymys atnaujintas." << endl;
    }

    // Apskaičiuoti mokinio vidurkį.
    if (pasirinkimas == 5) {
      if (mokiniuKiekis == 0) {
        cout << "Mokiniu sarasas tuscias." << endl;
        continue;
      }

      for (int i = 0; i < mokiniuKiekis; i++) {
        cout << i + 1 << " - " << vardai[i] << endl;
      }

      int mokinioNumeris;
      cout << "Iveskite mokinio numeri (1-" << mokiniuKiekis << "): ";
      cin >> mokinioNumeris;
      while (cin.fail() || mokinioNumeris < 1 ||
             mokinioNumeris > mokiniuKiekis) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki "
             << mokiniuKiekis << ": ";
        cin >> mokinioNumeris;
      }

      int mokinioIndeksas = mokinioNumeris - 1;
      if (pazymiuKiekis[mokinioIndeksas] == 0) {
        cout << "Mokinys pazymiu neturi." << endl;
        continue;
      }

      int suma = 0;
      for (int i = 0; i < pazymiuKiekis[mokinioIndeksas]; i++) {
        suma += pazymiai[mokinioIndeksas][i];
      }

      double vidurkis =
          static_cast<double>(suma) / pazymiuKiekis[mokinioIndeksas];
      cout << vardai[mokinioIndeksas] << " vidurkis: " << fixed
           << setprecision(2) << vidurkis << endl;
    }

    // Pašalinti mokinį.
    if (pasirinkimas == 6) {
      if (mokiniuKiekis == 0) {
        cout << "Mokiniu sarasas tuscias." << endl;
        continue;
      }

      for (int i = 0; i < mokiniuKiekis; i++) {
        cout << i + 1 << " - " << vardai[i] << endl;
      }

      int mokinioNumeris;
      cout << "Iveskite mokinio numeri (1-" << mokiniuKiekis << "): ";
      cin >> mokinioNumeris;
      while (cin.fail() || mokinioNumeris < 1 ||
             mokinioNumeris > mokiniuKiekis) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Neteisingas mokinio numeris. Iveskite skaiciu nuo 1 iki "
             << mokiniuKiekis << ": ";
        cin >> mokinioNumeris;
      }

      int mokinioIndeksas = mokinioNumeris - 1;
      for (int i = mokinioIndeksas; i < mokiniuKiekis - 1; i++) {
        vardai[i] = vardai[i + 1];
        pazymiuKiekis[i] = pazymiuKiekis[i + 1];
        for (int j = 0; j < MAX_PAZYMIU; j++) {
          pazymiai[i][j] = pazymiai[i + 1][j];
        }
      }

      mokiniuKiekis--;
      cout << "Mokinys pasalintas." << endl;
    }
  }

  return 0;
}
