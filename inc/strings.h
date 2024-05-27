#include <string>
#include <map>

using std::string, std::map;

enum Message
{
  ERR_RES,
  ERR_CARS,
  ERR_CLIENTS,
  ERR_REPORTS,

  ERR_WRONG_LOGIN,
  ERR_WRONG_PASS,
  ERR_LOGIN_EXISTS,

  ERR_ALREADY_RENTED,

  LOG_IN,
  REGISTER,
  QUIT,

  ACCEPT_RULES,

  ACCOUNT_CREATED,

  SHOW_PROFILE,
  BROWSE_CARS,
  REPORT_ISSUE,
  LOGOUT,
  CAR_RENTED,

  REPORT_ISSUE_PROMPT,

  BACK_MENU,

  AVAIL_CARS,

  PRICE,
  CURRENCY,
  AVAIL_AMOUNT,

  RENT,
  SEE_DETAILS,

  RENT_INPUT_NUM,

  INPUT_LOGIN,
  INPUT_PASS,
  INPUT_NAME,
  INPUT_SURNAME,

};

map<Message, string> translateableMessages{
    {ERR_RES, "Nie znaleziono katalogu zasobów. Utworzono domyślny."},
    {ERR_CARS, "Nie znaleziono pliku konfiguracji samochodów. Utworzono domyślny."},
    {ERR_CLIENTS, "Nie znaleziono katalogu danych klientów. Utworzono domyślny."},
    {ERR_REPORTS, "Nie znaleziono pliku dziennika zgłoszeń. Utworzono domyślny."},

    {ERR_WRONG_LOGIN, "Nieprawidłowy login"},
    {ERR_WRONG_PASS, "Nieprawidłowe hasło"},
    {ERR_LOGIN_EXISTS, "Konto z takim loginem już istnieje."},

    {ERR_ALREADY_RENTED, "Już masz wypożyczony samochód."},

    {LOG_IN, "Zaloguj się"},
    {REGISTER, "Utwórz nowy profil"},
    {QUIT, "Wyjdź"},

    {ACCEPT_RULES, "Akceptuj"},

    {ACCOUNT_CREATED, "Konto zostało utworzone. Możesz się teraz zalogować.\n\n"},

    {SHOW_PROFILE, "Wyświetl swój profil"},
    {BROWSE_CARS, "Przeglądaj ofertę"},
    {REPORT_ISSUE, "Zgłoś usterkę"},
    {LOGOUT, "Wyloguj"},
    {CAR_RENTED, " Wypożyczony samochód: "},

    {REPORT_ISSUE_PROMPT, "Opisz swój problem i zatwierdź [enter]."},

    {BACK_MENU, "Powrót do menu"},

    {AVAIL_CARS, "\nDostępne samochody\n\n"},

    {PRICE, "Cena"},
    {CURRENCY, "zł"},
    {AVAIL_AMOUNT, "Dostępna ilość"},

    {RENT, "Wypożycz samochód"},
    {SEE_DETAILS, "Wyświetl szczegóły o samochodzie"},

    {RENT_INPUT_NUM, "Podaj numer samochodu."},

    {INPUT_LOGIN, "Podaj login"},
    {INPUT_PASS, "Podaj hasło"},
    {INPUT_NAME, "Podaj imię"},
    {INPUT_SURNAME, "Podaj nazwisko"},
};

const string rules = R"(
Regulamin serwisu

1. Postanowienia ogólne
1.1. Regulamin określa zasady korzystania z usługi carsharingu 'Autko'.
1.2. Korzystając z usługi, użytkownik akceptuje wszystkie postanowienia regulaminu.
1.3. Usługa jest dostępna dla osób, które posiadają ważne prawo jazdy.

2. Rejestracja i konto użytkownika
2.1. Aby skorzystać z usługi, użytkownik musi zarejestrować się na platformie.
2.2. Rejestracja wymaga podania prawdziwych danych osobowych.
2.3. Użytkownik zobowiązuje się do aktualizowania swoich danych osobowych w przypadku ich zmiany.

3. Rezerwacja i wynajem pojazdu
3.1. Użytkownik może rezerwować pojazdy aplikacji.
3.2. Wynajem pojazdu rozpoczyna się w momencie wybrania odpowiedniej opcji w aplikacji i kończy się po zakończeniu sesji w aplikacji.

4. Opłaty
4.1. Opłata za korzystanie z pojazdu jest naliczana na podstawie minutowego taryfikatora.
4.2. Użytkownik zobowiązuje się do terminowego uiszczania opłat za wynajem pojazdu. W przypadku przekroczenia maksymalnego czasu wypożyczenia naliczana jest kara w wysokości 250zł.
4.3. W przypadku opóźnień w płatnościach, naliczane będą odsetki karne zgodnie z obowiązującymi przepisami prawa.

5. Zasady korzystania z pojazdu
5.1. Użytkownik zobowiązuje się do korzystania z pojazdu zgodnie z jego przeznaczeniem i w sposób zgodny z przepisami ruchu drogowego.
5.2. Zabrania się palenia tytoniu oraz spożywania alkoholu w pojeździe.
5.3. Użytkownik jest zobowiązany do dbania o czystość pojazdu i zgłaszania wszelkich uszkodzeń lub usterek przed rozpoczęciem jazdy.

6. Odpowiedzialność i ubezpieczenie
6.1. Pojazdy są objęte ubezpieczeniem OC i AC.
6.2. Użytkownik ponosi odpowiedzialność za wszelkie szkody powstałe z jego winy do kwoty 1000 PLN (franszyza).
6.3. W przypadku kradzieży pojazdu z winy użytkownika, użytkownik ponosi pełną odpowiedzialność finansową.

7. Rozwiązanie umowy
7.1. Umowa o korzystanie z usługi carsharingu może być rozwiązana przez każdą ze stron z zachowaniem 7-dniowego okresu wypowiedzenia.
7.2. Usługodawca ma prawo do natychmiastowego rozwiązania umowy w przypadku naruszenia regulaminu przez użytkownika.

8. Postanowienia końcowe
8.1. Regulamin wchodzi w życie z dniem jego publikacji.
8.2. Usługodawca zastrzega sobie prawo do wprowadzania zmian w regulaminie. O wszelkich zmianach użytkownicy będą informowani z 14-dniowym wyprzedzeniem.
8.3. W sprawach nieuregulowanych regulaminem mają zastosowanie przepisy prawa polskiego.
)";

const string defaultCarsConf = R"(
# This is a config file for all available cars. It can be updated in runtime using appropriate methods.
# This file is required for the program to function properly and it must have at least one car configured.
#
# The structure looks like this;
#
# cars:                       # main key
#  1:                         # car id - these are next integers from onwards
#    brand: "FSO"             # car brand
#    model: "Polonez Caro"    # car model
#    price: 10                # car price per minute
#    quantity: 1              # amount of all cars this type
#    specs:                   # misc car specifications - this should be self-explanatory
#      year: 1993
#      hp: 65
#      vmax: 150
#      seats: 5
#      doors: 5

cars:
  1:
    brand: "FSO"
    model: "Polonez Caro"
    price: 0.5
    quantity: 1
    specs:
      year: 1993
      hp: 65
      vmax: 150
      seats: 5
      doors: 5
  2:
    brand: "ZAZ"
    model: "Tavria"
    price: 0.75
    quantity: 3
    specs:
      year: 1989
      hp: 50
      vmax: 150
      seats: 5
      doors: 5
  3:
    brand: "Wartburg"
    model: "353"
    price: 1
    quantity: 1
    specs:
      year: 1979
      hp: 70
      vmax: 120
      seats: 5
      doors: 5
)";