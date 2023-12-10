# chess_clock_esp32
Clock for playing chess with ESP32 and two 7-segments displays

This is my first project on GitHub.
I created my chess clock with ESP32 S2 mini.
After a little modification, any other microcontroller can be used.

Game flow
The clock is set to five minutes. After switching it on, the buttons can change the game time. The starting player presses the button pulls and presses the button again. Subsequently, the players take turns in the game. When one player has zero minutes on the clock, the timer stops and the winning player wins.
Pressing both buttons makes it possible to return to the beginning.

Connecting
The code for the ESP 32 S2 mini is posted on Git Hub. The wiring of the individual components is according to the attached diagram.
To assemble it, you need
- ESP 32 S2 mini (or other microcontroller)
- 2 x TM1637 display module
- 2 x push button self-recovery 
- TP4056 charging module
- SPDT slide switch
- li-ion battery - 16850



CZ

Vytvořil jsem si vlastní šachové hodiny s ESP32 S2 mini.
Po malé úpravě lze použít jakýkoli jiný mikrokontrolér.

Průběh hry
Hodiny jsou nastaveny na pět minut. Po zapnutí je možné měnit čas hry pomocí tlačítek. Začínající hráč stiskne tlačítko táhne a znovu stiskne tlačítko. Následně se hráči ve hře střídají. Když má jeden z hráčů na hodinách nula minut, časovač se zastaví a vítězný hráč vyhrává.
Stisknutím obou tlačítek je možné se vrátit na začátek.

Zapojení
Kód pro ESP 32 S2 mini je zveřejněn na githubu. Zapojení jednotlivých komponent je podle přiloženého schématu.
K sestavení je potřeba
- ESP 32 S2 mini (nebo jiný mikrokontrolér)
- 2 x zobrazovací modul TM1637
- 2 x tlačítko 
- TP4056 charging module
- SPDT slide switch
- li-ion battery - 16850
