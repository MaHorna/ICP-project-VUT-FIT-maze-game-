Projekt ICP 2022/2023 - Pacman bludisko hra

Autor:
Matej Horňanský (xhorna17)

Popis programu:
Aplikácia umožní hrať hru typu Pac-Man, užívateľ ovláda panáčika pomocou WSAD alebo hore, dole, vlavo, vpravo šípkami. Panáčik sa pohybuje po bludisku z východzieho postavenia do cieľového.
V bludisku sa samostatne pohybujú duchovia. Ak sa panáčik stretne s duchom, hra (level) končí neúspechom.
Hra sa spúšťa medzerníkom a dá sa medzerníkom aj pozastaviť.
Mapa bludiska sa načíta pri spustení aplikácie zo súboru (možno vybrať z viacerých uloženýchmáp).
Priebeh hry je možné logovať (ukladať) do súboru a následne prehrať.

Ovládanie:
Hra - WSAD/šípky , medzerník - pause/play
Prehrávanie - X - začiatok, C -  koniec, lavá šípka - posun o krok späť, pravá šípka - posun o krok vpred , šípka hore - continuálne prehrávanie, šípka dole - prehrávanie po krokoch, medzerník - pause/play , alebo ovládanie s GUI tlačidlami.
Načítanie súborov: vyskakovacie okno (príklady pre hru a prehrávanie sú v priečinku examples)
Ukladanie súborov: vyskakovacie okno - je potrebné napísať celé meno súboru ("test1.txt") a uložiť(enter/tlačidlo)

Preklad a beh:
C++ program, využíva QT knižnice. je možné ho spustiť príkazom make:
make         - preloží program
make run     - preloží program a spustí ho
make clean   - vymaže vygenerované súbory
make pack    - vytvorí archív pre odovzdanie
make doxygen - vytvorí dokumentáciu

Preložený program s názvom icp_projekt_xhorna17 sa nachádza v zložke src.
Index dokumentácie - doc/html/index.html

Obmedzenia:
Nebol implementovaný pohyb myšou. 

Implementované: načítanie mapy, GUI, pohyb, prehra a výhra, logovanie hry, uloženie do súboru, prehratie tohto súboru krokmi aj plynule, skóre, počet krokov, čas hry, ovládanie klávesnicou
