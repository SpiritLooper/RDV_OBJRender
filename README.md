# RDV_OBJRender
Projet Représentation de données visuelles, Master Informatique | Rendu d'un fichier .obj en image anaglyphe

## Prérequis
- make
- g++

## Compiler le projet
1. Aller à la racine du projet puis `make`
2. Lancer le programme avec `build/obj_render.out` 


## Paramètres

Le programme peut s'exécuter avec 2 paramètres : 

- `obj_render.out chemin/vers/fichier/obj` pour rendre l'image du fichier en question
- `obj_render.out --no-3d` pour rendre une image simple / non-anaglyphe


> Par défaut le programme prend le fichier head.obj comme rendu anaglyphe

## Exemples de rendu

### Avec Anaglyphe
![GitHub Logo](/res/head.jpg)
![GitHub Logo](/res/diablo3.jpg)

### Sans Anaglyphe
![GitHub Logo](/res/head-no3d.jpg)
![GitHub Logo](/res/mario-no3d.jpg)
![GitHub Logo](/res/diablo3-no3d.jpg)
![GitHub Logo](/res/duck-no3d.jpg)


