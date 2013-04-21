chess
=====
###1. Compilation :
- Compile sans librairie extérieure avec la commande `make chesst`.
- Compile avec la **SDL** (`libsdl1.2-dev`, `libsdl-image1.2-dev`) avec la commande `make chess`.

###2. Exécution :
- L'exécutable peut être lancé en mode humain-humain (`./chess(t) h h`) ou ai-humain (`./chess(t) a h`)
- L'affichage se fait soit dans un terminal (`./chesst`) ou dans une fenêtre SDL (`./chess`) ( **Attention requiert** : `libsdl1.2`, `libsdl-image1.2`). Pour l'affichage graphique l'exécutable doit se trouver dans le même dossier que le dossier `pictures`.

###3. Commentaires sur le Code :
- `inputOuput/inputOuput.h` explique comment créer un nouveau rendu du jeu d'échec. C'est en travaillant sur ce template et sur `main.cpp` qu'il devrait être possible de jouer avec une autre AI qui est compilée séparément. Le top du top serait de rendre le renderer [Universal Chess Interface](http://wbec-ridderkerk.nl/html/UCIProtocol.html) compatible. Comme ça on pourrait jouer avec *n'importe* qu'elle AI (comme GNU Chess).
- Un autre grand point d'améliorations est le fonctionnement de `board.cpp`. Ses fonctions `colourMoves()` et `kingInDange()` devrait être fortement améliorés pour rendre n'importe qu'elle AI les utilisant plus performant.
- Récemment `Boardstate` a subit de lourde régression, faut trouver pourquoi.
