# BE Aquarium - Module de Simulation

Ce module implémente la classe `Simulation`, qui agit comme le contrôleur principal de l'écosystème. Il est responsable de l'orchestration temporelle, de la collecte de données statistiques et de l'analyse démographique des "bestioles".

## 🎯 Objectifs et Conformité au Sujet

Ce code a été conçu pour répondre aux exigences spécifiques du cahier des charges du BE C++ :

### 1. Orchestration Temporelle
[cite_start]Conformément à la section **"Description du problème initial"**, l'aquarium a la charge de coordonner la simulation au cours du temps[cite: 32].
* **Implémentation :** La méthode `step()` centralise l'évolution. Elle déclenche la mise à jour du `Milieu` (déplacements, collisions) et incrémente le temps global (`currentTime`).

### 2. Gestion des Comportements Dynamiques
[cite_start]Le sujet exige la gestion de comportements distincts (Grégaire, Peureuse, Kamikaze, Prévoyante, Personnalités Multiples) [cite: 102-108].
* **Implémentation :** À chaque pas de temps, la simulation recense la population vivante.
* **Technique :** Utilisation de `dynamic_cast` et de l'introspection via `getComportement()->getName()` pour identifier et comptabiliser les bestioles selon leur stratégie actuelle. [cite_start]Cela permet de suivre l'évolution des populations même si les bestioles changent de comportement (spécification des "Personnalités Multiples" [cite: 107]).

### 3. Analyse de la Mortalité et des Accessoires
[cite_start]L'analyse doit permettre d'observer l'évolution de la population et l'impact des caractéristiques (capteurs/accessoires) [cite: 116-118].
* **Implémentation :** Le système récupère les décès via `milieu.getAndClearRegistreDeces()`.
* [cite_start]**Statistiques Avancées :** Le code associe l'âge au décès aux accessoires portés (Carapace, Nageoires, Camouflage) [cite: 50, 80-88]. Cela permet de déterminer si certains équipements offrent un avantage de survie significatif.

### 4. Bilan Final (Analyse des résultats)
[cite_start]Le logiciel doit fournir un "état en fin de simulation" faisant office de bilan [cite: 119][cite_start], mais aussi permettre une "analyse fine" par pas de simulation[cite: 124].
* **Implémentation :** La méthode `afficherBilanFinal()` agrège l'historique complet. Elle découpe la simulation en fenêtres temporelles (ex: tous les 100 pas) pour afficher les taux de mortalité et l'espérance de vie moyenne par période.

---

## 🛠 Détails Techniques

### Dépendances Critiques
Le fichier `Simulation.cpp` nécessite les inclusions suivantes pour fonctionner (gestion du polymorphisme) :
* `#include "Simulation.h"`
* `#include "Bestiole.h"` (Nécessaire pour le `dynamic_cast`)
* `#include "Comportement.h"` (Nécessaire pour l'accès à `getName()`)

### Structure des Données
* [cite_start]**`historique`** : Stocke des snapshots (`EtatPopulation`) complets à chaque itération pour permettre un éventuel "Replay" ou une sauvegarde des états produits pour chaque pas[cite: 124].
* **`historiqueDeces`** : Vecteur optimisé stockant uniquement les métadonnées des bestioles mortes (Âge, Accessoires, Temps du décès) pour ne pas surcharger la mémoire vive avec des objets complets.
* **`statistics`** : Tableau léger stockant uniquement les compteurs de population par comportement (nb Grégaire, nb Kamikaze, etc.) pour la génération de graphiques.

### Algorithme Principal (`step`)
1.  **Mise à jour Physique** : Appel de `milieu.step()`.
2.  **Traitement des Décès** : Récupération des morts depuis le Milieu, extraction des stats (âge/accessoires), et archivage.
3.  **Recensement** : Parcours de toutes les bestioles vivantes pour mettre à jour les compteurs de comportements.
4.  **Snapshot** : Création et stockage de l'état courant.

---

## 🚀 Utilisation

Exemple d'instanciation et d'exécution dans le `main.cpp` :

```cpp
#include "Milieu.h"
#include "Simulation.h"

int main() {
    // 1. Création du milieu (Aquarium)
    Milieu monMilieu(640, 480); // Largeur, Hauteur

    // 2. Initialisation de la simulation
    Simulation sim(monMilieu);

    // 3. Boucle de simulation (ex: intégrée dans une boucle graphique)
    for (int i = 0; i < 1000; ++i) {
        sim.step();
        
        // Ici : Code de dessin (accès via sim.getDernierEtat())
    }

    // 4. Affichage des statistiques en console à la fin
    sim.afficherBilanFinal();

    return 0;
}
```