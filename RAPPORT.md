# Rapport de projet

**Alexandre Escudero**, **Théo Gautier**, **Ludwig Chieng**

*Mini jeu vidéo de stratégie militaire 2D en tour par tour, type Advance Wars, en C++ sous SDL2 et OpenGL.*

## Equipe

Pour la méthode de travail, nous avons travaillé à l’aide de l’extension Live Share de l’application Visual Studio Code. En effet, nous ne sommes pas à l'aise avec Git pour travailler en équipe et nous avions peur de perdre trop de temps pour organiser un workflow Git correct. Grâce à Live Share, nous avons pu travailler à plusieurs, en temps réel, sur le même code, tout en étant souvent en communication vocale. Cela nous a donc permis de travailler, la plupart du temps sur un seul PC qui hébergeait le code, ce qui a été particulièrement pratique, car nous avons rencontré un certain nombre de difficultés au moment de compiler le code sur nos différents ordinateurs personnels. Cela nous a permis également de travailler ensemble efficacement et de suivre en temps réel les modifications de chacun.

Pour être honnêtes, nous ne pouvons pas dire que sur l’écriture du code, les participations de chacun aient été tout à fait égales. C’est d’ailleurs surtout Ludwig qui a piloté le projet. Pour autant, nous avons tous les trois travaillé sur les parties “modèle”, “vue” et “contrôleur”, et avons suivi le travail de chacun sur toute la durée du projet. Pour faire simple, Alexandre a réalisé la majorité de la partie modèle, à savoir, le système d'attaque, les unités et les joueurs. Théo a surtout géré la vue avec les textures et les textes. Ludwig a fait le pathfinding A* et le contrôleur. La plupart du temps, nous avons fait des sessions revue de code pour faire le point sur ce qui a été codé.

## Préliminaires

Le choix de l'orienté object s'impose avec un tel projet. On a tenté du Test Driven Development avec GTest mais on a été incapable de mettre en place un workflow de tests unitaires efficaces donc on ne l'a globalement pas utilisé.

## Architecture

Tentative de design pattern MVC classique mais qui foire un peu. Il y a des zones mal encapsulées. Et les recoder ne serait pas rentable au vu du temps imparti.

*(voir le diagramme de classe dans `misc/`)*

Le `main` instancie un objet de classe `Game`, qui gère les classes MVC. Le modèle gère la map (et donc les tiles), les unités, les joueurs et l'IA.

### A*

Le pathfinding est exécuté par une classe `Astar` isolée qui ne dépend pas d'aucune classe du modèle.

Sa méthode `exec()` prend en paramètre un tableau 2D de `Astar::Node` ainsi que deux paramètres `Astar::Node` définissant les points de départ et d'arrivée du chemin à tracer.

Le modèle utilise le pathfinding à travers la méthode `Map::findPath()`, qui:

- transforme les données de la map en tableau 2D de `Astar::Node`,
- définit les `Astar::Node` qui sont des "murs" ou non,
- définit, pour chaque `Astar::Node`, ses `Astar::Node` voisins,
- appelle la méthode `Astar::exec()`, et traduit ce qu'elle retourne en `Tile::Path` (liste chainée de `Tile*`)
- renvoie le `Tile::Path`

### Génération procédurale de map

Probablement le point dont on est le plus statisfait. On utilise du Perlin noise pour générer l'altitude de chaque Tile. On définit chaque intervalle d'altitude comme étant un type de biome (Ocean, Coast, Shore, Plain, Forest, Mountain, Peak) et le tour est joué.

**En pratique, c'est un poil plus technique:**

On utilise 3 perlin noise avec des niveau de zooms différents pour avec une map à la fois jouable (terrain assez vaste) et intéressante (terrain assez varié).


``` cpp
// Altitude globale
alt = perlin1.GetNoise(x * ZOOM, y * ZOOM);

// Altitude variations fines
alt += perlin2.GetNoise(x * ZOOM * 1.3, y * ZOOM * 1.3) * 9/10 + 0.1;

// Crop si ça dépasse
alt = (alt > 1) ? .99 : alt;
alt = (alt < -1) ? -.99 : alt;

// Normalisation entre 0 et 1
alt /= 2;
alt += 0.5;

// Ecrase les grandes valeurs
float am = 1.8; // coef d'amortissement
alt = pow(pow(alt * 2, am) / 2, 1.0/am) + 0.0;

// Rogne les bords
alt = alt - 0.6/(x+3) - 0.6/(y+3);
alt = alt + 0.6/(x-3-SIZE_X) + 0.6/(y-3-SIZE_Y);

// Elève l'altitude de la plaine
alt = (alt < LIMIT_SHORE || alt > LIMIT_PLAIN) ? alt : alt + (.1 + perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) * .1);

// Rajoute de la forêt (parce que c'est beau la forêt on est fier de nos assets forêts aha)
alt = (alt < LIMIT_PLAIN || alt > LIMIT_FOREST) ? alt : (perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) > 0.3) ? LIMIT_PLAIN + 0.1 * perlin3.GetNoise(x * ZOOM * 1.8, y * ZOOM * 1.8) : alt;
alt = (alt <= LIMIT_FOREST) ? alt : alt - (.05 + perlin3.GetNoise(x * ZOOM * 2, y * ZOOM * 2) * .1);
```

`Map::isValidAltitudeMap()` vérifie que la proportion de chaque biome rend la partie jouable.

`Map::generateSpawns1vs1()` prend deux Tiles au hasard qui sont des terrains praticables (Shore, Plain, Forest) et dont il existe au moins un chemin entre les deux (que les joueurs ne soient pas sur deux îles différentes). Enfin, la méthode dispose les unités dans un rayon de Tiles donné autour du spawn du joueur.

## Améliorations pour la suite

### Performances

Fuite de mémoire quand on regénère la map. Cela vient probablement des destructeurs d'objets qu'on pas réalisé correctement (voire pas du tout parce que aled on sait pas comment faire). On atteint rarement les 60 fps, de l'optimisation à faire côté SDL_Texture sûrement.

### Game design

Ajouter des fonctionnalités pour choisir entre jeu contre IA ou contre un joueur. Chose qu'on a pas faite car on a pas trouvé d'architecture propre pour gérer des interfaces graphiques, les événements souris/claviers associés, etc... Idem pour les interfaces pour acheter des unités. Les interfaces graphiques sont des éléments lourds et délicats à gérer en programmation bas niveau donc on a préféré se concentrer sur le gameplay plus que sur les interfaces.

### Code

Le code commence à devenir lourd et le MVC qu'on a tenté de faire risque de ne pas être extensible. On a pris connaissance du livre *SDL Game Development* qui propose un autre design pattern qui semble éviter de tomber dans un code lourd. Ce design répartit le MVC au sein de chaque classe plutôt que d'avoir un modèle global, une vue globale et un controleur global. Si le projet serait à refaire, on opterait pour cette architecture.