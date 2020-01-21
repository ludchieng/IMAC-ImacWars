#  **IMAC-ImacWars** :crossed_swords::boom:
[![Ça c'est IMAC](https://img.shields.io/badge/Ça-293.svg)]()[![Ça c'est IMAC](https://img.shields.io/badge/c'est-f31.svg)]()[![Ça c'est IMAC](https://img.shields.io/badge/IMAC-25c.svg)]()

Modest turn-based military strategy game based on Advance Wars.

A short C++ project made for programming courses.

## **Instructions** :wrench::gear:

Run `make` in the "debug" folder.
Launch the game with:

```sh
./IMAC-ImacWars
```

**Note:** You might want to change the armies’ configurations. To do this, edit Model.cpp, uncomment the "generateArmies(...)" method of your choice (line 40)

```cpp
Model::Model()
{
  ...

  //generateArmies(ArmySize::CREW);
  generateArmies(ArmySize::FACE_TO_FACE);
  //generateArmies(ArmySize::SECTION);
  //generateArmies(ArmySize::BATTERY);
  //generateArmies(ArmySize::COMPANY);
}
```

## **Preview** :space_invader::joystick:

With Ubuntu's terminal:

![Gif Demo 1](demo-2.gif)

## **Gameplay** :video_game::game_die:

### **Rules**

Two players fight on a 9x16 tiles map. Each player has a set of units to operate in order to annihilate his enemy.

As this is a turn-based game, each player may choose a unit (and only one) to actuate. The unit can move or/and attack as long as it has enough movement points (MP).

### **Combat System**

There are three types of unit:

- **Infantry:** `4MP` | `1RATK`. Fast and agile but low damage and low range of fire (RATK).
- **Artillery:** `2MP` | `3RATK`. Slow but high range of fire
- **Tank:** `1MP` | `2RATK`. Very slow but high damage.

Attack costs differ depending on the type of unit:
- **Infantry:** ` AtkCost: 2MP`
- **Artillery:** ` AtkCost: 2MP`
- **Tank:** ` AtkCost: 1MP`

The power of a unit is defined as the addition of its attack points (ATK) and its defense points (DEF).

When a unit (the assailant) fight with another (the target), damage is calculated as follows:

```cpp
//Unit1 assaults Unit2:
dmgOn2 = atk1 * (power1 / power2) + variation1 + bonus;
dmgOn1 = atk2 * (power2 / power1) + variation2;
```

Variations parameter go randomly from -10 to +10. The bonus represents the surprise effect the assailant has upon the target.

Last but not least, if the assailant has a higher range of fire than the target. The target might not have the possibility to strike back. In that case, `dmgOnAssailant` equals 0.

#### 

---

## **Assessment specifications** :mortar_board::school::books:

> Le programme affiche une carte dans la console sous forme d’une grille indexée ainsi que les unités militaires présentes sur la carte. :heavy_check_mark:

> Les joueurs possèdent chacun leurs unités militaires, ils vont, chacun leurs tours, sélectionner une de leurs unités, la déplacer et la faire agir (notamment attaquer une autre unité). :heavy_check_mark:

> La partie se termine lorsqu’un des deux joueurs a détruit toutes les unités de son adversaire, le programme le proclame gagnant de la partie. :heavy_check_mark:

>Chaque joueur à un nombre défini en amont d’unités de combat. Chaque unité est définie par les caractéristiques suivantes :
> - l’id du joueur auquel elle appartient :heavy_check_mark:
> - ses points de vie (HP) :heavy_check_mark:
> - sa force (ATK) :heavy_check_mark:
> - ses coordonnées :heavy_check_mark:
> - sa dextérité (MP) :heavy_check_mark:

> Au début du tour, le joueur sélectionne une seule unité en indiquant ses coordonnées. Si la sélection est valide, alors le joueur peut la déplacer et/ou la faire attaquer une autre unité. :heavy_check_mark:

> S’il la déplace, le joueur rentre les coordonnées de destination et si elles sont valides (si la somme du déplacement en x et y est inférieure à la dextérité de l’unité) alors l’unité change de case. :heavy_check_mark:

> S’il attaque, le joueur rentre les coordonnées de l’unité cible. Si l’unité est valide (il s’agit d’une unité ennemie) alors un affrontement se produit. :heavy_check_mark:

> Un affrontement affecte les points de vie de chaque opposant dans cette ordre :
> - l’unité cible perd attaquant.pv × attanquant.puissance points de vie
> - l’unité attaquante perd cible.pv × cible.puissance points de vie :heavy_exclamation_mark:

Le calcul des dommages est légèrement différent (voir *Combat system*).

> Optionnel : Vous pouvez rajouter plusieurs autres caractéristiques pour être plus fidèle au jeu, notamment le type d’unité (infanteries, bazooka, tank, ...) :heavy_check_mark: et sa catégorie (à pied, véhicule, air...) :x:, puis revoir le calcul des dommages en fonction de l’efficacité d’une unité contre une autre (infanteries faibles contre tank mais forts contre bazooka) :heavy_exclamation_mark:

> **Joueur.** Vous pouvez définir des caractéristiques à un Joueur (nom, fonds de guerre , liste d’unité, effet spécial ?, ...), mais vous allez constater que pour faire fonctionner le jeu, vous n’avez finalement besoin que d’une seule donnée qui vous permettra d’identifier un joueur, notamment pour savoir à qui c’est le tour, à qui appartient une unité et surtout qui a gagné (et donc qui a perdu). Vous pouvez utiliser un entier, un caractère ou une chaine de caractère qui représente un nom/pseudonyme. :x:

Les joueurs sont désignés par "Joueur 1" et "Joueur 2".

> **UX.** Ce projet ne nécessite pas d’interface graphique (Enfin cela dépend de vous, c’est quand même plus chouette d’avoir un jeu graphique). En revanche, il faut un minimum de User-Experience, un minimum d’interaction Homme-Machine. :heavy_exclamation_mark:

Le jeu a été développé pour avoir l'UX la plus agréable possible, néanmoins, jouer une partie s'avère long car il faut entrer toutes les coordonnées une part une.

Travail sur l'UX:
- Chaque joueur et ses unités sont associés a une couleur,
- Lorsque le joueur débute son tour, la liste de ses unité apparaissent en blanc tandis que celle de l'ennemi s'efface en gris. Également, le bandeau prend sa couleur et un curseur apparaît à côté de son nom pour signaler qu'il a la main,
- Les coordonnées se donnent en lettre/nombre plutôt que nombre/nombre,
- Les saisies ne sont pas sensible à la casse
- Les no. de lignes sur la map sont affichés des deux côtés
- Lorsqu'une unité est sélectionnée, ses coordonnées sont surlignées dans le panel.

> **Menu.** Votre programme peut et devrait afficher un menu qui permet à l’utilisateur d’avoir une brève présentation du jeu et de sa configuration. Notamment il peut rentrer le nom de chaque joueur et définir combien d’unités ils ont. :x:

> **Tour de jeu.** Votre programme doit permettre à l’utilisateur de jouer son tour en choisissant son unité et le faisant agir. Avant cela, le joueur doit voir l’état actuel de ses unités (et des unités ennemies si vous le souhaitez) ainsi que leur position sur la carte. :heavy_check_mark:

> Après avoir consulté l’état du jeu, le joueur doit pouvoir sélectionner une unité, soit avec les coordonnées comme indiqué plus haut soit avec un id. Si les coordonnées (ou l’id) sont valides, le joueur doit choisir une action :heavy_check_mark: (ou resélectionner une unité si vous le pouvez :x:) parmi celles qui lui sont proposées.

Le joueur peut faire autant d'action qu'il souhaite avec une unité donnée tant que celle-ci possède encore des points de mouvement (MP). Mais une fois sélectionnée, il ne peut plus changer d'unité.

>  Idéalement une unité peut bouger une fois ET agir une fois mais vous pouvez simplifier et ne permettre qu’une action par tour. :heavy_exclamation_mark: Vous pouvez afficher le résultat d’une action (notamment d’un affrontement entre deux unités). :x:

Le résultat d'une action n'a pas été totalement implémentée. La partie *Model* et *Controller* est faite (voir `struct Model::FightReport`) mais la *View* n'affiche pas ces infos.

> Lorsque le programme conclut que le jeu est terminé, le gagnant doit être affiché et vous pouvez aussi afficher un score et l’état final de la carte. :heavy_check_mark: Vous pouvez aussi proposer de relancer le jeu ou de quitter. :x: