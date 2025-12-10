BE_bestioles_G2
===============

Simulateur d'écosystème simple en C++ (Bestioles) — projet de démonstration pédagogique.

Résumé
------
Ce projet simule des "bestioles" évoluant dans un milieu 2D. Chaque bestiole possède un comportement (grégaires, kamikaze, peureux, prévoyant, ou comportements multiples), des capteurs (yeux, oreilles) et éventuellement des accessoires (carapace, nageoires, camouflage) qui influent sur son mouvement et ses caractéristiques.

Structure du dépôt
------------------
- `includes/` : en-têtes (.h)
- `src/`      : sources (.cpp)
- `config.txt`: fichier de configuration (paramètres de la simulation)

Prérequis
---------
- Linux
- g++
- make
- Bibliothèque CImg

Clone et Compilation
-----------
Dans le répertoire où vous souhaitez clonez ce projet, copiez collez dans un terminal : 

```bash
git clone https://github.com/LucienDuhamel/BE_bestioles_G2
```

Depuis le répertoire `BE_bestioles` fraichement cloné :

```bash
make
```

Si vous souhaitez recompiler :

```bash
make clean
```

Exécution
---------
Après compilation, lancez :

```bash
./main
```

Commandes utiles
----------------
- `q` : quitter
- ` ` (espace) : pause/reprise
- `a` : ajouter une bestiole
- `r` : réinitialiser la simulation
- `k` : tuer toutes les bestioles


> [!WARNING]  
> Dans le cas où la fenêtre d'analyse ne propose pas de se fermer sur votre ordinateur, suivez les instructions suivantes :
> 1. Faites un <kbd>Ctrl</kbd> + <kbd>Esc</kbd>
> 2. Allez dans le terminal qui exécute le code
> 3. Appuyez sur <kbd>Ctrl</kbd> + <kbd>V</kbd>

Configuration
-------------
Le fichier `config.txt` contient la plupart des paramètres modifiant le comportement des bestioles et du milieu.
Il est nécessaire d'en respecter le format lors de l'ajout ou l'édition de paramètres.
Les lignes commençant par # ou // sont des commentaires et sont ignorées par le parser.
Voici les paramètres les plus utiles :

- Taille et affichage
  - `WIDTH`, `HEIGHT` : dimensions de la fenêtre
  - `DELAY` : délai entre étapes (ms)
  - `NB_BESTIOLES_INIT` : nombre initial de bestioles

- Proportions de comportements (doivent sommer à 1.0)
  - `PROP_GREGAIRE`, `PROP_KAMIKAZE`, `PROP_PEUREUX`, `PROP_PREVOYANT`, `PROP_MULTIPLES`

- Paramètres des capteurs
  - `PROBA_YEUX`, `PROBA_OREILLES` : probabilité qu'une bestiole ait respectivement yeux/oreilles
  - D'autres paramètres (angles, distances, pourcentages) se trouvent sous les sections `Capteurs` dans `config.txt`.

- Paramètres des accessoires
  - `PROBA_CARAPACE`, `PROBA_NAGEOIRES`, `PROBA_CAMOUFLAGE` : probabilités d'apparition
  - `COEFF_VITESSE_NAGEOIRE_MAX`, `COEFF_VITESSE_CARAPACE_MAX`, `COEFF_RESISTANCE_CARAPACE_MAX`, `CAMOUFLAGE_MIN`, `CAMOUFLAGE_MAX`

- Paramètres de comportements
  - `BESTIOLE_SCARED_NUMBER`, `REMAINING_SCARED_STEPS`, `SPEED_COEF` (peureux)
  - `T_PREDICT`, `DIST_MIN_COLLISION` (prevoyant)

Notes de conception importantes
------------------------------
- Certains comportements sont implémentés en tant que singletons (ex. grégaires, kamikaze, prévoyant), d'autres sont instanciés par bestiole (ex. peureux). La `BestioleFactory` construit les bestioles à partir d'une `listeComportements` et d'un vecteur de proportions — l'ordre des éléments dans `listeComportements` doit correspondre à l'ordre utilisé pour le vecteur `proportions` (voir `src/Milieu.cpp`).

- Les accessoires et capteurs sont assignés aléatoirement suivant les probabilités du fichier `config.txt`.

Développement
------------
- Pour ajouter un nouveau comportement :
  1. Créer `includes/ComportementX.h` et `src/ComportementX.cpp` dérivant de `Comportement`.
  2. Implémenter `getCouleur`, `reagit`, `clone` et (si nécessaire) `initFromConfig`.
  3. Ajouter l'instance ou le singleton à `Milieu::listeComportements` et mettre à jour `proportions` en conséquence.

- Pour ajouter un capteur/accessoire : suivre le pattern `ICapteur`/`IAccessoire` et implémenter `clone()` et `initFromConfig()`.


