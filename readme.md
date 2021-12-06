**POUR CONFIGURER LE PROJET**

1. Télécharger le projet 
2. Se mettre à la racine
3. Créer un dossier build `mkdir build`
4. Lancer en terminal `./configure.sh`, cela lancera le cmake (et remplira le dossier build)
5. Lancer en terminal `./build.sh`, cela lancera le makefile
6. Lancer en terminal `./run.sh`, lancera le programme
7. Enjoy !

P.S : Si les fichiers .sh, ne se lancent pas c'est probablement qu'ils ne sont pas executables. Lancer `chmod u+x configure.sh build.sh run.sh`
et revenir à l'étape 3.

P.P.S : Le fichier `compile.sh` lance `configure.sh` et `build.sh` en même temps, pour que ce soit plus rapide ! 
