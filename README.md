# FdF
> grade: 110/100

A simple wireframe graph generator with isometric projection.<br/>
The graph is generated according to a .fdf map file containing a matrix of integers.
An interger's position in the file represents its coordinates (x,y) and its value represents the depth (z).<br/>
_Examples at the bottom._

## Dependencies:
- 42's [minilibx](https://github.com/42Paris/minilibx-linux), install it in the inc/ directory.

## Usage:
- run `make` to create the executable.
- run the program with `./fdf <valid map file>`.
- in the program:
    - use TAB to zoom in.
    - use BACKSPACE to zoom out.
    - use the arrows to move the render around.
    - use ESC to exit the window.

<br/>

# FdF - Français
> note: 110/100

Un générateur de graphe en fil-de-fer avec projection isométrique.<br/>
Le graphe est généré d'après un fichier 'carte' .fdf contenant une matrice d'entiers.
La position d'un entier dans le fichier représente ses coordonnées (x,y) et sa valeur représente la profondeur (z). 

## Dépendances:
- La [minilibx](https://github.com/42Paris/minilibx-linux) de 42, à installer dans le répertoire inc/.

## Utilisation:
- lancer `make` pour créer l'exécutable.
- lancer le programme avec `./fdf <fichier carte valide>`.
- dans le programme:
    -utiliser TAB pour agrandir le rendu.
    -utiliser BACKSPACE pour réduire le rendu.
    -utiliser les flèches pour déplacer le rendu.
    -utiliser ESC pour quitter la fenêtre.

<p align='center'>
<img src='/others/fdf-42.png' width='400px'>
<img src='/others/fdf-mars.png' height='400px'>
<p/>
