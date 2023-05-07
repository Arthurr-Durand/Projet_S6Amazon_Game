# Project Amazons 

>## Sommaire
>
>- [Description du projet](#description-du-projet)
>- [Prérequis](#prérequis)
>- [Installation](#installation)
>- [Utilisation](#utilisation)
>    - [Compilation](#compilation)
>    - [Execution](#execution)
>    - [Tests](#tests)
>    - [Rapport](#rapport)
>    - [Nettoyage](#nettoyage)
>- [Contact](#contact)
>- [Remerciements](#tests)

--- 

## Description du projet
Ce projet a pour but de nous initier au développement client/serveur en créant une copie du [jeu des amazones](https://en.wikipedia.org/wiki/Game_of_the_Amazons) respectant ce modèle. L'objectif étant d'obtenir un serveur ainsi que des joueurs afin de les confronter à ceux des autres groupe de projets tout en respectant les règles du jeu.
Il répond au [sujet Amazons](https://www.labri.fr/perso/renault/working/teaching/projets/2022-23-S6-C-Amazons.php) réalisé dans le cadre d'un projet du semestre 6 proposés aux étudiants de l'ENSEIRB-MATMECA.
Le dépot est disponible sur la [forge de l'école](
https://thor.enseirb-matmeca.fr/ruby/projects/projetss6-amaz).

## Prérequis 

Ce projet necessite l'installation de  `git`, `make`, `gcc` ainsi que le paquet `libgsl23` pour acceder à la librairie GSL.
```sh
sudo apt-get install git
sudo apt-get install make
sudo apt-get install gcc
sudo apt-get install libgsl23
```
## Installation

Avant de commencer, il est neccessaire de cloner le dépot git disponible sur la forge de l'ENSEIRB-MATMECA.
```sh
git clone https://<user>@thor.enseirb-matmeca.fr/git/projetss6-amaz-19042
cd projetss6-amaz-19042
```

## Utilisation 


### Compilation

Par defaut, le chemin (GSL_PATH) est celui compatible avec les machines de l'école. Cependant il est possible compiler sur ca machine en faisant :
```sh
make run GSL_PATH=<your own path>
```
une fois la compilation effectuer un executable est créé dans le dossier install sous le nom de serveur.

### Execution

Plusieurs options sont disponibles lors de l'éxecution, si les arguments des options sont incorrectes, le programme prendra en compte les valeurs par défaut. 
```sh
-m - <entier>: Fixe la taille des coté du plateau.(par defaut : 5)

-t - <t/8>: choisit le type de plateau. (par defaut le plateau classique est choisit)
```
Elle sont à spécifier après le nom de l'executable.
```sh
./install/server [Options]
```

### Tests

Des tests sont disponible afin de vérifier le bon fonctionnement de chaque partie du projet.
Pour les executer il suffit de faire :
```sh
make alltests

./install/alltests
```

### Rapport 

Un rapport LaTeX est disponnible, il peut être compilé dans le fichier `doc/` en utilisant `pdflatex` :
```sh
cd doc/
pdflatex report.tex
```

### Nettoyage 
Les fichiers créés lors de la compilation peuvent être supprimé en utilisant : 
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

