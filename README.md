# Project Amazons 

>## Sommaire
>
>- [Description du projet](#description-du-projet)
>- [Prérequis](#prérequis)
>- [Installation](#installation)
>- [Utilisation](#utilisation)
>    - [Compilation](#compilation)
>    - [Exécution](#execution)
>    - [Tests](#tests)
>    - [Rapport](#rapport)
>    - [Nettoyage](#nettoyage)
>- [Contact](#contact)
>- [Remerciements](#tests)

--- 

## Description du projet
Ce projet a pour but de nous initier au développement client/serveur en créant une copie du [jeu des amazones](https://en.wikipedia.org/wiki/Game_of_the_Amazons) respectant ce modèle. L'objectif étant d'obtenir un serveur ainsi que des joueurs afin de les confronter à ceux des autres groupe de projet, tout en respectant les règles du jeu.
Il répond au [sujet Amazons](https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S6-C-Amazons.php) réalisé dans le cadre d'un projet du semestre 6 proposés aux étudiants de l'ENSEIRB-MATMECA.
Le dépot est disponible sur la [forge de l'école](
https://thor.enseirb-matmeca.fr/ruby/projects/projetss6-amaz).

## Prérequis 

Ce projet nécessite l'installation de  `git`, `make`, `gcc` ainsi que le paquet `libgsl23` pour accéder à la librairie GSL.
```sh
sudo apt-get install git
sudo apt-get install make
sudo apt-get install gcc
sudo apt-get install libgsl23
```
## Installation

Avant de commencer, il est nécessaire de cloner le dépot git disponible sur la forge de l'ENSEIRB-MATMECA.
```sh
git clone https://<user>@thor.enseirb-matmeca.fr/git/projetss6-amaz-19042
cd projetss6-amaz-19042
```

## Utilisation 


### Compilation

Par défaut, le chemin vers la bibliothèque GSL est celui compatible avec les machines de l'école mais le `Makefile` est paramétré pour trouver lui même le chemin.
Cependant, si le chemin n'est pas trouvé, il est possible d'indiquer le répertoire manuellement en ajoutant le paramètre suivant à chaque utilisation de `make` :
```sh
make <commande> GSL_PATH=<your own path>
```

Le serveur et les clients peuvent être compilés avec la ligne suivante :
```sh
make all
```

### Execution

Plusieurs options sont disponibles lors de l'éxecution, si les arguments des options sont incorrectes, le programme prendra en compte les valeurs par défaut. 
```sh
-m - <entier>: Fixe la taille des coté du plateau.(par defaut : 5)

-t - <t/8>: choisit le type de plateau. (par defaut le plateau classique est choisit)
```
Elle sont à spécifier après le nom de l'exécutable, disponible dans le fichier `install`.
```sh
./install/server [Options]
```

### Tests

Des tests sont disponibles afin de vérifier le bon fonctionnement de chaque partie du projet.

Les tests peuvent être compilés avec la ligne suivante :
```sh
make test
```

Ils peuvent être exécutés avec la commande :
```sh
./install/alltests
```

### Rapport 

Un rapport LaTeX est disponnible, il peut être compilé dans le fichier `doc/` en utilisant `pdflatex` :
```sh
cd doc/
pdflatex report.tex
```

### Nettoyage 
Les fichiers créés lors de la compilation peuvent être supprimés en utilisant : 
```sh
make clean
```

## Contact

- Cattarin Antton : acattarin@enseirb-matmeca.fr
- [Durand Arthur](https://www.linkedin.com/in/arthur-durand-50384a24b/) : adurand015@enseirb-matmeca.fr
- [Hamouche Luxel](https://www.linkedin.com/in/luxel-hamouche/) : lhamouche@enseirb-matmeca.fr
- Robert Joachim : jrobert003@enseirb-matmeca.fr

## Remerciements

Encadrant lors des séances de projet : M. Lion

Charger de projet : M. Renault

