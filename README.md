Donnie the Doggie este un joc platformer care urmareste povestea lui Donnie, un caine pierdut
in cautarea stapanului sau. In aceasta aventura, Donnie trece de obstacole care sfideaza legile
fizicii si locuri total neadecvate pentru un caine.

- Codul este separat in fisiere .h si .cpp
  toate clasele sunt definite in headerele lor proprii, eventual contin si functii simple
  functiile mai complexe sunt continute in Functii.cpp

- Clasele Meniu, VictoryScreen, LevelOne/Two mostenesc clasa Nivele.

- Clasa Nivele contine functii virtuale care apoi sunt folosite de fiecare mostenitor.
  La trecerea dintre nivele se creaza un unique pointer prin LevelFactory.h

- Clasa AssetLoadException mosteneste GameException
  care la randul eimosteneste std::exception.
  Aceste exceptii sunt "prinse" in main.

- Clasa Debugger<T> este template.
  Aceasta afiseaza in consola detaliile importante despre obiectul care ii apeleaza metodele
  In main este apelata functia friend debugPrint(...) cu parametrul find obiect al clasei Dog
  si apoi un vector de obiecte al clasei Wall.

Design Patterns:
- Factory Pattern
  implementat în LevelFactory, care creează instanțe de VictoryScreen, Menu LevelOne, LevelTwo,
  pe baza unui parametru (levelNumber).

- Template Pattern
  Clasa Nivele contine functii virtuale care sunt modificate de fiecare nivel in parte.
  In final va fi apelata functia runLevel(...) care este definita in Nivele.h

- Observer Pattern
  De fiecare data cand viata lui Donnie scade, HealthObserver este notificat.
  HealthDisplay vede acea notificare si afiseaza pe ecran numarul corespunzator de vieti.


Ce se intampla in tot acest cod?
main.cpp: fisierul principal in care se creaza fereastra, meniul, protagonistul, timer-ul,
efectiv tot ce este pe ecran este definiti si folosit aici.

Nivele.h: clasa parinte pentru clasele Menu, LevelOne/Two, VictoryScreen.
sunt definite variabilele si functiile necesare pt fiecare nivel, urmand ca ele sa fie
modificate de fiecare mostenitor dupa nevoie.

LevelFactory.h: implementeaza design pattern-ul de Factory. Face practic trecerea de la un
nivel la altul, sau la meniu sau la victoryScreen.

Wall.h: Un simplu sprite. Folosit pentru a crea obstacole in nivele.

PainGiver.h: Mosteneste clasa Wall, tot obstacole dar acestea scad viata lui Donnie.

Entity.h: Controleaza, monitorizeaza pozitia unui sprite.

Dog.h: Mosteneste clasa Entity. Aici este de fapt protagonistul nostru. Clasa este plina de variabile
pentru viteza, orientare, texturi pentru animatie si viata.
Aici sunt totodata definite si functiile pentru detectarea coliziunilor, miscare, cadere si damage.

HealthDisplay.h si HealthObserver.h: implementeaza design pattern-ul de observer. Se monitorizeaza viata lui Donnie
si interfata este actualizata conform acesteia.

GameException.h: Introduce clasele GameException si AssetLoadException care semnaleaza erorile de incarcare a
imaginilor din folder.

Functii.cpp: Aici sunt incluse toate toate fisierele si librariile de care avem nevoie. Aici sunt functiile pentru input,
detectarea coliziunilor, cadere, damage, miscarea camerei si animatia cainelui.

Debugger.h: Clasa template care afiseaza in consola informatiile importante despre obiectul care ii apeleaza functiile.




###Bibliografie:

Toate intrebarile pe care le-am avut au fost deja puse pe https://www.sfml-dev.org/forums

Tot jocul se bazeaza pe libraria https://www.sfml-dev.org/

Sprite-urile pt Donnie sunt luate de aici: https://spritedatabase.net/file/7205

Pentru timer am folosit font-ul pricedown.

Trenurile sunt luate de aici: https://kooky.itch.io/pixel-train

Acest tutorial m-a ajutat la instalare: https://youtu.be/NOy-7lKrpQE?si=3IKvnPFKggQ7gxm9

Link GitHub:
https://github.com/DinVin24/Donnie

